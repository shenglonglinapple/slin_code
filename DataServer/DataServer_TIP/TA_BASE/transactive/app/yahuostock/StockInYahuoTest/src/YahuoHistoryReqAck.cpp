#include "YahuoHistoryReqAck.h"

#include <fstream>
#include <sstream>
#include "CurlUtil.h"
#include "BaseException.h"

CYahuoHistoryReqAck::CYahuoHistoryReqAck()
{

}

CYahuoHistoryReqAck::~CYahuoHistoryReqAck()
{

}


std::string CYahuoHistoryReqAck::getHistoricalQuotesCsv(
	const std::string &instrument, 
	unsigned startYear, unsigned startMonth, unsigned startDay,
	unsigned endYear, unsigned endMonth, unsigned endDay, 
	const std::string &rangeType) 
{
	if (instrument.empty() == false) 
	{
		std::stringstream url;
		url << "http://ichart.yahoo.com/table.csv?s="
			<< instrument
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
			<< rangeType
			<< "&ignore=.csv";

		std::string historicalQuotesCsv = CurlUtil::getUrlData(url.str());
		
		//detail::string_util::trim(historicalQuotesCsv);
		if (historicalQuotesCsv.empty() || historicalQuotesCsv.at(0) != '<')
		{ // leading '<' indicates server error
			//return std::move(historicalQuotesCsv);
			return historicalQuotesCsv;
		} 
		else
		{
			throw CBaseException(__FILE__, __LINE__, "server (Yahoo! Finance) error");
		}
	} 
	else 
	{
		throw CBaseException(__FILE__, __LINE__, "empty instrument parameter");
	}
}//CYahuoHistoryReqAck

std::string CYahuoHistoryReqAck::getHistoricalQuotesCsv( const std::string &instrument, 
unsigned startYear, unsigned startMonth, unsigned startDay, 
unsigned endYear, unsigned endMonth, unsigned endDay, const YahuoReqAck::RangeType &rangeType )
{
	std::string strRangeTyep = YahuoReqAck::getString(rangeType);
	return getHistoricalQuotesCsv(instrument, startYear, startMonth, startDay, endYear, endMonth, endDay, strRangeTyep);
}
