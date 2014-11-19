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

void CDataUserHistoryBar::createRequest(unsigned int nInstrumentID, CSmartTraderClient* pMyTradeClient)
{
	CHistoryDataManager* pHistoryDataManager = NULL;
	Instrument* pInstrumentRef = NULL;

	QMutexLocker lock(&m_mutexForMapHistoryData);

	pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pInstrumentRef)
	{
		//TODO.
		return;
	}

	pHistoryDataManager = new CHistoryDataManager();

	pHistoryDataManager->m_nInstrumentID = nInstrumentID;
	pHistoryDataManager->m_pHistoryRequest->setRequestType(CHistoryDataRequest::HistoryRequestType_NumberSubscribe);
	pHistoryDataManager->m_pHistoryRequest->setInstrumentHandle(pInstrumentRef);
	pHistoryDataManager->m_pHistoryRequest->setBarType(FIVE_SECOND);
	pHistoryDataManager->m_pHistoryRequest->setTimeFrom(m_pProjectUtilityFun->getTimeNow_Qt() - 60 * 60 * 24 * 10);
	pHistoryDataManager->m_pHistoryRequest->setBarCount(6000);
	pHistoryDataManager->m_pHistoryRequest->setSubscribe(true);
	pHistoryDataManager->m_pHistoryRequest->sentRequest(pMyTradeClient);
	pHistoryDataManager->m_pHistoryRequest->logInfo();

	m_MapHistoryData.insert(nInstrumentID, pHistoryDataManager);
	pHistoryDataManager = NULL;
}



void CDataUserHistoryBar::onBarDataUpdate( const BarSummary &barData )
{
	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;

	{
		//TODO. historydata test
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
		pHistoryDataManager->m_pHistoryACK->logInfo();

	}//scoped_lock
}



void CDataUserHistoryBar::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;

	{
		//TODO. historydata test
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
			//TODO.
			MYLOG4CPP_ERROR<<" "<<"not find requestID="<<requestID;
			return;
		}

		pHistoryDataManager = iterMap.value();
		pHistoryDataManager->m_pHistoryACK->onHistoryDataDownloaded(bars);
		pHistoryDataManager->m_pHistoryACK->logInfo();
	}//scoped_lock

}



CHistoryDataManager*  CDataUserHistoryBar::findByID(unsigned int requestID)
{
	QMap<unsigned int, CHistoryDataManager*>::iterator iterMap;
	CHistoryDataManager* pHistoryDataManager = NULL;


	QMutexLocker lock(&m_mutexForMapHistoryData);
	iterMap = m_MapHistoryData.begin();
	while (iterMap != m_MapHistoryData.end())
	{
		pHistoryDataManager = NULL;
		pHistoryDataManager = iterMap.value();
		if (pHistoryDataManager->m_pHistoryRequest->m_nRequestID == requestID)
		{
			break;
		}
		iterMap++;
	}

	if (iterMap == m_MapHistoryData.end())
	{
		//find error
		//TODO.
		MYLOG4CPP_ERROR<<" "<<"not find requestID="<<requestID;
		pHistoryDataManager = NULL;
		return pHistoryDataManager;
	}

	pHistoryDataManager = iterMap.value();
	return pHistoryDataManager;

}



