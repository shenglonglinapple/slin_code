#ifndef __I_DB_CONNECTION_HH__
#define __I_DB_CONNECTION_HH__

#include "SQLData.h"

class IQueryAdapter;

class IDbConnection
{
public:

	IDbConnection()
	{
		return;
	}

	virtual ~IDbConnection() 
	{
		return;
	}

	virtual bool isAnyQueryActive( unsigned long ulMaxTimeoutInSecs ) = 0;

	virtual std::string getConnectionString() const = 0;

	virtual void open()  = 0;

	virtual bool isOpen()  = 0;

	virtual void exec(const CSQLData& sqlData, IQueryAdapter*& pQueryAdapter, bool isQuery = false, int prefetch = 10) = 0;

	virtual void incrementExecutionCount() = 0;

	virtual void decrementExecutionCount() = 0;

	virtual int getExecutionCount()  = 0;

	virtual bool isHealth()  = 0;

	virtual void setConStatus(bool bIsHealth)  = 0;

	virtual void cleanQuery( IQueryAdapter*& pQueryAdapter ) = 0;

};//IDbConnection



#endif /// __I_DB_CONNECTION_HH__


