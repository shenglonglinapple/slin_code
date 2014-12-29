#include "RealTimeStockManager.h"

#include "ProjectCommonData.h"
#include "BaseException.h"
#include "StockData.h"
#include "MyMarketData.h"
#include "MyInstrument.h"
#include "StaticStockManager.h"
#include "QtTimeHelper.h"

#include "YahuoRealTimeReqAck.h"
#include "HistoryStockManager.h"

#include "Log4cppLogger.h"



CRealTimeStockManager* CRealTimeStockManager::m_pInstance = 0;
QMutex CRealTimeStockManager::m_mutexInstance;

CRealTimeStockManager& CRealTimeStockManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CRealTimeStockManager();
	}
	return (*m_pInstance);
}

void CRealTimeStockManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;
}

CRealTimeStockManager::CRealTimeStockManager()
{
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();

	m_strTimeHistoryFrom = "2010-01-01 07:00:00";
	m_strTimeHistoryTo = "2010-01-02 07:00:00";
	m_nTimeHistoryFrom = 0;
	m_nTimeHistoryTo = 0;

	m_nTimeHistoryFrom = (unsigned int)m_pQtTimeHelper->strToDateTime_Qt(m_strTimeHistoryFrom);
	m_nTimeHistoryTo = (unsigned int)m_pQtTimeHelper->strToDateTime_Qt(m_strTimeHistoryTo);

	_FreeData_MapStockDataItemT_RealTime();
}

CRealTimeStockManager::~CRealTimeStockManager()
{	
	_FreeData_MapStockDataItemT_RealTime();	
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}
}



void CRealTimeStockManager::_FreeData_MapStockDataItemT_RealTime()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_RealTime);	
	_FreeData_MapStockDataItemT(m_MapStockDataItemT_RealTime);
}


void CRealTimeStockManager::_FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData)
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

void CRealTimeStockManager::removeRealTimeReq( const std::string& strSymbolUse )
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_RealTime);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = m_MapStockDataItemT_RealTime.begin();
	while (iterMap != m_MapStockDataItemT_RealTime.end())
	{
		pData = (iterMap->second);

		if (pData->m_strSymbolUse == strSymbolUse)
		{
			delete pData;
			pData = NULL;
			m_MapStockDataItemT_RealTime.erase(iterMap);
			return;
		}
		else
		{
			iterMap++;
		}		
	}
	
}

void CRealTimeStockManager::addRealTimeReq( const CStockData* pStockData )
{
	CStockData* pData = NULL;
	pData = new CStockData();

	*pData = *pStockData;
	QMutexLocker lock(&m_mutexMapStockDataItemT_RealTime);	
	m_MapStockDataItemT_RealTime.insert(
		MapStockDataItemValueTypeT(pData->m_strSymbolUse, pData));

	pData = NULL;
}

void CRealTimeStockManager::addRealTimeReq( const std::string& strSymbolUse )
{
	const CStockData* pDataFind = NULL;

	pDataFind = NULL;
	pDataFind = CStaticStockManager::getInstance().find_StockData_BySymbolUse(strSymbolUse);
	if (NULL == pDataFind)
	{
		MYLOG4CPP_ERROR<<"not find strSymbolUse="<<strSymbolUse;
		return;
	}
	addRealTimeReq(pDataFind);
}


std::string CRealTimeStockManager::_GetRealTime_Base(const std::string& strSymbolUse)
{
	int nFunRes = 0;
	std::list<YahuoReqAck::QuoteType> lstQuoteTypes;
	lstQuoteTypes.push_back(YahuoReqAck::stockExchange);
	lstQuoteTypes.push_back(YahuoReqAck::symbol);
	lstQuoteTypes.push_back(YahuoReqAck::changeRealTime);
	lstQuoteTypes.push_back(YahuoReqAck::changeinPercent);
	lstQuoteTypes.push_back(YahuoReqAck::lastTradeDate);
	lstQuoteTypes.push_back(YahuoReqAck::lastTradeTime);
	lstQuoteTypes.push_back(YahuoReqAck::open);
	lstQuoteTypes.push_back(YahuoReqAck::bid);
	lstQuoteTypes.push_back(YahuoReqAck::ask);
	lstQuoteTypes.push_back(YahuoReqAck::dayLow);
	lstQuoteTypes.push_back(YahuoReqAck::dayHigh);
	lstQuoteTypes.push_back(YahuoReqAck::dayRange);
	lstQuoteTypes.push_back(YahuoReqAck::lastTradePriceOnly);
	lstQuoteTypes.push_back(YahuoReqAck::_1yrTargetPrice);
	lstQuoteTypes.push_back(YahuoReqAck::volume);
	lstQuoteTypes.push_back(YahuoReqAck::averageDailyVolume);
	lstQuoteTypes.push_back(YahuoReqAck::name);

	CYahuoRealTimeReqAck  classCYahuoRealTimeReqAck;
	std::string petr4Quotes;

	try
	{
		petr4Quotes = classCYahuoRealTimeReqAck.getLatestQuotesCsv(strSymbolUse, lstQuoteTypes);
		std::cout << petr4Quotes << std::endl;
	}
	catch(CBaseException& e)
	{
		e.logInfo(__FILE__, __LINE__);
		petr4Quotes.clear();
		nFunRes = -1;
	}
	catch(...)
	{
		petr4Quotes.clear();
		nFunRes = -1;
	}

	return petr4Quotes;
}

void CRealTimeStockManager::_GetRealTime_MarketData(const std::string& strSymbolUse, CMyMarketData** ppMyMarketData )
{
	CMyMarketData* pMyMarketData = NULL;
	std::string strData;

	if (NULL == ppMyMarketData)
	{
		return;
	}

	if (NULL != *ppMyMarketData)
	{
		delete (*ppMyMarketData);
		(*ppMyMarketData) = NULL;
	}

	MYLOG4CPP_DEBUG<<"_GetRealTime_MarketData SymbolUse="<<strSymbolUse;
	strData = _GetRealTime_Base(strSymbolUse);
	if (false == strData.empty())
	{
		pMyMarketData = new CMyMarketData();
		pMyMarketData->setInstrumentCode(strSymbolUse);
		pMyMarketData->setValue(strData);

		(*ppMyMarketData) = pMyMarketData;
		pMyMarketData = NULL;
	}


}

void CRealTimeStockManager::getRealTime_MarketDataList( std::list<CMyMarketData*>& lstMyMarketData )
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_RealTime);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	CMyMarketData* pMyMarketData = NULL;

	iterMap = m_MapStockDataItemT_RealTime.begin();
	while (iterMap != m_MapStockDataItemT_RealTime.end())
	{
		pData = (iterMap->second);
		MYLOG4CPP_DEBUG<<"getRealTime_MarketDataList SymbolUse="<<pData->m_strSymbolUse;
		pMyMarketData = NULL;
		_GetRealTime_MarketData(pData->m_strSymbolUse, &pMyMarketData);
		if (NULL != pMyMarketData)
		{
			lstMyMarketData.push_back(pMyMarketData);
			pMyMarketData = NULL;
		}

		iterMap++;
	}//while

}




void CRealTimeStockManager::getRealTimeData_MyInstrument( const std::string& strSymbolUse, CMyInstrument** ppMyInstrument )
{
	CMyMarketData* pMyMarketData = NULL;
	CMyInstrument* pMyInstrument = NULL;

	if (NULL == ppMyInstrument)
	{
		return;
	}

	if (NULL != *ppMyInstrument)
	{
		delete (*ppMyInstrument);
		(*ppMyInstrument) = NULL;
	}

	_GetRealTime_MarketData(strSymbolUse, &pMyMarketData);


	if (NULL != pMyMarketData)
	{
		pMyInstrument = new CMyInstrument();
		pMyInstrument->setValue(pMyMarketData);

		(*ppMyInstrument) = pMyInstrument;
		pMyInstrument = NULL;

	}

	if (NULL != pMyMarketData)
	{
		delete (pMyMarketData);
		(pMyMarketData) = NULL;
	}

}











//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CRealTimeStockManager::_GetHistory_MarketData(const std::string& strSymbolUse, CMyMarketData** ppMyMarketData )
{
	CHistoryStockManager::LstHistoryDataT lstHistoryData;
	CHistoryStockManager::LstHistoryDataIterT iterLst;
	CHistoryData* pHistoryData = NULL;
	CMyMarketData* pMyMarketData = NULL;

	if (NULL == ppMyMarketData)
	{
		return;
	}

	if (NULL != *ppMyMarketData)
	{
		delete (*ppMyMarketData);
		(*ppMyMarketData) = NULL;
	}

	MYLOG4CPP_DEBUG<<"_GetHistory_MarketData SymbolUse="<<strSymbolUse;
	CHistoryStockManager::getInstance().downloadHistoryData(strSymbolUse,
		m_strTimeHistoryFrom, m_strTimeHistoryTo,	lstHistoryData);

	iterLst = lstHistoryData.begin();
	if (iterLst != lstHistoryData.end())
	{
		pHistoryData = (*iterLst);

		pMyMarketData = new CMyMarketData();
		pMyMarketData->setInstrumentCode(strSymbolUse);
		pMyMarketData->setValue(pHistoryData);

		(*ppMyMarketData) = pMyMarketData;
		pMyMarketData = NULL;
	}//while

	CHistoryStockManager::getInstance().freeLstHistoryDataT(lstHistoryData);
}
void CRealTimeStockManager::getHistory_MarketDataList( std::list<CMyMarketData*>& lstMyMarketData )
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_RealTime);	

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	CMyMarketData* pMyMarketData = NULL;

	iterMap = m_MapStockDataItemT_RealTime.begin();
	while (iterMap != m_MapStockDataItemT_RealTime.end())
	{
		pData = (iterMap->second);
		MYLOG4CPP_DEBUG<<"getHistory_MarketDataList SymbolUse="<<pData->m_strSymbolUse;
		pMyMarketData = NULL;
		_GetHistory_MarketData(pData->m_strSymbolUse, &pMyMarketData);
		if (NULL != pMyMarketData)
		{
			lstMyMarketData.push_back(pMyMarketData);
			pMyMarketData = NULL;
		}

		iterMap++;
	}//while

	//historyAddOneDay();
}

void CRealTimeStockManager::historyAddOneDay()
{
	m_nTimeHistoryFrom += DEF_INT_ONE_DAY_SECONDS;
	m_nTimeHistoryTo += DEF_INT_ONE_DAY_SECONDS;

	m_strTimeHistoryFrom = m_pQtTimeHelper->dateTimeToStr_Qt(m_nTimeHistoryFrom);
	m_strTimeHistoryTo = m_pQtTimeHelper->dateTimeToStr_Qt(m_nTimeHistoryTo);

}


void CRealTimeStockManager::getHistory_MyInstrument( const std::string& strSymbolUse, CMyInstrument** ppMyInstrument )
{
	CMyMarketData* pMyMarketData = NULL;
	CMyInstrument* pMyInstrument = NULL;

	if (NULL == ppMyInstrument)
	{
		return;
	}

	if (NULL != *ppMyInstrument)
	{
		delete (*ppMyInstrument);
		(*ppMyInstrument) = NULL;
	}

	_GetHistory_MarketData(strSymbolUse, &pMyMarketData);


	if (NULL != pMyMarketData)
	{
		pMyInstrument = new CMyInstrument();
		pMyInstrument->setValue(pMyMarketData);

		(*ppMyInstrument) = pMyInstrument;
		pMyInstrument = NULL;

	}

	if (NULL != pMyMarketData)
	{
		delete (pMyMarketData);
		(pMyMarketData) = NULL;
	}

}
//////////////////////////////////////////////////////////////////////////

