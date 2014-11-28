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


CDataUserHistoryBar* CDataUserHistoryBar::m_pInstance = 0;
QMutex CDataUserHistoryBar::m_mutexInstance;

CDataUserHistoryBar& CDataUserHistoryBar::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataUserHistoryBar();
	}
	return (*m_pInstance);
}

void CDataUserHistoryBar::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataUserHistoryBar::CDataUserHistoryBar()
{
	m_pProjectLogHelper = NULL;
	m_pProjectLogHelper = new CProjectLogHelper();
	m_pProjectUtilityFun = NULL;
	m_pProjectUtilityFun = new CProjectUtilityFun();

}

CDataUserHistoryBar::~CDataUserHistoryBar()
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

void CDataUserHistoryBar::_Init()
{
	_UniInit();
}

void CDataUserHistoryBar::_UniInit()
{

	{
		QMutexLocker lock(&m_mutexForMapHistoryData);
		QMap<unsigned int, CHistoryDataManager*>::Iterator iterMap;
		CHistoryDataManager* pDataRef = NULL;
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

void CDataUserHistoryBar::_FreeOldData(unsigned int nInstrumentID)
{
	//check exist
	{
		QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
		CHistoryDataManager* pHistoryDataManager = NULL;

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


void CDataUserHistoryBar::createRequest_Time(
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
		CHistoryDataManager* pHistoryDataManager = NULL;

		pHistoryDataManager = new CHistoryDataManager();
		pHistoryDataManager->setInstrumentID(nInstrumentID);//m_nInstrumentID = nInstrumentID;
		pHistoryDataManager->m_pHistoryRequest->setRequestType(CHistoryDataRequest::HistoryRequestType_Time);//HistoryRequestType_NumberSubscribe
		pHistoryDataManager->m_pHistoryRequest->setInstrumentHandle(pInstrumentRef);
		pHistoryDataManager->m_pHistoryRequest->setBarType(nBarType);//nBarType FIVE_SECOND
		pHistoryDataManager->m_pHistoryRequest->setTimeFrom(timeFrom);
		pHistoryDataManager->m_pHistoryRequest->setTimeTo(timeTo);
		pHistoryDataManager->m_pHistoryRequest->setSubscribe(false);
		pHistoryDataManager->m_pHistoryRequest->sentRequest(pMyTradeClient);
		pHistoryDataManager->m_pHistoryRequest->logInfo(__FILE__,__LINE__);
		m_MapHistoryData.insert(nInstrumentID, pHistoryDataManager);
		pHistoryDataManager = NULL;
	}

}


void CDataUserHistoryBar::createRequest_NumberSubscribe(
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
		CHistoryDataManager* pHistoryDataManager = NULL;

		pHistoryDataManager = new CHistoryDataManager();
		pHistoryDataManager->setInstrumentID(nInstrumentID);//
		pHistoryDataManager->m_pHistoryRequest->setRequestType(CHistoryDataRequest::HistoryRequestType_NumberSubscribe);
		pHistoryDataManager->m_pHistoryRequest->setInstrumentHandle(pInstrumentRef);
		pHistoryDataManager->m_pHistoryRequest->setBarType(nBarType);//nBarType FIVE_SECOND
		pHistoryDataManager->m_pHistoryRequest->setBarCount(nBarCount);
		pHistoryDataManager->m_pHistoryRequest->setSubscribe(bSubscribe);
		pHistoryDataManager->m_pHistoryRequest->sentRequest(pMyTradeClient);
		pHistoryDataManager->m_pHistoryRequest->logInfo(__FILE__,__LINE__);
		m_MapHistoryData.insert(nInstrumentID, pHistoryDataManager);
		pHistoryDataManager = NULL;
	}

}

void CDataUserHistoryBar::createRequest_NumberTimeSubscribe(
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
		CHistoryDataManager* pHistoryDataManager = NULL;

		pHistoryDataManager = new CHistoryDataManager();
		pHistoryDataManager->setInstrumentID(nInstrumentID);//
		pHistoryDataManager->m_pHistoryRequest->setRequestType(CHistoryDataRequest::HistoryRequestType_NumberTimeSubscribe);
		pHistoryDataManager->m_pHistoryRequest->setInstrumentHandle(pInstrumentRef);
		pHistoryDataManager->m_pHistoryRequest->setBarType(nBarType);//nBarType FIVE_SECOND
		pHistoryDataManager->m_pHistoryRequest->setBarCount(nBarCount);
		pHistoryDataManager->m_pHistoryRequest->setTimeFrom(nTimeFrom);
		pHistoryDataManager->m_pHistoryRequest->setSubscribe(bSubscribe);
		pHistoryDataManager->m_pHistoryRequest->sentRequest(pMyTradeClient);
		pHistoryDataManager->m_pHistoryRequest->logInfo(__FILE__,__LINE__);
		m_MapHistoryData.insert(nInstrumentID, pHistoryDataManager);
		pHistoryDataManager = NULL;
	}

}



void CDataUserHistoryBar::onBarDataUpdate( const BarSummary &barData )
{
	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;

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



void CDataUserHistoryBar::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars, unsigned int& nGetInstrumentID)
{
	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;

	{
		QMutexLocker lock(&m_mutexForMapHistoryData);
		iterMap = m_MapHistoryData.begin();
		while (iterMap != m_MapHistoryData.end())
		{
			pHistoryDataManager = iterMap.value();
			if (pHistoryDataManager->m_pHistoryRequest->m_nRequestID == requestID)
			{
				break;
			}
			pHistoryDataManager = NULL;
			iterMap++;
		}

		if (iterMap == m_MapHistoryData.end())
		{
			//find error
			MYLOG4CPP_ERROR<<" "<<"not find requestID="<<requestID;
			return;
		}

		pHistoryDataManager = iterMap.value();
		pHistoryDataManager->m_pHistoryACK->onHistoryDataDownloaded(bars);
		pHistoryDataManager->m_pHistoryACK->logInfo(__FILE__, __LINE__);
		nGetInstrumentID = pHistoryDataManager->getInstrumentID();
	}//scoped_lock

}



CHistoryDataManager*  CDataUserHistoryBar::findByInstrumentID(unsigned int nInstrumentID)
{
	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;


	QMutexLocker lock(&m_mutexForMapHistoryData);
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



