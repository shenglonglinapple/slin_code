#include "MyTradeClient.h"

CMyTradeClient::CMyTradeClient( const std::string &username, const std::string &password, bool enableDebug /*= false*/ )
{
	m_strUserName.clear();
	m_strUserName.clear();
	m_bEnableDebug = false;

	m_strUserName = username;
	m_strPassword = password;
	m_bEnableDebug = enableDebug;
}

CMyTradeClient::~CMyTradeClient( void )
{

}

int CMyTradeClient::logon( const std::string &ip, unsigned int port, bool synchronous /*= true*/ )
{
	m_strServerIP = ip;
	m_nServerPort = port;
	m_bSynchronous = synchronous;
	m_nLoginRes = 33;
	return m_nLoginRes;
}

void CMyTradeClient::logoff()
{

}


void CMyTradeClient::subscribeMarketData( const Instrument &instrument )
{

}

void CMyTradeClient::subscribeMarketData(unsigned int securityID)
{

}

void CMyTradeClient::unsubscribeMarketData(unsigned int securityID)
{

}

const Order & CMyTradeClient::buyMarket( Account &account, const Instrument &instrument, int quantity , int strategyID /*= 0*/, int masks /*= 0*/ )
{
	return m_orderLast;
}

const Order & CMyTradeClient::sellMarket( Account &account, const Instrument &instrument, int quantity , int strategyID /*= 0*/, int masks /*= 0*/ )
{
	return m_orderLast;
}

const Order & CMyTradeClient::buyLimit( Account &account, const Instrument &instrument, double price, int quantity, int strategyID /*= 0*/, int masks /*= 0*/ )
{
	return m_orderLast;
}	

const Order & CMyTradeClient::sellLimit( Account &account, const Instrument &instrument, double price, int quantity , int strategyID /*= 0*/, int masks /*= 0*/ )
{
	return m_orderLast;
}	

const Order & CMyTradeClient::buyStop( Account &account, const Instrument &instrument, double stopPx, int quantity , int strategyID /*= 0*/, int masks /*= 0*/ )
{
	return m_orderLast;
}

const Order & CMyTradeClient::sellStop( Account &account, const Instrument &instrument, double stopPx, int quantity , int strategyID /*= 0*/, int masks /*= 0*/ )
{
	return m_orderLast;
}

unsigned int CMyTradeClient::downloadHistoryData( const Instrument &instrument, BarType interval, unsigned int from, unsigned int to )
{
	return 0;
}

unsigned int CMyTradeClient::downloadHistoryData( const Instrument &instrument, BarType interval, unsigned short number, bool subscribe )
{
	return 0;
}

unsigned int CMyTradeClient::downloadHistoryData( const Instrument &instrument, BarType interval, unsigned int fromTime, unsigned short count, bool subscribe )
{
	return 0;
}
