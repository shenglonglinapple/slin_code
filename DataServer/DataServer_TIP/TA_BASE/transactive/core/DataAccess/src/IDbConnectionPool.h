#ifndef IDBCONNECTIONPOOL_H
#define IDBCONNECTIONPOOL_H


#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/DataAccessException.h"

#include "core/threads/src/ReEntrantThreadLockable.h"
#include "core/DataAccess/src/DbStatusItem.h"
#include "core/DataAccess/src/SQLStatement.h"


#include <list>

NS_BEGIN(TA_Base_Core)

class IQueryAdapter;
class IDbConnection;

class IDbConnectionPool
{
public:
	/*get one Connection, timeout (millseconds )*/
	virtual IDbConnection*  getConnection(long nTimeOut) = 0;//pop front

	/*free one Connection*/
	virtual void freeConnection(IDbConnection* pDbCon) = 0;//add to nail

	/*free all Connection*/

	virtual void removeUnHealthConnection() = 0;

	virtual void setDBPoolStatus(bool bIsHealth) = 0;

	virtual bool getDBPoolStatus() = 0;
public:
	virtual  void exec(
		const SQLStatement& rSqlObj, 
		IQueryAdapter*& pQueryAdapter, 
		bool isQuery = false, 
		int prefetch = 10
		) = 0;

	virtual void cleanQuery( IQueryAdapter*& pQuery ) = 0;
	virtual bool isQueryHealth(IQueryAdapter* pQueryAdapter) = 0;

	virtual ~IDbConnectionPool() 
	{

	};

public:
	virtual std::string getConnectionString() { return std::string(); }
	virtual int getInitialPoolSize() const {return 0;}
	virtual void setInitialPoolSize(int nInitialPoolSize){}
	virtual int getMinPoolSize() const {return 0;}
	virtual int getAcquireIncrement() const{return 0;}
	virtual void setAcquireIncrement(int nAcquireIncrement){}
	virtual int getMaxPoolSize() const{return 0;}
	virtual long getMaxIdleTime() const{return 0;}
	virtual void setMaxIdleTime(long nMaxIdleTime){}
	virtual int getAcquireRetryAttempts() const{return 0;}
	virtual void setAcquireRetryAttempts(int nAcquireRetryAttempts){}
	virtual int getAcquireRetryDelay() const{return 0;}
	virtual void setAcquireRetryDelay(int nAcquireRetryDelay){}

};

NS_END(TA_Base_Core)

#endif /// IDBCONNECTIONPOOL_H










