#include "DatabaseFactory.h"


#include "core/threads/src/ThreadGuard.h"

#include "core/DataAccess/src/SQLCode.h"
#include "core/DataAccess/src/DbStatusItem.h"
#include "core/DataAccess/src/DbStatusManager.h"
#include "core/DataAccess/src/ConnectionPoolManager.h"
#include "core/DataAccess/src/DbDataOperImp.h"



#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;


NS_BEGIN(TA_Base_Core)


// Definition of static member variables.
TA_Base_Core::ReEntrantThreadLockable CDatabaseFactory::m_singletonLock;
CDatabaseFactory* CDatabaseFactory::m_instance = NULL;


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                         Construction/Destruction                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

CDatabaseFactory& CDatabaseFactory::getInstance()
{
	ThreadGuard guard(m_singletonLock);


	if ( NULL == m_instance )
	{
		m_instance = new CDatabaseFactory();
	}

	return *m_instance;
}


void CDatabaseFactory::removeInstance()
{

	ThreadGuard guard(m_singletonLock);

	if ( m_instance != NULL )
	{
		delete m_instance;
		m_instance = NULL;
	}
}

CDatabaseFactory::CDatabaseFactory()
{
	TA_Base_Core::SQLCode::getInstance();
	TA_Base_Core::CDbStatusManager::getInstance();
	TA_Base_Core::CConnectionPoolManager::getInstance();

}

CDatabaseFactory::~CDatabaseFactory()
{
	TA_Base_Core::CConnectionPoolManager::removeInstance();
	TA_Base_Core::CDbStatusManager::removeInstance();
	TA_Base_Core::SQLCode::removeInstance();

}

void CDatabaseFactory::executeModification( EDataTypes nDataType, const SQLStatement& objSqlStatement)
{
	CDbStatusItem* pDbStatusItem = NULL;
	TA_Base_Core::CDbStatusManager::getInstance();
	TA_Base_Core::CDbStatusManager::getInstance().initDbStatusByCfg();
	pDbStatusItem = TA_Base_Core::CDbStatusManager::getInstance().getDbStatusItem(nDataType);
	
	if (NULL == pDbStatusItem)
	{
		LOG_ERROR<<"CDbStatusManager::getInstance().getDbStatusItem(nDataType) return NULL";
	}
	TA_Base_Core::CConnectionPoolManager::getInstance().createConnectionPool(pDbStatusItem);
	TA_Base_Core::CConnectionPoolManager::getInstance().exec(pDbStatusItem, objSqlStatement);
}

IDbDataOper* CDatabaseFactory::executeQuery( EDataTypes nDataType, const SQLStatement& objSqlStatement, const int numRows /*= 100*/ )
{
	CDbStatusItem* pDbStatusItem = NULL;
	IQueryAdapter* pQueryAdapter = NULL;
	IDbDataOper* pDbDataOper = NULL;

	TA_Base_Core::CDbStatusManager::getInstance();
	TA_Base_Core::CDbStatusManager::getInstance().initDbStatusByCfg();
	pDbStatusItem = TA_Base_Core::CDbStatusManager::getInstance().getDbStatusItem(nDataType);

	if (NULL == pDbStatusItem)
	{
		LOG_ERROR<<"CDbStatusManager::getInstance().getDbStatusItem(nDataType) return NULL";
	}
	TA_Base_Core::CConnectionPoolManager::getInstance().createConnectionPool(pDbStatusItem);
	pQueryAdapter = TA_Base_Core::CConnectionPoolManager::getInstance().exec(pDbStatusItem, objSqlStatement, numRows);
	if (NULL == pQueryAdapter)
	{
		LOG_WARNING<<"CConnectionPoolManager::getInstance().exec(pDbStatusItem, objSqlStatement, numRows) return NULL";
	}


	pDbDataOper = new CDbDataOperImp(pDbStatusItem, pQueryAdapter);
	pDbDataOper->fetchData(numRows);

	return pDbDataOper;

}


NS_END(TA_Base_Core)







