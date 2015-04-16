/*
manager MarketData history Data in one File
Analie each line  to MarketData class
*/
#ifndef __CLASS_MARKET_DATA_FILE_ANALIER__HH__
#define __CLASS_MARKET_DATA_FILE_ANALIER__HH__

#include "CFDServerCommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "InstrumentBarInfoRequest.h"


////////QT_BEGIN_NAMESPACE 

class CMarketDataDispatcher;
class CCFDServerUtilityFun;

class CMarketDataFileAnalier 
{
public:
	CMarketDataFileAnalier(void);
	~CMarketDataFileAnalier(void);

public:
	void setInstrumentBarInfoRequest(const CInstrumentBarInfoRequest& instrumentBarInfoRequest);
	int analierFile();

private:
	int _InitDispatcher();
	int _UnInitDispatcher();
private:
	CInstrumentBarInfoRequest		m_InstrumentBarInfoRequest;
	CMarketDataDispatcher*			m_pMarketDataDispatcher;
	CCFDServerUtilityFun*           m_pUtilityFun;
};

//////QT_END_NAMESPACE 


#endif //__CLASS_MARKET_DATA_FILE_ANALIER__HH__


