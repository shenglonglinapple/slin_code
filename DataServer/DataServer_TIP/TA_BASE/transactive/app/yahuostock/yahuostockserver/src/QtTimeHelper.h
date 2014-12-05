#ifndef __CLASS_QT_TIME_HELPER_H__
#define __CLASS_QT_TIME_HELPER_H__

#include <string>
#include <time.h>

class CQtTimeHelper 
{
public:
	CQtTimeHelper();
	virtual ~CQtTimeHelper();
public:
	time_t getTimeNow_Qt();
	std::string dateTimeToStr_Qt(time_t secsSince1Jan1970UTC);
	void getTimeInfo_Qt(time_t secsSince1Jan1970UTC,
		unsigned int& nYear, unsigned int& nMonth, unsigned int& nDay);
	time_t strToDateTime_Qt(const std::string& strTimeValue);
public:




};


#endif //__CLASS_QT_TIME_HELPER_H__
