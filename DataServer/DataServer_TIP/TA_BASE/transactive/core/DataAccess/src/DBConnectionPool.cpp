#include "core/DataAccess/src/DBConnectionPool.h"
#include <algorithm>

#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/DataAccessException.h"

#include "core/DataAccess/src/DbStatusItem.h"
#include "core/DataAccess/src/SQLStatement.h"
#include "core/DataAccess/src/IQueryAdapter.h"
#include "core/DataAccess/src/MysqlQueryAdapter.h"

#include "core/threads/src/ReEntrantThreadLockable.h"
#include "core/threads/src/ThreadGuard.h"

#include "core/CppConfigLib/src/RunParams.h"

#include "core/DataAccess/src/IDbConnection.h"
#include "core/DataAccess/src/MysqlConnection.h"
#include "core/DataAccess/src/ConnectionPoolManager.h"
#include "core/DataAccess/src/ConnectionPoolMonitor.h"

#include "core/mcl/cppconn/driver.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)

extern sql::Driver*  g_pMysqlDBDriver;


CDBConnectionPool::CDBConnectionPool( const CDbStatusItem& objDbStatusItem, int nMinPoolSize, int nMaxPoolSize)
:m_nInitialPoolSize(DEF_INITIAL_POOLSIZE)
, m_nMinPoolSize(nMinPoolSize)
, m_nAcquireIncrement(DEF_ACQUIRE_INCREMENT)
, m_nMaxPoolSize(nMaxPoolSize)
, m_nMaxIdleTime(DEF_CON_MAX_IDLETIME)
, m_nAcquireRetryAttempts(DEF_ACQUIRE_RETRYATTEMPTS)
, m_nAcquireRetryDelay(DEF_ACQUIRE_RETRYDELAY)
, m_bIsHealth(true)
, m_nIdleConNum(0)
, m_nTotalPoolNum(0)
, m_nUsingConNum(0)
, m_SemaphoreGetConnection(nMaxPoolSize)
{
	m_pDbStatusItem = NULL;
	m_pDbStatusItem = new CDbStatusItem();
	*m_pDbStatusItem = objDbStatusItem;
	
	_LogPoolInfo();
	_InitPool();

}

CDBConnectionPool::~CDBConnectionPool()
{
	_SetAllConnecionsStatus(false);
	removeUnHealthConnection();

	if (NULL != m_pDbStatusItem)
	{
		delete m_pDbStatusItem;
		m_pDbStatusItem = NULL;
	}
}


void CDBConnectionPool::_InitPool()
{
	_GetConStrInfo();

	{
		ThreadGuard guard(m_lockLstDBConnection);
		m_LstIdleDBConnetion.clear();
		m_LstUsingDBConnetion.clear();
		m_nIdleConNum = 0;
		m_nUsingConNum = 0;
	}

	{
		ThreadGuard guard(m_lockMapActiveQueryDBCon);

		m_mapActiveQueryDBCon.clear();
		m_nActiveQueryDBConNum = 0;
	}


	if (false == _CanNewConnection())
	{
		return;
	}

	//create con
	for (int nIndex = 0; nIndex < m_nInitialPoolSize; nIndex++)
	{
		_CreateConnection();
	}
}
void CDBConnectionPool::_SetAllConnecionsStatus(bool bISHealth)
{
	LstDBConnetionIterT iterLst;
	IDbConnection* pDbConnection = NULL;

	{
		ThreadGuard guard(m_lockLstDBConnection);

		iterLst = m_LstIdleDBConnetion.begin();
		while (iterLst != m_LstIdleDBConnetion.end())
		{
			pDbConnection = (*iterLst);
			pDbConnection->setConStatus(bISHealth);						
			iterLst++;
		}//while


		iterLst = m_LstUsingDBConnetion.begin();
		while (iterLst != m_LstUsingDBConnetion.end())
		{
			pDbConnection = (*iterLst);
			pDbConnection->setConStatus(bISHealth);
			iterLst++;
		}//while
	}

}


void CDBConnectionPool::_GetConStrInfo()
{
	LOG_DEBUG<<"get connection string Info:"
		<<" "<<"connectionStr="<<m_pDbStatusItem->getConnectionString()
		<<" "<<"m_strDBType="<<m_pDbStatusItem->m_strDbType
		<<" "<<"m_databaseName="<<m_pDbStatusItem->m_strSchema
		<<" "<<"m_userName="<<m_pDbStatusItem->m_strUser
		<<" "<<"m_password="<<m_pDbStatusItem->m_strPassword
		<<" "<<"m_hostName="<<m_pDbStatusItem->m_strIP;



}


void CDBConnectionPool::_CreateConnection()
{
	IDbConnection* pDbConnection = NULL;
	std::string strLogInfo;

	if (false == _CanNewConnection())
	{
		return;
	}
	
	
	//create con
	try
	{			
		switch (m_pDbStatusItem->m_nDbServerType)
		{
		case DbServerType_OracleDb:
			strLogInfo = "not support db type!";
			m_pDbStatusItem->logInfo(strLogInfo);
			break;
		case DbServerType_MysqlDb:
			if (NULL == g_pMysqlDBDriver)
			{
				LOG_ERROR<<"the Mysql database Driver is null";
				DataAccessException db(0, "the Mysql database Driver is null");
				throw db;
			}
			pDbConnection = new MysqlConnection(g_pMysqlDBDriver, *m_pDbStatusItem);
			break;
		default:
			strLogInfo = "not support db type!";
			m_pDbStatusItem->logInfo(strLogInfo);
			break;
		}

		if (NULL == pDbConnection)
		{
			LOG_ERROR<<"create database connection failed!";
			DataAccessException db(0, "create database connection failed!");
			throw db;
		}

		pDbConnection->open();
	}
	catch (DataAccessException& e)
	{
		LOG_ERROR<<"new Connection error!"
			<<" "<<"m_connectionStr="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"getErrorCode="<<e.getErrorCode()
			<<" "<<"getErrorMsg="<<e.getErrorMsg();
		throw e;
	}
	catch (...)
	{
		LOG_ERROR<<"new Connection error!"
			<<" "<<"m_connectionStr="<<m_pDbStatusItem->getConnectionString();

		DataAccessException db(0, "_CreateConnection Exception");
		throw db;
	}

	//add to lst nail
	if (NULL != pDbConnection)
	{
		ThreadGuard guard(m_lockLstDBConnection);
		m_LstIdleDBConnetion.push_back(pDbConnection);
		m_nIdleConNum++;
		m_nTotalPoolNum++;

		LOG_DEBUG<<"CDBConnectionPool new Connection"
			<<" "<<"m_connectionStr="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"pDbConnection=0x"<<pDbConnection;

		_LogPoolInfo();

		pDbConnection = NULL;	
	}
}

void CDBConnectionPool::_DestoryConnection(IDbConnection* pDbConnection)
{
	LstDBConnetionIterT findIter;

	//remove pDbConnection from IDlE list
	if (NULL != pDbConnection)
	{
		ThreadGuard guard(m_lockLstDBConnection);

		findIter = m_LstIdleDBConnetion.end();
		findIter = std::find(m_LstIdleDBConnetion.begin(), m_LstIdleDBConnetion.end(), pDbConnection);
		if (findIter != m_LstIdleDBConnetion.end())
		{
			pDbConnection = (*findIter);
			m_nIdleConNum--;
			m_nTotalPoolNum--;
			_LogPoolInfo();
			m_LstIdleDBConnetion.erase(findIter);
		}

	//remove pDbConnection from using list
		findIter = m_LstUsingDBConnetion.end();
		findIter = std::find(m_LstUsingDBConnetion.begin(), m_LstUsingDBConnetion.end(), pDbConnection);
		if (findIter != m_LstUsingDBConnetion.end())
		{
			pDbConnection = (*findIter);
			m_nUsingConNum--;
			m_nTotalPoolNum--;
			_LogPoolInfo();
			m_LstUsingDBConnetion.erase(findIter);
		}
	}


	//remove pDbConnection's all query
	if (NULL != pDbConnection)
	{
		MapQueryDBConT  mapQueryDBConTmp;
		_GetConnectionAllQuery(pDbConnection, mapQueryDBConTmp);

		//add to monitor
		CConnectionPoolMonitor::getInstance().addConnection(pDbConnection, mapQueryDBConTmp);
		mapQueryDBConTmp.clear();
	}
	


}

void CDBConnectionPool::_GetConnectionAllQuery(IDbConnection* pDbConnection, MapQueryDBConT& mapQueryDBCon)
{

	MapQueryDBConIterT iterMap;
	IQueryAdapter* pQueryAdapterInMap = NULL;
	IDbConnection* pDbConnectionInMap = NULL;

	if (NULL == pDbConnection)
	{
		return;
	}

	ThreadGuard guard(m_lockMapActiveQueryDBCon);

	iterMap = m_mapActiveQueryDBCon.begin();
	while (iterMap != m_mapActiveQueryDBCon.end())
	{
		pQueryAdapterInMap = (iterMap->first);
		pDbConnectionInMap = (iterMap->second);
		if (pDbConnectionInMap == pDbConnection)
		{
			mapQueryDBCon.insert(MapQueryDBConValueT(pQueryAdapterInMap, pDbConnectionInMap));
			m_mapActiveQueryDBCon.erase(iterMap);
			m_nActiveQueryDBConNum--;
			iterMap = m_mapActiveQueryDBCon.begin();
		}
		else
		{
			iterMap++;
		}

	}//while

}

//////////////////////////////////////////////////////////////////////////
bool CDBConnectionPool::_CanNewConnection()
{

	bool bFunRes = true;
	ThreadGuard guard(m_lockLstDBConnection);

	if (m_nTotalPoolNum >= m_nMaxPoolSize)
	{
		bFunRes = false;
	}

	return bFunRes;	
}
void CDBConnectionPool::_AcquireIncreNewConnections()
{

	for (int nIndex = 0; nIndex < m_nAcquireIncrement; nIndex++)
	{
		_CreateConnection();
	}

	return;
}

IDbConnection* CDBConnectionPool::_GetConnectionFormIdleLst()
{

	IDbConnection* pDbConnection = NULL;

	ThreadGuard guard(m_lockLstDBConnection);

		if (!m_LstIdleDBConnetion.empty())
		{
			pDbConnection = m_LstIdleDBConnetion.front();
			m_LstIdleDBConnetion.pop_front();
			m_nIdleConNum--;
	}

	if (NULL != pDbConnection)
	{
		m_LstUsingDBConnetion.push_back(pDbConnection);
		m_nUsingConNum++;
		_LogPoolInfo();
	}

	return pDbConnection;
}



IDbConnection* CDBConnectionPool::getConnection( long nTimeOut )
{

	IDbConnection* pDbConnection = NULL;

	{
		LOG_DEBUG<<"getConnection begin lock  m_mutexGetConnection";

		ThreadGuard guard(m_mutexGetConnection);

		LOG_DEBUG<<"getConnection end lock  m_mutexGetConnection";



		//wait here
		LOG_DEBUG<<"begin wait m_SemaphoreGetConnection";

		m_SemaphoreGetConnection.wait();

		LOG_DEBUG<<"end wait m_SemaphoreGetConnection";


		pDbConnection = _TryGetConnection();
		if (NULL != pDbConnection)
		{
			pDbConnection->incrementExecutionCount();
			return pDbConnection;
		}
	}
	
	LOG_ERROR<<"wait getConnection still NULL";

	return pDbConnection;	
}



IDbConnection* CDBConnectionPool::_TryGetConnection()
{

	IDbConnection* pDbConnectionGet = NULL;

	pDbConnectionGet = _GetConnectionFormIdleLst();
	if (NULL != pDbConnectionGet)
	{
		return pDbConnectionGet;
	}

	//add new con and get con for use
	while (true == _CanNewConnection())
	{
		_AcquireIncreNewConnections();

		pDbConnectionGet = _GetConnectionFormIdleLst();
		if (NULL != pDbConnectionGet)
		{
			return pDbConnectionGet;
		}
	}//while

	return pDbConnectionGet;	
}

void CDBConnectionPool::freeConnection( IDbConnection* pDbConnection )
{
	LstDBConnetionIterT iterLst;

	if (NULL == pDbConnection)
	{
		return;
	}

	//
	{
		ThreadGuard guard(m_lockLstDBConnection);

		iterLst = std::find(m_LstUsingDBConnetion.begin(), m_LstUsingDBConnetion.end(), pDbConnection);
		if (iterLst != m_LstUsingDBConnetion.end())
		{
			m_LstUsingDBConnetion.erase(iterLst);
			m_nUsingConNum--;

			//
			pDbConnection->decrementExecutionCount();
			m_LstIdleDBConnetion.push_back(pDbConnection);
			m_nIdleConNum++;
			_LogPoolInfo();
			LOG_DEBUG<<"m_SemaphoreGetConnection.post";
			
			m_SemaphoreGetConnection.post();
		}
		else
		{
			LOG_ERROR<<"freeConnection not find connection in UsingDBConnetionList"
				<<" "<<"m_LstUsingDBConnetion.size="<<m_LstUsingDBConnetion.size()
				<<" "<<"ConnectionHandle=0x"<<pDbConnection;
		}
	}

	return;
}

void CDBConnectionPool::removeUnHealthConnection()
{
	LstDBConnetionT lstDbConnecions;
	LstDBConnetionIterT iterLst;
	IDbConnection* pDbConnection = NULL;
	MapQueryDBConT mapQueryDBConTmp;

	_GetUnHealthConnections(lstDbConnecions);

	iterLst = lstDbConnecions.begin();
	while (iterLst != lstDbConnecions.end())
	{
		pDbConnection = (*iterLst);
	
		mapQueryDBConTmp.clear();
		_GetConnectionAllQuery(pDbConnection, mapQueryDBConTmp);
		CConnectionPoolMonitor::getInstance().addConnection(pDbConnection, mapQueryDBConTmp);
		mapQueryDBConTmp.clear();

		iterLst++;
	}//while
	lstDbConnecions.clear();

}



void CDBConnectionPool::_GetUnHealthConnections(LstDBConnetionT& lstDbConnecions)
{
	LstDBConnetionIterT iterLst;
	IDbConnection* pDbConnection = NULL;

	ThreadGuard guard(m_lockLstDBConnection);

	iterLst = m_LstIdleDBConnetion.begin();
	while (iterLst != m_LstIdleDBConnetion.end())
	{
		pDbConnection = (*iterLst);
		if (false == pDbConnection->isHealth())
		{
			lstDbConnecions.push_back(pDbConnection);
			m_LstIdleDBConnetion.erase(iterLst);
			iterLst = m_LstIdleDBConnetion.begin();
			m_nIdleConNum--;
			m_nTotalPoolNum--;
			_LogPoolInfo();	
		}
		else
		{
			iterLst++;
		}

	}//while


}

void CDBConnectionPool::exec( const SQLStatement& rSqlObj, IQueryAdapter*& pQueryAdapter, bool isQuery /*= false*/, int prefetch /*= 10 */ )
{
	IDbConnection* pDbConnection = NULL;
	pDbConnection = getConnection();
	if (NULL == pDbConnection)
	{
		LOG_ERROR<<"getConnection error!";
		return;
	}

	try
	{
		pDbConnection->exec(rSqlObj, pQueryAdapter, isQuery, prefetch);
	}
	catch (DataAccessException& e)
	{
		if (NULL != pQueryAdapter)
		{
			delete pQueryAdapter;
			pQueryAdapter = NULL;
		}
		freeConnection(pDbConnection);
		throw e;
	}

	if (NULL != pQueryAdapter)
	{
		ThreadGuard guard(m_lockMapActiveQueryDBCon);
		m_mapActiveQueryDBCon.insert(MapQueryDBConValueT(pQueryAdapter, pDbConnection));
		m_nActiveQueryDBConNum++;
	}

	freeConnection(pDbConnection);
}




void CDBConnectionPool::setDBPoolStatus(bool bIsHealth)
{
	m_bIsHealth = bIsHealth;

	LOG_DEBUG<<"CDBConnectionPool::setDBPoolStatus"
		<<" "<<"m_connectionStr="<<m_pDbStatusItem->getConnectionString()
		<<" "<<"m_bIsHealth="<<m_bIsHealth;


	_SetAllConnecionsStatus(m_bIsHealth);

	if (false == m_bIsHealth)
	{
		removeUnHealthConnection();
	}
}

bool CDBConnectionPool::getDBPoolStatus()
{

	return m_bIsHealth;
}

void CDBConnectionPool::cleanQuery( IQueryAdapter*& pQueryAdapter )
{
	MapQueryDBConIterT iterMap;
	IDbConnection* pDbConnection = NULL;

	if (NULL == pQueryAdapter)
	{
		LOG_WARNING<<"cleanQuery param error! NULL == pQuery";
		return;
	}

	{
		ThreadGuard guard(m_lockMapActiveQueryDBCon);

		iterMap = m_mapActiveQueryDBCon.find(pQueryAdapter);
		if (iterMap != m_mapActiveQueryDBCon.end())
		{
			pDbConnection = (iterMap->second);
			pDbConnection->cleanQuery(pQueryAdapter);

			m_mapActiveQueryDBCon.erase(iterMap);
			m_nActiveQueryDBConNum--;
		}
		else
		{
			CConnectionPoolMonitor::getInstance().cleanQuery(pQueryAdapter);
		}
	}
}


bool CDBConnectionPool::isQueryHealth( IQueryAdapter* pQueryAdapter )
{
	MapQueryDBConIterT iterMap;
	IDbConnection* pDbConnection = NULL;
	bool bIsQueryHealth = false;

	if (NULL == pQueryAdapter)
	{
		LOG_WARNING<<"cleanQuery param error! NULL == pQuery";
		bIsQueryHealth = false;
		return bIsQueryHealth;
	}

	{
		ThreadGuard guard(m_lockMapActiveQueryDBCon);

		iterMap = m_mapActiveQueryDBCon.find(pQueryAdapter);
		if (iterMap != m_mapActiveQueryDBCon.end())
		{
			bIsQueryHealth = true;
			return bIsQueryHealth;
		}
		else
		{
			bIsQueryHealth = CConnectionPoolMonitor::getInstance().isQueryHealth(pQueryAdapter);
		}
	}

	return bIsQueryHealth;
}
//////////////////////////////////////////////////////////////////////////
std::string CDBConnectionPool::getConnectionString()
{

	return m_pDbStatusItem->getConnectionString();
}

int CDBConnectionPool::getInitialPoolSize() const
{

	return m_nInitialPoolSize;
}

void CDBConnectionPool::setInitialPoolSize( int nInitialPoolSize )
{
	m_nInitialPoolSize = nInitialPoolSize;
}

int CDBConnectionPool::getMinPoolSize() const
{
	return m_nMinPoolSize;
}

void CDBConnectionPool::setAcquireIncrement( int nAcquireIncrement )
{
	m_nAcquireIncrement = nAcquireIncrement;
}


void CDBConnectionPool::setMaxIdleTime( long nMaxIdleTime )
{
	m_nMaxIdleTime = nMaxIdleTime;
}

void CDBConnectionPool::setAcquireRetryAttempts( int nAcquireRetryAttempts )
{
	m_nAcquireRetryAttempts = nAcquireRetryAttempts;
}

void CDBConnectionPool::setAcquireRetryDelay( int nAcquireRetryDelay )
{
	m_nAcquireRetryDelay = nAcquireRetryDelay;
}

int CDBConnectionPool::getAcquireRetryDelay() const
{
	return m_nAcquireRetryDelay;
}

int CDBConnectionPool::getAcquireRetryAttempts() const
{
	return m_nAcquireRetryAttempts;
}

int CDBConnectionPool::getAcquireIncrement() const
{
	return m_nAcquireIncrement;
}

int CDBConnectionPool::getMaxPoolSize() const
{
	return m_nMaxPoolSize;
}

long CDBConnectionPool::getMaxIdleTime() const
{
	return m_nMaxIdleTime;
}

void CDBConnectionPool::_LogPoolInfo()
{
	LOG_DEBUG<<"m_connectionStr="<<m_pDbStatusItem->getConnectionString()
		<<" "<<"m_nIdleConNum="<<m_nIdleConNum
		<<" "<<"m_nUsingConNum="<<m_nUsingConNum
		<<" "<<"m_nTotalPoolNum="<<m_nTotalPoolNum;
		
}
NS_END(TA_Base_Core)




















