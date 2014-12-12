#include "MyMarketData.h"

#include <QtCore/QString>
#include <QtCore/QStringList>



CMyMarketData::CMyMarketData()
{

}

CMyMarketData::CMyMarketData( unsigned int secID )
{

}

CMyMarketData::CMyMarketData( const CMyMarketData & )
{

}

CMyMarketData::~CMyMarketData()
{

}

CMyMarketData & CMyMarketData::operator=( const CMyMarketData & )
{

	return *this;
}

void CMyMarketData::setSecurityID( unsigned int secID )
{
	m_nSecurityID = secID;
}

unsigned int CMyMarketData::getSecurityID() const
{
	return m_nSecurityID;
}

int CMyMarketData::getMarketStatus() const
{
	return m_nMarketStatus;
}

unsigned int CMyMarketData::getTime() const
{
	return m_nTime;
}

int CMyMarketData::getVolume( int type ) const
{
	enum VolumeType nVolumeType = (enum VolumeType)type;
	switch (nVolumeType)
	{
	case OPEN_INTEREST:
		return m_nVolume_OPEN_INTEREST;
		break;
	case OPENING_VOLUME:
		return m_nVolume_OPENING_VOLUME;
		break;
	case LAST_TRADED_VOLUME:
		return m_nVolume_LAST_TRADED_VOLUME;
		break;
	case TOTAL_TRADED_VOLUME:
		return m_nVolume_TOTAL_TRADED_VOLUME;
		break;
	}
	return m_nVolume_LAST_TRADED_VOLUME;

}

int CMyMarketData::getBidVol( int level ) const
{
	return m_nBidVol;
}

int CMyMarketData::getAskVol( int level ) const
{
	return m_nAskVol;
}

float CMyMarketData::getPrice( int type ) const
{
	enum PriceType nPriceType = (enum PriceType)type;
	switch (nPriceType)
	{
	case OPENNING_PRICE:
		return m_fPrice_OPENNING_PRICE;
		break;
	case SESSION_HIGH:
		return m_fPrice_SESSION_HIGH;
		break;
	case SESSION_LOW:
		return m_fPrice_SESSION_LOW;
		break;
	case REFERENCE_PRICE:
		return m_fPrice_REFERENCE_PRICE;
		break;
	case YESTERDAY_SETTLMENT_PRICE:
		return m_fPrice_YESTERDAY_SETTLMENT_PRICE;
		break;
	case LAST_TRADED_PRICE:
		return m_fPrice_LAST_TRADED_PRICE;
		break;
	case SETTLEMENT_PRICE:
		return m_fPrice_SETTLEMENT_PRICE;
		break;
	}
	return m_fPrice_LAST_TRADED_PRICE;

}

float CMyMarketData::getBidPx( int level ) const
{
	return m_fBidPx;
}

float CMyMarketData::getAskPx( int level ) const
{
	return m_fAskPx;
}

unsigned int CMyMarketData::getDataBits() const
{
	return m_nDataBits;
}

unsigned int CMyMarketData::getChangeBits() const
{
	return m_nChangeBits;
}

void CMyMarketData::setValue( const std::string& strData )
{
	//TODO
	/*
	"Shanghai","600667.SS","+0.26","+4.60%","12/10/2014","2:00am",5.76,5.91,5.92,5.44,6.11,"5.44 - 6.11",5.91,N/A,128066608,0,""
	*/
	/*
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
	*/
	
	
	QString strGetData;
	QStringList strLstGetData;
	int nIndex = 0;

	strGetData = strData.c_str();
	strLstGetData = strGetData.split(",");

	QString stockExchange;
	QString symbol;
	QString changeRealTime;
	QString changeinPercent;
	QString lastTradeDate;
	QString lastTradeTime;
	QString open;
	QString bid;
	QString ask;
	QString dayLow;
	QString dayHigh;
	QString dayRange;
	QString lastTradePriceOnly;
	QString str_1yrTargetPrice;
	QString volume;
	QString averageDailyVolume;
	QString name;


	nIndex = 0;
	stockExchange = strLstGetData[nIndex];
	nIndex++;
	symbol = strLstGetData[nIndex];
	nIndex++;
	changeRealTime = strLstGetData[nIndex];
	nIndex++;
	changeinPercent = strLstGetData[nIndex];
	nIndex++;
	lastTradeDate = strLstGetData[nIndex];
	nIndex++;
	lastTradeTime = strLstGetData[nIndex];
	nIndex++;
	open = strLstGetData[nIndex];
	nIndex++;
	bid = strLstGetData[nIndex];
	nIndex++;
	ask = strLstGetData[nIndex];
	nIndex++;
	dayLow = strLstGetData[nIndex];
	nIndex++;
	dayHigh = strLstGetData[nIndex];
	nIndex++;
	dayRange = strLstGetData[nIndex];
	nIndex++;
	lastTradePriceOnly = strLstGetData[nIndex];
	nIndex++;
	str_1yrTargetPrice = strLstGetData[nIndex];
	nIndex++;
	volume = strLstGetData[nIndex];
	nIndex++;
	averageDailyVolume = strLstGetData[nIndex];
	nIndex++;
	name = strLstGetData[nIndex];
	
}
