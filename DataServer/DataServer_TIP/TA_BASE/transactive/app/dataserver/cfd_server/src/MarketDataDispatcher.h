/*
Dispatcher MarketData class by SecurityID(InstumentID)
*/
#ifndef __CLASS_MARKET_DATA_DISPATCHER__HH__
#define __CLASS_MARKET_DATA_DISPATCHER__HH__

#include "CFDServerCommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "MarketData.h"
#include "InstrumentBarInfoRequest.h"


////////QT_BEGIN_NAMESPACE 

class CInstrumentBarInfoCalculator;

class CMarketDataDispatcher 
{
public:
	typedef std::map<unsigned int, CInstrumentBarInfoCalculator*>				MapInstrumentIDBarInfoCalcT;
	typedef std::map<unsigned int, CInstrumentBarInfoCalculator*>::iterator		MapInstrumentIDBarInfoCalcIterT;
	typedef std::map<unsigned int, CInstrumentBarInfoCalculator*>::value_type   MapInstrumentIDBarInfoCalcValueTypeT;

public:
	CMarketDataDispatcher(void);
	~CMarketDataDispatcher(void);

public:
	int dispatcherMarketData(const MarketData& marketData);
	void setInstrumentBarInfoRequest( const CInstrumentBarInfoRequest& instrumentBarInfoRequest );

private:
	int _ClearDataInMap(MapInstrumentIDBarInfoCalcT* pMapInstrumentIDBarInfoCalc);

private:
	MapInstrumentIDBarInfoCalcT*   m_mapInstrumentIDBarInfoCalc;
	CInstrumentBarInfoRequest m_InstrumentBarInfoRequest;

};

//////QT_END_NAMESPACE 


#endif //__CLASS_MARKET_DATA_DISPATCHER__HH__


