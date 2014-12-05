#ifndef __CLASS_YAHUO_HISTORY_REQACK_H__
#define __CLASS_YAHUO_HISTORY_REQACK_H__

#include <list>
#include "YahuoReqAck.h"

#include "YahuoReqAck.h"

class CYahuoHistoryReqAck 
{
public:
	CYahuoHistoryReqAck();
	virtual ~CYahuoHistoryReqAck();
public:
	std::string getHistoricalQuotesCsv(
		const std::string &instrument, 
		unsigned startYear, unsigned startMonth, unsigned startDay, 
		unsigned endYear, unsigned endMonth, unsigned endDay, 
		const std::string &rangeType);

	std::string getHistoricalQuotesCsv(
		const std::string &instrument, 
		unsigned startYear, unsigned startMonth, unsigned startDay, 
		unsigned endYear, unsigned endMonth, unsigned endDay, 
		const YahuoReqAck::RangeType &rangeType);
public:
	void test_CYahuoHistoryReqAck();
};


#endif //__CLASS_YAHUO_HISTORY_REQACK_H__
