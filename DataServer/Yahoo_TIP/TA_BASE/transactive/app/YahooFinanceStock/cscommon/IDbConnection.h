#ifndef __I_DB_CONNECTION_HH__
#define __I_DB_CONNECTION_HH__

#include <QtCore/QList>
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
	virtual QString getConnectionString() const = 0;
	virtual void open()  = 0;
	virtual bool isOpen()  = 0;
	virtual qint32 execQuery(const CSQLData& sqlData, IQueryAdapter*& pQueryAdapter) = 0;
	virtual qint32 execModify( const CSQLData& sqlData ) = 0;
	virtual qint32 execModifyBatch( const CSQLData& sqlData, const QList<QVariantList*>& LstData) = 0;
	virtual qint32 commitTransaction() = 0;
	virtual qint32 startTransaction() = 0;
	virtual void incrementExecutionCount() = 0;
	virtual void decrementExecutionCount() = 0;
	virtual qint32 getExecutionCount()  = 0;
	virtual bool isHealth()  = 0;
	virtual void setConStatus(bool bIsHealth)  = 0;
	virtual void cleanQuery( IQueryAdapter*& pQueryAdapter ) = 0;

};//IDbConnection



#endif /// __I_DB_CONNECTION_HH__


