#ifndef __CLASS_CFDSERVER_UTILITY_FUN_H__
#define __CLASS_CFDSERVER_UTILITY_FUN_H__ 


#include "CFDServerCommonData.h"

#include "MarketData.h"
#include "BarCalculator.h"

QT_BEGIN_NAMESPACE

class CAWorkTime;

class CCFDServerUtilityFun
{
public:
	CCFDServerUtilityFun(void);	
	~CCFDServerUtilityFun(void);
public:
	/*
	"%d-%d-%d %d:%d:%d"
	"%04d-%02d-%02d %02d:%02d:%02d"  
	*/
	time_t strToDateTime(const std::string& strTimeValue);

	/*
	"%04d-%02d-%02d %02d:%02d:%02d"  
	*/
	std::string dataTimeToStr(time_t nTimeValue);


	/*
	"%04d-%02d-%02d %02d:%02d:%02d"  
	2014-01-28 16:20:30
	nHourClock24=17  nMinuteSet=21 nSecondSet=31

	2014-01-28 17:21:31
	*/
	std::string resetTime(const std::string& strTimeValue, int nHourClock24, int nMinuteSet, int nSecondSet);
	/*
	"%04d-%02d-%02d %02d:%02d:%02d"  
	2014-01-28 16:20:30
	nHourClock24Get=16  nMinuteGet=20 nSecondGet=30
	*/
	void getHourMinuteSecond(const std::string& strTimeValue, int& nHourClock24Get, int& nMinuteGet, int& nSecondGet);

	BigInt64 getAutoTimeOutMilliseconds(const std::string& strTimeValueCurrent, const std::string& strAutoRunTime24Clock);

	std::string mysys_boost_intTostr(int nVal);
	int mysys_boost_strToint(std::string& strNumber);

public:
	void logMarketDataInfo(const std::string& strInfo, const MarketData &marketData);
	void logBarInfo(const std::string& strInfo, int interval, Bar* pBarInfo);
public:
	int checkUtilityFun();
private:
	CAWorkTime*  m_pWorkTime;


};


QT_END_NAMESPACE


#endif // __CLASS_CFDSERVER_UTILITY_FUN_H__









