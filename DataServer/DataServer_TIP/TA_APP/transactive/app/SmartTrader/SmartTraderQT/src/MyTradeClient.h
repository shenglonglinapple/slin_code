#ifndef __CLASS_MY_TRADER_CLIENT_HH__
#define __CLASS_MY_TRADER_CLIENT_HH__

#include "MyBar.h"
#include "MyInstrument.h"
#include "MyMarketData.h"


class CMyTradeClient
{
public:
	/// Constructor of TradeClient with user name and the password
	CMyTradeClient();
	virtual ~CMyTradeClient(void);

public:
	/// Logon to the remote server
    int logon(const std::string &ip, unsigned int port, bool synchronous,
		const std::string &username, const std::string &password, bool enableDebug);

	/// Logoff from OMS
    void logoff();

	/// Subscribe real-time market data for specific instrument
	void subscribeMarketData(const CMyInstrument &instrument);
	void subscribeMarketData(unsigned int nInstrumentID);

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

	

};



#endif//__CLASS_MY_TRADER_CLIENT_HH__

