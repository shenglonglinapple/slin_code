#ifndef __CLASS_CONNECTION_POOL_MONITOR_HH__
#define __CLASS_CONNECTION_POOL_MONITOR_HH__

#include <vector>
#include <list>
#include <queue>
#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/DataAccessException.h"

#include "core/threads/src/ReEntrantThreadLockable.h"
#include "core/DataAccess/src/DbStatusItem.h"
#include "core/DataAccess/src/SQLStatement.h"
#include "core/threads/src/BoostThread.h"
#include "core/threads/src/Condition.h"

#include "core/DataAccess/src/IDbConnection.h"
#include "core/DataAccess/src/IDbConnectionPool.h"
#include "core/DataAccess/src/DBConnectionPool.h"

NS_BEGIN(TA_Base_Core)

class CAWorkTime;

class CConnectionPoolMonitor : public TA_Base_Core::CBoostThread
{
private:
	enum EThreadJobState
	{
		JobState_Begin,
		JobState_Init,
		JobState_MontinorConnectionPool,		
		JobState_CheckWaitingQueue,
		JobState_MontinorConnections,		
		JobState_UnInit,
		JobState_End,
	};
public:
	static CConnectionPoolMonitor& getInstance();
	static void removeInstance();
	virtual ~CConnectionPoolMonitor();
private:
	CConnectionPoolMonitor();
	CConnectionPoolMonitor(CConnectionPoolMonitor & );
	CConnectionPoolMonitor & operator = (CConnectionPoolMonitor & );
	static CConnectionPoolMonitor* m_instance;
	static TA_Base_Core::ReEntrantThreadLockable m_singletonLock;

public:

	/**
	* run
	*
	* Cycles through the connections in its vector and deletes the ones
	* that are not being used.
	*/

	virtual void run();


	/**
	* terminate
	*
	* Waits until an appropriate break and then stop running the thread.
	*/

	virtual void terminate();

	void addConnection( IDbConnection* pDbConnection, CDBConnectionPool::MapQueryDBConT& mapQueryDBCon );
	void cleanQuery( IQueryAdapter*& pQuery );
	bool isQueryHealth( IQueryAdapter* pQueryAdapter );
	void removeUnHealthConnections(int nSeconds);

private:
	void  _ThreadJob();
	void  _ProcessUserTerminate(); 

private:
	void  _Procees_Init();	
	void  _Procees_MontinorConnectionPool();
	void  _Procees_CheckWaitingQueue();
	void  _Procees_MontinorConnections();
	void  _Procees_UnInit();
private:
	void _AddMonitoredConnectons();
	void _AddMonitorQueryDBCon(CDBConnectionPool::MapQueryDBConT& mapQueryDBCon );
	void _CleanConnectionAllQueryInMap(IDbConnection* pDbConnection);
	void _DestoryConnection(IDbConnection* pDbConnection);
private:
	bool	m_toTerminate;
	EThreadJobState  m_nThreadJobState;
	// Used to pause the thread execution so that it can be terminated.
	TA_Base_Core::Condition m_conditionTimer;


private:
	// These are the connections that are being monitored.
	std::list< IDbConnection* > m_monitoredConnections;

	// this lock provide thread safety for adding/removing items
	// from the vectors of monitored and waiting connections.
	TA_Base_Core::ReEntrantThreadLockable m_lockMonitoredConnections;


	// These are the connections that should be added to the 
	// vector of monitored connections in the next pass.  This
	// vector is treated like a queue, however a queue cannot be
	// used because we need to traverse through it.
	std::list< IDbConnection* >  m_waitingQueue;

	// this lock provide thread safety for adding/removing items
	// from the vectors of monitored and waiting connections.
	TA_Base_Core::ReEntrantThreadLockable m_lockWaitingQueue;


	TA_Base_Core::ReEntrantThreadLockable  m_lockMapMonitroQueryDBCon;
	CDBConnectionPool::MapQueryDBConT m_mapMonitorQueryDBCon;


	// This value determines how often the database connections 
	// should be reaped (refreshed).  It is in minutes.
	int m_reapIntervalInMins;
	int m_reapIntervalInMillSeconds;
	int m_reapIntervalInSeconds;


	//
	CAWorkTime*   m_pWorkTimeMonitorConnecionPool;



};


NS_END(TA_Base_Core)

#endif // #define __CLASS_CONNECTION_POOL_MONITOR_HH__















