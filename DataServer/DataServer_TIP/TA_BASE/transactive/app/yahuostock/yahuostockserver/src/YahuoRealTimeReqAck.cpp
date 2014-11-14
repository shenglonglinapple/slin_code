#include "YahuoRealTimeReqAck.h"

#include <fstream>
#include <sstream>
#include "CurlUtil.h"
#include "BaseException.h"

CYahuoRealTimeReqAck::CYahuoRealTimeReqAck()
{

}

CYahuoRealTimeReqAck::~CYahuoRealTimeReqAck()
{

}


std::string CYahuoRealTimeReqAck::getLatestQuotesCsv(
	const std::string &instruments, 
	const std::string &quoteTypes)
{
	if (instruments.empty() == false)
	{
		if (quoteTypes.empty() == false) 
		{
			std::stringstream url;
			url << "http://finance.yahoo.com/d/quotes.csv?s="
				<< instruments
				<< "&f="
				<< quoteTypes;
			std::string latestQuotesCsv = CurlUtil::getUrlData(url.str());
			//detail::string_util::trim(latestQuotesCsv);
			if (latestQuotesCsv.empty() || latestQuotesCsv.at(0) != '<') 
			{ // leading '<' indicates server error
				//return std::move(latestQuotesCsv);
				return latestQuotesCsv;
			} 
			else 
			{
				throw CBaseException(__FILE__, __LINE__, "server (Yahoo! Finance) error");
			}
		}
		else 
		{
			//throw CBaseException(__FILE__, __LINE__, "missing RangeType conversion");
			throw CBaseException(__FILE__, __LINE__, "empty quoteTypes");
		}
	} 
	else 
	{
		//throw Exception(__FILE__, __LINE__, __FUNCTION__, "empty instruments parameter");
		throw CBaseException(__FILE__, __LINE__, "empty instruments parameter");
	}
}

std::string CYahuoRealTimeReqAck::getLatestQuotesCsv(
	const std::string &instruments,
	std::list<YahuoReqAck::QuoteType> quoteTypes)
{
	std::string quoteTypesString;
	std::list<YahuoReqAck::QuoteType>::iterator iterLst;
	iterLst = quoteTypes.begin();
	while (iterLst != quoteTypes.end())
	{
		std::string strQuotesType;
		strQuotesType.clear();
		strQuotesType = YahuoReqAck::getString(*iterLst);

		//quoteTypesString.append(detail::conversion::getString(quoteType));
		quoteTypesString.append(strQuotesType);

		iterLst++;
	}
	return this->getLatestQuotesCsv(instruments, quoteTypesString);
}

