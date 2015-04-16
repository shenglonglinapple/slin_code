#ifndef DBCONNECTIONPOOL_H
#define DBCONNECTIONPOOL_H

#include "IDbConnectionPool.h"
#include "core/threads/src/ReEntrantThreadLockable.h"
#include "core/threads/src/TASemaphore.h"
#include "core/threads/src/ThreadGuard.h"
#include "core/DataAccess/src/DataAccessException.h"

#include <list>

NS_BEGIN(TA_Base_Core)

class IQueryAdapter;
class IDbConnection;

class CDBConnectionPool : public IDbConnectionPool
{
public:
	typedef   std::list<IDbConnection*>               LstDBConnetionT;
	typedef   std::list<IDbConnection*>::iterator     LstDBConnetionIterT;

	typedef   std::map<IQueryAdapter*, IDbConnection*>             MapQueryDBConT;
	typedef   std::map<IQueryAdapter*, IDbConnection*>::iterator   MapQueryDBConIterT;
	typedef   std::map<IQueryAdapter*, IDbConnection*>::value_type   MapQueryDBConValueT;

public:
	CDBConnectionPool(const CDbStatusItem& objDbStatusItem, int nMinPoolSize, int nMaxPoolSize);
	virtual ~CDBConnectionPool();
public:
	/*get one Connection, timeout (millseconds )*/
	IDbConnection*  getConnection(long nTimeOut=1000);

	/*free one Connection*/
	void freeConnection(IDbConnection* pDbConnection);

	/*free all Connection*/

	void removeUnHealthConnection();
 
	void setDBPoolStatus(bool bIsHealth);

	bool getDBPoolStatus();

public:
	void exec(
		const SQLStatement& rSqlObj, 
		IQueryAdapter*& pQueryAdapter, 
		bool isQuery = false, 
		int prefetch = 10
		);

	void cleanQuery( IQueryAdapter*& pQueryAdapter );

	bool isQueryHealth(IQueryAdapter* pQueryAdapter);

public:
	std::string getConnectionString();
	int getInitialPoolSize() const;
	void setInitialPoolSize(int nInitialPoolSize);
	int getMinPoolSize() const;
	int getAcquireIncrement() const;
	void setAcquireIncrement(int nAcquireIncrement);
	int getMaxPoolSize() const;
	long getMaxIdleTime() const;
	void setMaxIdleTime(long nMaxIdleTime);
	int getAcquireRetryAttempts() const;
	void setAcquireRetryAttempts(int nAcquireRetryAttempts);
	int getAcquireRetryDelay() const;
	void setAcquireRetryDelay(int nAcquireRetryDelay);

private:
	void _InitPool();
	void _SetAllConnecionsStatus(bool bISHealth);
	void _CreateConnection();
	void _GetConStrInfo();
	void _DestoryConnection(IDbConnection* pDbConnection);
	IDbConnection* _GetConnectionFormIdleLst();
	void _AcquireIncreNewConnections();
	bool _CanNewConnection();
	IDbConnection* _TryGetConnection();
private:
	void _LogPoolInfo();
	void _GetConnectionAllQuery(IDbConnection* pDbConnection, MapQueryDBConT& mapQueryDBCon);
	void _GetUnHealthConnections(LstDBConnetionT& lstDbConnecions);
protected:
	// Database connection data	
	CDbStatusItem* m_pDbStatusItem;

	/*first init connection size*/
	int	m_nInitialPoolSize;
	/*connection min size in pool*/
	int m_nMinPoolSize;
	/*acquire once connection size*/
	int m_nAcquireIncrement;
	/*max connections in pool*/
	int m_nMaxPoolSize;
	/*connection idle time (seconds), idle time > maxIdletime pool will close this connection*/
	long m_nMaxIdleTime;
	/*acquire one connection retry times eg.3 */
	int m_nAcquireRetryAttempts;
	/*acquire one connection each retry delay (millseconds) eg.5 */
	int m_nAcquireRetryDelay;

	bool m_bIsHealth;
protected:
	TA_Base_Core::ReEntrantThreadLockable  m_lockLstDBConnection;
	LstDBConnetionT  m_LstIdleDBConnetion;
	int m_nIdleConNum;
	int m_nTotalPoolNum;


	LstDBConnetionT  m_LstUsingDBConnetion;
	int m_nUsingConNum;


	TA_Base_Core::ReEntrantThreadLockable  m_lockMapActiveQueryDBCon;
	MapQueryDBConT m_mapActiveQueryDBCon;
	int m_nActiveQueryDBConNum;


private:
	TA_Base_Core::ReEntrantThreadLockable  m_mutexGetConnection;
	TA_Base_Core::CTASemaphore m_SemaphoreGetConnection;



};

NS_END(TA_Base_Core)

#endif /// DBCONNECTIONPOOL_H




