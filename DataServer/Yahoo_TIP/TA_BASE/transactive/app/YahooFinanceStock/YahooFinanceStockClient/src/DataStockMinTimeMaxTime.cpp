#include "DataStockMinTimeMaxTime.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Log4cppLogger.h"
#include "QtTimeHelper.h"
#include "StockMinTimeMaxTime.h"
#include "ClientDBManager.h"
#include "SignalSlotManager.h"


CDataStockMinTimeMaxTime* CDataStockMinTimeMaxTime::m_pInstance = 0;
QMutex CDataStockMinTimeMaxTime::m_mutexInstance;

CDataStockMinTimeMaxTime& CDataStockMinTimeMaxTime::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataStockMinTimeMaxTime();
	}
	return (*m_pInstance);
}

void CDataStockMinTimeMaxTime::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataStockMinTimeMaxTime::CDataStockMinTimeMaxTime()
{
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
	CSignalSlotManager::getInstance().set_Signal_DataChange_StockMinTimeMaxTime(this);
}

CDataStockMinTimeMaxTime::~CDataStockMinTimeMaxTime()
{
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}
	
}


void CDataStockMinTimeMaxTime::appendOrUpdate(const CStockMinTimeMaxTime* pData )
{
	CStockMinTimeMaxTime* pFind = NULL;

	CClientDBManager::getInstance().selectSymbolMinMaxTime(pData->m_strSymbolUse, &pFind);

	if (NULL == pFind)
	{
		CClientDBManager::getInstance().insertSymbolMinMaxTime(pData);
	}
	else
	{
		CClientDBManager::getInstance().updateSymbolMinMaxTime(pData);

		delete pFind;
		pFind = NULL;
	}

	CSignalSlotManager::getInstance().emit_DataChange_StockMinTimeMaxTime();
}
