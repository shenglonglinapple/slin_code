#ifndef __CLASS__DATABASE_FACTORY_HH__
#define __CLASS__DATABASE_FACTORY_HH__

#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/DataAccessException.h"
#include "core/DataAccess/src/SQLStatement.h"
#include "core/threads/src/ReEntrantThreadLockable.h"

NS_BEGIN(TA_Base_Core)

class IDbDataOper;

class CDatabaseFactory
{
public:
	static CDatabaseFactory& getInstance();
	static void removeInstance();
	virtual ~CDatabaseFactory();
private:
	CDatabaseFactory();
	CDatabaseFactory(CDatabaseFactory & );
	CDatabaseFactory & operator = (CDatabaseFactory & );
	static CDatabaseFactory* m_instance;
	static TA_Base_Core::ReEntrantThreadLockable m_singletonLock;
public:
	void executeModification(EDataTypes nDataType, const SQLStatement& objSqlStatement);
	IDbDataOper* executeQuery(EDataTypes nDataType, const SQLStatement& objSqlStatement,const int numRows = 100);

	//bool moreData(IDbDataOper*& returnData);


};

NS_END(TA_Base_Core)


#endif // __CLASS__CONNECTION_POOL_MANAGER_HH__



