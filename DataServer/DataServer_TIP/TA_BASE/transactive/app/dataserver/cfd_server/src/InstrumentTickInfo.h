#ifndef __CLASS_INSTRUMENT_TICK_INFO_H__
#define __CLASS_INSTRUMENT_TICK_INFO_H__ 


#include "CFDServerCommonData.h"
#include "BarCalculator.h"

////////QT_BEGIN_NAMESPACE


class CInstrumentTickInfo
{
public:
	CInstrumentTickInfo(Tick& tickInfo);	
	~CInstrumentTickInfo(void);

public:
	CInstrumentTickInfo& operator=(const CInstrumentTickInfo& instrumentTickInfo);
public:
	void logInfo();
public:
	Tick m_TickInfo;
};


//////QT_END_NAMESPACE


#endif // __CLASS_INSTRUMENT_BAR_INFO_H__









