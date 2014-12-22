#ifndef __I_PROCESS_RECV_DATA__HH__
#define __I_PROCESS_RECV_DATA__HH__

#include <memory>
#include "MyInstrument.h"
#include "MyMarketData.h"
#include "MyBar.h"

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
	virtual void onInstrumentDownloaded(const CMyInstrument& instrument) = 0;
	virtual void onMarketDataUpdate( const CMyMarketData &marketData ) = 0;
	virtual void onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars ) =0;
	virtual void onBarDataUpdate(const BarSummary &barData) = 0;


};


//QT_END_NAMESPACE

#endif//__I_PROCESS_RECV_DATA__HH__


