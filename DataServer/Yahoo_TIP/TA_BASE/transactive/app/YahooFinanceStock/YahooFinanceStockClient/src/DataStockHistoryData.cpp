#include "DataStockHistoryData.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Log4cppLogger.h"
#include "QtTimeHelper.h"
#include "HistoryData.h"
#include "WorkTime.h"
#include "ClientDBManager.h"
#include "SignalSlotManager.h"


CDataStockHistoryData* CDataStockHistoryData::m_pInstance = 0;
QMutex CDataStockHistoryData::m_mutexInstance;

CDataStockHistoryData& CDataStockHistoryData::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataStockHistoryData();
	}
	return (*m_pInstance);
}

void CDataStockHistoryData::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataStockHistoryData::CDataStockHistoryData()
{
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();

	CSignalSlotManager::getInstance().set_Signal_DataChange_StockHistoryData(this);

}

CDataStockHistoryData::~CDataStockHistoryData()
{
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}

}



void CDataStockHistoryData::setData( const QString& strSymbolUse, const QList<CHistoryData*>& lstData )
{
	CWorkTimeNoLock workTime(0);
	m_strSymbolUse = strSymbolUse;
	MYLOG4CPP_DEBUG<<"CDataStockHistoryData setData begin";
	workTime.workBegin();
	CClientDBManager::getInstance().setDataHistoryDataLst(m_strSymbolUse, lstData);
	CSignalSlotManager::getInstance().emit_DataChange_StockHistoryData();
	workTime.workEnd();
	MYLOG4CPP_DEBUG<<"CDataStockHistoryData setData end getWorkTime="<<workTime.getWorkTime()<<" "<<"ms";
}



