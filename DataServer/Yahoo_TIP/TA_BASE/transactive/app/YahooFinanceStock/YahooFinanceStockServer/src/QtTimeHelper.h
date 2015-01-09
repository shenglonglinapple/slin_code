#ifndef __CLASS_QT_TIME_HELPER_H__
#define __CLASS_QT_TIME_HELPER_H__

#include <time.h>
#include <QtCore/QString>

class CQtTimeHelper 
{
public:
	CQtTimeHelper();
	virtual ~CQtTimeHelper();
public:
	time_t getTimeNow_Qt();
	QString  dateTimeToStr_Qt(time_t secsSince1Jan1970UTC);
	time_t strToDateTime_Qt(const QString & strTimeValue);

public:
	void getTimeInfo_Qt(time_t secsSince1Jan1970UTC,unsigned int& nYear, unsigned int& nMonth, unsigned int& nDay);




};


#endif //__CLASS_QT_TIME_HELPER_H__
