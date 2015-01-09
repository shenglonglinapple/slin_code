#include "YahuoDataToLocalDB.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>

#include "BaseException.h"
#include "TotalStocksData.h"
#include "StockData.h"

#include "ProcessYahuoDataToLocalDB.h"

#include "Log4cppLogger.h"



CYahuoDataToLocalDB* CYahuoDataToLocalDB::m_pInstance = 0;
QMutex CYahuoDataToLocalDB::m_mutexInstance;

CYahuoDataToLocalDB& CYahuoDataToLocalDB::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CYahuoDataToLocalDB();
	}
	return (*m_pInstance);
}

void CYahuoDataToLocalDB::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CYahuoDataToLocalDB::CYahuoDataToLocalDB()
{
	m_pProcessYahuoDataToLocalDB = NULL;
	m_pProcessYahuoDataToLocalDB = new CProcessYahuoDataToLocalDB();

	_FreeData_MapStockDataItemT_Total();
	_LoadData_MapStockDataItemT_Total();


}

CYahuoDataToLocalDB::~CYahuoDataToLocalDB()
{	

	_FreeData_MapStockDataItemT_Total();

	if (NULL != m_pProcessYahuoDataToLocalDB)
	{
		delete m_pProcessYahuoDataToLocalDB;
		m_pProcessYahuoDataToLocalDB = NULL;
	}

	
}



void CYahuoDataToLocalDB::_LoadData_MapStockDataItemT_Total()
{
	qint32 nArrSize = 0;
	CStockData* pCStockData = NULL;
	qint32  nIndex = 0;
	QString  strSymbol;
	QString  strNamePinYin;
	QString  strSymbolExtern;


	nArrSize = sizeof(s_SSSZ_Stocks) / sizeof (*s_SSSZ_Stocks);
	MYLOG4CPP_INFO<<"s_SSSZ_Stocks ArrSize="<<nArrSize;

	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

		for (nIndex = 0; nIndex < nArrSize; nIndex++)
		{
			pCStockData = new CStockData();
			//setValue
			strSymbol = s_SSSZ_Stocks[nIndex].m_psz_Symbol;
			strNamePinYin = s_SSSZ_Stocks[nIndex].m_psz_NamePinYin;
			strSymbolExtern = s_SSSZ_Stocks[nIndex].m_psz_SymbolExtern;
			pCStockData->setValue(nIndex, strSymbol, strNamePinYin, strSymbolExtern);

			m_MapStockDataItemT_Total.insert(
				MapStockDataItemValueTypeT(pCStockData->m_strSymbolUse, pCStockData));

			pCStockData = NULL;
		}//for
	}


	if (NULL != pCStockData)
	{
		delete pCStockData;
		pCStockData = NULL;
	}

}


void CYahuoDataToLocalDB::_FreeData_MapStockDataItemT_Total()
{
	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		MapStockDataItemIterT iterMap;
		CStockData* pData = NULL;

		iterMap = m_MapStockDataItemT_Total.begin();
		while (iterMap != m_MapStockDataItemT_Total.end())
		{
			pData = (iterMap->second);

			delete pData;
			pData = NULL;

			iterMap++;
		}

		m_MapStockDataItemT_Total.clear();
	}

}


void CYahuoDataToLocalDB::doWork_YahuoDataToLocalDB()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		qSleep(10);

		pData = (iterMap->second);
		m_pProcessYahuoDataToLocalDB->processStock(pData->m_strSymbolUse);

		pData = NULL;
		iterMap++;
	}

}


void CYahuoDataToLocalDB::doWork_getStockID(std::list<qint32>& LstStockID)
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	LstStockID.clear();

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		qSleep(10);

		pData = (iterMap->second);
		
		LstStockID.push_back(pData->m_nStockID);

		pData = NULL;
		iterMap++;
	}
}
void CYahuoDataToLocalDB::doWork_getStockSymbolUse(std::list<QString>& LstStockSymbolUse)
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		qSleep(10);

		pData = (iterMap->second);

		LstStockSymbolUse.push_back(pData->m_strSymbolUse);

		pData = NULL;
		iterMap++;
	}
}

void CYahuoDataToLocalDB::qSleep(int nMilliseconds)
{
#ifdef Q_OS_WIN
	Sleep(uint(nMilliseconds));
#else
	struct timespec ts = { nMilliseconds / 1000, (nMilliseconds % 1000) * 1000 * 1000 };
	nanosleep(&ts, NULL);
#endif

}
void CYahuoDataToLocalDB::qWait(int nMilliseconds)
{
	QElapsedTimer timer;
	timer.start();
	do 
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, nMilliseconds);
		qSleep(10);
	} while (timer.elapsed() < nMilliseconds);

}




