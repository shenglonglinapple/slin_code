#include "YahuoReqAck.h"
#include "BaseException.h"

YahuoReqAck::YahuoReqAck()
{

}

YahuoReqAck::~YahuoReqAck()
{

}

std::string YahuoReqAck::getString( RangeType rangeType )
{
	switch (rangeType) 
	{
	case YahuoReqAck::daily:
		return "d";
	case YahuoReqAck::weekly:
		return "w";
	case YahuoReqAck::monthly:
		return "m";
	case YahuoReqAck::dividendsOnly:
		return "v";
	}
	//throw CBaseException(__FILE__, __LINE__, __FUNCTION__, "missing RangeType conversion");
	throw CBaseException(__FILE__, __LINE__, "missing RangeType conversion");
}

std::string YahuoReqAck::getString( QuoteType quoteType )
{
	switch (quoteType) 
	{
	case YahuoReqAck::ask:
		return "a";
	case YahuoReqAck::averageDailyVolume:
		return "a2";
	case YahuoReqAck::askSize:
		return "a5";
	case YahuoReqAck::bid:
		return "b";
	case YahuoReqAck::askRealTime:
		return "b2";
	case YahuoReqAck::bidRealTime:
		return "b3";
	case YahuoReqAck::bookValue:
		return "b4";
	case YahuoReqAck::bidSize:
		return "b6";
	case YahuoReqAck::changeAndPercentChange:
		return "c";
	case YahuoReqAck::change:
		return "c1";
	case YahuoReqAck::commission:
		return "c3";
	case YahuoReqAck::changeRealTime:
		return "c6";
	case YahuoReqAck::afterHoursChangeRealTime:
		return "c8";
	case YahuoReqAck::dividendShare:
		return "d";
	case YahuoReqAck::lastTradeDate:
		return "d1";
	case YahuoReqAck::tradeDate:
		return "d2";
	case YahuoReqAck::earningsShare:
		return "e";
	case YahuoReqAck::errorIndication:
		return "e1";
	case YahuoReqAck::epsEstimateCurrentYear:
		return "e7";
	case YahuoReqAck::epsEstimateNextYear:
		return "e8";
	case YahuoReqAck::epsEstimateNextQuarter:
		return "e9";
	case YahuoReqAck::floatShares:
		return "f6";
	case YahuoReqAck::dayLow:
		return "g";
	case YahuoReqAck::dayHigh:
		return "h";
	case YahuoReqAck::_52WeekLow:
		return "j";
	case YahuoReqAck::_52WeekHigh:
		return "k";
	case YahuoReqAck::holdingsGainPercent:
		return "g1";
	case YahuoReqAck::annualizedGain:
		return "g3";
	case YahuoReqAck::holdingsGain:
		return "g4";
	case YahuoReqAck::holdingsGainPercentRealTime:
		return "g5";
	case YahuoReqAck::holdingsGainRealTime:
		return "g6";
	case YahuoReqAck::moreInfo:
		return "i";
	case YahuoReqAck::orderBookRealTime:
		return "i5";
	case YahuoReqAck::marketCapitalization:
		return "j1";
	case YahuoReqAck::marketCapRealTime:
		return "j3";
	case YahuoReqAck::ebitda:
		return "j4";
	case YahuoReqAck::changeFrom52WeekLow:
		return "j5";
	case YahuoReqAck::percentChangeFrom52WeekLow:
		return "j6";
	case YahuoReqAck::lastTradeRealTimeWithTime:
		return "k1";
	case YahuoReqAck::changePercentRealTime:
		return "k2";
	case YahuoReqAck::lastTradeSize:
		return "k3";
	case YahuoReqAck::changeFrom52WeekHigh:
		return "k4";
	case YahuoReqAck::percebtChangeFrom52WeekHigh:
		return "k5";
	case YahuoReqAck::lastTradeWithTime:
		return "l";
	case YahuoReqAck::lastTradePriceOnly:
		return "l1";
	case YahuoReqAck::highLimit:
		return "l2";
	case YahuoReqAck::lowLimit:
		return "l3";
	case YahuoReqAck::dayRange:
		return "m";
	case YahuoReqAck::dayRangeRealTime:
		return "m2";
	case YahuoReqAck::_50DayMovingAverage:
		return "m3";
	case YahuoReqAck::_200DayMovingAverage:
		return "m4";
	case YahuoReqAck::changeFrom200DayMovingAverage:
		return "m5";
	case YahuoReqAck::percentChangeFrom200DayMovingAverage:
		return "m6";
	case YahuoReqAck::changeFrom50DayMovingAverage:
		return "m7";
	case YahuoReqAck::percentChangeFrom50DayMovingAverage:
		return "m8";
	case YahuoReqAck::name:
		return "n";
	case YahuoReqAck::notes:
		return "n4";
	case YahuoReqAck::open:
		return "o";
	case YahuoReqAck::previousClose:
		return "p";
	case YahuoReqAck::pricePaid:
		return "p1";
	case YahuoReqAck::changeinPercent:
		return "p2";
	case YahuoReqAck::priceSales:
		return "p5";
	case YahuoReqAck::priceBook:
		return "p6";
	case YahuoReqAck::exDividendDate:
		return "q";
	case YahuoReqAck::peRatio:
		return "r";
	case YahuoReqAck::dividendPayDate:
		return "r1";
	case YahuoReqAck::peRatioRealTime:
		return "r2";
	case YahuoReqAck::pegRatio:
		return "r5";
	case YahuoReqAck::priceEpsEstimateCurrentYear:
		return "r6";
	case YahuoReqAck::priceEpsEstimateNextYear:
		return "r7";
	case YahuoReqAck::symbol:
		return "s";
	case YahuoReqAck::sharesOwned:
		return "s1";
	case YahuoReqAck::shortRatio:
		return "s7";
	case YahuoReqAck::lastTradeTime:
		return "t1";
	case YahuoReqAck::tradeLinks:
		return "t6";
	case YahuoReqAck::tickerTrend:
		return "t7";
	case YahuoReqAck::_1yrTargetPrice:
		return "t8";
	case YahuoReqAck::volume:
		return "v";
	case YahuoReqAck::holdingsValue:
		return "v1";
	case YahuoReqAck::holdingsValueRealTime:
		return "v7";
	case YahuoReqAck::_52WeekRange:
		return "w";
	case YahuoReqAck::dayValueChange:
		return "w1";
	case YahuoReqAck::dayValueChangeRealTime:
		return "w4";
	case YahuoReqAck::stockExchange:
		return "x";
	case YahuoReqAck::dividendYield:
		return "y";
	}
	throw CBaseException(__FILE__, __LINE__, "missing RangeType conversion");
}
