#include "MyTradeClient.h"

#include "DataWorker.h"
#include "DataRealTimeWorker.h"

#include "ReqData.h"
#include "StockData.h"
#include "StaticStockManager.h"
#include "Log4cppLogger.h"



CMyTradeClient::CMyTradeClient( const std::string &username, const std::string &password, bool enableDebug /*= false*/ )
{
	m_strUserName.clear();
	m_strUserName.clear();
	m_bEnableDebug = false;

	m_strUserName = username;
	m_strPassword = password;
	m_bEnableDebug = enableDebug;


	m_pDataWorker = NULL;
	m_pDataWorker = new CDataWorker();
	m_pDataWorker->setDataProcessHandle(this);
	m_pDataWorker->start();

	m_pDataRealTimeWorker = NULL;
	m_pDataRealTimeWorker = new CDataRealTimeWorker();
	m_pDataRealTimeWorker->setDataProcessHandle(this);
	m_pDataRealTimeWorker->start();
}

CMyTradeClient::~CMyTradeClient( void )
{
	if (NULL != m_pDataWorker)
	{
		m_pDataWorker->terminateAndWait();
		delete m_pDataWorker;
		m_pDataWorker = NULL;
	}

	if (NULL != m_pDataRealTimeWorker)
	{
		m_pDataRealTimeWorker->terminateAndWait();
		delete m_pDataRealTimeWorker;
		m_pDataRealTimeWorker = NULL;
	}
}

int CMyTradeClient::logon( const std::string &ip, unsigned int port, bool synchronous /*= true*/ )
{
	m_strServerIP = ip;
	m_nServerPort = port;
	m_bSynchronous = synchronous;
	m_nLoginRes = 33;

	CReqData* pReqData = new CReqData();
	pReqData->setAutoRequestID();
	pReqData->setReqType(EReqType_DownLoadStockID);
	m_pDataWorker->append_req(pReqData);
	return m_nLoginRes;
}

void CMyTradeClient::logoff()
{

}

void CMyTradeClient::subscribeMarketData( const CMyInstrument &instrument )
{
	CReqData* pReqData = NULL;	

	pReqData = new CReqData();
	pReqData->setAutoRequestID();
	pReqData->setReqType(EReqType_SubscribeMarketData);
	pReqData->setInstrumentCode(instrument.getInstrumentCode());

	m_pDataWorker->append_req(pReqData);
}
void CMyTradeClient::subscribeMarketData(unsigned int securityID)
{
	CReqData* pReqData = NULL;
	const CStockData* pStockData = NULL;
	pStockData = CStaticStockManager::getInstance().find_StockData_BySymbolUse(securityID);

	pReqData = new CReqData();
	pReqData->setAutoRequestID();
	pReqData->setReqType(EReqType_SubscribeMarketData);
	pReqData->setInstrumentCode(pStockData->m_strSymbolUse);
	m_pDataWorker->append_req(pReqData);
}

void CMyTradeClient::unsubscribeMarketData( unsigned int nInstrumentID )
{
	CReqData* pReqData = NULL;	
	const CStockData* pStockeData = NULL;

	pStockeData = CStaticStockManager::getInstance().find_StockData_BySymbolUse(nInstrumentID);

	if (NULL != pStockeData)
	{
		pReqData = new CReqData();
		pReqData->setAutoRequestID();
		pReqData->setReqType(EReqType_UnSubscribeMarketData);

		pReqData->setInstrumentCode(pStockeData->m_strSymbolUse);
		m_pDataWorker->append_req(pReqData);

	}
}


unsigned int CMyTradeClient::downloadHistoryData( const CMyInstrument &instrument, enum BarType interval, unsigned int from, unsigned int to )
{
	CReqData* pReqData = NULL;	
	unsigned int requestID = 0;

	pReqData = new CReqData();
	pReqData->setAutoRequestID();
	pReqData->setReqType(EReqType_DownloadHistoryData);
	pReqData->setMyBarType(interval);
	pReqData->setInstrumentCode(instrument.getInstrumentCode());

	m_pDataWorker->append_req(pReqData);
	requestID = pReqData->getRequestID();

	return requestID;
}

void CMyTradeClient::onInstrumentDownloaded( const CMyInstrument &instrument )
{
	MYLOG4CPP_WARNING<<"CMyTradeClient::onInstrumentDownloaded"
		<<" "<<"you must create class like:  CYourClient : public CMyTradeClient";
}


void CMyTradeClient::onMarketDataUpdate( const CMyMarketData &marketData )
{
	MYLOG4CPP_WARNING<<"CMyTradeClient::onMarketDataUpdate"
		<<" "<<"you must create class like:  CYourClient : public CMyTradeClient";


}


void CMyTradeClient::onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars )
{
	MYLOG4CPP_WARNING<<"CMyTradeClient::onHistoryDataDownloaded"
		<<" "<<"std::auto_ptr<CMyBars> CMyBarsPtr  bars->size="<<bars->size()
		<<" "<<"you must create class like:  CYourClient : public CMyTradeClient";

	//std::auto_ptr<CMyBars> CMyBarsPtr 

}

void CMyTradeClient::onBarDataUpdate(const BarSummary &barData)
{
	MYLOG4CPP_WARNING<<"CMyTradeClient::onBarDataUpdate"
		<<" "<<"barData.instrumentID="<<barData.instrumentID
		<<" "<<"barData.bars.size()="<<barData.bars.size()
		<<" "<<"you must create class like:  CYourClient : public CMyTradeClient";

}

