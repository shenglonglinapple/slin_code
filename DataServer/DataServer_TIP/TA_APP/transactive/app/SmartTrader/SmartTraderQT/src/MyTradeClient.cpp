#include "MyTradeClient.h"

#include "ReqData.h"
#include "StockData.h"
#include "StaticStockManager.h"
#include "MyServer.h"
#include "ClientComManager.h"
#include "Log4cppLogger.h"



CMyTradeClient::CMyTradeClient()
{

}

CMyTradeClient::~CMyTradeClient( void )
{
	
}



int CMyTradeClient::logon( const std::string &ip, unsigned int port, bool synchronous, 
						  const std::string &username, const std::string &password, bool enableDebug)
{
	return CClientComManager::getInstance().logon(ip, port, synchronous,
		username, password,enableDebug );

}

void CMyTradeClient::logoff()
{
	CClientComManager::getInstance().logoff();
}

void CMyTradeClient::subscribeMarketData( const CMyInstrument &instrument )
{
	CClientComManager::getInstance().subscribeMarketData(instrument);
}
void CMyTradeClient::subscribeMarketData(unsigned int nInstrumentID)
{
	CClientComManager::getInstance().subscribeMarketData(nInstrumentID);

}

void CMyTradeClient::unsubscribeMarketData( unsigned int nInstrumentID )
{
	CClientComManager::getInstance().unsubscribeMarketData(nInstrumentID);

}


QString CMyTradeClient::downloadHistoryData( const CMyInstrument &instrument, enum EMyBarType interval, unsigned int from, unsigned int to )
{
	return CClientComManager::getInstance().downloadHistoryData(instrument, interval, from, to);
}

QString CMyTradeClient::buyMarket( const CMyInstrument &instrument, int nVolume )
{
	return CClientComManager::getInstance().buyMarket(instrument, nVolume);
}

QString CMyTradeClient::sellMarket( const CMyInstrument &instrument, int nVolume )
{
	return CClientComManager::getInstance().sellMarket(instrument, nVolume);

}
