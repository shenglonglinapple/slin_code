#include "InitDBByYahuoData.h"



#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>


#include "BaseException.h"
#include "StockData.h"
#include "TotalStocksData.h"
#include "YahuoHistoryReqAck.h"
#include "HistoryDataProcssHelper.h"
#include "InitYahuoDataToFile.h"
#include "ProcessFileDataToDB.h"
#include "Log4cppLogger.h"



CInitDBByYahuoData* CInitDBByYahuoData::m_pInstance = 0;
QMutex CInitDBByYahuoData::m_mutexInstance;

CInitDBByYahuoData& CInitDBByYahuoData::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CInitDBByYahuoData();
	}
	return (*m_pInstance);
}

void CInitDBByYahuoData::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CInitDBByYahuoData::CInitDBByYahuoData()
{
	m_pInitYahuoDataToFile = NULL;
	m_pInitYahuoDataToFile = new CInitYahuoDataToFile();
	m_pProcessFileDataToDB = NULL;
	m_pProcessFileDataToDB = new CProcessFileDataToDB();

	_FreeData_MapStockDataItemT_Total();
	_LoadData_MapStockDataItemT_Total();


}

CInitDBByYahuoData::~CInitDBByYahuoData()
{	

	_FreeData_MapStockDataItemT_Total();

	if (NULL != m_pInitYahuoDataToFile)
	{
		delete m_pInitYahuoDataToFile;
		m_pInitYahuoDataToFile = NULL;
	}

	if (NULL != m_pProcessFileDataToDB)
	{
		delete m_pProcessFileDataToDB;
		m_pProcessFileDataToDB = NULL;
	}
}



void CInitDBByYahuoData::_LoadData_MapStockDataItemT_Total()
{
	int nArrSize = 0;
	CStockData* pCStockData = NULL;
	int nIndex = 0;
	std::string strSymbol;
	std::string strName;
	std::string strNamePinYin;
	std::string strSymbolExtern;
	std::string strSymbolUse;


	nArrSize = sizeof(s_SSSZ_Stocks) / sizeof (*s_SSSZ_Stocks);
	MYLOG4CPP_INFO<<"s_SSSZ_Stocks ArrSize="<<nArrSize;

	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

		for (nIndex = 0; nIndex < nArrSize; nIndex++)
		{
			pCStockData = new CStockData();

			strSymbol = s_SSSZ_Stocks[nIndex].m_psz_Symbol;
			//strName = s_SSSZ_Stocks[nIndex].m_psz_Name;
			strNamePinYin = s_SSSZ_Stocks[nIndex].m_psz_NamePinYin;
			strSymbolExtern = s_SSSZ_Stocks[nIndex].m_psz_SymbolExtern;
			strSymbolUse = strSymbol + strSymbolExtern;

			
			pCStockData->m_strSymbol = strSymbol;
			pCStockData->m_strNamePinYin = strNamePinYin;
			pCStockData->m_strSymbolExtern = strSymbolExtern;
			pCStockData->m_nIndex = nIndex;
			pCStockData->m_strSymbolUse = strSymbolUse;
			pCStockData->m_strName = strNamePinYin;

			m_MapStockDataItemT_Total.insert(
				MapStockDataItemValueTypeT(strSymbolUse, pCStockData));

			pCStockData = NULL;
		}//for
	}


	if (NULL != pCStockData)
	{
		delete pCStockData;
		pCStockData = NULL;
	}

}


void CInitDBByYahuoData::_FreeData_MapStockDataItemT_Total()
{
	{
		QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	
		_FreeData_MapStockDataItemT(m_MapStockDataItemT_Total);
	}

}


void CInitDBByYahuoData::_FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData)
{

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = mapStockData.begin();
	while (iterMap != mapStockData.end())
	{
		pData = (iterMap->second);

		delete pData;
		pData = NULL;

		iterMap++;
	}

	mapStockData.clear();

	return;
}

void CInitDBByYahuoData::doWork_initTotalStocksYahuoDataToFile()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	int nFunCheckRes = 0;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		qSleep(10);

		pData = (iterMap->second);
		m_pInitYahuoDataToFile->getAndSaveHistoryData(pData->m_strSymbolUse);

		pData = NULL;
		iterMap++;
	}

}

void CInitDBByYahuoData::doWork_ProcessFileToSQliteDb()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	int nFunCheckRes = 0;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		qSleep(10);

		pData = (iterMap->second);
		m_pProcessFileDataToDB->proceeFileData(pData->m_strSymbolUse);

		pData = NULL;
		iterMap++;
	}

}



void CInitDBByYahuoData::qSleep(int nMilliseconds)
{
#ifdef Q_OS_WIN
	Sleep(uint(nMilliseconds));
#else
	struct timespec ts = { nMilliseconds / 1000, (nMilliseconds % 1000) * 1000 * 1000 };
	nanosleep(&ts, NULL);
#endif

}
void CInitDBByYahuoData::qWait(int nMilliseconds)
{
	QElapsedTimer timer;
	timer.start();
	do 
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, nMilliseconds);
		qSleep(10);
	} while (timer.elapsed() < nMilliseconds);

}



