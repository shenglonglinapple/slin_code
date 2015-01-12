#include "StockDataManager.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>

#include "BaseException.h"
#include "StockDataActor.h"

#include "Log4cppLogger.h"



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



void CStockDataManager::addStockData( const QList<QString>* pLstStock )
{	
	CStockDataActor* pData = NULL;
	qint32  nIndex = 0;
	QString  strSymbolUse;
	QList<QString>::const_iterator iterLst;
	QMap<QString,CStockDataActor*>::iterator iterFind;

	MYLOG4CPP_INFO<<"CStockDataManager addStockData pLstStock->size="<<pLstStock->size();

	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);
	iterLst = pLstStock->begin();
	while (iterLst != pLstStock->end())
	{
		strSymbolUse = (*iterLst);
		MYLOG4CPP_DEBUG<<"strSymbolUse="<<strSymbolUse;

		//if (strSymbolUse.contains("000008"))//000008.SZ
		{
			pData = new CStockDataActor();
			pData->setValue(strSymbolUse);

			iterFind = m_MapStockDataItemT_Total.find(pData->m_strSymbolUse);
			if (iterFind != m_MapStockDataItemT_Total.end())
			{
				MYLOG4CPP_ERROR<<"find same name m_strSymbolUse="<<pData->m_strSymbolUse;
				//find same name
				delete pData;
				pData = NULL;
			}
			else
			{
				m_MapStockDataItemT_Total.insert(pData->m_strSymbolUse, pData);
				pData = NULL;
			}
		}//if


		iterLst++;
	}//while
}


void CStockDataManager::_FreeData_SSSZ_Stocks()
{
	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		QMap<QString,CStockDataActor*>::iterator iterMap;
		CStockDataActor* pData = NULL;

		iterMap = m_MapStockDataItemT_Total.begin();
		while (iterMap != m_MapStockDataItemT_Total.end())
		{
			pData = (iterMap.value());

			delete pData;
			pData = NULL;

			iterMap++;
		}

		m_MapStockDataItemT_Total.clear();
	}

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
	QMap<QString,CStockDataActor*>::iterator iterMap;
	CStockDataActor* pData = NULL;
	QString strSymbolUse;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		strSymbolUse = (iterMap.key());
		pData = (iterMap.value());

		LstStock.push_back(strSymbolUse);

		iterMap++;
	}

}








