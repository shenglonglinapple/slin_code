#include "DataUserHistoryBar.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "Instrument.h"
#include "ProjectLogHelper.h"
#include "Log4cppLogger.h"

#include "HistoryDataManager.h"
#include "SmartTraderClient.h"
#include "ProjectUtilityFun.h"
#include "DataTotalInstrument.h"


CDataHistoryQuotesManager* CDataHistoryQuotesManager::m_pInstance = 0;
QMutex CDataHistoryQuotesManager::m_mutexInstance;

CDataHistoryQuotesManager& CDataHistoryQuotesManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataHistoryQuotesManager();
	}
	return (*m_pInstance);
}

void CDataHistoryQuotesManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataHistoryQuotesManager::CDataHistoryQuotesManager()
{
	m_pProjectLogHelper = NULL;
	m_pProjectLogHelper = new CProjectLogHelper();
	m_pProjectUtilityFun = NULL;
	m_pProjectUtilityFun = new CProjectUtilityFun();

}

CDataHistoryQuotesManager::~CDataHistoryQuotesManager()
{
	if (NULL != m_pProjectLogHelper)
	{
		delete m_pProjectLogHelper;
		m_pProjectLogHelper = NULL;
	}

	if (NULL != m_pProjectUtilityFun)
	{
		delete m_pProjectUtilityFun;
		m_pProjectUtilityFun = NULL;
	}

}

void CDataHistoryQuotesManager::_Init()
{
	_UniInit();
}

void CDataHistoryQuotesManager::_UniInit()
{

	{
		QMutexLocker lock(&m_mutexForMapHistoryData);
		QMap<unsigned int, CHistoryQutoes*>::Iterator iterMap;
		CHistoryQutoes* pDataRef = NULL;
		iterMap = m_MapHistoryData.begin();
		while (iterMap != m_MapHistoryData.end())
		{
			pDataRef = iterMap.value();

			delete pDataRef;
			pDataRef = NULL;

			iterMap++;
		}
		m_MapHistoryData.clear();
	}

}

void CDataHistoryQuotesManager::_FreeOldData(unsigned int nInstrumentID)
{
	//check exist
	{
		QMap<unsigned int, CHistoryQutoes*>::iterator iterMap;
		CHistoryQutoes* pHistoryDataManager = NULL;

		QMutexLocker lock(&m_mutexForMapHistoryData);
		if (m_MapHistoryData.contains(nInstrumentID))
		{
			//find ok		
			iterMap = m_MapHistoryData.find(nInstrumentID);
			pHistoryDataManager = iterMap.value();
			delete pHistoryDataManager;
			pHistoryDataManager = NULL;
			iterMap.value() = NULL;
			m_MapHistoryData.erase(iterMap);
		}
	}
}


void CDataHistoryQuotesManager::createRequest_Time(
	unsigned int nInstrumentID, 
	enum BarType nBarType,
	time_t timeFrom,
	time_t timeTo,
	CSmartTraderClient* pMyTradeClient)
{
	Instrument* pInstrumentRef = NULL;
	pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pInstrumentRef)
	{
		//TODO.
		return;
	}
	_FreeOldData(nInstrumentID);
	//create new one
	{
		QMutexLocker lock(&m_mutexForMapHistoryData);
		CHistoryQutoes* pHistoryQutoes = NULL;
		CHistoryDataRequest* pHistoryRequest = NULL;
		pHistoryRequest = new CHistoryDataRequest();

		pHistoryRequest->setRequestType(CHistoryDataRequest::HistoryRequestType_Time);//HistoryRequestType_NumberSubscribe
		pHistoryRequest->setInstrumentHandle(pInstrumentRef);
		pHistoryRequest->setBarType(nBarType);//nBarType FIVE_SECOND
		pHistoryRequest->setTimeFrom(timeFrom);
		pHistoryRequest->setTimeTo(timeTo);
		pHistoryRequest->setSubscribe(false);
		pHistoryRequest->sentRequest(pMyTradeClient);
		pHistoryRequest->logInfo(__FILE__,__LINE__);

		pHistoryQutoes = new CHistoryQutoes();
		pHistoryQutoes->setHistoryDataRequest(pHistoryRequest);
		pHistoryQutoes->setInstrumentID(nInstrumentID);//m_nInstrumentID = nInstrumentID;

		delete pHistoryRequest;
		pHistoryRequest = NULL;

		m_MapHistoryData.insert(nInstrumentID, pHistoryQutoes);
		pHistoryQutoes = NULL;
	}

}


void CDataHistoryQuotesManager::createRequest_NumberSubscribe(
	unsigned int nInstrumentID, 
	enum BarType nBarType,
	int nBarCount,
	bool bSubscribe,
	CSmartTraderClient* pMyTradeClient)
{
	Instrument* pInstrumentRef = NULL;
	pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pInstrumentRef)
	{
		//TODO.
		return;
	}

	_FreeOldData(nInstrumentID);

	//create new one
	{
		QMutexLocker lock(&m_mutexForMapHistoryData);
		CHistoryQutoes* pHistoryQutoes = NULL;
		CHistoryDataRequest* pHistoryRequest = NULL;
		pHistoryRequest = new CHistoryDataRequest();


		pHistoryRequest->setRequestType(CHistoryDataRequest::HistoryRequestType_NumberSubscribe);
		pHistoryRequest->setInstrumentHandle(pInstrumentRef);
		pHistoryRequest->setBarType(nBarType);//nBarType FIVE_SECOND
		pHistoryRequest->setBarCount(nBarCount);
		pHistoryRequest->setSubscribe(bSubscribe);
		pHistoryRequest->sentRequest(pMyTradeClient);
		pHistoryRequest->logInfo(__FILE__,__LINE__);


		pHistoryQutoes = new CHistoryQutoes();
		pHistoryQutoes->setHistoryDataRequest(pHistoryRequest);
		pHistoryQutoes->setInstrumentID(nInstrumentID);//m_nInstrumentID = nInstrumentID;

		delete pHistoryRequest;
		pHistoryRequest = NULL;

		m_MapHistoryData.insert(nInstrumentID, pHistoryQutoes);
		pHistoryQutoes = NULL;
	}

}

void CDataHistoryQuotesManager::createRequest_NumberTimeSubscribe(
	unsigned int nInstrumentID, 
	enum BarType nBarType,
	unsigned int nTimeFrom,
	int nBarCount,
	bool bSubscribe,
	CSmartTraderClient* pMyTradeClient)
{
	Instrument* pInstrumentRef = NULL;
	pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pInstrumentRef)
	{
		//TODO.
		return;
	}

	_FreeOldData(nInstrumentID);

	//create new one
	{
		QMutexLocker lock(&m_mutexForMapHistoryData);
		CHistoryQutoes* pHistoryQutoes = NULL;
		CHistoryDataRequest* pHistoryRequest = NULL;

		pHistoryRequest = new CHistoryDataRequest();

		pHistoryRequest->setRequestType(CHistoryDataRequest::HistoryRequestType_NumberTimeSubscribe);
		pHistoryRequest->setInstrumentHandle(pInstrumentRef);
		pHistoryRequest->setBarType(nBarType);//nBarType FIVE_SECOND
		pHistoryRequest->setBarCount(nBarCount);
		pHistoryRequest->setTimeFrom(nTimeFrom);
		pHistoryRequest->setSubscribe(bSubscribe);
		pHistoryRequest->sentRequest(pMyTradeClient);
		pHistoryRequest->logInfo(__FILE__,__LINE__);

		pHistoryQutoes = new CHistoryQutoes();
		pHistoryQutoes->setHistoryDataRequest(pHistoryRequest);
		pHistoryQutoes->setInstrumentID(nInstrumentID);//

		delete pHistoryRequest;
		pHistoryRequest = NULL;

		m_MapHistoryData.insert(nInstrumentID, pHistoryQutoes);
		pHistoryQutoes = NULL;
	}

}



void CDataHistoryQuotesManager::onBarDataUpdate( const BarSummary &barData )
{
	QMap<unsigned int, CHistoryQutoes*>::iterator iterMap;
	CHistoryQutoes* pHistoryDataManager = NULL;

	{
		QMutexLocker lock(&m_mutexForMapHistoryData);

		if (!m_MapHistoryData.contains(barData.instrumentID))
		{
			//find error
			MYLOG4CPP_ERROR<<" "<<"find error instrumentID="<<barData.instrumentID;
			return;
		}
		iterMap = m_MapHistoryData.find(barData.instrumentID);

		pHistoryDataManager = iterMap.value();
		pHistoryDataManager->m_pHistoryACK->onBarDataUpdate(barData);
		pHistoryDataManager->m_pHistoryACK->logInfo(__FILE__, __LINE__);

	}//scoped_lock
}



void CDataHistoryQuotesManager::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars, unsigned int& nGetInstrumentID)
{
	QMap<unsigned int, CHistoryQutoes*>::iterator iterMap;
	CHistoryQutoes* pHistoryQutoes = NULL;

	{
		QMutexLocker lock(&m_mutexForMapHistoryData);
		iterMap = m_MapHistoryData.begin();
		while (iterMap != m_MapHistoryData.end())
		{
			pHistoryQutoes = iterMap.value();
			if (pHistoryQutoes->m_nRequestID == requestID)
			{
				break;
			}
			pHistoryQutoes = NULL;
			iterMap++;
		}

		if (iterMap == m_MapHistoryData.end())
		{
			//find error
			MYLOG4CPP_ERROR<<" "<<"not find requestID="<<requestID;
			return;
		}

		pHistoryQutoes = iterMap.value();
		pHistoryQutoes->m_pHistoryACK->onHistoryDataDownloaded(bars);
		pHistoryQutoes->m_pHistoryACK->logInfo(__FILE__, __LINE__);
		nGetInstrumentID = pHistoryQutoes->getInstrumentID();
	}//scoped_lock

}
void CDataHistoryQuotesManager::lock()
{
	MYLOG4CPP_DEBUG<<" "<<"m_mutexForMapHistoryData.lock";
	m_mutexForMapHistoryData.lock();
}

void CDataHistoryQuotesManager::unlock()
{
	MYLOG4CPP_DEBUG<<" "<<"m_mutexForMapHistoryData.unlock";
	m_mutexForMapHistoryData.unlock();
}

CHistoryQutoes*  CDataHistoryQuotesManager::lockUseData(unsigned int nInstrumentID)
{
	QMap<unsigned int, CHistoryQutoes*>::iterator iterMap;
	CHistoryQutoes* pHistoryDataManager = NULL;

	//CDataHistoryQuotesManager::getInstance().lock();

	//QMutexLocker lock(&m_mutexForMapHistoryData);
	iterMap = m_MapHistoryData.begin();
	while (iterMap != m_MapHistoryData.end())
	{
		pHistoryDataManager = NULL;
		pHistoryDataManager = iterMap.value();
		if (pHistoryDataManager->getInstrumentID() == nInstrumentID)
		{
			break;
		}
		iterMap++;
	}

	if (iterMap == m_MapHistoryData.end())
	{
		//find error
		MYLOG4CPP_ERROR<<" "<<"not find nInstrumentID="<<nInstrumentID;
		pHistoryDataManager = NULL;
		return pHistoryDataManager;
	}

	pHistoryDataManager = iterMap.value();
	return pHistoryDataManager;



}



