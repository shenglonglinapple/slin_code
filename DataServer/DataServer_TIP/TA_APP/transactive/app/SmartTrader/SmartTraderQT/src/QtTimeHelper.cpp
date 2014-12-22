#include "QtTimeHelper.h"

#include <QtCore/QDateTime>
#include <QtCore/QUuid>



CQtTimeHelper::CQtTimeHelper()
{

}

CQtTimeHelper::~CQtTimeHelper()
{

}



time_t CQtTimeHelper::getTimeNow_Qt()
{
	QDateTime time_local;
	time_t timeGetTimeValue;

	time_local = QDateTime::currentDateTime();

	timeGetTimeValue = time_local.toTime_t();

	return timeGetTimeValue;
}

std::string CQtTimeHelper::dateTimeToStr_Qt(time_t secsSince1Jan1970UTC)
{
	//QDateTime	fromTime_t ( uint seconds )
	QDateTime time_utc;
	QDateTime time_local;
	QString   strTime_utc;
	QString   strTime_local;
	std::string strTime_local_Res;


	//time_utc.setTimeSpec(Qt::UTC);
	//time_utc.setTime_t(0);
	//QString strUTC = time_utc.toString("yyyy-MM-dd hh:mm:ss"); //strUTC = "1970-01-01 00:00:00"

	//time_local.setTimeSpec(Qt::LocalTime);
	//time_local.setTime_t(0);
	//QString strTime_local = time_local.toString("yyyy-MM-dd hh:mm:ss"); //strUTC = "1970-01-01 08:00:00"

	time_utc.setTimeSpec(Qt::UTC);
	time_utc.setTime_t(secsSince1Jan1970UTC);//(uint secsSince1Jan1970UTC
	strTime_utc = time_utc.toString("yyyy-MM-dd hh:mm:ss");

	time_local.setTimeSpec(Qt::LocalTime);
	time_local.setTime_t(secsSince1Jan1970UTC);//(uint secsSince1Jan1970UTC
	strTime_local = time_local.toString("yyyy-MM-dd hh:mm:ss");

	strTime_local_Res = strTime_local.toStdString();

	return strTime_local_Res;
}
time_t CQtTimeHelper::strToDateTime_Qt(const std::string& strTimeValue)
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


	strTime_local = strTimeValue.c_str();
	time_local = QDateTime::fromString(strTime_local, "yyyy-MM-dd hh:mm:ss");
	time_local.setTimeSpec(Qt::LocalTime);
	nTime_local = time_local.toTime_t();
	return nTime_local;
}

void CQtTimeHelper::getTimeInfo_Qt(time_t secsSince1Jan1970UTC,
								   unsigned int& nYear, unsigned int& nMonth, unsigned int& nDay)
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

//"12/10/2014 2:00am"
time_t CQtTimeHelper::strToDateTime_Qt_AmPm(const std::string& strTimeValue)
{
	QString   strTime_local;
	time_t    nTime_local;
	QDateTime time_local;

	strTime_local = strTimeValue.c_str();
	time_local = QDateTime::fromString(strTime_local, "MM/dd/yyyy h:mmap");
	time_local.setTimeSpec(Qt::LocalTime);
	nTime_local = time_local.toTime_t();
	return nTime_local;
}

QString CQtTimeHelper::getUUID()
{
	QUuid newUuid = QUuid::createUuid();
	//std::cout << qPrintable(newUuid.toString()) << std::endl;
	QString strUUID;
	strUUID = newUuid.toString();
	return strUUID;
}
