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

	/// process receiving instrument information 
	virtual void onInstrumentDownloaded(const Instrument& instrument) = 0;

	virtual void onMarketDataUpdate( const Instrument &instrument ) = 0;

	virtual void onAccountDownloaded(Account& account) = 0;

};


//QT_END_NAMESPACE

#endif//__I_PROCESS_RECV_DATA__HH__


