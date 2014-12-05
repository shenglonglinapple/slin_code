#include "InitDBByYahuoData.h"



#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>


#include "BaseException.h"
#include "StockData.h"
#include "TotalStocksData.h"
#include "YahuoHistoryReqAck.h"
#include "HistoryDataProcssHelper.h"


#include "Log4cppLogger.h"




CInitDBByYahuoData::CInitDBByYahuoData()
{
	_FreeData_MapStockDataItemT_Total();
	_LoadData_MapStockDataItemT_Total();

}

CInitDBByYahuoData::~CInitDBByYahuoData()
{	
	_FreeData_MapStockDataItemT_Total();
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
			pCStockData->m_strName = "";

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

void CInitDBByYahuoData::_ProcessTotalStocks()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_Total);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	int nFunCheckRes = 0;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		qSleep(100);

		pData = (iterMap->second);

		_GetAndSaveHistoryData(pData->m_strSymbolUse);

		pData = NULL;
		iterMap++;
	}

}



void CInitDBByYahuoData::_GetAndSaveHistoryData(const std::string& strSymbolUse)
{
	int nFunRes = 0;
	CYahuoHistoryReqAck classCYahuoHistoryReqAck;
	std::string petr4HistoricalPrices;

	try
	{
		petr4HistoricalPrices = classCYahuoHistoryReqAck.getHistoricalQuotesCsv(
			strSymbolUse, 1970, 1, 1, 2014, 12, 4, YahuoReqAck::daily);
	}
	catch(CBaseException& e)
	{
		nFunRes = -1;
	}
	catch(...)
	{
		nFunRes = -1;
	}

	if (0 == nFunRes)
	{
		_SaveDataToFile(strSymbolUse, petr4HistoricalPrices);
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

void CInitDBByYahuoData::dowork()
{
	_ProcessTotalStocks();
}

void CInitDBByYahuoData::_SaveDataToFile(const std::string& strSymbolUse, const std::string& strData)
{
	CHistoryDataProcessHelper    objHelper;
	objHelper.saveDataToFile(strSymbolUse, strData);
}
