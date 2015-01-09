#include "YahuoHistoryReqAck.h"

#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <sstream>

#include "BaseException.h"

CYahuoHistoryReqAck::CYahuoHistoryReqAck()
{

}

CYahuoHistoryReqAck::~CYahuoHistoryReqAck()
{

}


QString CYahuoHistoryReqAck::getRequestUrl(
	const QString &strSymbolUse, 
	qint32 startYear, qint32 startMonth, qint32 startDay,
	qint32 endYear, qint32 endMonth, qint32 endDay, 
	const QString &rangeType) 
{
	QString strUrl;
	std::stringstream byteUrl;

	byteUrl << "http://ichart.yahoo.com/table.csv?s="
		<< strSymbolUse.toStdString()
		<< "&a="
		<< startMonth - 1
		<< "&b="
		<< startDay
		<< "&c="
		<< startYear
		<< "&d="
		<< endMonth - 1
		<< "&e="
		<< endDay
		<< "&f="
		<< endYear
		<< "&g="
		<< rangeType.toStdString()
		<< "&ignore=.csv";

	strUrl = byteUrl.str().c_str();
	return strUrl;

	
	//"http://ichart.finance.yahoo.com/table.csv?s=600155.SS&a=00&b=1&c=2014&d=02&e=1&f=2014";
}//

QString CYahuoHistoryReqAck::getRequestUrl( const QString &strSymbolUse, 
qint32 startYear, qint32 startMonth, unsigned startDay, 
qint32 endYear, qint32 endMonth, qint32 endDay, const YahuoReqAck::RangeType &rangeType )
{
	QString strRangeTyep = YahuoReqAck::getString(rangeType);
	return getRequestUrl(strSymbolUse, startYear, startMonth, startDay, endYear, endMonth, endDay, strRangeTyep);
}






void CYahuoHistoryReqAck::test_CYahuoHistoryReqAck()
{

	CYahuoHistoryReqAck classCYahuoHistoryReqAck;
	QString strResGet;
	strResGet= classCYahuoHistoryReqAck.getRequestUrl("600667.SS", 2010, 4, 1, 2014, 10, 13, YahuoReqAck::dividendsOnly);
	// if data can not be retrieved by any of the functions, an exception is thrown

	QString petr4HistoricalPrices = classCYahuoHistoryReqAck.getRequestUrl("600667.SS",
		2014, 4, 2,
		2014, 10, 7,
		YahuoReqAck::daily);
}