#include "StockDataManager.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>

#include "BaseException.h"
#include "TotalStocksData.h"
#include "StockDataActor.h"
#include "ConfigInfo.h"
#include "Log4cppLogger.h"
#include "SymbolUseManager.h"


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
	_LoadData_SSSZ_Stocks();


}

CStockDataManager::~CStockDataManager()
{	

	_FreeData_SSSZ_Stocks();
}



void CStockDataManager::_LoadData_SSSZ_Stocks()
{
	qint32 nArrSize = 0;
	CStockDataActor* pData = NULL;
	qint32  nIndex = 0;
	QString  strSymbol;
	QString  strNamePinYin;
	QString  strSymbolExtern;
	QMap<QString,CStockDataActor*>::iterator iterFind;
	qint32 nMinStockIndex = 0;
	qint32 nMaxStockIndex = 0;

	nMinStockIndex = CConfigInfo::getInstance().getMinStockIndex();
	nMaxStockIndex = CConfigInfo::getInstance().getMaxStockIndex();

	nArrSize = sizeof(s_SSSZ_Stocks) / sizeof (*s_SSSZ_Stocks);
	if (nMaxStockIndex > nArrSize)
	{
		nMaxStockIndex = nArrSize;
	}
	MYLOG4CPP_INFO<<"s_SSSZ_Stocks ArrSize="<<nArrSize
		<<" "<<"nMinStockIndex="<<nMinStockIndex
		<<" "<<"nMaxStockIndex="<<nMaxStockIndex;


	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

		for (nIndex = nMinStockIndex; nIndex < nMaxStockIndex; nIndex++)
		{
			//setValue
			strSymbol = s_SSSZ_Stocks[nIndex].m_psz_Symbol;
			strNamePinYin = s_SSSZ_Stocks[nIndex].m_psz_NamePinYin;
			strSymbolExtern = s_SSSZ_Stocks[nIndex].m_psz_SymbolExtern;
			MYLOG4CPP_DEBUG<<"strSymbol="<<strSymbol<<" "<<"strSymbolExtern="<<strSymbolExtern;
			
			//if (strSymbol.contains("002033.SZ"))//000008.SZ
			//if (strSymbol.contains("8"))//000008.SZ
			{
				pData = new CStockDataActor();
				pData->setValue(strSymbol, strSymbolExtern);

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


		}//for
	}

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

void CStockDataManager::doWork_Save_HistoryData( const QString& strSymbolUse, const QString& strHistoryData )
{
	QMap<QString,CStockDataActor*>::iterator iterMap;
	CStockDataActor* pData = NULL;

	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		iterMap = m_MapStockDataItemT_Total.find(strSymbolUse);
	}

	if (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap.value());
		
		pData->saveData(strHistoryData);

		pData = NULL;
	}
}
void CStockDataManager::doWork_getStockSymbolUse(QList<QString>& LstStockSymbolUse)
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
	QMap<QString,CStockDataActor*>::iterator iterMap;
	CStockDataActor* pData = NULL;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap.value());

		LstStockSymbolUse.push_back(pData->m_strSymbolUse);

		pData = NULL;
		iterMap++;
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

void CStockDataManager::doWork_getStockMinTimeMaxTime( const QString& strSymbolUse, CStockMinTimeMaxTime** ppValueGet )
{
	QMap<QString,CStockDataActor*>::iterator iterMap;
	CStockDataActor* pData = NULL;

	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		iterMap = m_MapStockDataItemT_Total.find(strSymbolUse);
	}

	if (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap.value());
		pData->getStockMinTimeMaxTime(strSymbolUse, ppValueGet);
		pData = NULL;
	}
}

void CStockDataManager::doWork_HistoryData( const QString& strSymbolUse, const QString& strFrom, const QString& strTo, QList<CHistoryData*>& lstData )
{
	QMap<QString,CStockDataActor*>::iterator iterMap;
	CStockDataActor* pData = NULL;

	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		iterMap = m_MapStockDataItemT_Total.find(strSymbolUse);
	}

	if (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap.value());
		pData->selectData(strFrom, strTo, lstData);

		pData = NULL;
	}
}

void CStockDataManager::doWork_UpdateFailedCount( const QString& strSymbolUse )
{
	QMap<QString,CStockDataActor*>::iterator iterMap;
	CStockDataActor* pData = NULL;

	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		iterMap = m_MapStockDataItemT_Total.find(strSymbolUse);
	}

	if (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap.value());
		pData->updateFailedCount(strSymbolUse);

		pData = NULL;
	}
}

int CStockDataManager::doWork_Select_FailedCount(const QString& strSymbolUse, int& nFailedCount )
{
	int nFunRes = 0;
	QMap<QString,CStockDataActor*>::iterator iterMap;
	CStockDataActor* pData = NULL;
	CSymbolUseManager* pSymbolUseManager = NULL;

	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		iterMap = m_MapStockDataItemT_Total.find(strSymbolUse);
	}

	if (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap.value());
		pData->select_TABLE_SYMBOLUSE_MANAGER(&pSymbolUseManager);

		pData = NULL;
	}
	if (NULL != pSymbolUseManager)
	{
		nFailedCount = pSymbolUseManager->m_nUpdateFailed;
		delete pSymbolUseManager;
		pSymbolUseManager = NULL;
	}

	return nFunRes;
}
void CStockDataManager::doWork_getMaxTime( const QString& strSymbolUse, QString& strMaxTime )
{
	QMap<QString,CStockDataActor*>::iterator iterMap;
	CStockDataActor* pData = NULL;
	CSymbolUseManager* pSymbolUseManager = NULL;

	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		iterMap = m_MapStockDataItemT_Total.find(strSymbolUse);
	}

	strMaxTime.clear();
	if (iterMap != m_MapStockDataItemT_Total.end())
	{
		pData = (iterMap.value());
		pData->select_TABLE_SYMBOLUSE_MANAGER(&pSymbolUseManager);

		pData = NULL;
	}

	if (NULL != pSymbolUseManager)
	{
		strMaxTime = pSymbolUseManager->m_strMaxTime;
		delete pSymbolUseManager;
		pSymbolUseManager = NULL;
	}
}








