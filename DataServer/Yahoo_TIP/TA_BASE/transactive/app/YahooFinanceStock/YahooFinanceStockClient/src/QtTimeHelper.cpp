#include "QtTimeHelper.h"

#include <QtCore/QDateTime>
#include "ProjectCommonData.h"

CQtTimeHelper::CQtTimeHelper()
{

}

CQtTimeHelper::~CQtTimeHelper()
{

}



time_t CQtTimeHelper::getCurrentTime()
{
	QDateTime time_local;
	time_t timeGetTimeValue;

	time_local = QDateTime::currentDateTime();

	timeGetTimeValue = time_local.toTime_t();

	return timeGetTimeValue;
}

QString CQtTimeHelper::getCurrentTimeStr()
{
	QString strCurrentTime;
	QDateTime time_local;
	time_local.setTimeSpec(Qt::LocalTime);
	time_local = QDateTime::currentDateTime();

	//strCurrentTime = time_local.toString("yyyy-MM-dd hh:mm:ss");
	strCurrentTime = time_local.toString(DEFVALUE_String_DataTime_Format);
	return strCurrentTime;
}


QString  CQtTimeHelper::getStringValue(time_t secsSince1Jan1970UTC)
{
	//QDateTime	fromTime_t ( uint seconds )
	QDateTime time_utc;
	QDateTime time_local;
	QString   strTime_utc;
	QString   strTime_local;
	QString  strTime_local_Res;


	//time_utc.setTimeSpec(Qt::UTC);
	//time_utc.setTime_t(0);
	//QString strUTC = time_utc.toString("yyyy-MM-dd hh:mm:ss"); //strUTC = "1970-01-01 00:00:00"

	//time_local.setTimeSpec(Qt::LocalTime);
	//time_local.setTime_t(0);
	//QString strTime_local = time_local.toString("yyyy-MM-dd hh:mm:ss"); //strUTC = "1970-01-01 08:00:00"

	time_utc.setTimeSpec(Qt::UTC);
	time_utc.setTime_t(secsSince1Jan1970UTC);//(uint secsSince1Jan1970UTC
	strTime_utc = time_utc.toString(DEFVALUE_String_DataTime_Format);
	//strTime_utc = time_utc.toString("yyyy-MM-dd hh:mm:ss");
	//

	time_local.setTimeSpec(Qt::LocalTime);
	time_local.setTime_t(secsSince1Jan1970UTC);//(uint secsSince1Jan1970UTC
	//strTime_local = time_local.toString("yyyy-MM-dd hh:mm:ss");
	strTime_local = time_local.toString(DEFVALUE_String_DataTime_Format);

	strTime_local_Res = strTime_local;

	return strTime_local_Res;
}

QString CQtTimeHelper::getStringValue( const QDateTime& nDataTime )
{
	QString   strTime_local;
	QDateTime time_local = nDataTime;
	time_local.setTimeSpec(Qt::LocalTime);

	strTime_local = time_local.toString(DEFVALUE_String_DataTime_Format);
	return strTime_local;
}


QDateTime CQtTimeHelper::getDateTimeValue( const QString & strTimeValue )
{
	QDateTime time_local;
	QString   strTime_local;

	strTime_local = strTimeValue;
	time_local.setTimeSpec(Qt::LocalTime);
	time_local = QDateTime::fromString(strTime_local, DEFVALUE_String_DataTime_Format);
	//
	return time_local;
}

time_t CQtTimeHelper::getTimeValue(const QString & strTimeValue)
{
	QString   strTime_local;
	time_t    nTime_local;
	QDateTime time_local;
	/*
	QDateTime dateTime = QDateTime::fromString("1970-01-01 08:00:00","yyyy-MM-dd hh:mm:ss");
	dateTime.setTimeSpec(Qt::LocalTime);
	uint secondsLocal= dateTime.toTime_t();  //secondsLocal =0;
	dateTime.setTimeSpec(Qt::UTC);
	uint secondsUTC = dateTime.toTime_t();   //secondsUTC = 28800;8Сʱ
	*/


	strTime_local = strTimeValue;
	//time_local = QDateTime::fromString(strTime_local, "yyyy-MM-dd hh:mm:ss");
	time_local = QDateTime::fromString(strTime_local, DEFVALUE_String_DataTime_Format);
	//
	time_local.setTimeSpec(Qt::LocalTime);
	nTime_local = time_local.toTime_t();
	return nTime_local;
}

void CQtTimeHelper::getTimeYearMonthDay(
	time_t secsSince1Jan1970UTC,
	unsigned int& nYear, 
	unsigned int& nMonth, 
	unsigned int& nDay)
{
	QDateTime time_local;
	QDate date_local;
	int nYearGet;
	int nMonthGet;
	int nDayGet;

	time_local.setTimeSpec(Qt::LocalTime);
	time_local.setTime_t(secsSince1Jan1970UTC);//(uint secsSince1Jan1970UTC
	date_local = time_local.date();
	date_local.getDate(&nYearGet, &nMonthGet, &nDayGet);

	nYear = nYearGet;
	nMonth = nMonthGet;
	nDay = nDayGet;

}
