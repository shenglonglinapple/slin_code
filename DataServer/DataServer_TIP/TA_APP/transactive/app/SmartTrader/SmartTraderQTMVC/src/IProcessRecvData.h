#ifndef __I_PROCESS_RECV_DATA__HH__
#define __I_PROCESS_RECV_DATA__HH__




#include "API.h"
#include "Bar.h"
#include "Order.h"
#include "Account.h"
#include "Currency.h"
#include "Instrument.h"
#include <memory>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class IProcessRecvData
{
public:
	IProcessRecvData()
	{

	}
	virtual ~IProcessRecvData()
	{
	
	}
public:
	/// process receiving instrument information 
	virtual void onInstrumentDownloaded(const Instrument& instrument) = 0;

	//MYCODE ERROR HERE
	/// Hook method when receive market data
	//virtual void onMarketDataUpdate(const MarketData &marketData);

	virtual void onMarketDataUpdate( const Instrument &instrument ) = 0;

	virtual void onAccountDownloaded(Account& account) = 0;

	/// Hook method when the order is accepted by exchange.
	virtual void onOrderAccepted(const Order &order) = 0;

	/// Hook method when order is canceled.
	virtual void onOrderCanceled(const Order &order) = 0;

	/// Hook method when order is rejected.
	virtual void onOrderRejected(const Order &order) = 0;

	/// Hook method when order filled
	virtual void onOrderFilled(const Order &order) = 0;

	/// Hook method when cancel request get rejected
	virtual void onCancelReject(const Order &order) = 0;

public:
	/// Hook method when receive bar summary update
	virtual void onBarDataUpdate(const BarSummary &barData) = 0;

	/// Hook method when history data is downloaded
	virtual void onHistoryDataDownloaded(unsigned int requestID, BarsPtr bars) = 0;

};


//QT_END_NAMESPACE

#endif//__I_PROCESS_RECV_DATA__HH__


