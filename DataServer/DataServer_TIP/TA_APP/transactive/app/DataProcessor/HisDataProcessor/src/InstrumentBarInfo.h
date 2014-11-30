#ifndef __CLASS_INSTRUMENT_BAR_INFO_H__
#define __CLASS_INSTRUMENT_BAR_INFO_H__ 


#include "CFDServerCommonData.h"
#include "BarCalculator.h"

QT_BEGIN_NAMESPACE


class CInstrumentBarInfo
{
public:
	CInstrumentBarInfo(int interval, Bar& barInfo);	
	~CInstrumentBarInfo(void);

public:
	CInstrumentBarInfo& operator=(const CInstrumentBarInfo& instrumentBarInfo);
public:
	void logInfo();
public:
	int m_nInterval;
	Bar m_BarInfo;
};


QT_END_NAMESPACE


#endif // __CLASS_INSTRUMENT_BAR_INFO_H__









