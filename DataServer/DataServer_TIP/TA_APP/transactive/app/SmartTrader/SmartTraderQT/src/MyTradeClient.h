#ifndef __CLASS_MY_TRADER_CLIENT_HH__
#define __CLASS_MY_TRADER_CLIENT_HH__

#include "MyBar.h"
#include "MyInstrument.h"
#include "MyMarketData.h"

class CDataWorker;

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
	unsigned int downloadHistoryData( const CMyInstrument &instrument, enum BarType interval, unsigned int from, unsigned int to );


public:
	/// Hook method when receiving instrument information 
	virtual void onInstrumentDownloaded(const CMyInstrument &instrument);
	/// Hook method when receive market data
	virtual void onMarketDataUpdate(const CMyMarketData &marketData);
	/// Hook method when history data is downloaded
	virtual void onHistoryDataDownloaded(unsigned int requestID, BarsPtr bars);
	/// Hook method when receive bar summary update
	virtual void onBarDataUpdate(const BarSummary &barData);

private:
	std::string m_strUserName;
	std::string m_strPassword;
	bool m_bEnableDebug;
	std::string m_strServerIP;
	int m_nServerPort;
	bool m_bSynchronous;
	int m_nLoginRes;

private:
	CDataWorker* m_pDataWorker;
};



#endif//__CLASS_MY_TRADER_CLIENT_HH__

