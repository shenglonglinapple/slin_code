#include "MyInstrument.h"

#include <time.h>
#include <math.h>       /* isnan, sqrt */
#include <limits>

#include "StockData.h"
#include "MyMarketData.h"

#include "QtTimeHelper.h"
#include "Log4cppLogger.h"



CMyInstrument::CMyInstrument()
{
	_ClearData();
}

CMyInstrument::~CMyInstrument()
{
}


CMyInstrument& CMyInstrument::operator=( const CMyInstrument& objCopy )
{
	m_nInstrumentID = objCopy.m_nInstrumentID;
	m_strInstrumentCode = objCopy.m_strInstrumentCode;
	m_strUnderlyingCode = objCopy.m_strUnderlyingCode;
	m_strExchangeName = objCopy.m_strExchangeName;

	m_chDecimalPlace = objCopy.m_chDecimalPlace;
	m_fTickSize = objCopy.m_fTickSize;
	m_fTickValue = objCopy.m_fTickValue;
	m_nBidVolume = objCopy.m_nBidVolume;

	m_nAskVolume = objCopy.m_nAskVolume;
	m_nLastVolume = objCopy.m_nLastVolume;
	m_nTotalVolume = objCopy.m_nTotalVolume;

	m_fBidPrice = objCopy.m_fBidPrice;
	m_fAskPrice = objCopy.m_fAskPrice;
	m_fLowPrice = objCopy.m_fLowPrice;
	m_fHighPrice = objCopy.m_fHighPrice;

	m_fLastPrice = objCopy.m_fLastPrice;
	m_fOpeningPrice = objCopy.m_fOpeningPrice;
	m_fSettlementPrice = objCopy.m_fSettlementPrice;
	m_timeUpdateTime = objCopy.m_timeUpdateTime;
	m_strGetupdateTime = objCopy.m_strGetupdateTime;

	m_fValuePerPoint = objCopy.m_fValuePerPoint;
	m_nLegSize = objCopy.m_nLegSize;
	m_nLegSecurityID = objCopy.m_nLegSecurityID;
	m_nMarketStatus = objCopy.m_nMarketStatus;
	m_nSecurityType = objCopy.m_nSecurityType;
	m_nOrderTypes = objCopy.m_nOrderTypes;



	m_strExchangeName = objCopy.m_strExchangeName;//Exchange Name//ExchangeName//交易所
	m_strInstrumentCode = objCopy.m_strInstrumentCode;//Contract Name//InstrumentCode//合约名称
	m_nBidVolume = objCopy.m_nBidVolume;//Bid Volume//BidVolume//买量
	m_fBidPrice = objCopy.m_fBidPrice;//Bid//BidPrice//买价
	m_fAskPrice = objCopy.m_fAskPrice;//Offer//AskPrice//卖价
	m_nAskVolume = objCopy.m_nAskVolume;//Offer Volume//AskVolume//卖量
	m_fLastPrice = objCopy.m_fLastPrice;//Last//LastPrice//成交价
	m_nLastVolume = objCopy.m_nLastVolume;//Last Volume//LastVolume//成交量
	m_strChangeTmp = objCopy.m_strChangeTmp;//Change//变动
	m_strYDSPTmp = objCopy.m_strYDSPTmp;//YDSP//昨收盘
	m_nMarketStatus = objCopy.m_nMarketStatus;//Status//MarketStatus//市场状态
	m_fOpeningPrice = objCopy.m_fOpeningPrice;//Opening//OpeningPrice//开市价
	m_strBidTotalTmp = objCopy.m_strBidTotalTmp;//Bid Total//买累计
	m_strOfferTotalTmp = objCopy.m_strOfferTotalTmp;//Offer Total//卖累计
	m_fLowPrice = objCopy.m_fLowPrice;//Low//LowPrice//最低价
	m_fHighPrice = objCopy.m_fHighPrice;//High//HighPrice//最高价
	m_strCloseingTmp = objCopy.m_strCloseingTmp;//Closeing//收盘价
	m_strRefPriceTmp = objCopy.m_strRefPriceTmp;//Ref Price//参考价

	return *this;
}

void CMyInstrument::_ClearData()
{
	m_nInstrumentID = 0;
	m_strInstrumentCode.clear();
	m_strUnderlyingCode.clear();
	m_strExchangeName.clear();

	m_chDecimalPlace = 0;
	m_fTickSize = 0;
	m_fTickValue = 0;
	m_nBidVolume = 0;

	m_nAskVolume = 0;
	m_nLastVolume = 0;
	m_nTotalVolume = 0;

	m_fBidPrice = 0;
	m_fAskPrice = 0;
	m_fLowPrice = 0;
	m_fHighPrice = 0;

	m_fLastPrice = 0;
	m_fOpeningPrice = 0;
	m_fSettlementPrice = 0;
	m_timeUpdateTime = 0;
	m_strGetupdateTime.clear();

	m_fValuePerPoint = 0;
	m_nLegSize = 0;
	m_nLegSecurityID = 0;
	m_nMarketStatus = 0;
	m_nSecurityType = 0;
	m_nOrderTypes = 0;

}

void CMyInstrument::logInfo(const std::string& file, int line)
{
	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strExchangeName="<<m_strExchangeName
		<<" "<<"m_strUnderlyingCode="<<m_strUnderlyingCode
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode;
}


void CMyInstrument::setDefaultValue()
{
	m_nInstrumentID = 0;
	m_strExchangeName = "AAAA";
	m_strUnderlyingCode = "BB";
	m_strInstrumentCode = "AAAA_BB_CC";
}


//////////////////////////////////////////////////////////////////////////
unsigned int CMyInstrument::getInstrumentID() const
{
	return m_nInstrumentID;
}

const std::string & CMyInstrument::getInstrumentCode() const
{
	return m_strInstrumentCode;
}

const std::string & CMyInstrument::getUnderlyingCode() const
{
	return m_strUnderlyingCode;
}

const std::string & CMyInstrument::getExchangeName() const
{
	return m_strExchangeName;
}

char CMyInstrument::getDecimalPlace() const
{
	return m_chDecimalPlace;
}

float CMyInstrument::getTickSize() const
{
	return m_fTickSize;
}

float CMyInstrument::getTickValue() const
{
	return m_fTickValue;
}

int CMyInstrument::getBidVolume() const
{
	return m_nBidVolume;
}

int CMyInstrument::getBidVolume( int level ) const
{
	return m_nBidVolume;
}

int CMyInstrument::getAskVolume() const
{
	return m_nAskVolume;
}

int CMyInstrument::getAskVolume( int level ) const
{
	return m_nAskVolume;
}

int CMyInstrument::getLastVolume() const
{
	return m_nLastVolume;
}

int CMyInstrument::getTotalVolume() const
{
	return m_nTotalVolume;
}

float CMyInstrument::getBidPrice() const
{
	return m_fBidPrice;
}

float CMyInstrument::getBidPrice( int level ) const
{
	return m_fBidPrice;
}

float CMyInstrument::getAskPrice() const
{
	return m_fAskPrice;
}

float CMyInstrument::getAskPrice( int level ) const
{
	return m_fAskPrice;
}	

float CMyInstrument::getLowPrice() const
{
	return m_fLowPrice;
}

float CMyInstrument::getHighPrice() const
{
	return m_fHighPrice;
}	

float CMyInstrument::getLastPrice() const
{
	return m_fLastPrice;
}

float CMyInstrument::getOpeningPrice() const
{
	return m_fOpeningPrice;
}

float CMyInstrument::getSettlementPrice() const
{
	return m_fSettlementPrice;
}

unsigned int CMyInstrument::getUpdateTime() const
{
	return m_timeUpdateTime;
}

double CMyInstrument::getValuePerPoint() const
{
	return m_fValuePerPoint;
}

int CMyInstrument::getLegSize() const
{
	return m_nLegSize;
}

int CMyInstrument::getLegRatio( int index ) const
{
	return m_nLegRatio;
}


unsigned int CMyInstrument::getLegSecurityID( int index ) const
{
	return m_nLegSecurityID;
}


int CMyInstrument::getMarketStatus() const
{
	return m_nMarketStatus;
}

int CMyInstrument::getSecurityType() const
{
	return m_nSecurityType;
}

unsigned int CMyInstrument::getOrderTypes() const
{
	return m_nOrderTypes;
}

void CMyInstrument::setValue(const CStockData* pStockData )
{
	if (NULL == pStockData)
	{
		return;
	}

	this->m_nInstrumentID = pStockData->m_nStockID;
	this->m_strInstrumentCode = pStockData->m_strSymbolUse;
	this->m_strExchangeName = pStockData->m_strSymbolExtern;
	this->m_strUnderlyingCode = pStockData->m_strSymbolExtern;

}

void CMyInstrument::setValue(const CMyMarketData* pMyMarketData)
{
	if (NULL == pMyMarketData)
	{
		return;
	}
	CQtTimeHelper timerHelper;

	this->m_nInstrumentID = pMyMarketData->getSecurityID();
	this->m_timeUpdateTime = pMyMarketData->getTime();
	this->m_strGetupdateTime = timerHelper.dateTimeToStr_Qt(m_timeUpdateTime);

	this->m_fLastPrice = pMyMarketData->getPrice(CMyMarketData::LAST_TRADED_PRICE);
	this->m_nLastVolume = pMyMarketData->getVolume(CMyMarketData::LAST_TRADED_VOLUME);
}
template<typename T>
bool CMyInstrument::uti_isnan(T value)
{
	return value != value;
}

// requires #include <limits>
template<typename T>
bool CMyInstrument::uti_isinf(T value)
{
	return std::numeric_limits<T>::has_infinity() &&
		value == std::numeric_limits<T>::infinity();
}
float CMyInstrument::checkFloatNanValue(const float& fValueTmp)
{
	/*
	According to the IEEE standard, 
	NaN values have the odd property that comparisons involving them are always false. 
	That is, for a float f, f != f will be true only if f is NaN
	*/

	/*
	#include <boost/algorithm/string.hpp>
	#include <boost/math/special_functions/fpclassify.hpp> 
	if ((boost::math::isnan)(fValueTmp))
	{
	//x is NaN
	return 0;
	} 
	*/
	if (uti_isnan(fValueTmp))
	{
		//x is NaN
		return 0;
	}

	return fValueTmp;
}


