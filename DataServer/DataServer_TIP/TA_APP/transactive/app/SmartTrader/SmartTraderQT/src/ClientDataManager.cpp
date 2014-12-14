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
	m_pClientLoginParam = NULL;
	m_pSmartTraderClient = NULL;	
	
	_InitLoginParam();
	_InitTraderClient();

	CStaticStockManager::getInstance();
	CDataTotalInstrument::getInstance();
	CDataHistoryQuotesManager::getInstance();
}

CClientDataManager::~CClientDataManager(void)
{		
	CDataHistoryQuotesManager::removeInstance();
	CDataTotalInstrument::removeInstance();
	CStaticStockManager::removeInstance();

	_UnInitTraderClient();
	_UnInitLoginParam();

}



void CClientDataManager::_InitLoginParam()
{
	m_pClientLoginParam = new CClientLoginParam();
	m_pClientLoginParam->setDefaultValue();
}
void CClientDataManager::_UnInitLoginParam()
{
	if (NULL != m_pClientLoginParam)
	{
		delete m_pClientLoginParam;
		m_pClientLoginParam = NULL;
	}
}

void CClientDataManager::_InitTraderClient()
{
	if (NULL == m_pSmartTraderClient)
	{
		m_pSmartTraderClient = new CSmartTraderClient(*m_pClientLoginParam);
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



void CClientDataManager::slotClientLoginParamChanged(CClientLoginParam* pClientLoginParam )
{
	int nloginToServerRes = 0;

	MYLOG4CPP_DEBUG<<"CClientDataManager process slotClientLoginParamChanged"
		<<" "<<"pClientLoginParam=0x"<<pClientLoginParam;

	_UnInitLoginParam();
	_InitLoginParam();
	*m_pClientLoginParam = *pClientLoginParam;

	_InitTraderClient();
	nloginToServerRes = m_pSmartTraderClient->loginToServer();

	MYLOG4CPP_DEBUG<<" "<<"emit"
		<<" "<<"class:"<<"CClientDataManager"
		<<" "<<"fun:"<<"slotClientLoginParamChanged()"
		<<" "<<"emit"
		<<" "<<"signalLoginToServerResult(int)"
		<<" "<<"param:"
		<<" "<<"nloginToServerRes="<<nloginToServerRes;

	emit signalLoginToServerResult(nloginToServerRes);
}

void CClientDataManager::onInstrumentDownloaded( const CMyInstrument& instrument )
{	
	MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::onInstrumentDownloaded"
		<<" "<<"getInstrumentID="<<instrument.getInstrumentID();

	CDataTotalInstrument::getInstance().onInstrumentDownloaded(instrument);

	if (1 == instrument.getInstrumentID())
	{
		m_pSmartTraderClient->subscribeMarketData(instrument);
	}
}

void CClientDataManager::onMarketDataUpdate( const CMyMarketData &marketData )
{
	MYLOG4CPP_DEBUG<<" "<<"CClientDataManager::onInstrumentDownloaded"
		<<" "<<"getSecurityID="<<marketData.getSecurityID();

	CDataTotalInstrument::getInstance().onMarketDataUpdate(marketData);

}

void CClientDataManager::onHistoryDataDownloaded( unsigned int requestID, CMyBarsPtr bars )
{
	MYLOG4CPP_WARNING<<"CSmartTraderClient::onHistoryDataDownloaded"
		<<" "<<"std::auto_ptr<CMyBars> CMyBarsPtr  bars->size="<<bars->size();

	//std::auto_ptr<CMyBars> CMyBarsPtr 
	CDataHistoryQuotesManager::getInstance().onHistoryDataDownloaded(requestID, bars);

}

void CClientDataManager::onBarDataUpdate(const CMyBarSummary &barData)
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
	enum EMyBarType interval;
	unsigned int from;
	unsigned int to ;
	unsigned int requestID = 0;

	pInstrument = CDataTotalInstrument::getInstance().findInstrumentByID(pHistoryDataRequest->m_nInstruemntID);
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

	requestID = m_pSmartTraderClient->downloadHistoryData(*pInstrument, interval, from, to);

	CDataHistoryQuotesManager::getInstance().addReqest(requestID, pHistoryDataRequest);

}



