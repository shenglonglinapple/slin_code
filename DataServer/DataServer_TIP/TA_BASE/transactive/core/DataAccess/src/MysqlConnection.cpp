#include "MysqlConnection.h"

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


using TA_Base_Core::ThreadGuard;



NS_BEGIN(TA_Base_Core)


MysqlConnection::MysqlConnection( sql::Driver* pDriver, const CDbStatusItem& objDbStatusItem )
{
	m_pDriver = pDriver;
	m_pConnection = NULL;
	m_pDbStatusItem = NULL;

	m_pDbStatusItem = new CDbStatusItem();
	*m_pDbStatusItem = objDbStatusItem;

	m_pWorkTimeConnecion = new CWorkTimeLock();
	m_pWorkTimeUsingConnecion = new CWorkTimeLock();
	m_pWorkTimeNotUsingConnecion = new CWorkTimeLock();	
	m_bIsHealth = true;
	_CreateConnection();
}


/**
* ~MysqlConnection
* 
* Sole standard destructor.  Frees the handles allocated in the constructor.
*/
MysqlConnection::~MysqlConnection()
{
	_CleanAllQuery();
	_Close();

	if (NULL != m_pWorkTimeConnecion)
	{
		delete m_pWorkTimeConnecion;
		m_pWorkTimeConnecion = NULL;
	}

	if (NULL != m_pWorkTimeUsingConnecion)
	{
		delete m_pWorkTimeUsingConnecion;
		m_pWorkTimeUsingConnecion = NULL;
	}

	if (NULL != m_pWorkTimeNotUsingConnecion)
	{
		delete m_pWorkTimeNotUsingConnecion;
		m_pWorkTimeNotUsingConnecion = NULL;
	}

	if (NULL != m_pDbStatusItem)
	{
		delete m_pDbStatusItem;
		m_pDbStatusItem = NULL;
	}

}


void MysqlConnection::_CleanAllQuery()
{
	IQueryAdapter* pQueryAdapter = NULL;
	ThreadGuard guard( m_LockMapActiveQuery );

	for ( std::map<IQueryAdapter*, long>::iterator itLoop = m_mapActiveQuery.begin();
		m_mapActiveQuery.end() != itLoop; ++itLoop )
	{

		try
		{
			pQueryAdapter = (itLoop->first);
			if ( NULL == pQueryAdapter)
			{
				LOG_WARNING<<"Unexpected NULL pointer of MysqlQueryAdapter";				
				continue;
			}

			delete (pQueryAdapter);

			LOG_DEBUG<<"MysqlConnection::_CleanAllQuery Destory Query,"
				<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
				<<" "<<"ConnectionHandle=0x"<<this
				<<" "<<"QueryHandle=0x"<<pQueryAdapter
				<<" "<<"TotalQuerySize="<<m_mapActiveQuery.size();
		
			pQueryAdapter = NULL;
		}
		catch (...)
		{
			LOG_ERROR<<"_CleanAllQuery error! delete (pQueryAdapter)";
		}
	}

	m_mapActiveQuery.clear();
}

void MysqlConnection::_Close()
{

	// The connection is closed when the server is detached.
	try
	{
		ThreadGuard guard( m_lockConnection );
		if (NULL != m_pConnection)
		{
			LOG_DEBUG<<"begin delete one mysql::Connection"
				<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
				<<" "<<"ConnectionHandle="<<this
				<<" "<<"mysql::ConnectionHandle="<<m_pConnection;

			if (NULL != m_pConnection)
			{
				delete m_pConnection;
				m_pConnection = NULL;
			}


			LOG_DEBUG<<"end delete one mysql::Connection"
				<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
				<<" "<<"ConnectionHandle="<<this
				<<" "<<"mysql::ConnectionHandle="<<m_pConnection
				<<" "<<"TotalQuerySize="<<m_mapActiveQuery.size()
				<<" "<<"IsHealth="<<m_bIsHealth
				<<" "<<"workTimeMillSeconds="<<m_pWorkTimeConnecion->getNotWorkTimeMillSeconds();


			m_pWorkTimeConnecion->workEnd();


		}
	}
	catch(sql::SQLException &e)
	{
		LOG_ERROR<<"MysqlConnection::_Close sql::SQLExceptio MCL_ERROR="<<e.what();
	}
	catch (...)
	{
		LOG_ERROR<<"MysqlConnection::_Close Unknown exception";
	}
}

/**
* createConnection
* 
* creates the underlying framework to support a session
*/
void MysqlConnection::_CreateConnection()
{
	_Close();

	try
	{
		ThreadGuard guard( m_lockConnection );
		
		if (NULL == m_pDriver)
		{
			LOG_ERROR<<"Mysql database Driver is null";
			return;
		}	

		sql::ConnectOptionsMap connection_properties;
		connection_properties["hostName"] = m_pDbStatusItem->m_strIP;
		connection_properties["userName"] = m_pDbStatusItem->m_strUser;
		connection_properties["password"] = m_pDbStatusItem->m_strPassword;
		connection_properties["metadataUseInfoSchema"] = true;

		m_pConnection = m_pDriver->connect(connection_properties); 
		if (NULL == m_pConnection)
		{
			LOG_ERROR<<"Cannot connect to the database server.";
			throw std::exception("Cannot connect to the database server.");
		}

		m_pConnection->setSchema(m_pDbStatusItem->m_strSchema);

		// set this session mode with backslash disabled, same with oracle
		std::auto_ptr< sql::Statement > stmt(m_pConnection->createStatement());
		stmt->execute("set session sql_mode=concat(@@sql_mode,',NO_BACKSLASH_ESCAPES')");

		m_pWorkTimeConnecion->workBegin();
		m_pWorkTimeUsingConnecion->workBegin();
		m_pWorkTimeNotUsingConnecion->workBegin();
		setConStatus(true);

		LOG_DEBUG<<"new one mysql::Connection"
			<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString();

		LOG_DEBUG<<"new one mysql::Connection"
			<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"ConnectionHandle="<<this
			<<" "<<"mysql::ConnectionHandle="<<m_pConnection
			<<" "<<"TotalQuerySize="<<m_mapActiveQuery.size()
			<<" "<<"IsHealth="<<m_bIsHealth
			<<" "<<"workTimeMillSeconds="<<m_pWorkTimeConnecion->getNotWorkTimeMillSeconds();

	}
	catch(sql::SQLException & e)
	{
		LOG_ERROR<<"MYSQL_ERROR:"
			<<" "<<"getSQLStateCStr="<<e.getSQLStateCStr()
			<<" "<<"errormsg="<<e.what()
			<<" "<<"errorcode="<<e.getErrorCode();

		DataAccessException db(e.getErrorCode(), e.what());

		throw db;
	}		
	catch(...)
	{
		LOG_ERROR<<"MYSQL_ERROR:"<<"unknown database exception";

		DataAccessException db(0, "unknown database exception");

		throw db;
	}	
}

/**
* getConnectionString
*
* Returns the connection string for this MysqlConnection.
*
* @return std::string  the connection string in the form
*                      databaseName:userName:password:hostName
*/
std::string MysqlConnection::getConnectionString() const
{
	return m_pDbStatusItem->getConnectionString();
}

bool MysqlConnection::isOpen()
{
	bool bIsOpen = false;
	bool bIsClosed = false;

	ThreadGuard guard( m_lockConnection );

	try
	{
		if (NULL != m_pConnection)
		{
			bIsClosed = m_pConnection->isClosed();
		}
		else
		{
			bIsClosed = true;
		}
	}	
	catch(sql::SQLException & e)
	{
		LOG_ERROR<<"MYSQL_ERROR:"
			<<" "<<"getSQLStateCStr="<<e.getSQLStateCStr()
			<<" "<<"errormsg="<<e.what()
			<<" "<<"errorcode="<<e.getErrorCode();

		DataAccessException db(e.getErrorCode(), e.what());

		throw db;
	}		
	catch(...)
	{
		LOG_ERROR<<"MYSQL_ERROR:"<<"unknown database exception";

		DataAccessException db(0, "unknown database exception");

		throw db;
	}


	bIsOpen = !bIsClosed;

	return bIsOpen;
}

void MysqlConnection::open()
{

	if (isOpen())
	{
		LOG_DEBUG<<"use established connection";
		return;
	}


	try  
	{
		// connection closed, reconnect to the database server
		_CreateConnection();	
		LOG_DEBUG<<"use new connection";
	}
	catch(DataAccessException &e)
	{
		LOG_ERROR<<"MYSQL_ERROR:"
			<<" "<<"errormsg="<<e.getReason()
			<<" "<<"errorcode="<<e.getErrorCode();

		DataAccessException db(e.getErrorCode(), e.what());

		throw db;
	}
	catch(sql::SQLException & e)
	{
		LOG_ERROR<<"MYSQL_ERROR:"
			<<" "<<"errormsg="<<e.what()
			<<" "<<"errorcode="<<e.getErrorCode();

		DataAccessException db(e.getErrorCode(), e.what());

		throw db;
	}	
	catch(...)
	{
		LOG_ERROR<<"MYSQL_ERROR:"<<"unknown database exception";

		DataAccessException db(0, "unknown database exception");

		throw db;
	}	
	
}



/**
* exec
*
* Executes the given statement on the database.  This method
* handles both queries (e.g. "SELECT...") and non-queries (e.g."INSERT...")
*
* @param statement    the statement to execute
* @param isQuery      a bool that is true if the statement is a query
* @param numColumns   the number of columns to retrieve
* @param bindType     the type of binding required
* @return true if the statement was executed, false otherwise
*/
void MysqlConnection::exec( const SQLStatement& rSqlObj, IQueryAdapter*& pIQueryAdapter, bool isQuery /*= false*/, int prefetch /*= FETCH_MAX_ROWS*/)
{
	if ( NULL != pIQueryAdapter )
	{
		LOG_ERROR<<"pIQueryAdapter should not be other value except NULL";
		cleanQuery( pIQueryAdapter );
	}

	std::string strSql;
	_GetSQL(strSql, rSqlObj);

	if (strSql.empty())
	{
		LOG_ERROR<<"SQL statement is empty";
		DataAccessException db(0, "unknown SQL error!");
		throw db;		
	}

	LOG_DEBUG<<"Begin execute the SQL statement:"
		<<" "<<"SQLID="<<rSqlObj.m_strSQLID
		<<" "<<"StrSQL=""[["<<strSql<<"]]";
	

	// check the database connection first, if it already closed, open it
	open();

	sql::ResultSet* pQuery = NULL;	
	try
	{		
		ThreadGuard guard( m_lockConnection );

		if (NULL == m_pConnection)
		{
			LOG_ERROR<<"Connection is NULL";
			DataAccessException db(0, "Connection is NULL");
			throw db;		
		}

		std::auto_ptr< sql::Statement > stmt(m_pConnection->createStatement());
		if (isQuery) //select *
		{
			pQuery = stmt->executeQuery(strSql);
		}
		else //like the insert command
		{
			bool bRetCode = stmt->execute(strSql);
			if(bRetCode)
			{
				LOG_DEBUG<<"the statement is not a insert like statement";
			}
		
		}
	}
	catch(DataAccessException& e)
	{
		throw e;
	}
	catch(sql::SQLException & e)
	{
		LOG_DEBUG<<"Failed to execute the SQL statement:"
			<<" "<<"SQLID="<<rSqlObj.m_strSQLID
			<<" "<<"StrSQL=""[["<<strSql<<"]]";

		DataAccessException db(e.getErrorCode(),  e.what());
		db.logInfo(LogFLInfo);

		delete pQuery; 
		pQuery = NULL;

		throw db;
	}	
	catch(...)
	{
		LOG_DEBUG<<"Failed to execute the SQL statement:"
			<<" "<<"SQLID="<<rSqlObj.m_strSQLID
			<<" "<<"StrSQL=""[["<<strSql<<"]]";

		DataAccessException db(0,  "unknown database exception");
		db.logInfo(LogFLInfo);

		delete pQuery; 
		pQuery = NULL;

		throw db;
	}	

	//just save the pointer, here
	if ( NULL != pQuery )
	{
		ThreadGuard guard( m_LockMapActiveQuery );
		pIQueryAdapter = new MysqlQueryAdapter( pQuery );

		if (m_mapActiveQuery.find(pIQueryAdapter) == m_mapActiveQuery.end())
		{
			//not find add in
			m_mapActiveQuery[pIQueryAdapter] = QUERY_EXIST;

			LOG_DEBUG<<"MysqlConnection::exec new Query"
				<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
				<<" "<<"ConnectionHandle=0x"<<this
				<<" "<<"QueryHandle=0x"<<pIQueryAdapter
				<<" "<<"TotalQuerySize=0x"<<m_mapActiveQuery.size();
		}
		else
		{
			//replace
			LOG_ERROR<<"MysqlConnection::exec new Query but find same in map"
				<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
				<<" "<<"ConnectionHandle=0x"<<this
				<<" "<<"QueryHandle=0x"<<pIQueryAdapter
				<<" "<<"TotalQuerySize=0x"<<m_mapActiveQuery.size();

			delete pIQueryAdapter;
			pIQueryAdapter = NULL;

		}
	}

	
}





/**
* incrementExecutionCount
*
* Increment the count of threads that are using this connection right now.
* Note: The count does not include threads that have this connection open, 
* but are not executing on it right now.
*/
void MysqlConnection::incrementExecutionCount()
{
	ThreadGuard guard( m_LockExecutionCount );
	m_nExecutionCount++;
	m_pWorkTimeUsingConnecion->workBegin();
	m_pWorkTimeNotUsingConnecion->workBegin();
	LOG_DEBUG<<"MysqlConnection::incrementExecutionCount()"
		<<" "<<"Execution count="<<m_nExecutionCount;
	
}


/**
* decrementExecutionCount
*
* Decrement the count of threads that are using this connection right now.
* Note: The count does not include threads that have this connection open,
* but are not executing on it right now.
*/
void MysqlConnection::decrementExecutionCount()
{
	BigInt64 nExeSQLUsingTimeMillseconds = 0;

	ThreadGuard guard( m_LockExecutionCount );
	if (m_nExecutionCount > 0)
	{
		m_pWorkTimeUsingConnecion->workEnd();
		m_pWorkTimeNotUsingConnecion->workBegin();
		nExeSQLUsingTimeMillseconds = m_pWorkTimeUsingConnecion->getWorkTimeMillSeconds();

		m_nExecutionCount--;
	}

	LOG_DEBUG<<"MysqlConnection::decrementExecutionCount()"
		<<" "<<"Execution count="<<m_nExecutionCount
		<<" "<<"ExeSQL UsingTimeMillseconds="<<nExeSQLUsingTimeMillseconds;


}




bool MysqlConnection::isAnyQueryActive( unsigned long ulMaxTimeoutInSecs )
{
	IQueryAdapter* pQueryAdapter = NULL;
	bool bIsActive = false;
	ThreadGuard guard( m_LockMapActiveQuery );

	for ( std::map<IQueryAdapter*, long>::iterator itLoop = m_mapActiveQuery.begin(); 
		m_mapActiveQuery.end() != itLoop; ++itLoop )
	{
		pQueryAdapter = (itLoop->first);
		if ( NULL == pQueryAdapter)
		{
			LOG_WARNING<<"Unexpected NULL pointer of OCIQueryAdapter";
			continue;
		}

		if ( pQueryAdapter->isActive( ulMaxTimeoutInSecs ))
		{
			bIsActive = true;
			return bIsActive;
		}
	}

	return bIsActive;
}


bool MysqlConnection::_CheckAnyNotQueryActive( unsigned long ulMaxTimeoutInSecs )
{

	IQueryAdapter* pQueryAdapter = NULL;
	bool bIsNotActive = false;
	ThreadGuard guard( m_LockMapActiveQuery );

	for ( std::map<IQueryAdapter*, long>::iterator itLoop = m_mapActiveQuery.begin(); 
		m_mapActiveQuery.end() != itLoop; ++itLoop )
	{
		pQueryAdapter = (itLoop->first);
		if ( NULL == pQueryAdapter)
		{
			LOG_WARNING<<"Unexpected NULL pointer of OCIQueryAdapter";
			continue;
		}

		if (false == pQueryAdapter->isActive( ulMaxTimeoutInSecs ))
		{
			bIsNotActive = true;
			return bIsNotActive;
		}
	}

	return bIsNotActive;
}

void MysqlConnection::cleanQuery( IQueryAdapter*& pQueryAdapter )
{
    if ( NULL == pQueryAdapter )
    {
		LOG_WARNING<<"Unexpected NULL pointer of OCIQueryAdapter";
        return;
    }


    ThreadGuard guard( m_LockMapActiveQuery );
	IQueryAdapter* pQueryAdapterGet = NULL;

    std::map<IQueryAdapter*, long>::iterator itExistQuery = m_mapActiveQuery.find( pQueryAdapter );
    if ( m_mapActiveQuery.end() != itExistQuery )
    {
		pQueryAdapterGet = (itExistQuery->first);

        // Destructor will clean query
        delete (pQueryAdapterGet);
		pQueryAdapterGet = NULL;
        m_mapActiveQuery.erase( itExistQuery );


		LOG_DEBUG<<"MysqlConnection::cleanQuery Destory Query"
			<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"ConnectionHandle="<<this
			<<" "<<"QueryHandle="<<pQueryAdapter
			<<" "<<"TotalQuerySize="<<m_mapActiveQuery.size();
    }
    else
    {
		LOG_WARNING<<"Specified query is not found in this connection"
			<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"ConnectionHandle="<<this
			<<" "<<"QueryHandle="<<pQueryAdapter
			<<" "<<"TotalQuerySize="<<m_mapActiveQuery.size();

        delete pQueryAdapter;
		pQueryAdapter = NULL;
    }

    // Set pointer to NULL
    pQueryAdapter = NULL;


}

void  MysqlConnection::_GetSQL(std::string& strSql, const SQLStatement& rSqlObj)
{
	if (!rSqlObj.m_strCommonSQL.empty())
	{
		strSql = rSqlObj.m_strCommonSQL;
	}
	else if (!rSqlObj.m_strMySQLSQL.empty())
	{
		strSql = rSqlObj.m_strMySQLSQL;
	}
}


bool MysqlConnection::isHealth()
{
	long nReapIntervalInSeconds = 0;
	long nQueryMaxSzie = 0;
	long nQueryMaxIdleTime = 0;

	nQueryMaxIdleTime = DEF_QUERY_MAX_IDLETIME;
	nReapIntervalInSeconds = DEF_CON_MAX_IDLETIME;
	nQueryMaxSzie = DEF_QUERY_MAX_SIZE;


	{
		if (false == m_bIsHealth)
		{
			return m_bIsHealth;
		}
	}

	{
		ThreadGuard guardConnecion( m_lockConnection );
		ThreadGuard guardQuery( m_LockMapActiveQuery );
		ThreadGuard guardExeCout( m_LockExecutionCount );
		//check connection 
		if (m_pWorkTimeNotUsingConnecion->getNotWorkTimeSeconds() > nReapIntervalInSeconds)
		{
			m_bIsHealth = false;
			return m_bIsHealth;
		}

		if (m_mapActiveQuery.size() > nQueryMaxSzie)
		{
			m_bIsHealth = false;
			return m_bIsHealth;
		}

	}


	{
		if (true == _CheckAnyNotQueryActive(nQueryMaxIdleTime))
		{
			m_bIsHealth = false;
			return m_bIsHealth;
		}
	}

	return m_bIsHealth;
}

void MysqlConnection::setConStatus(bool bIsHealth)
{

	m_bIsHealth = bIsHealth;


	LOG_DEBUG<<"MysqlConnection::setConStatus"
		<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
		<<" "<<"ConnectionHandle="<<this
		<<" "<<"mysql::ConnectionHandle="<<m_pConnection
		<<" "<<"TotalQuerySize="<<m_mapActiveQuery.size()
		<<" "<<"IsHealth="<<m_bIsHealth
		<<" "<<"workTimeMillSeconds="<<m_pWorkTimeConnecion->getNotWorkTimeMillSeconds();

}


NS_END(TA_Base_Core)





