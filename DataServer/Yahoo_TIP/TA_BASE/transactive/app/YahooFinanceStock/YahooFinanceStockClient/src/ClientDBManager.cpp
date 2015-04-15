#include "ClientDBManager.h"

#include <QtCore/QStringList>
#include <QtCore/QByteArray>

#include "ProjectCommonDef.h"

#include "QtTimeHelper.h"
#include "WorkTime.h"
#include "ConfigInfo.h"
#include "UserInfo.h"
#include "UserTradeInfo.h"
#include "ClientDbOper.h"
#include "UserAccount.h"
#include "Log4cppLogger.h"

CClientDBManager* CClientDBManager::m_pInstance = 0;
QMutex CClientDBManager::m_mutexInstance;

CClientDBManager& CClientDBManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CClientDBManager();
	}
	return (*m_pInstance);
}

void CClientDBManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CClientDBManager::CClientDBManager(void)
{
	m_pUserInfo = NULL;
	m_pUserInfo = new CUserInfo();

	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();

	QMutexLocker lock(&m_mutex_ClientDbOper);
	m_pClientDbOper = NULL;
	m_pUserInfo->setUseID(CConfigInfo::getInstance().getUserName(), CConfigInfo::getInstance().getPassWord());
	m_pClientDbOper = new CClientDbOper(m_pUserInfo->m_strUserID);
}

CClientDBManager::~CClientDBManager(void)
{
	QMutexLocker lock(&m_mutex_ClientDbOper);
	if (NULL != m_pClientDbOper)
	{
		delete m_pClientDbOper;
		m_pClientDbOper = NULL;
	}
	if (NULL != m_pUserInfo)
	{
		delete m_pUserInfo;
		m_pUserInfo = NULL;
	}
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}
}



void CClientDBManager::resetDataHistory( const QString& strSymbolUse, const QList<CHistoryData*>& lstData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	CWorkTimeNoLock workTime(0);
	workTime.workBegin();
	MYLOG4CPP_DEBUG<<"CClientDBManager::resetDataHistory() begin";

	if (NULL != m_pClientDbOper)
	{
		m_pClientDbOper->reset_TABLE_BAR_DATA_1DAY(strSymbolUse, lstData);
	}
	workTime.workEnd();
	MYLOG4CPP_DEBUG<<"CClientDBManager::resetDataHistory() end getWorkTime="<<workTime.getWorkTime()<<" "<<"ms";
}

QSqlDatabase* CClientDBManager::getDB()
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	QSqlDatabase* pDBHandle = NULL;
	if (NULL != m_pClientDbOper)
	{
		pDBHandle = m_pClientDbOper->getDB();
	}
	return pDBHandle;
}

qint32 CClientDBManager::insertSymbolMinMaxTime( const CStockMinTimeMaxTime* pData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->insertSymbolMinMaxTime(pData);
	}
	return nFunRes;
}

qint32 CClientDBManager::updateSymbolMinMaxTime( const CStockMinTimeMaxTime* pData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->updateSymbolMinMaxTime(pData);
	}
	return nFunRes;
}

qint32 CClientDBManager::selectSymbolMinMaxTime( const QString& strSymbolUse, CStockMinTimeMaxTime** ppData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->selectSymbolMinMaxTime(strSymbolUse, ppData);
	}
	return nFunRes;
}

qint32 CClientDBManager::insertUserTradeInfo(const CUserTradeInfo* pData)
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->insertUserTradeInfo(pData);
	}
	return nFunRes;
}




qint32 CClientDBManager::resetUserAccount( const CUserAccount* pData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->resetUserAccount(pData);
	}
	return nFunRes;
}

qint32 CClientDBManager::resetAllStockInfo(const QList<CStockInfo*>& lstData)
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->resetAllStockInfo(lstData);
	}
	return nFunRes;
}

qint32 CClientDBManager::insertUserAmount(const CUserAccount* pData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->insertUserAccount(pData);
	}
	return nFunRes;
}

qint32 CClientDBManager::resetUserHoldAccount( const QList<CUserHoldAccount*>& lstData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->resetUserHoldAccount(lstData);
	}
	return nFunRes;
}
