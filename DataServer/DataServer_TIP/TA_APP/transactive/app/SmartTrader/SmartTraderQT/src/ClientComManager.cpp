#include "ClientComManager.h"

#include "ReqData.h"
#include "StockData.h"
#include "MyServer.h"
#include "StaticStockManager.h"

#include "BaseException.h"
#include "Log4cppLogger.h"


CClientComManager* CClientComManager::m_pInstance = 0;
QMutex CClientComManager::m_mutexInstance;

CClientComManager& CClientComManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CClientComManager();
	}
	return (*m_pInstance);
}

void CClientComManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;
}

CClientComManager::CClientComManager()
{
}

CClientComManager::~CClientComManager()
{	
}



int CClientComManager::logon( const std::string &ip, unsigned int port, bool synchronous , 
							 const std::string &username, const std::string &password, bool enableDebug  )
{
	m_strServerIP = ip;
	m_nServerPort = port;
	m_bSynchronous = synchronous;
	m_nLoginRes = 33;

	CReqData* pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
	pReqData->setReqType(EReqType_DownLoadStockID);

	CMyServer::getInstance().recv_req(pReqData);
	pReqData = NULL;

	return m_nLoginRes;
}

void CClientComManager::logoff()
{

}

void CClientComManager::subscribeMarketData( const CMyInstrument &instrument )
{
	CReqData* pReqData = NULL;	

	pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
	pReqData->setReqType(EReqType_SubscribeMarketData);
	pReqData->setInstrumentCode(instrument.getInstrumentCode());

	CMyServer::getInstance().recv_req(pReqData);
	pReqData = NULL;

}
void CClientComManager::subscribeMarketData(unsigned int nInstrumentID)
{
	CReqData* pReqData = NULL;
	const CStockData* pStockData = NULL;
	pStockData = CStaticStockManager::getInstance().find_StockData_BySymbolUse(nInstrumentID);

	pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
	pReqData->setReqType(EReqType_SubscribeMarketData);
	pReqData->setInstrumentCode(pStockData->m_strSymbolUse);
	CMyServer::getInstance().recv_req(pReqData);
	pReqData = NULL;
}

void CClientComManager::unsubscribeMarketData( unsigned int nInstrumentID )
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
		CMyServer::getInstance().recv_req(pReqData);
		pReqData = NULL;

	}
}


QString CClientComManager::downloadHistoryData( const CMyInstrument &instrument, enum EMyBarType interval, unsigned int from, unsigned int to )
{
	CReqData* pReqData = NULL;	
	QString requestID = 0;

	pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
	pReqData->setReqType(EReqType_DownloadHistoryData);
	pReqData->setMyBarType(interval);
	pReqData->setInstrumentCode(instrument.getInstrumentCode());

	requestID = pReqData->getRequestUUID();

	CMyServer::getInstance().recv_req(pReqData);
	pReqData = NULL;

	return requestID;
}

QString CClientComManager::buyMarket( const CMyInstrument &instrument, int nVolume )
{
	CReqData* pReqData = NULL;	
	QString requestID = 0;

	pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
	pReqData->setReqType(EReqType_BUYMARKET);
	pReqData->setInstrumentCode(instrument.getInstrumentCode());
	pReqData->setVolume(nVolume);

	requestID = pReqData->getRequestUUID();

	CMyServer::getInstance().recv_req(pReqData);
	pReqData = NULL;

	return requestID;

}

QString CClientComManager::sellMarket( const CMyInstrument &instrument, int nVolume )
{
	CReqData* pReqData = NULL;	
	QString requestID = 0;

	pReqData = new CReqData();
	pReqData->setAutoRequestUUID();
	pReqData->setReqType(EReqType_SELLMARKET);
	pReqData->setInstrumentCode(instrument.getInstrumentCode());
	pReqData->setVolume(nVolume);

	requestID = pReqData->getRequestUUID();

	CMyServer::getInstance().recv_req(pReqData);
	pReqData = NULL;


	return requestID;

}

