#include "ConnectionPoolManager.h"

#include <sstream>
#include <time.h>
#include <algorithm>


#include <boost/lexical_cast.hpp>
#include "core/mcl/cppconn/driver.h"

#include "IDbConnectionPool.h"
#include "DBConnectionPool.h"
#include "ConnectionPoolMonitor.h"

#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/DataAccessException.h"

#include "core/threads/src/ReEntrantThreadLockable.h"
#include "core/DataAccess/src/DbStatusItem.h"
#include "core/DataAccess/src/SQLStatement.h"
#include "core/threads/src/ThreadGuard.h"
#include "core/CppConfigLib/src/RunParams.h"
#include "ConnectionPoolManager.h"
#include "core/utilities/src/WorkTime.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;


NS_BEGIN(TA_Base_Core)

// the type of the database server
sql::Driver*  g_pMysqlDBDriver = NULL;



// Definition of static member variables.
TA_Base_Core::ReEntrantThreadLockable CConnectionPoolManager::m_singletonLock;
CConnectionPoolManager* CConnectionPoolManager::m_instance = NULL;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                         Construction/Destruction                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

CConnectionPoolManager& CConnectionPoolManager::getInstance()
{
	ThreadGuard guard(m_singletonLock);


	if ( NULL == m_instance )
	{
		m_instance = new CConnectionPoolManager();
	}

	return *m_instance;
}


void CConnectionPoolManager::removeInstance()
{

	ThreadGuard guard(m_singletonLock);

	if ( m_instance != NULL )
	{
		delete m_instance;
		m_instance = NULL;
	}
}

CConnectionPoolManager::CConnectionPoolManager()
: m_nMaxPoolSize(DEF_MAX_POOLSIZE)
, m_nMinPoolSize(DEF_MIN_POOLSIZE)
{

	m_queryRetryInterval = 0;
	m_nRemoveUnHealthConTime = DEF_REMOVE_UNHEALTH_CON_TIME; //seconds

	// Construct a ConnectionReaper thread.  It will be responsible
	// for cleaning up connections that are being refreshed and 
	// the existing connections when auto-reconnect occurs.

	LOG_DEBUG<<"Starting ConnectionPoolMonitor";
	
	CConnectionPoolMonitor::getInstance();

	//added by hongzhi, solve thread hang when setting runparam
	if ( true == CRunParams::getInstance().isSetParam("QueryRetryInterval") )
	{
		std::string queryRetryInterval = CRunParams::getInstance().getStringParamValue("QueryRetryInterval");
		try
		{
			m_queryRetryInterval = boost::lexical_cast<unsigned long>( queryRetryInterval.c_str() );
		}
		catch( boost::bad_lexical_cast& )
		{
			LOG_ERROR<<"Failed to parse to an unsigned long Bad Runparam value for queryRetryInterval="<<queryRetryInterval;

		}

		LOG_DEBUG<<"QueryRetryInterval is set as (seconds) m_queryRetryInterval="<<m_queryRetryInterval;

	}

	// check run parameter for connection pool maximum size and minimum size
	if (TA_Base_Core::CRunParams::getInstance().isSetParam("RPARAM_DBCONNMAX"))
	{
		std::string strConnMax = CRunParams::getInstance().getStringParamValue("RPARAM_DBCONNMAX");
		m_nMaxPoolSize = atoi(strConnMax.c_str());
		if(m_nMaxPoolSize <= 0) // if conversion failed or <= 0 value has been set, then set to default value
		{
			m_nMaxPoolSize = DEF_MAX_POOLSIZE;
		}
		LOG_DEBUG<<"Database connection pool maximum size has been set m_nMaxPoolSize="<<m_nMaxPoolSize;

	}

	if (TA_Base_Core::CRunParams::getInstance().isSetParam("RPARAM_DBCONNMIN"))
	{
		std::string strConnMin = CRunParams::getInstance().getStringParamValue("RPARAM_DBCONNMIN");
		m_nMinPoolSize = atoi(strConnMin.c_str());
		if(m_nMinPoolSize < 0) // if conversion failed or < 0 value has been set, then set to default value
		{
			m_nMinPoolSize = DEF_MIN_POOLSIZE;
		}
		LOG_DEBUG<<"Database connection pool maximum size has been set m_nMinPoolSize="<<m_nMinPoolSize;

	}

	g_pMysqlDBDriver = NULL;
	g_pMysqlDBDriver = (sql::Driver*)get_driver_instance();  // for mysql db connection

	ThreadGuard guard(m_lockMapDbConnectionPools);

	m_mapDbConnectionPools.clear();
}

CConnectionPoolManager::~CConnectionPoolManager()
{

	closeAll();

	LOG_DEBUG<<"begin Stop ConnectionPoolMonitor";

	CConnectionPoolMonitor::removeInstance();

	if (NULL != g_pMysqlDBDriver)
	{
		//delete g_pMysqlDBDriver;
		g_pMysqlDBDriver = NULL;
	}

	LOG_DEBUG<<"end Stop ConnectionPoolMonitor";

}


int CConnectionPoolManager::createConnectionPool( CDbStatusItem* pDbStatusItem )
{
	int nFunRes = 0;

	IDbConnectionPool* pNewConPool = NULL;
	IDbConnectionPool* pConPoolGet = NULL;
	bool bConnectionExists = false;
	bool bConnectionHealth = false;
	std::string connectionStr;
	


	ThreadGuard guard(m_mutexCreatePool);
	
	if (NULL == pDbStatusItem || false == pDbStatusItem->isValid())
	{
		nFunRes = -1;
		return nFunRes;
	}

	connectionStr = pDbStatusItem->getConnectionString();
	bConnectionExists = _ConnectionExists(pDbStatusItem);
	if (bConnectionExists)
	{
		pConPoolGet = _GetConnectionPool(pDbStatusItem);
		bConnectionHealth = pConPoolGet->getDBPoolStatus();
	}

	//if connection pool still exists and status is Health then return,
	if (bConnectionExists && bConnectionHealth)
	{
		LOG_DEBUG<<" "<<"connectionStr="<<pDbStatusItem->getConnectionString()
			<<" "<<"is exist in DB Connection Pool";

		return nFunRes;
	}


	// If it is automatically reconnecting or there is not an existing connection
	// create a new OCIConnection to handle sessions with the given details.
	try
	{
		pNewConPool = new CDBConnectionPool(*pDbStatusItem, m_nMinPoolSize, m_nMaxPoolSize);
	}
	catch(DataAccessException &e)		
	{
		LOG_ERROR<<"can not open DB connection="<<pDbStatusItem->getConnectionString()
			<<" "<<"error getReason"<<e.getReason();

		delete pNewConPool;
		pNewConPool = NULL;

		throw e;
	}
	catch(...)
	{
		LOG_ERROR<<"can not open DB connection="<<pDbStatusItem->getConnectionString();

		delete pNewConPool;
		pNewConPool = NULL;
		throw;
	}

	if (bConnectionExists && NULL != pNewConPool)
	{
		pConPoolGet = _GetConnectionPool(pDbStatusItem);
		pConPoolGet->setDBPoolStatus(true);		

		//if connection pool still exists and status is UnHealth then try to connection, if connection is ok, then free this connection
		delete pNewConPool;
		pNewConPool = NULL;
	}
	if (NULL != pNewConPool)
	{
		ThreadGuard guard(m_lockMapDbConnectionPools);

		if (m_mapDbConnectionPools.find(connectionStr) != m_mapDbConnectionPools.end())
		{
			delete pNewConPool;
			pNewConPool = NULL;
		}
		else
		{
			m_mapDbConnectionPools.insert(MapDBConnectionValueT(connectionStr, pNewConPool));
		}
	}

	return nFunRes;
}

void CConnectionPoolManager::open( CDbStatusItem* pDbStatusItem )
{

	//check pool
	LOG_DEBUG<<"connectionStr="<<pDbStatusItem->getConnectionString()
		<<" "<<" is not in DB Connection Pool, then create new one";
	
	createConnectionPool(pDbStatusItem);
}

bool CConnectionPoolManager::isOpen( CDbStatusItem* pDbStatusItem )
{
	bool bFunRes = false;
	bool bConnectionExists = false;
	bool bConnectionHealth = false;

	bConnectionExists = _ConnectionExists(pDbStatusItem);
	if (bConnectionExists)
	{
		IDbConnectionPool* pConPoolGet = _GetConnectionPool(pDbStatusItem);
		bConnectionHealth = pConPoolGet->getDBPoolStatus();
	}

	if (bConnectionExists && bConnectionHealth)
	{
		bFunRes = true;
	}
	return bFunRes;
}


void CConnectionPoolManager::setPoolUnHealth( CDbStatusItem* pDbStatusItem )
{
	LOG_DEBUG<<"CConnectionPoolManager::setPoolUnHealth"
		<<" "<<"connectionStr="<<pDbStatusItem->getConnectionString();

	_SetPoolStatus(pDbStatusItem, false);

	CConnectionPoolMonitor::getInstance().removeUnHealthConnections(m_nRemoveUnHealthConTime);
}



void CConnectionPoolManager::_SetPoolStatus(CDbStatusItem* pDbStatusItem, bool bIsHealth)
{

	IDbConnectionPool* pDbConnectionPool = NULL;
	MapDBConnectionIterT iterMapFind;
	std::string connectionStrFind = pDbStatusItem->getConnectionString();

	//check pool
	if (false == _ConnectionExists(pDbStatusItem))
	{
		LOG_DEBUG<<" "<<"connectionStr="<<pDbStatusItem->getConnectionString()
			<<" "<<"not in DB Connection Pool";
		return;
	}


	{
		ThreadGuard guard(m_lockMapDbConnectionPools);

		iterMapFind = m_mapDbConnectionPools.begin();
		iterMapFind = m_mapDbConnectionPools.find(connectionStrFind);
		if (iterMapFind != m_mapDbConnectionPools.end())
		{
			pDbConnectionPool = (iterMapFind->second);
			//delete
			pDbConnectionPool->setDBPoolStatus(bIsHealth);
		}
	}
}


void CConnectionPoolManager::close( CDbStatusItem* pDbStatusItem )
{ 
	LOG_DEBUG<<" "<<"CConnectionPoolManager::close  connectionStr="<<pDbStatusItem->getConnectionString();
	_SetPoolStatus(pDbStatusItem, false);


}



void CConnectionPoolManager::closeAll()
{

	IDbConnectionPool* pDbConnectionPool = NULL;
	MapDBConnectionIterT iterMap;

	ThreadGuard guard(m_lockMapDbConnectionPools);

	iterMap = m_mapDbConnectionPools.begin();
	while (iterMap != m_mapDbConnectionPools.end())
	{
		pDbConnectionPool = (iterMap->second);
		//delete
		pDbConnectionPool->setDBPoolStatus(false);
		delete pDbConnectionPool;
		pDbConnectionPool = NULL;

		iterMap++;
	}
	m_mapDbConnectionPools.clear();
}

void CConnectionPoolManager::cleanQuery( CDbStatusItem* pDbStatusItem, IQueryAdapter*& pQuery )
{

	IDbConnectionPool* pDBConPool = NULL;
	MapDBConnectionIterT iterMapFind;
	std::string connectionStrFind = pDbStatusItem->getConnectionString();

	//check pool
	if (false == _ConnectionExists(pDbStatusItem))
	{
		LOG_DEBUG<<" "<<"connectionStr="<<pDbStatusItem->getConnectionString()
			<<" "<<"not in DB Connection Pool";

		return;
	}


	{
		ThreadGuard guard(m_lockMapDbConnectionPools);
		
		iterMapFind = m_mapDbConnectionPools.begin();
		iterMapFind = m_mapDbConnectionPools.find(connectionStrFind);
		if (iterMapFind != m_mapDbConnectionPools.end())
		{
			//delete
			pDBConPool = (iterMapFind->second);
			pDBConPool->cleanQuery(pQuery);
		}

	}
}




bool CConnectionPoolManager::isQueryHealth( CDbStatusItem* pDbStatusItem, IQueryAdapter* pQueryAdapter )
{

	IDbConnectionPool* pDBConPool = NULL;
	MapDBConnectionIterT iterMapFind;
	std::string connectionStrFind = pDbStatusItem->getConnectionString();
	bool bIsQueryHealth = false;

	//check pool
	if (false == _ConnectionExists(pDbStatusItem))
	{
		LOG_DEBUG<<" "<<"connectionStr="<<pDbStatusItem->getConnectionString()
			<<" "<<"not in DB Connection Pool";

		bIsQueryHealth = false;
		return bIsQueryHealth;
	}


	{
		ThreadGuard guard(m_lockMapDbConnectionPools);

		iterMapFind = m_mapDbConnectionPools.begin();
		iterMapFind = m_mapDbConnectionPools.find(connectionStrFind);
		if (iterMapFind != m_mapDbConnectionPools.end())
		{
			//delete
			pDBConPool = (iterMapFind->second);
			bIsQueryHealth = pDBConPool->isQueryHealth(pQueryAdapter);
		}

	}

	return bIsQueryHealth;
}


IQueryAdapter* CConnectionPoolManager::exec( CDbStatusItem* pDbStatusItem, const SQLStatement& rSqlObj, int numRows )
{

	IDbConnectionPool* pDBConPoolGet = NULL;
	int prefetch = numRows;
	unsigned long retry = 0;
	bool execOk = false;
	unsigned long nTrytimes = EXEC_NUM_RETRIES;//3
	IQueryAdapter* pQueryAdapter = NULL;

	//check pool
	if (false == _ConnectionExists(pDbStatusItem))
	{
		LOG_DEBUG<<" "<<"connectionStr="<<pDbStatusItem->getConnectionString()
			<<" "<<"not in DB Connection Pool";


		return pQueryAdapter;
	}

	pDBConPoolGet = _GetConnectionPool(pDbStatusItem);

	LOG_DEBUG<<"begin execute the SQL statement";

	// Execute the statement.
	try
	{
		pDBConPoolGet->exec(rSqlObj, pQueryAdapter, true, prefetch);
		execOk = true;
	}
	catch(...)
	{
		if ( NULL != pQueryAdapter )
		{
			cleanQuery( pDbStatusItem, pQueryAdapter );
		}
		LOG_DEBUG<<"Fail execute the SQL statement";
		execOk = false;
	}

	LOG_DEBUG<<"End execute the SQL statement";

	return pQueryAdapter;
}


void CConnectionPoolManager::exec( CDbStatusItem* pDbStatusItem, const SQLStatement& rSqlObj )
{

	IDbConnectionPool* pDBConPoolGet = NULL;
	unsigned long retry = 0;
	bool execOk = false;
	IQueryAdapter* pQueryAdapter = NULL;

	//check pool
	if (false == _ConnectionExists(pDbStatusItem))
	{
		LOG_DEBUG<<" "<<"connectionStr="<<pDbStatusItem->getConnectionString()
			<<" "<<"not in DB Connection Pool";

		return;
	}

	pDBConPoolGet = _GetConnectionPool(pDbStatusItem);

	LOG_DEBUG<<"begin execute the SQL statement";

	try
	{
		pDBConPoolGet->exec(rSqlObj, pQueryAdapter, false, 0);

		if ( NULL != pQueryAdapter )
		{
			LOG_ERROR<< "execute none query command should not return query";
			cleanQuery( pDbStatusItem, pQueryAdapter );
		}

		if (NULL != pQueryAdapter)
		{
			LOG_ERROR<<"query should be null";
		}
		execOk = true;
	}
	catch(...)
	{
		LOG_DEBUG<<"Fail execute the SQL statement";

		if ( NULL != pQueryAdapter )
		{
			cleanQuery( pDbStatusItem, pQueryAdapter );
		}

		pQueryAdapter = NULL;
	}


	LOG_DEBUG<<"End execute the SQL statement";
}

bool CConnectionPoolManager::_ConnectionExists( CDbStatusItem* pDbStatusItem )
{
	bool bConnectionExist = false;
	MapDBConnectionIterT iterMapFind;
	std::string connectionStrFind;
	IDbConnectionPool* pDBConPoolGet = NULL;

	connectionStrFind = pDbStatusItem->getConnectionString();

	{
		ThreadGuard guard(m_lockMapDbConnectionPools);

		iterMapFind = m_mapDbConnectionPools.begin();
		iterMapFind = m_mapDbConnectionPools.find(connectionStrFind);
		if (iterMapFind != m_mapDbConnectionPools.end())
		{
			pDBConPoolGet = (iterMapFind->second);
			bConnectionExist = true;
		}
	}

	return bConnectionExist;
}



IDbConnectionPool* CConnectionPoolManager::_GetConnectionPool( CDbStatusItem* pDbStatusItem )
{

	MapDBConnectionIterT iterMapFind;
	IDbConnectionPool* pDBConPoolGet = NULL;
	std::string connectionStr;

	ThreadGuard guard(m_lockMapDbConnectionPools);

	connectionStr = pDbStatusItem->getConnectionString();

	iterMapFind = m_mapDbConnectionPools.begin();
	iterMapFind = m_mapDbConnectionPools.find(connectionStr);
	if (iterMapFind != m_mapDbConnectionPools.end())
	{
		pDBConPoolGet = (iterMapFind->second);
	}
	return pDBConPoolGet;
}



void CConnectionPoolManager::removeUnHealthConnection()
{

	MapDBConnectionIterT iterMap;
	IDbConnectionPool* pDBConPool = NULL;

	ThreadGuard guard(m_lockMapDbConnectionPools);

	iterMap = m_mapDbConnectionPools.begin();
	while (iterMap != m_mapDbConnectionPools.end())
	{
		pDBConPool = (iterMap->second);
		pDBConPool->removeUnHealthConnection();	

		iterMap++;
	}//while

	return;
}




NS_END(TA_Base_Core)







