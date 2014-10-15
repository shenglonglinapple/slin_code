//
//  csv_string.cpp
//  quote
//
//  Copyright (C) 2013, 2014  André Pereira Henriques
//  aphenriques (at) outlook (dot) com
//
//  This file is part of quote.
//
//  quote is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  quote is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with quote.  If not, see <http://www.gnu.org/licenses/>.
//

#include <iostream>
//#include <curl/curl.h>
#include "quote.h"



#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#ifndef UNDEBUG_FILE
#define DEBUG_FLAG 1
#else
#define DEBUG_FLAG 0
#endif

void test_c_log()
{
	printf( "The file is %s.\n", __FILE__ );
	printf( "The date is %s.\n", __DATE__ );
	printf( "The time is %s.\n", __TIME__ );
	printf( "This is line %d.\n", __LINE__ );
	printf( "This function is %s.\n", __FUNCTION__ );
}

int main(int argc, const char * argv[]) 
{
	test_c_log();

	try 
	{
		// manual curl initialization must be performed to use quote functions in a multi-threaded context, otherwise it can be ignored.
		// check http://curl.haxx.se/libcurl/c/curl_easy_init.html
		//curl_global_init(CURL_GLOBAL_ALL);

		std::cout << "downloading... 1" << std::endl;
		// more QuoteType types are available in QuoteTypes.h
// 		std::cout << quote::getLatestQuotesCsv(
// 			"petr4.sa",
// 		{quote::QuoteType::symbol, 
// 		quote::QuoteType::name,
// 		quote::QuoteType::lastTradePriceOnly, 
// 		quote::QuoteType::lastTradeDate, 
// 		quote::QuoteType::lastTradeTime, 
// 		quote::QuoteType::open, 
// 		quote::QuoteType::dayLow, 
// 		quote::QuoteType::dayHigh, 
// 		quote::QuoteType::dayRange, 
// 		quote::QuoteType::dividendShare, 
// 		quote::QuoteType::peRatio}
// 		) << std::endl;
		std::list<quote::QuoteType> lstQuoteTypes;
		lstQuoteTypes.push_back(quote::QuoteType::symbol);
		lstQuoteTypes.push_back(quote::QuoteType::name);
		lstQuoteTypes.push_back(quote::QuoteType::lastTradePriceOnly);
		lstQuoteTypes.push_back(quote::QuoteType::lastTradeDate);
		lstQuoteTypes.push_back(quote::QuoteType::lastTradeTime);
		lstQuoteTypes.push_back(quote::QuoteType::open);
		lstQuoteTypes.push_back(quote::QuoteType::dayLow);
		lstQuoteTypes.push_back(quote::QuoteType::dayHigh);
		lstQuoteTypes.push_back(quote::QuoteType::dayRange);
		lstQuoteTypes.push_back(quote::QuoteType::dividendShare);
		lstQuoteTypes.push_back(quote::QuoteType::peRatio);

		std::string petr4Quotes = quote::getLatestQuotesCsv("petr4.sa", lstQuoteTypes);
		std::cout << petr4Quotes << std::endl;

		// QuoteType types can also be passed as template parameters
		//std::cout << quote::getLatestQuotesCsv<quote::QuoteType::symbol, quote::QuoteType::name, quote::QuoteType::lastTradePriceOnly, quote::QuoteType::lastTradeDate, quote::QuoteType::lastTradeTime, quote::QuoteType::open, quote::QuoteType::dayLow, quote::QuoteType::dayHigh, quote::QuoteType::dayRange, quote::QuoteType::dividendShare, quote::QuoteType::peRatio>("MSFT") << std::endl;
		std::cout << quote::getHistoricalQuotesCsv("petr4.sa", 2010, 4, 1, 2014, 10, 13, quote::RangeType::dividendsOnly) << std::endl;
		// if data can not be retrieved by any of the functions, an exception is thrown

		std::cout << "downloading... 2" << std::endl;
		std::string petr4HistoricalPrices = quote::getHistoricalQuotesCsv("petr4.sa",
			2014, 4, 2,
			2014, 10, 7,
			quote::RangeType::daily);
		std::cout << petr4HistoricalPrices << std::endl;

	} 
	catch (const std::exception& exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
		return 1;
	} 
	catch (...) 
	{
		std::cerr << "Error: unknown exception" << std::endl;
		return 1;
	}
	std::cout << "end of sample" << std::endl;
	return 0;
}




#if 0
#include <iostream>
#include "quote.h"

int main(int argc, const char * argv[]) {
	// all Yahoo! Finance quote types are implemented (this is just a sample)
	std::string petr4Quotes = quote::getLatestQuotesCsv("petr4.sa", {quote::QuoteType::symbol,
		quote::QuoteType::name,
		quote::QuoteType::lastTradePriceOnly,
		quote::QuoteType::lastTradeDate,
		quote::QuoteType::lastTradeTime});
	std::cout << petr4Quotes << std::endl;
	// quote ranges can be daily, weekly, monthly, or dividends only
	std::string petr4HistoricalPrices = quote::getHistoricalQuotesCsv("petr4.sa",
		2014, 4, 2,
		2014, 4, 7,
		quote::RangeType::daily);
	std::cout << petr4HistoricalPrices << std::endl;
	return 0;
}
// prints:
// "PETR4.SA","PETROBRAS   -PN",15.96,"4/22/2014","4:07pm"
// Date,Open,High,Low,Close,Volume,Adj Close
// 2014-04-07,15.70,16.46,15.70,16.46,50400200,16.46
// 2014-04-04,15.62,15.71,15.35,15.44,33173500,15.44
// 2014-04-03,15.53,15.65,15.12,15.40,56189100,15.40
// 2014-04-02,15.71,16.60,15.70,15.56,66007000,14.59
#endif








