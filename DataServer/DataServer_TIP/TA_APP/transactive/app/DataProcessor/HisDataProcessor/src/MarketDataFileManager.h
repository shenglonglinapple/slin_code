/*
manager MarketData history Data in one File
*/
#ifndef __CLASS_MARKET_DATA_FILE_MANAGER__HH__
#define __CLASS_MARKET_DATA_FILE_MANAGER__HH__

#include "CFDServerCommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "InstrumentBarInfoRequest.h"

QT_BEGIN_NAMESPACE 

class CMarketDataFileAnalier;

class CMarketDataFileManager 
{
public:
	enum enAnalierType
	{
		AnalierType_Begin,

		AnalierType_Dispatch_MarkketData,

		AnalierType_End,
	};
public:
	CMarketDataFileManager(enAnalierType nAnalierType);
	~CMarketDataFileManager(void);
public:
	void setInstrumentBarInfoRequest(const CInstrumentBarInfoRequest& instrumentBarInfoRequest);
	int analierFile();
private:
	CInstrumentBarInfoRequest		m_InstrumentBarInfoRequest;
	CMarketDataFileAnalier*			m_pMarketDataFileAnalier;
	enAnalierType m_nAnalierType;
};

QT_END_NAMESPACE 


#endif //__CLASS_MARKET_DATA_FILE_MANAGER__HH__


