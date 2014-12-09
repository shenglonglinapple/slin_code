#include "MyInstrument.h"

#include "ProjectUtilityFun.h"

#include "Log4cppLogger.h"




CMyInstrument::CMyInstrument()
:m_Currency(0,"0")
{
	_ClearData();

	m_pUtilityFun = NULL;
	m_pUtilityFun = new CProjectUtilityFun();

}

CMyInstrument::~CMyInstrument()
{
	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}

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


void CMyInstrument::setValue( const Instrument &instrument)
{
	_ClearData();

	m_fOpeningPrice  = instrument.getOpeningPrice();
	m_fOpeningPrice = m_pUtilityFun->checkFloatNanValue(m_fOpeningPrice);

	m_fLastPrice = instrument.getLastPrice();
	m_fLastPrice = m_pUtilityFun->checkFloatNanValue(m_fLastPrice);

	m_nInstrumentID = instrument.getInstrumentID();
	m_strInstrumentCode = instrument.getInstrumentCode().c_str();
	m_strUnderlyingCode = instrument.getUnderlyingCode().c_str();
	m_strExchangeName = instrument.getExchangeName().c_str();

	m_chDecimalPlace = instrument.getDecimalPlace();
	m_fTickSize = instrument.getTickSize();
	m_fTickSize = m_pUtilityFun->checkFloatNanValue(m_fTickSize);

	m_fTickValue  = instrument.getTickValue();
	m_fTickValue = m_pUtilityFun->checkFloatNanValue(m_fTickValue);

	m_nBidVolume  = instrument.getBidVolume();

	m_nAskVolume  = instrument.getAskVolume();
	m_nLastVolume  = instrument.getLastVolume();
	m_nTotalVolume  = instrument.getTotalVolume();

	m_fBidPrice  = instrument.getBidPrice();
	m_fBidPrice = m_pUtilityFun->checkFloatNanValue(m_fBidPrice);

	m_fAskPrice = instrument.getAskPrice();
	m_fAskPrice = m_pUtilityFun->checkFloatNanValue(m_fAskPrice);

	m_fLowPrice = instrument.getLowPrice();
	m_fLowPrice = m_pUtilityFun->checkFloatNanValue(m_fLowPrice);

	m_fHighPrice  = instrument.getHighPrice();
	m_fHighPrice = m_pUtilityFun->checkFloatNanValue(m_fHighPrice);

	m_fLastPrice = instrument.getLastPrice();
	m_fLastPrice = m_pUtilityFun->checkFloatNanValue(m_fLastPrice);

	m_fOpeningPrice  = instrument.getOpeningPrice();
	m_fOpeningPrice = m_pUtilityFun->checkFloatNanValue(m_fOpeningPrice);

	m_fSettlementPrice  = instrument.getSettlementPrice();
	m_fSettlementPrice = m_pUtilityFun->checkFloatNanValue(m_fSettlementPrice);

	m_timeUpdateTime  = instrument.getUpdateTime();
	m_strGetupdateTime = m_pUtilityFun->dateTimeToStr_Qt(m_timeUpdateTime);
	//m_strGetupdateTime = m_pUtilityFun->dateTimeToStr_Qt(m_timeUpdateTime);

	//strGetupdateTime  = instrument.getInstrumentID();

	m_fValuePerPoint  = instrument.getValuePerPoint();
	m_nLegSize = instrument.getLegSize();
	m_nLegSecurityID  = instrument.getLegSecurityID(0);
	m_nMarketStatus = instrument.getMarketStatus();
	m_nSecurityType = instrument.getSecurityType();
	m_nOrderTypes  = instrument.getOrderTypes();

}


void CMyInstrument::logInfo(const std::string& file, int line, const QString& strLogInfo)
{
	MYLOG4CPP_DEBUG_Base<<" ["<<file<<":"<<line<<"] "
		<<" "<<strLogInfo.toStdString()
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

Instrument * CMyInstrument::getLeg( int index ) const
{
	return NULL;
}

unsigned int CMyInstrument::getLegSecurityID( int index ) const
{
	return m_nLegSecurityID;
}

const Currency & CMyInstrument::getCurrency() const
{
	return m_Currency;
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




