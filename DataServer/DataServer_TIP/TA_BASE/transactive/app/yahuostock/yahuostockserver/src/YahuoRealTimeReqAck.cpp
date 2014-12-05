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
			std::string latestQuotesCsv = CurlUtil::getInstance().getUrlData(url.str());
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





void CYahuoRealTimeReqAck::test_CYahuoRealTimeReqAck()
{
	std::list<YahuoReqAck::QuoteType> lstQuoteTypes;
	lstQuoteTypes.push_back(YahuoReqAck::stockExchange);
	lstQuoteTypes.push_back(YahuoReqAck::symbol);
	lstQuoteTypes.push_back(YahuoReqAck::changeRealTime);
	lstQuoteTypes.push_back(YahuoReqAck::changeinPercent);
	lstQuoteTypes.push_back(YahuoReqAck::lastTradeDate);
	lstQuoteTypes.push_back(YahuoReqAck::lastTradeTime);
	lstQuoteTypes.push_back(YahuoReqAck::open);
	lstQuoteTypes.push_back(YahuoReqAck::bid);
	lstQuoteTypes.push_back(YahuoReqAck::ask);
	lstQuoteTypes.push_back(YahuoReqAck::dayLow);
	lstQuoteTypes.push_back(YahuoReqAck::dayHigh);
	lstQuoteTypes.push_back(YahuoReqAck::dayRange);
	lstQuoteTypes.push_back(YahuoReqAck::lastTradePriceOnly);
	lstQuoteTypes.push_back(YahuoReqAck::_1yrTargetPrice);
	lstQuoteTypes.push_back(YahuoReqAck::volume);
	lstQuoteTypes.push_back(YahuoReqAck::averageDailyVolume);
	lstQuoteTypes.push_back(YahuoReqAck::name);

	CYahuoRealTimeReqAck  classCYahuoRealTimeReqAck;
	std::string petr4Quotes = classCYahuoRealTimeReqAck.getLatestQuotesCsv("600667.SS", lstQuoteTypes);//"Ì«¼«ÊµÒµ"
	std::cout << petr4Quotes << std::endl;
}
