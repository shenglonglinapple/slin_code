#include "StockDataManager.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>

#include "BaseException.h"
#include "StockDataActor.h"

#include "Log4cppLogger.h"
#include "StockInfo.h"



CStockDataManager* CStockDataManager::m_pInstance = 0;
QMutex CStockDataManager::m_mutexInstance;

CStockDataManager& CStockDataManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CStockDataManager();
	}
	return (*m_pInstance);
}

void CStockDataManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CStockDataManager::CStockDataManager()
{
	_FreeData_SSSZ_Stocks();
}

CStockDataManager::~CStockDataManager()
{	
	_FreeData_SSSZ_Stocks();
}

void CStockDataManager::_FreeLstData(QList<CStockInfo*>& lstData)
{
	foreach (CStockInfo* pData, lstData)
	{
		delete pData;
		pData = NULL;
	}
	lstData.clear();
}
void CStockDataManager::_FreeData_SSSZ_Stocks()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
	_FreeLstData(m_lstStockInfoData);
}

void CStockDataManager::addStockData(const QList<CStockInfo*>* pLstStockInfoData)
{	
	qint32  nIndex = 0;
	QString  strSymbolUse;
	QList<CStockInfo*>::const_iterator iterLst;
	QMap<QString,CStockDataActor*>::iterator iterFind;
	CStockInfo* pRef = NULL;

	MYLOG4CPP_INFO<<"CStockDataManager addStockData pLstStockInfoData->size="<<pLstStockInfoData->size();

	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);
	iterLst = pLstStockInfoData->begin();
	while (iterLst != pLstStockInfoData->end())
	{
		pRef = (*iterLst);
		strSymbolUse = pRef->m_strSymbolUse;
		MYLOG4CPP_DEBUG<<"addStockData strSymbolUse="<<strSymbolUse;

		{
			CStockInfo* pNewStockInfo = NULL;
			pNewStockInfo = new CStockInfo();
			*pNewStockInfo = *pRef;

			m_lstStockInfoData.push_back(pNewStockInfo);
			pNewStockInfo = NULL;
			
		}//if

		iterLst++;
	}//while
}





void CStockDataManager::qSleep(int nMilliseconds)
{
#ifdef Q_OS_WIN
	Sleep(uint(nMilliseconds));
#else
	struct timespec ts = { nMilliseconds / 1000, (nMilliseconds % 1000) * 1000 * 1000 };
	nanosleep(&ts, NULL);
#endif

}
void CStockDataManager::qWait(int nMilliseconds)
{
	QElapsedTimer timer;
	timer.start();
	do 
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, nMilliseconds);
		qSleep(1);
	} while (timer.elapsed() < nMilliseconds);

}

void CStockDataManager::getAllStockData( QList<QString>& LstStock )
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
	QString strSymbolUse;

	foreach (CStockInfo* pData, m_lstStockInfoData)
	{
		strSymbolUse = pData->m_strSymbolUse;
		LstStock.push_back(strSymbolUse);
	}
}








