#include "MysqlQueryAdapter.h"


#include <time.h>
//#include "core/mcl/cppconn/sqlstring.h"

#include <algorithm>
#include "core/mcl/driver/mysql_public_iface.h"
#include "core/mcl/cppconn/exception.h"
#include "core/mcl/cppconn/driver.h"
#include "core/mcl/cppconn/connection.h"

#include "core/threads/src/ThreadGuard.h"
#include "core/DataAccess/src/MysqlQueryAdapter.h"
#include "core/DataAccess/src/DataAccessException.h"

#include "core/CppConfigLib/src/RunParams.h"
#include "core/DataAccess/src/DataAccessException.h"
#include "core/utilities/src/WorkTime.h"


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;



NS_BEGIN(TA_Base_Core)

MysqlQueryAdapter::MysqlQueryAdapter( sql::ResultSet* pQuery ) : 
m_pQuery( pQuery )
{
	m_bHaveDoMoveFirst = 0;
	if (NULL == m_pQuery)
	{
		LOG_ERROR<<"Can't initialize with NULL pointer of mysql::ResultSet";
	}
	m_pWorkTimeQueryAction = new CWorkTimeNoLock();
    _UpdateLatestActionTime();
}


MysqlQueryAdapter::~MysqlQueryAdapter()
{
    cleanQuery();
	delete m_pWorkTimeQueryAction;
	m_pWorkTimeQueryAction = NULL;
}

bool MysqlQueryAdapter::hasMore()
{
	_UpdateLatestActionTime();

    ThreadGuard guardQuery( m_queryLock );

    if ( NULL == m_pQuery )
    {
		LOG_ERROR<<"Query is closed by timeout";

		DataAccessException db(0, "Query is closed by timeout");

		throw db;
    }

    return (!m_pQuery->isAfterLast());
}

void MysqlQueryAdapter::fetchData( int numColumns, DbDataRowBuffers& data, long lMaxRows )
{

	if (numColumns > FETCH_MAX_COLS)
	{
		LOG_ERROR<<"Number of columns is out of range"
			<<" "<<"numColumns="<<numColumns
			<<" "<<"FETCH_MAX_COLS="<<FETCH_MAX_COLS;
		return;
	}

	if (lMaxRows < 0 || lMaxRows > FETCH_MAX_ROWS)
	{
		LOG_ERROR<<"Number of rows is out of range"
			<<" "<<"lMaxRows="<<lMaxRows
			<<" "<<"FETCH_MAX_ROWS="<<FETCH_MAX_ROWS;
		return;
	}


	_UpdateLatestActionTime();

    ThreadGuard guardQuery( m_queryLock );

    data.clear();

    if ( NULL == m_pQuery )
    {
		LOG_ERROR<<"Query is closed by timeout";
		DataAccessException db(0, "Query is closed by timeout");
		throw db;
    }

    try
    {
        if ( m_pQuery->rowsCount() <= 0)
        {
			LOG_DEBUG<<"no rows returns from SQL";
            return;
        }

		if (0 == m_bHaveDoMoveFirst)
		{
			m_pQuery->first();
			m_bHaveDoMoveFirst++;
		}

        if ( m_pQuery->getRow() + lMaxRows <= m_pQuery->rowsCount() )
        {
			LOG_DEBUG<<"{MCL}: current record index="<<m_pQuery->getRow()
				<<"and get batch record count="<<m_pQuery->rowsCount()<<" after this round.";

            _FillDataBuffer( numColumns, data, lMaxRows );
        }
        else
        {
			LOG_DEBUG<<"{MCL}: current record index="<<m_pQuery->getRow()
				<<"and get batch record count="<<m_pQuery->rowsCount()<<" after this round.";

            _FillDataBuffer( numColumns, data, m_pQuery->rowsCount() - m_pQuery->getRow() + 1 ); //1-based numbering mechnism. be cafeful
        }
    }
    catch( sql::SQLException & e )
    {
		DataAccessException db(e.getErrorCode(), e.getSQLStateCStr());
		db.logInfo(LogFLInfo);
		throw db;
    }
	catch(DataAccessException& db)
	{
		db.logInfo(LogFLInfo);
		throw db;
    }
    catch( ... )
    {
		DataAccessException db(0, "Unknown reason");
		db.logInfo(LogFLInfo);
		throw db;
    }
}

void MysqlQueryAdapter::_FillDataBuffer( int numColumns, DbDataRowBuffers& data, long lMaxRows )
{
    ThreadGuard guardQuery( m_queryLock );

    data.clear();

    if ( NULL == m_pQuery )
    {
		LOG_ERROR<<"Query is closed by timeout";
		DataAccessException db(0, "Query is closed by timeout");
		throw db;
    }

	sql::ResultSetMetaData* pRsMetaData = m_pQuery->getMetaData() ; // use of auto_prt, need not delete

	if ( NULL == pRsMetaData )
	{
		LOG_ERROR<<"get result set MetaData pointer failed";
		DataAccessException db(0, "get result set MetaData pointer failed");
		throw db;
	}

    int nFieldNumber = pRsMetaData->getColumnCount();

	if ( numColumns > nFieldNumber )
	{
		LOG_ERROR<<"column number is bigger than the SQL returns"
			<<" "<<"numColumns="<<numColumns
			<<" "<<"nFieldNumber="<<nFieldNumber;
		DataAccessException db(0, "column number is bigger than the SQL returns");
		db.logInfo(LogFLInfo);
		throw db;
	}


    try
    {
        long lOffset = 0;
        while( !m_pQuery->isAfterLast() && ( lOffset < lMaxRows ))
        {
            DbDataRow dataRow;
            for ( int nColLoop = 0; nColLoop < numColumns; ++nColLoop )
            {
				std::string strFieldName = pRsMetaData->getColumnName(nColLoop + 1);  // 1-based 
                std::string strValue = m_pQuery->getString(nColLoop + 1);

				LOG_DEBUG<<"SQL field name:"<<strFieldName<<" "<<"value:"<<strValue;
 
                dataRow.push_back(strValue);
            }
            data.push_back(dataRow);
            m_pQuery->next();
            ++lOffset;
        }
    }
    catch( sql::SQLException & e )
    {
		DataAccessException db(e.getErrorCode(), e.getSQLStateCStr());
		db.logInfo(LogFLInfo);
		throw db;
    }
    catch( ... )
    {
		DataAccessException db(0, "Unknown exception");
		db.logInfo(LogFLInfo);
		throw db;
    }
}




int MysqlQueryAdapter::getLstColumnName(MapColumNameIndexT& mapColumNameIndex)
{
	ThreadGuard guardQuery( m_queryLock );
	int nFieldNumber = 0;
	int lOffset = 0;
	std::string strFieldName;

	mapColumNameIndex.clear();

	if ( NULL == m_pQuery )
	{
		LOG_ERROR<<"Query is closed by timeout";
		DataAccessException db(0, "Query is closed by timeout");
		throw db;
	}

	sql::ResultSetMetaData* pRsMetaData = m_pQuery->getMetaData() ; // use of auto_prt, need not delete

	if ( NULL == pRsMetaData )
	{
		LOG_ERROR<<"get result set MetaData pointer failed";
		DataAccessException db(0, "get result set MetaData pointer failed");
		throw db;
	}

	nFieldNumber = pRsMetaData->getColumnCount();

	try
	{
		if ( !m_pQuery->isAfterLast())
		{
			for ( int nColLoop = 0; nColLoop < nFieldNumber; ++nColLoop )
			{
				strFieldName = pRsMetaData->getColumnName(nColLoop + 1);  // 1-based 
				LOG_DEBUG<<"getColumnName:"<<strFieldName;

				mapColumNameIndex.insert(MapColumNameIndexValueT(strFieldName, nColLoop));
			}
			++lOffset;
		}
	}
	catch( sql::SQLException & e )
	{
		DataAccessException db(e.getErrorCode(), e.getSQLStateCStr());
		db.logInfo(LogFLInfo);
		throw db;
	}
	catch( ... )
	{
		DataAccessException db(0, "Unknown exception");
		db.logInfo(LogFLInfo);
		throw db;
	}

	return nFieldNumber;
}

bool MysqlQueryAdapter::cleanQuery()
{
    ThreadGuard guardQuery( m_queryLock );

    if ( NULL == m_pQuery )
    {
        return false;
    }

    try
    {
        if ( !m_pQuery->isClosed() )
        {
            m_pQuery->close();
        }
    }
    catch (...)
    {
		LOG_ERROR<<"Mysql_ERROR: unknown";
        // Continue to delete query, it must be deleted.
    }

    try
    {
		if (NULL != m_pQuery)
		{
			delete m_pQuery;
            m_pQuery = NULL;
		}        
    }
    catch (...)
    {
		LOG_ERROR<<"Mysql_ERROR: unknown";
        return false;
    }

    return true;
}

bool MysqlQueryAdapter::isActive( unsigned long ulMaxTimeoutInSecs )
{
	ThreadGuard guardQuery( m_queryLock );
	BigInt64 tmNoneActiveTime = 0;
	bool bIsActive = true;

	if ( NULL == m_pQuery )
	{
		bIsActive = false;
		return bIsActive;
	}

	tmNoneActiveTime = m_pWorkTimeQueryAction->getNotWorkTimeSeconds();
	//time_t tmNoneActiveTime = time( NULL ) - m_tmLatestActionTime;

	if ( tmNoneActiveTime > ulMaxTimeoutInSecs )
	{
		bIsActive = false;
		return bIsActive;
	}

	return bIsActive;
}


void MysqlQueryAdapter::_UpdateLatestActionTime()
{
	ThreadGuard guardQuery( m_queryLock );
    // update latest action time in public member function
	m_pWorkTimeQueryAction->workBegin();
}



NS_END(TA_Base_Core)














