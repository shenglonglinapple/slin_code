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
	//"%04d-%02d-%02d %02d:%02d:%02d"
public:
	time_t strToDateTime_Qt(const std::string& strTimeValue);
	std::string dateTimeToStr_Qt(time_t nTimeValue);
	time_t getTimeNow_Qt();

public:
	float checkFloatNanValue(const float& fValueTmp);
public:
	template<typename T> bool uti_isnan(T value);
	template<typename T> bool uti_isinf(T value);
};



//QT_END_NAMESPACE

#endif // __CLASS_PROJECT_UTILITY_FUN_H__









