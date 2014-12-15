#ifndef __CLASS_SMART_TRADER_CLIENT_HH__
#define __CLASS_SMART_TRADER_CLIENT_HH__

#include <QtCore/QObject>

#include "ProjectCommonDef.h"
#include "MyTradeClient.h"
#include "ClientLoginParam.h"
#include "MyInstrument.h"

#include "TradeClient.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class IProcessRecvData;

#ifdef USING_YAHUO_DATA
class CSmartTraderClient : public CMyTradeClient
{ 
public:
	CSmartTraderClient(const CClientLoginParam& clientLoginParam);
	virtual ~CSmartTraderClient();
public:
	int loginToServer();
	void setProcessRecvDataHandle(IProcessRecvData* pHandle);
public:
	/// Download history data from server from a time span 
	unsigned int my_downloadHistoryData( const CMyInstrument &instrument, enum BarType interval, unsigned int from, unsigned int to );

public:
	/// Hook method when receiving instrument information 
	virtual void onInstrumentDownloaded(const CMyInstrument &instrument);
	/// Hook method when receive market data
	virtual void onMarketDataUpdate(const CMyMarketData &marketData);
	/// Hook method when history data is downloaded
	virtual void onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars );
	virtual void onBarDataUpdate(const BarSummary &barData);
private:
	CClientLoginParam* m_pClientLoginParam;
	IProcessRecvData* m_pProcessRecvDataHandle;
}; 
#else
class CSmartTraderClient : public TradeClient
{ 
public:
	CSmartTraderClient(const CClientLoginParam& clientLoginParam);
	virtual ~CSmartTraderClient();
public:
	int loginToServer();
	void setProcessRecvDataHandle(IProcessRecvData* pHandle);
public:
	/// Download history data from server from a time span 
	unsigned int my_downloadHistoryData( const CMyInstrument &instrument, enum BarType interval, unsigned int from, unsigned int to );

public:
	/// Hook method when receiving instrument information 
	virtual void onInstrumentDownloaded(const Instrument &instrument);

	/// Hook method when receive market data
	virtual void onMarketDataUpdate(const MarketData &marketData);

	/// Hook method when history data is downloaded
	virtual void onHistoryDataDownloaded(unsigned int requestID, BarsPtr bars);

	virtual void onBarDataUpdate(const BarSummary &barData);

private:
	CClientLoginParam* m_pClientLoginParam;
	IProcessRecvData* m_pProcessRecvDataHandle;
};
#endif


//QT_END_NAMESPACE




#endif//__CLASS_SMART_TRADER_CLIENT_HH__



