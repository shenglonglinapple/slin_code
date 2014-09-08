#ifndef __CLASS_PROJECT_UTILITY_FUN_H__
#define __CLASS_PROJECT_UTILITY_FUN_H__ 




#include "TradeClient.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CProjectUtilityFun
{
public:
	CProjectUtilityFun(void);	
	~CProjectUtilityFun(void);

public:
	//"%d-%d-%d %d:%d:%d"
	time_t strToDateTime(const std::string& strTimeValue);

	//"%04d-%02d-%02d %02d:%02d:%02d"
	std::string dataTimeToStr(time_t nTimeValue);

public:
	void log_Instrument_info(const std::string& file, int line, const std::string& strLogInfo, const Instrument &instrument );
	float checkFloatNanValue(const float& fValueTmp);

};



//QT_END_NAMESPACE

#endif // __CLASS_PROJECT_UTILITY_FUN_H__









