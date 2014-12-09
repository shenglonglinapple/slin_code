#ifndef __CLASS_MY_TRADER_CLIENT_HH__
#define __CLASS_MY_TRADER_CLIENT_HH__


#include "TradeClient.h"

class CMyTradeClient
{
public:
	/// Constructor of TradeClient with user name and the password
	CMyTradeClient(const std::string &username, const std::string &password, bool enableDebug = false);
	virtual ~CMyTradeClient(void);

public:
	/// Logon to the remote server
    int logon(const std::string &ip, unsigned int port, bool synchronous = true);

	/// Logoff from OMS
    void logoff();

	/// Subscribe real-time market data for specific instrument
	void subscribeMarketData(const Instrument &instrument);

	/// Subscribe real-time market data by instrument id
	void subscribeMarketData(unsigned int securityID);

	/// Unsubscribe the market data
	void unsubscribeMarketData(unsigned int securityID);

	/// Place a buy market order against specific instrument
	const Order & buyMarket(Account &account, const Instrument &instrument, int quantity , int strategyID = 0, int masks = 0);

	/// Place a sell market order against specific instrument
	const Order & sellMarket(Account &account, const Instrument &instrument, int quantity , int strategyID = 0, int masks = 0);

	/// Place a buy limit order against specific instrument
	const Order & buyLimit(Account &account, const Instrument &instrument, double price, int quantity, int strategyID = 0, int masks = 0);

	/// Place a sell limit order against specific instrument
	const Order & sellLimit(Account &account, const Instrument &instrument, double price, int quantity , int strategyID = 0, int masks = 0);

	/// Place a buy stop order against specific instrument
	const Order & buyStop(Account &account, const Instrument &instrument, double stopPx, int quantity , int strategyID = 0, int masks = 0);

	/// Place a sell stop order against specific instrument
	const Order & sellStop(Account &account, const Instrument &instrument, double stopPx, int quantity , int strategyID = 0, int masks = 0);

	/// Download history data from server from a time span 
	unsigned int downloadHistoryData( const Instrument &instrument, BarType interval, unsigned int from, unsigned int to );

	/// Download the latest N bars and subscribe the following bars, the new bars will be pushed automatically after subscription 
	unsigned int downloadHistoryData( const Instrument &instrument, BarType interval, unsigned short number, bool subscribe );

	/// Download N bars since a time point, and subscribe the bar data from the time point when to subscribe. 
	unsigned int downloadHistoryData( const Instrument &instrument, BarType interval, unsigned int fromTime, unsigned short count, bool subscribe );

private:
	std::string m_strUserName;
	std::string m_strPassword;
	bool m_bEnableDebug;
	std::string m_strServerIP;
	int m_nServerPort;
	bool m_bSynchronous;
	int m_nLoginRes;
private:
	Order m_orderLast;
	
};



#endif//__CLASS_MY_TRADER_CLIENT_HH__

