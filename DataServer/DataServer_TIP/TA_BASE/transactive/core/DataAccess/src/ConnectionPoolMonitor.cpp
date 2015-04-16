#include "ConnectionPoolMonitor.h"

#include "core/threads/src/ThreadGuard.h"
#include "core/CppConfigLib/src/RunParams.h"
#include "ConnectionPoolManager.h"
#include "core/utilities/src/WorkTime.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)

// Definition of static member variables.
TA_Base_Core::ReEntrantThreadLockable CConnectionPoolMonitor::m_singletonLock;
CConnectionPoolMonitor* CConnectionPoolMonitor::m_instance = NULL;



CConnectionPoolMonitor& CConnectionPoolMonitor::getInstance()
{
	ThreadGuard guard(m_singletonLock);

	if ( NULL == m_instance )
	{
		m_instance = new CConnectionPoolMonitor();
		m_instance->start();
	}

	return *m_instance;
}


void CConnectionPoolMonitor::removeInstance()
{

	ThreadGuard guard(m_singletonLock);

	if ( m_instance != NULL )
	{
		m_instance->terminateAndWait();
		delete m_instance;
		m_instance = 0;
	}
}


CConnectionPoolMonitor::CConnectionPoolMonitor()
{

	m_reapIntervalInMins = 0;
	m_reapIntervalInSeconds = 0;
	m_reapIntervalInMillSeconds = 0;
	m_pWorkTimeMonitorConnecionPool = NULL;
	m_pWorkTimeMonitorConnecionPool = new CWorkTimeLock();
	m_pWorkTimeMonitorConnecionPool->workBegin();
	m_toTerminate = false;
	m_nThreadJobState = JobState_Begin;

}


/** 
* ~ConnectionReaper
*
* Destructor that deletes any left over OCIConnection objects from 
* the vector of old connections.
*/

CConnectionPoolMonitor::~CConnectionPoolMonitor() 
{

	_Procees_UnInit();
	if (NULL != m_pWorkTimeMonitorConnecionPool)
	{
		delete m_pWorkTimeMonitorConnecionPool;
		m_pWorkTimeMonitorConnecionPool = NULL;
	}
}


/**
* terminate
*
* Waits until an appropriate break and then stop running the thread.
*/

void CConnectionPoolMonitor::terminate()
{		

	// wake up!  Time to die!
	m_toTerminate = true;
	m_conditionTimer.signal();
}

void CConnectionPoolMonitor::addConnection( IDbConnection* pDbConnection, CDBConnectionPool::MapQueryDBConT& mapQueryDBCon )
{

	int nQueerySize = 0;
	nQueerySize = (int)mapQueryDBCon.size();

	{
		ThreadGuard guard(m_lockWaitingQueue);

		m_waitingQueue.push_back(pDbConnection);
	}

	if (false == mapQueryDBCon.empty())
	{
		_AddMonitorQueryDBCon(mapQueryDBCon);		
	}

	LOG_DEBUG<<"add one ConnectionHandle to WaitingQueue"
		<<" "<<"ConnectionHandle=0x"<<pDbConnection
		<<" "<<"nQueerySize="<<nQueerySize;

	m_conditionTimer.signal();
}


void CConnectionPoolMonitor::cleanQuery( IQueryAdapter*& pQuery )
{

	CDBConnectionPool::MapQueryDBConIterT iterMap;
	IQueryAdapter* pQueryAdapterInMap = NULL;
	IDbConnection* pDbConnectionInMap = NULL;

	ThreadGuard guard(m_lockMapMonitroQueryDBCon);

	iterMap = m_mapMonitorQueryDBCon.find(pQuery);

	if (iterMap != m_mapMonitorQueryDBCon.end())
	{
		pQueryAdapterInMap = (iterMap->first);
		pDbConnectionInMap = (iterMap->second);

		pDbConnectionInMap->cleanQuery(pQuery);

		pQuery = NULL;

		m_mapMonitorQueryDBCon.erase(iterMap);//

	}
	else
	{
		LOG_WARNING<<"try to clean one Query "
			<<" "<<"QueryHandle=0x"<<pQuery
			<<" "<<"but its connection have been deleted, so just set NULL value";

		pQuery = NULL;
	}
}

bool CConnectionPoolMonitor::isQueryHealth( IQueryAdapter* pQueryAdapter )
{

	CDBConnectionPool::MapQueryDBConIterT iterMap;
	IQueryAdapter* pQueryAdapterInMap = NULL;
	IDbConnection* pDbConnectionInMap = NULL;
	bool bIsQueryHealth = false;

	ThreadGuard guard(m_lockMapMonitroQueryDBCon);

	iterMap = m_mapMonitorQueryDBCon.find(pQueryAdapter);
	if (iterMap != m_mapMonitorQueryDBCon.end())
	{
		bIsQueryHealth = true;
		return bIsQueryHealth;
	}
	else
	{
		LOG_ERROR<<"isQueryHealth "
			<<" "<<"QueryHandle=0x"<<pQueryAdapter
			<<" "<<"its connection and all QueryHandles in this connection have been deleted by timeout";


		bIsQueryHealth = false;
	}

	return bIsQueryHealth;
}



//////////////////////////////////////////////////////////////////////////

/**
* run
*
* Sleeps for the reap interval, then tells the OCIAccess object to 
* refresh its connections.  This thread then monitors the old connections
* and deletes them when they are no longer being used.
*/

void CConnectionPoolMonitor::run()
{

	while( !m_toTerminate )
	{
		_ThreadJob();
		//TA_Base_Core::Thread::sleep(1000);
		m_conditionTimer.timedWait(1000);
	}

	_ProcessUserTerminate();
}
void CConnectionPoolMonitor::_ThreadJob()
{

	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		m_nThreadJobState = JobState_Init;
		break;
	case JobState_Init:
		_Procees_Init();
		m_nThreadJobState = JobState_MontinorConnectionPool;
		break;
	case JobState_MontinorConnectionPool:
		_Procees_MontinorConnectionPool();
		m_nThreadJobState = JobState_CheckWaitingQueue;
		break;
	case JobState_CheckWaitingQueue:
		_Procees_CheckWaitingQueue();
		m_nThreadJobState = JobState_MontinorConnections;
		break;
	case JobState_MontinorConnections:
		_Procees_MontinorConnections();
		m_nThreadJobState = JobState_MontinorConnectionPool;
		break;
	case JobState_UnInit:
		_Procees_UnInit();
		m_nThreadJobState = JobState_End;
		break;
	case JobState_End:
		break;
	default:
		break;
	}
}

void CConnectionPoolMonitor::_ProcessUserTerminate()
{

	_Procees_UnInit();
	m_nThreadJobState = JobState_End;

}

void CConnectionPoolMonitor::_Procees_Init()
{

	m_reapIntervalInMins = 0;
	m_reapIntervalInSeconds = 0;
	m_reapIntervalInMillSeconds = 0;
	// Set the reap interval to the value specified in the RunParams.
	if ( TA_Base_Core::CRunParams::getInstance().isSetParam( "DbReapInterval" ) )
	{
		m_reapIntervalInMins = atoi( TA_Base_Core::CRunParams::getInstance().getStringParamValue( "DbReapInterval" ).c_str() );
	}

	// The valid range for the reap interval is 10 mins to 10080 mins (7 days).
	// If no value is specified or if the value is out of the given range,
	// set the default reap interval to 120 minutes => 2 hours.
	if ( ( m_reapIntervalInMins < 10 ) || ( m_reapIntervalInMins > 10080 ) )
	{    
		//m_reapIntervalInMins = 120;//minutes
		m_reapIntervalInMins = DEF_CON_MAX_IDLETIME / 60;//120 minutes
	}

	LOG_ERROR<<"ConnectionPoolMonitor m_reapIntervalInMins="<<m_reapIntervalInMins<<" "<<"minutes";

	m_reapIntervalInSeconds = m_reapIntervalInMins * 60;//seconds
	m_reapIntervalInMillSeconds = m_reapIntervalInMins * 60* 1000;//millsecs

}

void CConnectionPoolMonitor::_Procees_MontinorConnectionPool()
{
	BigInt64 nMonitorPoolNotWorkTimeSecconds = 0;

	nMonitorPoolNotWorkTimeSecconds = m_pWorkTimeMonitorConnecionPool->getNotWorkTimeSeconds(); 
	if (nMonitorPoolNotWorkTimeSecconds > m_reapIntervalInSeconds)
	{
		LOG_DEBUG<<"nMonitorPoolNotWorkTimeSecconds="<<nMonitorPoolNotWorkTimeSecconds
			<<" "<<">"
			<<" "<<"m_reapIntervalInSeconds="<<m_reapIntervalInSeconds
			<<" "<<"then run CConnectionPoolManager::removeUnHealthConnection()";


		CConnectionPoolManager::getInstance().removeUnHealthConnection();
		m_pWorkTimeMonitorConnecionPool->workBegin();
		m_reapIntervalInSeconds = m_reapIntervalInMins * 60;//seconds
	}

}

void  CConnectionPoolMonitor::_Procees_CheckWaitingQueue()
{

	_AddMonitoredConnectons();
}

void CConnectionPoolMonitor::_Procees_MontinorConnections()
{
	ThreadGuard guard(m_lockMonitoredConnections);

	std::list< IDbConnection* >::iterator  iterList;
	IDbConnection* pDbConnection = NULL;
	long nQueryMaxIdleTime = 0;
	nQueryMaxIdleTime = DEF_QUERY_MAX_IDLETIME;

	iterList = m_monitoredConnections.begin();
	while (iterList != m_monitoredConnections.end())
	{
		pDbConnection = (*iterList);
		if (pDbConnection->isAnyQueryActive(nQueryMaxIdleTime))
		{
			iterList++;
		}
		else
		{
			_DestoryConnection(pDbConnection);
 			m_monitoredConnections.erase(iterList);
 			iterList = m_monitoredConnections.begin();

			LOG_DEBUG<<"after Destory one Connection"
				<<" "<<"ConnectionHandle=0x"<<pDbConnection
				<<" "<<"m_monitoredConnections.size="<<m_monitoredConnections.size();

			pDbConnection = NULL;

		}
		
	}//while

}

void CConnectionPoolMonitor::_Procees_UnInit()
{

	{
		_AddMonitoredConnectons();
	}


	{
		ThreadGuard guard(m_lockMonitoredConnections);

		std::list< IDbConnection* >::iterator  iterList;
		IDbConnection* pDbConnection = NULL;

		iterList = m_monitoredConnections.begin();
		while (iterList != m_monitoredConnections.end())
		{
			pDbConnection = (*iterList);

			_DestoryConnection(pDbConnection);
			m_monitoredConnections.erase(iterList);
			iterList = m_monitoredConnections.begin();

			LOG_DEBUG<<"after Destory one Connection"
				<<" "<<"ConnectionHandle=0x"<<pDbConnection
				<<" "<<"m_monitoredConnections.size="<<m_monitoredConnections.size();

			pDbConnection = NULL;

		}//while
		m_monitoredConnections.clear();
	}

}


void  CConnectionPoolMonitor::_AddMonitoredConnectons()
{
	std::list< IDbConnection* >::iterator  iterList;
	IDbConnection* pDbConnection = NULL;

	//add to moniter
	ThreadGuard guardWaitingQueue(m_lockWaitingQueue);
	ThreadGuard guardMonitor(m_lockMonitoredConnections);
	iterList = m_waitingQueue.begin();
	while (iterList != m_waitingQueue.end())
	{
		pDbConnection = (*iterList);
		m_monitoredConnections.push_back(pDbConnection);


		LOG_DEBUG<<"move one ConnectionHandle from WaitingQueue to MonitorConnectionPool"
			<<" "<<"ConnectionHandle=0x"<<pDbConnection
			<<" "<<"m_monitoredConnections.size="<<m_monitoredConnections.size();

		iterList++;
	}
	m_waitingQueue.clear();

}



void CConnectionPoolMonitor::_AddMonitorQueryDBCon(CDBConnectionPool::MapQueryDBConT& mapQueryDBCon )
{

	CDBConnectionPool::MapQueryDBConIterT iterMap;
	IQueryAdapter* pQueryAdapter = NULL;
	IDbConnection* pDbConnection = NULL;
	int nQueryHandleCount = 0;

	ThreadGuard guard(m_lockMapMonitroQueryDBCon);


	iterMap = mapQueryDBCon.begin();
	while (iterMap != mapQueryDBCon.end())
	{
		pQueryAdapter = (iterMap->first);
		pDbConnection = (iterMap->second);

		m_mapMonitorQueryDBCon.insert(CDBConnectionPool::MapQueryDBConValueT(pQueryAdapter, pDbConnection));
		nQueryHandleCount++;

		LOG_DEBUG<<"add one QueryHandle to MonitorQueuePool "
			<<" "<<"ConnectionHandle=0x"<<pDbConnection
			<<" "<<"QueryHandle=0x"<<pQueryAdapter;

		iterMap++;
	}

	mapQueryDBCon.clear();

	LOG_DEBUG<<"total add"
		<<" "<<"nQueryHandleCount="<<nQueryHandleCount
		<<" "<<"QueryHandles to MonitorQueuePool"
		<<" "<<"ConnectionHandle=0x"<<pDbConnection
		<<" "<<"m_mapMonitorQueryDBCon.size="<<m_mapMonitorQueryDBCon.size();


}

void CConnectionPoolMonitor::_DestoryConnection(IDbConnection* pDbConnection)
{
	std::string strConnection;
	if (NULL == pDbConnection)
	{
		return;
	}

	_CleanConnectionAllQueryInMap(pDbConnection);

	strConnection = pDbConnection->getConnectionString();

	LOG_DEBUG<<"begin Destory one Connection"
		<<" "<<"strConnection=0x"<<strConnection
		<<" "<<"ConnectionHandle=0x"<<pDbConnection;


	delete pDbConnection;


	LOG_DEBUG<<"end Destory one Connection"
		<<" "<<"strConnection=0x"<<strConnection
		<<" "<<"ConnectionHandle=0x"<<pDbConnection;

	pDbConnection = NULL;
}

void CConnectionPoolMonitor::_CleanConnectionAllQueryInMap(IDbConnection* pDbConnection)
{
	CDBConnectionPool::MapQueryDBConIterT iterMap;
	IQueryAdapter* pQueryAdapterInMap = NULL;
	IDbConnection* pDbConnectionInMap = NULL;
	int nQueryHandleCount = 0;

	ThreadGuard guard(m_lockMapMonitroQueryDBCon);


	iterMap = m_mapMonitorQueryDBCon.begin();
	while (iterMap != m_mapMonitorQueryDBCon.end())
	{
		pQueryAdapterInMap = (iterMap->first);
		pDbConnectionInMap = (iterMap->second);

		if (pDbConnectionInMap == pDbConnection)
		{
			pDbConnectionInMap->cleanQuery(pQueryAdapterInMap);

			LOG_DEBUG<<"delete one QueryHandle"
				<<" "<<"ConnectionHandle=0x"<<pDbConnection
				<<" "<<"QueryHandle=0x"<<pQueryAdapterInMap;

			nQueryHandleCount++;

			m_mapMonitorQueryDBCon.erase(iterMap);
			iterMap = m_mapMonitorQueryDBCon.begin();
		}
		else
		{
			iterMap++;
		}		
	}

	LOG_DEBUG<<"total delete"
		<<" "<<"nQueryHandleCount="<<nQueryHandleCount
		<<" "<<"ConnectionHandle=0x"<<pDbConnection
		<<" "<<"m_mapMonitorQueryDBCon.size="<<m_mapMonitorQueryDBCon.size();

}

void CConnectionPoolMonitor::removeUnHealthConnections( int nSeconds )
{
	BigInt64 nMonitorPoolNotWorkTimeSecconds = 0;
	nMonitorPoolNotWorkTimeSecconds = m_pWorkTimeMonitorConnecionPool->getNotWorkTimeSeconds();
	m_reapIntervalInSeconds = nMonitorPoolNotWorkTimeSecconds + nSeconds;
	LOG_DEBUG<<"CConnectionPoolMonitor will do removeUnHealthConnections after "
		<<" "<<nSeconds
		<<" "<<"Seconds";

}

NS_END(TA_Base_Core)



