#include "ClientDataManager.h"

#include <QtCore/QStringList>
#include <QtGui/QMessageBox>

//
#include "SmartTraderClient.h"
#include "ClientLoginParam.h"
//
#include "HistoryDataRequest.h"
//
#include "DataTotalInstrument.h"
#include "DataTotalMyInstrument.h"
#include "StaticStockManager.h"

#include "DataHistoryQuotesManager.h"
//
#include "Log4cppLogger.h"

CClientDataManager* CClientDataManager::m_pInstance = 0;
QMutex CClientDataManager::m_mutexInstance;

CClientDataManager& CClientDataManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CClientDataManager();
	}
	return (*m_pInstance);
}

void CClientDataManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CClientDataManager::CClientDataManager(void)
{	
	m_pSmartTraderClient = NULL;	
	_InitTraderClient(NULL);

	CStaticStockManager::getInstance();
	CDataTotalMyInstrument::getInstance();
	CDataTotalInstrument::getInstance();
	CDataHistoryQuotesManager::getInstance();
}

CClientDataManager::~CClientDataManager(void)
{		
	CDataHistoryQuotesManager::removeInstance();
	CDataTotalMyInstrument::removeInstance();
	CStaticStockManager::removeInstance();
	CDataTotalInstrument::removeInstance();

	_UnInitTraderClient();
}

void CClientDataManager::_InitTraderClient(CClientLoginParam* pClientLoginParam)
{
	if (NULL == pClientLoginParam)
	{
		return;
	}
	if (NULL == m_pSmartTraderClient)
	{
		m_pSmartTraderClient = new CSmartTraderClient(*pClientLoginParam);
		m_pSmartTraderClient->setProcessRecvDataHandle(this);
	}
}
void CClientDataManager::_UnInitTraderClient()
{
	if (NULL != m_pSmartTraderClient)
	{
		//TODO. debug mode will crash
		m_pSmartTraderClient->logoff();
		m_pSmartTraderClient->setProcessRecvDataHandle(NULL);

		delete m_pSmartTraderClient;
		m_pSmartTraderClient = NULL;
	}
}



int CClientDataManager::loginToServer(CClientLoginParam* pClientLoginParam )
{
	int nloginToServerRes = -1;

	MYLOG4CPP_DEBUG<<"CClientDataManager loginToServer";

	pClientLoginParam->logInfo(__FILE__, __LINE__);

	_InitTraderClient(pClientLoginParam);

	if (NULL != m_pSmartTraderClient)
	{
		nloginToServerRes = m_pSmartTraderClient->loginToServer();
	}

	return nloginToServerRes;
}

void CClientDataManager::onInstrumentDownloaded( const CMyInstrument& instrument )
{	
	if (instrument.getInstrumentID() == 900957)
	{
		MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::onInstrumentDownloaded"
			<<" "<<"getInstrumentID="<<instrument.getInstrumentID();
	}


	CDataTotalMyInstrument::getInstance().onInstrumentDownloaded(instrument);

	if (1 == instrument.getInstrumentID())
	{
		m_pSmartTraderClient->subscribeMarketData(instrument.getInstrumentID());
	}
}

void CClientDataManager::onMarketDataUpdate( const CMyMarketData &marketData )
{
	MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::onInstrumentDownloaded"
		<<" "<<"getSecurityID="<<marketData.getSecurityID();

	CDataTotalMyInstrument::getInstance().onMarketDataUpdate(marketData);

}

void CClientDataManager::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	MYLOG4CPP_WARNING<<"CSmartTraderClient::onHistoryDataDownloaded"
		<<" "<<"std::auto_ptr<CMyBars> CMyBarsPtr  bars->size="<<bars->size();

	//std::auto_ptr<CMyBars> CMyBarsPtr 
	CDataHistoryQuotesManager::getInstance().onHistoryDataDownloaded(requestID, bars);

}

void CClientDataManager::onBarDataUpdate(const BarSummary &barData)
{
	MYLOG4CPP_WARNING<<"CClientDataManager::onBarDataUpdate"
		<<" "<<"barData.instrumentID="<<barData.instrumentID
		<<" "<<"barData.bars.size()="<<barData.bars.size();

	//std::auto_ptr<CMyBars> CMyBarsPtr 
	CDataHistoryQuotesManager::getInstance().onBarDataUpdate(barData);

}

void CClientDataManager::downloadHistoryData(const CHistoryDataRequest* pHistoryDataRequest)
{
	CMyInstrument* pInstrument = NULL;
	enum BarType interval;
	unsigned int from;
	unsigned int to ;
	unsigned int requestID = 0;

	pInstrument = CDataTotalMyInstrument::getInstance().findInstrumentByID(pHistoryDataRequest->m_nInstruemntID);
	if (NULL == pInstrument)
	{
		return;
	}

	MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::downloadHistoryData"
		<<" "<<"m_nInstruemntID="<<pHistoryDataRequest->m_nInstruemntID
		<<" "<<"m_strInstrumentCode="<<pHistoryDataRequest->m_strInstrumentCode;

	interval = pHistoryDataRequest->m_nBarType;
	from = pHistoryDataRequest->m_nTimeFrom;
	to = pHistoryDataRequest->m_nTimeTo;

	requestID = m_pSmartTraderClient->my_downloadHistoryData(*pInstrument, interval, from, to);

	CDataHistoryQuotesManager::getInstance().addReqest(requestID, pHistoryDataRequest);

}



