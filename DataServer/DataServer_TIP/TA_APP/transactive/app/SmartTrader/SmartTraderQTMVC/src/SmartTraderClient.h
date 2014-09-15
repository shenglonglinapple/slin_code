#ifndef __CLASS_SMART_TRADER_CLIENT_HH__
#define __CLASS_SMART_TRADER_CLIENT_HH__

#include <QtCore/QObject>

#include "TradeClient.h"
#include "ClientLoginParam.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class IProcessRecvData;

class CSmartTraderClient : public QObject, public TradeClient
{ 
	Q_OBJECT



public:
	CSmartTraderClient(const CClientLoginParam& clientLoginParam);
	virtual ~CSmartTraderClient();
public:
	int loginToServer();
	void setProcessRecvDataHandle(IProcessRecvData* pHandle);
public:
	/// Hook method when receiving instrument information 
	virtual void onInstrumentDownloaded(const Instrument &instrument);
	virtual void onMarketDataUpdate(const Instrument &instrument);
	/// Hook method when account downloaded
	virtual void onAccountDownloaded(Account& account);

	/// Hook method when the order is accepted by exchange.
	virtual void onOrderAccepted(const Order &order);

	/// Hook method when order is canceled.
	virtual void onOrderCanceled(const Order &order);

	/// Hook method when order is rejected.
	virtual void onOrderRejected(const Order &order);

	/// Hook method when order filled
	virtual void onOrderFilled(const Order &order);

	/// Hook method when cancel request get rejected
	virtual void onCancelReject(const Order &order);

	/// Hook method when receive bar summary update
	virtual void onBarDataUpdate(const BarSummary &barData);

private:
	CClientLoginParam* m_pClientLoginParam;
	IProcessRecvData* m_pProcessRecvDataHandle;
}; 

//QT_END_NAMESPACE




#endif//__CLASS_SMART_TRADER_CLIENT_HH__



