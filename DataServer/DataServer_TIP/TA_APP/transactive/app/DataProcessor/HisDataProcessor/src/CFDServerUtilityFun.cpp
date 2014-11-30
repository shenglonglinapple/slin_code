#include "CFDServerUtilityFun.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list> 
#include <time.h>
#include "WorkTime.h"

#include "BarCalculator.h"
#include <boost/date_time/posix_time/posix_time.hpp>  
#include "boost/lexical_cast.hpp" 
#include "boost/tokenizer.hpp"


#include "BoostLogger.h"
USING_BOOST_LOG;

QT_BEGIN_NAMESPACE

//static const int DEF_VALUE_INT_MAXBUFFERSIZE = 1024;



CCFDServerUtilityFun::CCFDServerUtilityFun( void )
{
	BOOST_LOG_FUNCTION();
	m_pWorkTime = NULL;
	m_pWorkTime = new CWorkTimeNoLock();

}

CCFDServerUtilityFun::~CCFDServerUtilityFun( void )
{
	BOOST_LOG_FUNCTION();
	if (NULL != m_pWorkTime)
	{
		delete m_pWorkTime;
		m_pWorkTime = NULL;
	}

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


//"%d-%d-%d %d:%d:%d"
//YYYY-MM-DD HH:MM:SS
time_t CCFDServerUtilityFun::strToDateTime(const std::string& strTimeValue)
{
	tm tmTime;
	int nYearValue = 0;
	int nMonthValue = 0;
	int nDayValue = 0;
	int nHourValue = 0;
	int nMinuteValue = 0;
	int nSecondValue = 0;
	time_t timeGetTimeValue = time(NULL);
	
	if (strTimeValue.empty())
	{
		return timeGetTimeValue;
	}

	sscanf(strTimeValue.c_str(),
		"%d-%d-%d %d:%d:%d", 
		&nYearValue, &nMonthValue, &nDayValue, 
		&nHourValue, &nMinuteValue, &nSecondValue);

	tmTime.tm_year  = nYearValue-1900;
	tmTime.tm_mon   = nMonthValue-1;
	tmTime.tm_mday  = nDayValue;
	tmTime.tm_hour  = nHourValue;
	tmTime.tm_min   = nMinuteValue;
	tmTime.tm_sec   = nSecondValue;
	tmTime.tm_isdst = 0;

	timeGetTimeValue = mktime(&tmTime); //dec 8 TC
	return timeGetTimeValue; //seconds
}

#if 0

//"%04d-%02d-%02d %02d:%02d:%02d"
std::string CCFDServerUtilityFun::dataTimeToStr(time_t nTimeValue)
{
	BOOST_LOG_FUNCTION();
	std::string	strTimeString;
	char* pszCurTime = NULL;
	struct tm* pTM = NULL;
	time_t time_Value = (time_t)nTimeValue;

	pszCurTime =new char[DEF_VALUE_INT_MAXBUFFERSIZE];
	memset(pszCurTime, 0, DEF_VALUE_INT_MAXBUFFERSIZE);

	pTM = localtime(&(time_Value));

	//TIMESTR--%Y%m%d%H%M%S
	//format to string
	if ( NULL != pTM )
	{
		sprintf(pszCurTime, "%04d-%02d-%02d %02d:%02d:%02d",
			pTM->tm_year + 1900, pTM->tm_mon + 1, pTM->tm_mday,
			pTM->tm_hour, pTM->tm_min, pTM->tm_sec); 
		strTimeString = pszCurTime;     
	}

	if (NULL != pszCurTime)
	{
		delete[] pszCurTime;
		pszCurTime = NULL;
	}

	pTM = NULL;

	return strTimeString;
}
#endif



//"%04d-%02d-%02d %02d:%02d:%02d"
std::string CCFDServerUtilityFun::dataTimeToStr(time_t nTimeValue)
{
	BOOST_LOG_FUNCTION();
	std::string	strTimeString;
	boost::posix_time::ptime boostTimeValue;

	try
	{
		// boostTimeValue = boost::posix_time::from_time_t(nTimeValue) error
		boostTimeValue = boost::posix_time::from_time_t(nTimeValue) + boost::posix_time::hours(8);
		strTimeString = m_pWorkTime->getTimeString(&boostTimeValue);
	}
	catch (...)
	{
		LOG_ERROR<<"CCFDServerUtilityFun::dataTimeToStr"
			<<" "<<"nTimeValue="<<nTimeValue
			<<" "<<"strTimeString="<<strTimeString;
		
		strTimeString.clear();
		return strTimeString;
	}
	//"%04d-%02d-%02d %02d:%02d:%02d"
	return strTimeString;
}


//"%04d-%02d-%02d %02d:%02d:%02d"  
//nHourClock24=18  nMinuteSet=30 nSecondSet=20
std::string CCFDServerUtilityFun::resetTime(const std::string& strTimeValue, int nHourClock24, int nMinuteSet, int nSecondSet)
{
	tm tmTime;
	int nYearValue = 0;
	int nMonthValue = 0;
	int nDayValue = 0;
	int nHourValue = 0;
	int nMinuteValue = 0;
	int nSecondValue = 0;
	time_t timeGetTimeValue = time(NULL);
	std::string strTimeValueChange;

	if (strTimeValue.empty())
	{
		return strTimeValueChange;
	}

	sscanf(strTimeValue.c_str(),
		"%d-%d-%d %d:%d:%d", 
		&nYearValue, &nMonthValue, &nDayValue, 
		&nHourValue, &nMinuteValue, &nSecondValue);

	tmTime.tm_year  = nYearValue-1900;
	tmTime.tm_mon   = nMonthValue-1;
	tmTime.tm_mday  = nDayValue;
	tmTime.tm_hour  = nHourValue;
	tmTime.tm_min   = nMinuteValue;
	tmTime.tm_sec   = nSecondValue;
	tmTime.tm_isdst = 0;

	//reset
	tmTime.tm_hour  = nHourClock24;
	tmTime.tm_min   = nMinuteSet;
	tmTime.tm_sec   = nSecondSet;

	timeGetTimeValue = mktime(&tmTime); //dec 8 TC

	strTimeValueChange = dataTimeToStr(timeGetTimeValue);

	return strTimeValueChange; 
}



//"%04d-%02d-%02d %02d:%02d:%02d"  
//nHourClock24=18  nMinuteSet=30 nSecondSet=20
void CCFDServerUtilityFun::getHourMinuteSecond(const std::string& strTimeValue, int& nHourClock24Get, int& nMinuteGet, int& nSecondGet)
{
	tm tmTime;
	int nYearValue = 0;
	int nMonthValue = 0;
	int nDayValue = 0;
	int nHourValue = 0;
	int nMinuteValue = 0;
	int nSecondValue = 0;
	time_t timeGetTimeValue = time(NULL);

	nHourClock24Get = 0;
	nMinuteGet = 0;
	nSecondGet = 0;

	if (strTimeValue.empty())
	{
		return;
	}

	sscanf(strTimeValue.c_str(),
		"%d-%d-%d %d:%d:%d", 
		&nYearValue, &nMonthValue, &nDayValue, 
		&nHourValue, &nMinuteValue, &nSecondValue);

	tmTime.tm_year  = nYearValue-1900;
	tmTime.tm_mon   = nMonthValue-1;
	tmTime.tm_mday  = nDayValue;
	tmTime.tm_hour  = nHourValue;
	tmTime.tm_min   = nMinuteValue;
	tmTime.tm_sec   = nSecondValue;
	tmTime.tm_isdst = 0;

	//get info
	nHourClock24Get = tmTime.tm_hour;
	nMinuteGet = tmTime.tm_min;
	nSecondGet = tmTime.tm_sec;

	return; 
}

/*
Milliseconds

two type:

type one:
strCurrentTime = "2014-01-28 11:00:00"
AutoRunTime24Clock = "2014-01-28 13:00:00"
m_nWorkTimeAutoTimeOut = "2014-01-28 13:00:00" - "2014-01-28 11:00:00"

type two:
strCurrentTime = "2014-01-28 11:00:00"
AutoRunTime24Clock = "2014-01-28 03:00:00"
m_nWorkTimeAutoTimeOut = "2014-01-29 03:00:00" - "2014-01-28 11:00:00"

*/
BigInt64 CCFDServerUtilityFun::getAutoTimeOutMilliseconds(const std::string& strTimeValueCurrent, const std::string& strAutoRunTime24Clock)
{
	time_t timeCurrent;
	time_t timeAutoRunTime24Clock;
	std::string strTimeValueReset;
	int nHourGet = 0;
	int nMinGet = 0;
	int nSecondGet = 0;
	BigInt64 nAutoTimeOut = 0;
	BigInt64 nSecondsOneDay = 0;

	nSecondsOneDay = TIME_BASE_S_1DAY;

	strTimeValueReset = strTimeValueCurrent;

	getHourMinuteSecond(strAutoRunTime24Clock, nHourGet, nMinGet, nSecondGet);//
	strTimeValueReset = resetTime(strTimeValueCurrent, nHourGet, nMinGet, nSecondGet);

	timeCurrent = strToDateTime(strTimeValueCurrent);
	timeAutoRunTime24Clock = strToDateTime(strTimeValueReset);

	if (timeAutoRunTime24Clock > timeCurrent)
	{
		nAutoTimeOut = timeAutoRunTime24Clock - timeCurrent;//seconds
		nAutoTimeOut = nAutoTimeOut * 1000;//Milliseconds
	}
	else
	{
		nAutoTimeOut = nSecondsOneDay - (timeCurrent - timeAutoRunTime24Clock);
		nAutoTimeOut = nAutoTimeOut * 1000;//Milliseconds
	}

	return nAutoTimeOut;
}


std::string	CCFDServerUtilityFun::mysys_boost_intTostr(int nVal)
{
	std::string strNumber;

	strNumber = boost::lexical_cast<std::string>(nVal);

	return strNumber;
}


int	CCFDServerUtilityFun::mysys_boost_strToint(std::string& strNumber)
{
	int nNumber;
	if (strNumber.empty())
	{
		nNumber = 0;
		return nNumber;
	}
	nNumber = boost::lexical_cast<int>(strNumber);

	return nNumber;
}

int CCFDServerUtilityFun::checkUtilityFun()
{
	int nFunRes = 0;
	std::string strNow;
	time_t timeNow = 0;

	std::string strNowTwo;
	time_t timeNowTwo = 0;

	strNow = m_pWorkTime->getCurrentTime(NULL);////2014-01-28 11:00:00
	timeNow = strToDateTime(strNow);
	strNowTwo = dataTimeToStr(timeNow);
	timeNowTwo = strToDateTime(strNowTwo);

	if (strNow == strNowTwo && timeNow == timeNowTwo)
	{
		LOG_INFO<<"CCFDServerUtilityFun::checkUtilityFun OK!"
			<<" "<<"strNow="<<strNow
			<<" "<<"timeNow="<<timeNow
			<<" "<<"strNowTwo="<<strNowTwo
			<<" "<<"timeNowTwo="<<timeNowTwo;
		nFunRes = 0;
	}
	else
	{
		LOG_ERROR<<"CCFDServerUtilityFun::checkUtilityFun ERROR!"
			<<" "<<"strNow="<<strNow
			<<" "<<"timeNow="<<timeNow
			<<" "<<"strNowTwo="<<strNowTwo
			<<" "<<"timeNowTwo="<<timeNowTwo;
		nFunRes = -1;
	}

	return nFunRes;

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void CCFDServerUtilityFun::logBarInfo(const std::string& strInfo, int interval, Bar* pBarInfo)
{
	BOOST_LOG_FUNCTION();
	std::string strBarTime;

	strBarTime = dataTimeToStr(pBarInfo->Time);
	LOG_TRACE<<strInfo<<"interval="<<interval<<" "<<"pBarInfo->Time="<<pBarInfo->Time;
	LOG_TRACE<<strInfo<<"interval="<<interval<<" "<<"strBarTime="<<strBarTime;
	LOG_TRACE<<strInfo<<"interval="<<interval<<" "<<"pBarInfo->Open="<<pBarInfo->Open;
	LOG_TRACE<<strInfo<<"interval="<<interval<<" "<<"pBarInfo->Close="<<pBarInfo->Close;
	LOG_TRACE<<strInfo<<"interval="<<interval<<" "<<"pBarInfo->High="<<pBarInfo->High;
	LOG_TRACE<<strInfo<<"interval="<<interval<<" "<<"pBarInfo->Low="<<pBarInfo->Low;
	LOG_TRACE<<strInfo<<"interval="<<interval<<" "<<"pBarInfo->Volume="<<pBarInfo->Volume;

}


void CCFDServerUtilityFun::logMarketDataInfo(const std::string& strInfo, const MarketData &marketData)
{
	BOOST_LOG_FUNCTION();
	//temp value
	MarketData::PriceType nPriceTypeValue = MarketData::LAST_TRADED_PRICE;
	MarketData::VolumeType nVolumeTypeValue = MarketData::LAST_TRADED_VOLUME;
	unsigned int nSecurityIDValue = 0;
	MarketData::MarketStatus nMarkerStatusValue = (MarketData::MarketStatus)MarketData::PRE_OPEN;
	unsigned int nTimeValue = 0;
	std::string  strTimeValue = "";
	int nVolumeValue = 0;
	int nBidVolValue = 0;
	int nAskVolValue = 0;
	float fPriceValue = 0;
	float fBidPxValue = 0;
	float fAskPxValue = 0;
	unsigned int nDataBitsValue = 0;
	unsigned int nChangeBitsValue = 0;
	//

	nSecurityIDValue = marketData.getSecurityID();
	nMarkerStatusValue = (MarketData::MarketStatus)(marketData.getMarketStatus());

// 	Tick  newTick;
// 	newTick.Time = marketData.getTime();//nTimeValue
// 	newTick.BidPx = marketData.getBidPx(1);//fBidPxValue
// 	newTick.AskPx = marketData.getAskPx(1);//fAskPxValue
// 	newTick.LastPx = marketData.getPrice(MarketData::LAST_TRADED_PRICE);//fPriceValue
// 	newTick.BidVol = marketData.getBidVol(1);//nBidVolValue
// 	newTick.AskVol = marketData.getAskVol(1);//nAskVolValue
// 	newTick.LastVol = marketData.getVolume(MarketData::LAST_TRADED_VOLUME);//nVolumeValue

	//
	nTimeValue = marketData.getTime();
	strTimeValue = dataTimeToStr(nTimeValue);
	fBidPxValue = marketData.getBidPx(1);
	fAskPxValue = marketData.getAskPx(1);
	fPriceValue = marketData.getPrice(nPriceTypeValue);

	nBidVolValue = marketData.getBidVol(1);
	nAskVolValue = marketData.getAskVol(1);
	nVolumeValue = marketData.getVolume(nVolumeTypeValue);

	nDataBitsValue = marketData.getDataBits();
	nChangeBitsValue = marketData.getChangeBits();
	//
	LOG_TRACE<<"MarketData"<<"->"<<"nSecurityIDValue="<<nSecurityIDValue;
	LOG_TRACE<<"MarketData"<<"->"<<"nMarkerStatusValue="<<nMarkerStatusValue;
	LOG_TRACE<<"MarketData"<<"->"<<"Tick"<<"->"<<"nTimeValue="<<nTimeValue;
	LOG_TRACE<<"MarketData"<<"->"<<"Tick"<<"->"<<"strTimeValue="<<strTimeValue;
	LOG_TRACE<<"MarketData"<<"->"<<"Tick"<<"->"<<"BidPx="<<fBidPxValue;
	LOG_TRACE<<"MarketData"<<"->"<<"Tick"<<"->"<<"AskPx="<<fAskPxValue;
	LOG_TRACE<<"MarketData"<<"->"<<"Tick"<<"->"<<"LastPx="<<fPriceValue;
	LOG_TRACE<<"MarketData"<<"->"<<"Tick"<<"->"<<"BidVol="<<nBidVolValue;
	LOG_TRACE<<"MarketData"<<"->"<<"Tick"<<"->"<<"AskVol="<<nAskVolValue;
	LOG_TRACE<<"MarketData"<<"->"<<"Tick"<<"->"<<"LastVol="<<nVolumeValue;

}



QT_END_NAMESPACE
















