#ifndef __CLASS_MY_TRADER_CLIENT_HH__
#define __CLASS_MY_TRADER_CLIENT_HH__

#include "MyBar.h"
#include "MyInstrument.h"
#include "MyMarketData.h"


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
	void subscribeMarketData(const CMyInstrument &instrument);
	void subscribeMarketData(unsigned int securityID);

	/// Unsubscribe the market data
	void unsubscribeMarketData(unsigned int nInstrumentID);
	//return req id
	QString downloadHistoryData( const CMyInstrument &instrument, enum EMyBarType interval, unsigned int from, unsigned int to );
public:
	/// Place a buy market order against specific instrument
	//return req id
	QString buyMarket(const CMyInstrument &instrument, int nVolume);

	/// Place a sell market order against specific instrument
	//return req id
	QString sellMarket(const CMyInstrument &instrument, int nVolume);



public:
	/// Hook method when receiving instrument information 
	virtual void onInstrumentDownloaded(const CMyInstrument &instrument) = 0;
	/// Hook method when receive market data
	virtual void onMarketDataUpdate(const CMyMarketData &marketData) = 0;
	/// Hook method when history data is downloaded
	virtual void onHistoryDataDownloaded(QString requestID, pSetMyBarsPtr bars) = 0;
	/// Hook method when receive bar summary update
	virtual void onBarDataUpdate(const CMyBarSummary &barData) = 0;

private:
	std::string m_strUserName;
	std::string m_strPassword;
	bool m_bEnableDebug;
	std::string m_strServerIP;
	int m_nServerPort;
	bool m_bSynchronous;
	int m_nLoginRes;

};



#endif//__CLASS_MY_TRADER_CLIENT_HH__

