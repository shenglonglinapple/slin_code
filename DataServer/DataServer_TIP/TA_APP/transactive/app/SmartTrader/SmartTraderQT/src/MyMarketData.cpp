#include "MyMarketData.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include "ProjectCommonData.h"
#include "QtTimeHelper.h"
#include "HistoryData.h"

CMyMarketData::CMyMarketData()
{
	_ClearData();
}

CMyMarketData::CMyMarketData( unsigned int secID )
{
	_ClearData();
}	

CMyMarketData::CMyMarketData( const CMyMarketData & )
{
	_ClearData();
}

CMyMarketData::~CMyMarketData()
{
	_ClearData();
}

CMyMarketData & CMyMarketData::operator=( const CMyMarketData & objcopy)
{
	m_nInstrumentID = objcopy.m_nInstrumentID;
	m_strInstrumentCode = objcopy.m_strInstrumentCode;
	m_nMarketStatus = objcopy.m_nMarketStatus;
	m_nTime = objcopy.m_nTime;
	m_nVolume_OPEN_INTEREST = objcopy.m_nVolume_OPEN_INTEREST;
	m_nVolume_OPENING_VOLUME = objcopy.m_nVolume_OPENING_VOLUME;
	m_nVolume_LAST_TRADED_VOLUME = objcopy.m_nVolume_LAST_TRADED_VOLUME;
	m_nVolume_TOTAL_TRADED_VOLUME = objcopy.m_nVolume_TOTAL_TRADED_VOLUME;
	m_nBidVol = objcopy.m_nBidVol;
	m_nAskVol = objcopy.m_nAskVol;
	m_fPrice_OPENNING_PRICE = objcopy.m_fPrice_OPENNING_PRICE;
	m_fPrice_SESSION_HIGH = objcopy.m_fPrice_SESSION_HIGH;
	m_fPrice_SESSION_LOW = objcopy.m_fPrice_SESSION_LOW;
	m_fPrice_REFERENCE_PRICE = objcopy.m_fPrice_REFERENCE_PRICE;
	m_fPrice_YESTERDAY_SETTLMENT_PRICE = objcopy.m_fPrice_YESTERDAY_SETTLMENT_PRICE;
	m_fPrice_LAST_TRADED_PRICE = objcopy.m_fPrice_LAST_TRADED_PRICE;
	m_fPrice_SETTLEMENT_PRICE = objcopy.m_fPrice_SETTLEMENT_PRICE;
	m_fBidPx = objcopy.m_fBidPx;
	m_fAskPx = objcopy.m_fAskPx;
	m_nDataBits = objcopy.m_nDataBits;
	m_nChangeBits = objcopy.m_nChangeBits;

	return *this;
}
void CMyMarketData::_ClearData()
{
	m_nInstrumentID = 0;
	m_strInstrumentCode.clear();
	m_nMarketStatus = 0;
	m_nTime = 0;
	m_nVolume_OPEN_INTEREST = 0;
	m_nVolume_OPENING_VOLUME = 0;
	m_nVolume_LAST_TRADED_VOLUME = 0;
	m_nVolume_TOTAL_TRADED_VOLUME = 0;
	m_nBidVol = 0;
	m_nAskVol = 0;
	m_fPrice_OPENNING_PRICE = 0;
	m_fPrice_SESSION_HIGH = 0;
	m_fPrice_SESSION_LOW = 0;
	m_fPrice_REFERENCE_PRICE = 0;
	m_fPrice_YESTERDAY_SETTLMENT_PRICE = 0;
	m_fPrice_LAST_TRADED_PRICE = 0;
	m_fPrice_SETTLEMENT_PRICE = 0;
	m_fBidPx = 0;
	m_fAskPx = 0;
	m_nDataBits = 0;
	m_nChangeBits = 0;

}
void CMyMarketData::setInstrumentID( unsigned int nInstrumentID )
{
	m_nInstrumentID = nInstrumentID;
}

unsigned int CMyMarketData::getInstrumentID() const
{
	return m_nInstrumentID;
}
void CMyMarketData::setInstrumentCode(const std::string& strInstrumentCode)
{
	QString strID;
	m_strInstrumentCode = strInstrumentCode;

	strID = m_strInstrumentCode.substr(0, m_strInstrumentCode.find(".")).c_str();
	m_nInstrumentID = strID.toUInt();

	
}
std::string CMyMarketData::getInstrumentCode() const
{
	return m_strInstrumentCode;
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
	CMyMarketData::EMyVolumeType nVolumeType = (CMyMarketData::EMyVolumeType)type;
	switch (nVolumeType)
	{
	case CMyMarketData::OPEN_INTEREST:
		return m_nVolume_OPEN_INTEREST;
		break;
	case CMyMarketData::OPENING_VOLUME:
		return m_nVolume_OPENING_VOLUME;
		break;
	case CMyMarketData::LAST_TRADED_VOLUME:
		return m_nVolume_LAST_TRADED_VOLUME;
		break;
	case CMyMarketData::TOTAL_TRADED_VOLUME:
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
	CMyMarketData::EMyPriceType nPriceType = (CMyMarketData::EMyPriceType)type;
	switch (nPriceType)
	{
	case CMyMarketData::OPENNING_PRICE:
		return m_fPrice_OPENNING_PRICE;
		break;
	case CMyMarketData::SESSION_HIGH:
		return m_fPrice_SESSION_HIGH;
		break;
	case CMyMarketData::SESSION_LOW:
		return m_fPrice_SESSION_LOW;
		break;
	case CMyMarketData::REFERENCE_PRICE:
		return m_fPrice_REFERENCE_PRICE;
		break;
	case CMyMarketData::YESTERDAY_SETTLMENT_PRICE:
		return m_fPrice_YESTERDAY_SETTLMENT_PRICE;
		break;
	case CMyMarketData::LAST_TRADED_PRICE:
		return m_fPrice_LAST_TRADED_PRICE;
		break;
	case CMyMarketData::SETTLEMENT_PRICE:
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
	"Shanghai","600667.SS","+0.26","+4.60%","12/10/2014","2:00am",
	5.76,5.91,5.92,5.44,6.11,
	"5.44 - 6.11",5.91,N/A,128066608,0,""
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
	CQtTimeHelper  qtTimeHelper;

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
	QString symbolID;//symbolID = symbol.substr(0, symbol.find("."));
	QString lastTradeDataTime;//lastTradeDate+" "+lastTradeTime

	nIndex = 0;	stockExchange = strLstGetData[nIndex];
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

	stockExchange.replace(QChar('"'), QChar(' '));
	symbol.replace(QChar('"'), QChar(' '));
	changeRealTime.replace(QChar('"'), QChar(' '));
	changeinPercent.replace(QChar('"'), QChar(' '));
	lastTradeDate.replace(QChar('"'), QChar(' '));
	lastTradeTime.replace(QChar('"'), QChar(' '));
	open.replace(QChar('"'), QChar(' '));
	bid.replace(QChar('"'), QChar(' '));
	ask.replace(QChar('"'), QChar(' '));
	dayLow.replace(QChar('"'), QChar(' '));
	dayHigh.replace(QChar('"'), QChar(' '));
	dayRange.replace(QChar('"'), QChar(' '));
	lastTradePriceOnly.replace(QChar('"'), QChar(' '));
	str_1yrTargetPrice.replace(QChar('"'), QChar(' '));
	volume.replace(QChar('"'), QChar(' '));
	averageDailyVolume.replace(QChar('"'), QChar(' '));
	name.replace(QChar('"'), QChar(' '));

	symbol = symbol.trimmed();
	m_strInstrumentCode = symbol.toStdString();//set m_strInstrumentCode

	symbolID = symbol.mid(0, symbol.indexOf("."));
	symbolID = symbolID.trimmed();

	stockExchange = stockExchange.trimmed();
	symbol = symbol.trimmed();
	changeRealTime = changeRealTime.trimmed();
	changeinPercent = changeinPercent.trimmed();
	lastTradeDate = lastTradeDate.trimmed();
	lastTradeTime = lastTradeTime.trimmed();
	open = open.trimmed();
	bid = bid.trimmed();
	ask = ask.trimmed();
	dayLow = dayLow.trimmed();
	dayHigh = dayHigh.trimmed();
	dayRange = dayRange.trimmed();
	lastTradePriceOnly = lastTradePriceOnly.trimmed();
	str_1yrTargetPrice = str_1yrTargetPrice.trimmed();
	volume = volume.trimmed();
	averageDailyVolume = averageDailyVolume.trimmed();
	name = name.trimmed();


	m_nInstrumentID = symbolID.toUInt();
	m_fPrice_LAST_TRADED_PRICE = lastTradePriceOnly.toFloat();
	//"12/10/2014","2:00am",
	if ("N/A" == lastTradeDate || "N/A" == lastTradeTime)
	{
		lastTradeDataTime = DEF_VALUE_STRING_UTC_START_DATE_TIME.c_str();
	}
	else
	{
		lastTradeDataTime = lastTradeDate + " " + lastTradeTime;
	}
	m_nTime = qtTimeHelper.strToDateTime_Qt_AmPm(lastTradeDataTime.toStdString());

}

void CMyMarketData::setValue(const CHistoryData* pHistoryData)
{
	CQtTimeHelper qtTimeHelper;
	if (NULL == pHistoryData)
	{
		return;
	}
	m_nTime = (unsigned int)qtTimeHelper.strToDateTime_Qt(pHistoryData->m_strDate.toStdString());
	m_fPrice_LAST_TRADED_PRICE = pHistoryData->m_strClose.toFloat();
	m_nVolume_LAST_TRADED_VOLUME = pHistoryData->m_strVolume.toInt();
}