#ifndef __CLASS_YAHUO_HISTORY_REQACK_H__
#define __CLASS_YAHUO_HISTORY_REQACK_H__

#include <QtCore/QString>
#include "YahuoReqAck.h"

class CYahuoHistoryReqAck 
{
public:
	CYahuoHistoryReqAck();
	virtual ~CYahuoHistoryReqAck();
public:
	QString getRequestUrl(
		const QString &strSymbolUse, 
		qint32 startYear, qint32 startMonth, qint32 startDay, 
		qint32 endYear, qint32 endMonth, qint32 endDay, 
		const QString &rangeType);


	QString getRequestUrl(
		const QString &strSymbolUse, 
		qint32 startYear, qint32 startMonth, unsigned startDay,
		qint32 endYear, qint32 endMonth, qint32 endDay, 
		const YahuoReqAck::RangeType &rangeType );
public:
	void test_CYahuoHistoryReqAck();
};


#endif //__CLASS_YAHUO_HISTORY_REQACK_H__
