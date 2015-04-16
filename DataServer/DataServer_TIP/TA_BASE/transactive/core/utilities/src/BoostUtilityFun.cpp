#include "core/utilities/src/BoostUtilityFun.h"


NS_BEGIN(TA_Base_Core)


CBoostUtilityFun::CBoostUtilityFun( void )
{

}

CBoostUtilityFun::~CBoostUtilityFun( void )
{

}




//////////////////////////////////////////////////////////////////////////
/////b/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



//0C632E95-26C6-A803-C191-FDCA3A738D0D
std::string CBoostUtilityFun::mysys_boost_generateUUID()
{
	std::string strUUID36;

	boost::uuids::uuid nUUID = boost::uuids::random_generator()();
	//std::cout << uuid << std::endl;
	//7feb24af-fc38-44de-bc38-04defc3804de
	strUUID36 = boost::lexical_cast<std::string>(nUUID);

	// Return the UUID as a std::string
	return strUUID36;
}







//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


//"%d-%d-%d %d:%d:%d"
//YYYY-MM-DD HH:MM:SS
time_t CBoostUtilityFun::mysys_boost_StrToDateTime(const std::string& strTimeValue)
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




//"%04d-%02d-%02d %02d:%02d:%02d"
std::string CBoostUtilityFun::mysys_boost_DataTimeToStr(time_t nTimeValue)
{
	std::string	strTimeString;
	boost::posix_time::ptime boostTimeValue;
	boostTimeValue = boost::posix_time::from_time_t(nTimeValue);
	strTimeString = _GetTimeString(&boostTimeValue);
	//"%04d-%02d-%02d %02d:%02d:%02d"
	return strTimeString;
}

//m_pWorkTime->getTimeString(&boostTimeValue);
std::string CBoostUtilityFun::_GetTimeString(boost::posix_time::ptime* pfbtime)
{
	std::string	strTimeStringTmp;
	std::string	strTimeStringGet;
	int pos = 0;
	std::string strSubTmp;
	std::string strYear;
	std::string strMonth;
	std::string strDay;
	std::string strHour;
	std::string strMin;
	std::string strSecond;

	if (NULL == pfbtime)
	{
		return strTimeStringGet;
	}

	//linshenglong take care   20140218T150717.514548 or 20140218T150717
	//YYYYMMDDTHHMMSS.SSSSSS or YYYYMMDDTHHMMSS
	//std::string strTime = boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());
	strTimeStringTmp = boost::posix_time::to_iso_string(*pfbtime);

	if (strTimeStringTmp.size() > 4)
	{
		//YYYY
		strYear = strTimeStringTmp.substr(0, 4);
		//MMDDTHHMMSS.SSSSSS
		strSubTmp = strTimeStringTmp.substr(4);
	}
	else
	{
		return strTimeStringGet;
	}

	if (strSubTmp.size() > 2)
	{
		//MM
		strMonth = strSubTmp.substr(0, 2);
		//DDTHHMMSS.SSSSSS
		strSubTmp = strSubTmp.substr(2);
	}
	else
	{
		return strTimeStringGet;
	}

	if (strSubTmp.size() > 3)
	{
		//DD
		strDay = strSubTmp.substr(0, 2);
		//HHMMSS.SSSSSS
		strSubTmp = strSubTmp.substr(3);
	}
	else
	{
		return strTimeStringGet;
	}

	if (strSubTmp.size() > 2)
	{
		//HH
		strHour = strSubTmp.substr(0, 2);
		//MMSS.SSSSSS
		strSubTmp = strSubTmp.substr(2);
	}
	else
	{
		return strTimeStringGet;
	}

	if (strSubTmp.size() > 2)
	{
		//MM
		strMin = strSubTmp.substr(0, 2);
		//SS.SSSSSS
		strSubTmp = strSubTmp.substr(2);
	}
	else
	{
		return strTimeStringGet;
	}

	if (strSubTmp.size() >= 2)
	{
		//SS
		strSecond = strSubTmp.substr(0, 2);
	}
	else
	{
		return strTimeStringGet;
	}

	//"%04d-%02d-%02d %02d:%02d:%02d"
	strTimeStringGet = strYear + "-" + strMonth + "-" + strDay + " " + strHour + ":" + strMin + ":" + strSecond;

	return strTimeStringGet;
}

int  CBoostUtilityFun::mysys_boost_ToLwr(std::string &strSrc)
{
	int nFunRes = 0;
	if (strSrc.empty())
	{
		return nFunRes;
	}

	boost::algorithm::to_lower(strSrc);
	//boost::algorithm::to_lower_copy(strSrc);
	return nFunRes;
}

int  CBoostUtilityFun::mysys_boost_ToUpper(std::string &strSrc)
{
	int nFunRes = 0;
	if (strSrc.empty())
	{
		return nFunRes;
	}

	boost::algorithm::to_upper(strSrc);
	//boost::algorithm::to_lower_copy(strSrc);
	return nFunRes;

}


int  CBoostUtilityFun::mysys_boost_trim(std::string& strSrc)
{
	int nFunRes = 0;

	boost::algorithm::trim(strSrc);

	return nFunRes;
}

int	CBoostUtilityFun::mysys_boost_stricmp(std::string& strLeft, std::string& strRight)
{
	int nFunRes = 0;
	std::string strLeftCopy;
	std::string strRightCopy;

	strLeftCopy	= strLeft;
	strRightCopy = strRight;

	boost::algorithm::to_upper(strLeftCopy);
	boost::algorithm::to_upper(strRight);

	nFunRes = -1;
	if (strLeftCopy == strRightCopy)
	{
		nFunRes = 0;
	}

	return nFunRes;
}

std::string	CBoostUtilityFun::mysys_boost_intTostr(int nVal)
{
	std::string strNumber;

	strNumber = boost::lexical_cast<std::string>(nVal);

	return strNumber;
}

std::string	CBoostUtilityFun::mysys_boost_unsignedintTostr(unsigned int nVal)
{
	std::string strNumber;

	strNumber = boost::lexical_cast<std::string>(nVal);

	return strNumber;
}

int	CBoostUtilityFun::mysys_boost_strToint(std::string& strNumber)
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

double CBoostUtilityFun::mysys_boost_strTodouble( std::string& strNumber )
{
	double nNumber;
	if (strNumber.empty())
	{
		nNumber = 0;
		return nNumber;
	}

	nNumber = boost::lexical_cast<double>(strNumber);

	return nNumber;

}



void CBoostUtilityFun::mysys_boost_sleep(int ms)
{
	boost::xtime timeTmp;
	boost::xtime_get(&timeTmp, boost::TIME_UTC_);
	timeTmp.nsec += ms%1000*1000*1000;
	timeTmp.sec += ms/1000;
	boost::thread::sleep(timeTmp);
}


//////////////////////////////////////////////////////////////////////////
////boost//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////





#if 0


std::string  CBoostUtilityFun::mysys_boost_GetTimeStr(unsigned int uTimeVale)
{
	int nFunRes = 0;
	unsigned int nGetTime = 0;
	tm* ptmVale;
	time_t timetValue;
	boost::posix_time::ptime ptimeTimetValue;
	boost::posix_time::ptime ptimePtmValue;
	std::string  strGetTime;

	nGetTime =  uTimeVale;
	timetValue = (time_t)nGetTime;
	time ( &timetValue );
	//printf ( "The current local time is: %s", ctime (&rawtime) );
	strGetTime = ctime (&timetValue);

	timetValue = (time_t)nGetTime; 
	ptmVale = localtime( &timetValue );
	timetValue = mktime( ptmVale );

	ptimeTimetValue = boost::posix_time::from_time_t( timetValue );
	ptimePtmValue = boost::posix_time::ptime_from_tm( *ptmVale );

	strGetTime = boost::posix_time::to_simple_string(ptimeTimetValue);
	strGetTime = boost::posix_time::to_simple_string(ptimePtmValue);

	return strGetTime;
}

//"%04d-%02d-%02d %02d:%02d:%02d"
std::string CBoostUtilityFun::mysys_boost_DataTimeToStr(time_t nTimeValue)
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




NS_END(TA_Base_Core)
















