#ifndef __CLASS_SMART_TRADER_CLIENT_HH__
#define __CLASS_SMART_TRADER_CLIENT_HH__

#include <QtCore/QObject>

#include "MyTradeClient.h"
#include "ClientLoginParam.h"
#include "MyInstrument.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class IProcessRecvData;

class CSmartTraderClient : public CMyTradeClient
{ 
public:
	CSmartTraderClient(const CClientLoginParam& clientLoginParam);
	virtual ~CSmartTraderClient();
public:
	int loginToServer();
	void setProcessRecvDataHandle(IProcessRecvData* pHandle);
public:
	/// Hook method when receiving instrument information 
	virtual void onInstrumentDownloaded(const CMyInstrument &instrument);
	/// Hook method when receive market data
	virtual void onMarketDataUpdate(const CMyMarketData &marketData);
	/// Hook method when history data is downloaded
	virtual void onHistoryDataDownloaded( unsigned int requestID, CMyBarsPtr bars );
	virtual void onBarDataUpdate(const CMyBarSummary &barData);


private:
	CClientLoginParam* m_pClientLoginParam;
	IProcessRecvData* m_pProcessRecvDataHandle;
}; 

//QT_END_NAMESPACE




#endif//__CLASS_SMART_TRADER_CLIENT_HH__



