#ifndef __CLASS__CONNECTION_POOL_MANAGER_HH__
#define __CLASS__CONNECTION_POOL_MANAGER_HH__


#include <string>
#include <vector>
#include <map>
#include <list>

#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/DataAccessException.h"

#include "core/threads/src/ReEntrantThreadLockable.h"
#include "core/DataAccess/src/DbStatusItem.h"
#include "core/DataAccess/src/SQLStatement.h"


NS_BEGIN(TA_Base_Core)

class IDbConnectionPool;
class IQueryAdapter;

class CConnectionPoolManager
{
public:
	static CConnectionPoolManager& getInstance();
	static void removeInstance();
	virtual ~CConnectionPoolManager();

public:
	int createConnectionPool(CDbStatusItem* pDbStatusItem);

	/*
	DataType,DataAction,DBType,Database,User,Password,Hostname,DBType,Database,User,Password,Hostname,
	Event_Ad,Read,Mysql,tra_occ,IT271350_5,IT271350_5,192.168.123.43,Oracle,TRANSACT,IT271350_5,IT271350_5,
	*/
	void open( CDbStatusItem* pDbStatusItem );
	bool isOpen( CDbStatusItem* pDbStatusItem );
	void close( CDbStatusItem* pDbStatusItem );
	void closeAll();
	void removeUnHealthConnection();

	void setPoolUnHealth( CDbStatusItem* pDbStatusItem );
public:
	IQueryAdapter* exec( CDbStatusItem* pDbStatusItem, const SQLStatement& rSqlObj, int numRows );

	void cleanQuery( CDbStatusItem* pDbStatusItem, IQueryAdapter*& pQuery );
	bool isQueryHealth( CDbStatusItem* pDbStatusItem, IQueryAdapter* pQueryAdapter );
	void exec( CDbStatusItem* pDbStatusItem, const SQLStatement& rSqlObj );
private:
	typedef   std::map<std::string, IDbConnectionPool*>               MapDBConnectionT;
	typedef   std::map<std::string, IDbConnectionPool*>::iterator     MapDBConnectionIterT;
	typedef   std::map<std::string, IDbConnectionPool*>::value_type   MapDBConnectionValueT;

private:
	bool _ConnectionExists(CDbStatusItem* pDbStatusItem);
	IDbConnectionPool* _GetConnectionPool( CDbStatusItem* pDbStatusItem );
	void _SetPoolStatus(CDbStatusItem* pDbStatusItem, bool bIsHealth);
private:
	TA_Base_Core::ReEntrantThreadLockable m_mutexCreatePool;
	TA_Base_Core::ReEntrantThreadLockable m_lockMapDbConnectionPools;
	MapDBConnectionT m_mapDbConnectionPools;

private:
	CConnectionPoolManager();
	CConnectionPoolManager(CConnectionPoolManager & );
	CConnectionPoolManager & operator = (CConnectionPoolManager & );
	static CConnectionPoolManager* m_instance;
	static TA_Base_Core::ReEntrantThreadLockable m_singletonLock;

private:
	unsigned long m_queryRetryInterval;	//added by hongzhi, make it a class member instead of runparam
	int  m_nMaxPoolSize;  // the maximum number of connections that can be opened in the pool
	int  m_nMinPoolSize;  // the minimum number of connections to be opened when the pool is created
	int  m_nRemoveUnHealthConTime;// 300 seconds
};

NS_END(TA_Base_Core)


#endif // __CLASS__CONNECTION_POOL_MANAGER_HH__



