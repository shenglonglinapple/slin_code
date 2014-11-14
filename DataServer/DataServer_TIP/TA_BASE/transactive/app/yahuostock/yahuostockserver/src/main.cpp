//#include "vld.h"
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")//winsock2

#include "Log4cppLogger.h"


#include "YahuoReqAck.h"
#include "YahuoRealTimeReqAck.h"
#include "BaseException.h"
#include "YahuoHistoryReqAck.h"

void tetstCYahuoHistoryReqAck()
{

	CYahuoHistoryReqAck classCYahuoHistoryReqAck;
	std::cout << classCYahuoHistoryReqAck.getHistoricalQuotesCsv("600667.SS", 2010, 4, 1, 2014, 10, 13, YahuoReqAck::dividendsOnly) << std::endl;
	// if data can not be retrieved by any of the functions, an exception is thrown

	std::cout << "downloading... 2" << std::endl;
	std::string petr4HistoricalPrices = classCYahuoHistoryReqAck.getHistoricalQuotesCsv("600667.SS",
		2014, 4, 2,
		2014, 10, 7,
		YahuoReqAck::daily);
	std::cout << petr4HistoricalPrices << std::endl;
};

void testCYahuoRealTimeReqAck()
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
	std::string petr4Quotes = classCYahuoRealTimeReqAck.getLatestQuotesCsv("600667.SS", lstQuoteTypes);//"三全食品"
	std::cout << petr4Quotes << std::endl;
}



int main()
{
	CLog4cppLogger::getInstance();
	CLog4cppLogger::getInstance().initLog();
	CLog4cppLogger::getInstance().testLog();


	testCYahuoRealTimeReqAck();
	tetstCYahuoHistoryReqAck();


	CLog4cppLogger::removeInstance();
	return 0;
}