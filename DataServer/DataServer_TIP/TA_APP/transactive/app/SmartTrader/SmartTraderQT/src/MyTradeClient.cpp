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


	if (NULL != m_pDataRealTimeWorker)
	{
		m_pDataRealTimeWorker->setDataProcessHandle(NULL);
		m_pDataRealTimeWorker->terminateAndWait();
		delete m_pDataRealTimeWorker;
		m_pDataRealTimeWorker = NULL;
	}

	if (NULL != m_pDataWorker)
	{
		m_pDataWorker->setDataProcessHandle(NULL);
		m_pDataWorker->terminateAndWait();
		delete m_pDataWorker;
		m_pDataWorker = NULL;
	}
}

int CMyTradeClient::logon( const std::string &ip, unsigned int port, bool synchronous /*= true*/ )
{
	m_strServerIP = ip;
	m_nServerPort = port;
	m_bSynchronous = synchronous;
	m_nLoginRes = 33;

	CReqData* pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
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
	pReqData->setAutoRequestUUID();
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
	pReqData->setAutoRequestUUID();
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
		pReqData->setAutoRequestUUID();
		pReqData->setReqType(EReqType_UnSubscribeMarketData);

		pReqData->setInstrumentCode(pStockeData->m_strSymbolUse);
		m_pDataWorker->append_req(pReqData);

	}
}


QString CMyTradeClient::downloadHistoryData( const CMyInstrument &instrument, enum EMyBarType interval, unsigned int from, unsigned int to )
{
	CReqData* pReqData = NULL;	
	QString requestID = 0;

	pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
	pReqData->setReqType(EReqType_DownloadHistoryData);
	pReqData->setMyBarType(interval);
	pReqData->setInstrumentCode(instrument.getInstrumentCode());

	m_pDataWorker->append_req(pReqData);
	requestID = pReqData->getRequestUUID();

	return requestID;
}

QString CMyTradeClient::buyMarket( const CMyInstrument &instrument, int nVolume )
{
	CReqData* pReqData = NULL;	
	QString requestID = 0;

	pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
	pReqData->setReqType(EReqType_BUYMARKET);
	pReqData->setInstrumentCode(instrument.getInstrumentCode());
	pReqData->setVolume(nVolume);

	m_pDataWorker->append_req(pReqData);
	requestID = pReqData->getRequestUUID();

	return requestID;

}

QString CMyTradeClient::sellMarket( const CMyInstrument &instrument, int nVolume )
{
	CReqData* pReqData = NULL;	
	QString requestID = 0;

	pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
	pReqData->setReqType(EReqType_SELLMARKET);
	pReqData->setInstrumentCode(instrument.getInstrumentCode());
	pReqData->setVolume(nVolume);

	m_pDataWorker->append_req(pReqData);
	requestID = pReqData->getRequestUUID();

	return requestID;

}
