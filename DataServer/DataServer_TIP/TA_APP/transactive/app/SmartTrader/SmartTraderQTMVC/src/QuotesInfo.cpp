#include "QuotesInfo.h"

#include "ProjectUtilityFun.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE





static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange = "Change";//Change//变动//价格变化颜色

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName = "Exchange Name";//ExchangeName//交易所
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode = "Contract Name";//InstrumentCode//合约名称

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidVolume = "Bid Volume";//BidVolume//买量
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidPrice = "Bid";//BidPrice//买价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskVolume = "Offer Volume";//AskVolume//卖量
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskPrice = "Offer";//AskPrice//卖价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastVolume = "Last Volume";//LastVolume//成交量
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastPrice = "Last";//LastPrice//成交价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_YDSP = "YDSP";//YDSP//昨收盘

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus = "Status";//MarketStatus//市场状态
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice = "Opening";//OpeningPrice//开市价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidTotal = "Bid Total";//Bid Total//买累计
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal = "Offer Total";//Offer Total//卖累计

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LowPrice = "Low";//LowPrice//最低价
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_HighPrice = "High";//HighPrice//最高价


static const std::string DEFVALUE_String_ColumnName_SmartQuotes_Closeing = "Closeing";//Closeing//收盘价
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_RefPrice = "Ref Price";//Ref Price//参考价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime = "UpdateTime";//更新时间


//////////////////////////////////////////////////////////////////////////
//ex
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentID = "InstrumentID";



//////////////////////////////////////////////////////////////////////////

CQuotesInfo::CQuotesInfo()
{
	m_nInstrumentPriceChange = IconDelegate::InstrumentPriceChange_NoQuotes;

	_ClearData();

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

	m_pUtilityFun = NULL;
	m_pUtilityFun = new CProjectUtilityFun();

}

CQuotesInfo::~CQuotesInfo()
{
	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}

}


CQuotesInfo& CQuotesInfo::operator=( const CQuotesInfo& exchangeParam )
{
	m_nInstrumentPriceChange = exchangeParam.m_nInstrumentPriceChange;

	m_nInstrumentID = exchangeParam.m_nInstrumentID;
	m_strInstrumentCode = exchangeParam.m_strInstrumentCode;
	m_strUnderlyingCode = exchangeParam.m_strUnderlyingCode;
	m_strExchangeName = exchangeParam.m_strExchangeName;

	m_chDecimalPlace = exchangeParam.m_chDecimalPlace;
	m_fTickSize = exchangeParam.m_fTickSize;
	m_fTickValue = exchangeParam.m_fTickValue;
	m_nBidVolume = exchangeParam.m_nBidVolume;

	m_nAskVolume = exchangeParam.m_nAskVolume;
	m_nLastVolume = exchangeParam.m_nLastVolume;
	m_nTotalVolume = exchangeParam.m_nTotalVolume;

	m_fBidPrice = exchangeParam.m_fBidPrice;
	m_fAskPrice = exchangeParam.m_fAskPrice;
	m_fLowPrice = exchangeParam.m_fLowPrice;
	m_fHighPrice = exchangeParam.m_fHighPrice;

	m_fLastPrice = exchangeParam.m_fLastPrice;
	m_fOpeningPrice = exchangeParam.m_fOpeningPrice;
	m_fSettlementPrice = exchangeParam.m_fSettlementPrice;
	m_timeUpdateTime = exchangeParam.m_timeUpdateTime;
	m_strGetupdateTime = exchangeParam.m_strGetupdateTime;

	m_fValuePerPoint = exchangeParam.m_fValuePerPoint;
	m_nLegSize = exchangeParam.m_nLegSize;
	m_nLegSecurityID = exchangeParam.m_nLegSecurityID;
	m_nMarketStatus = exchangeParam.m_nMarketStatus;
	m_nSecurityType = exchangeParam.m_nSecurityType;
	m_nOrderTypes = exchangeParam.m_nOrderTypes;



	m_strExchangeName = exchangeParam.m_strExchangeName;//Exchange Name//ExchangeName//交易所
	m_strInstrumentCode = exchangeParam.m_strInstrumentCode;//Contract Name//InstrumentCode//合约名称
	m_nBidVolume = exchangeParam.m_nBidVolume;//Bid Volume//BidVolume//买量
	m_fBidPrice = exchangeParam.m_fBidPrice;//Bid//BidPrice//买价
	m_fAskPrice = exchangeParam.m_fAskPrice;//Offer//AskPrice//卖价
	m_nAskVolume = exchangeParam.m_nAskVolume;//Offer Volume//AskVolume//卖量
	m_fLastPrice = exchangeParam.m_fLastPrice;//Last//LastPrice//成交价
	m_nLastVolume = exchangeParam.m_nLastVolume;//Last Volume//LastVolume//成交量
	m_strChangeTmp = exchangeParam.m_strChangeTmp;//Change//变动
	m_strYDSPTmp = exchangeParam.m_strYDSPTmp;//YDSP//昨收盘
	m_nMarketStatus = exchangeParam.m_nMarketStatus;//Status//MarketStatus//市场状态
	m_fOpeningPrice = exchangeParam.m_fOpeningPrice;//Opening//OpeningPrice//开市价
	m_strBidTotalTmp = exchangeParam.m_strBidTotalTmp;//Bid Total//买累计
	m_strOfferTotalTmp = exchangeParam.m_strOfferTotalTmp;//Offer Total//卖累计
	m_fLowPrice = exchangeParam.m_fLowPrice;//Low//LowPrice//最低价
	m_fHighPrice = exchangeParam.m_fHighPrice;//High//HighPrice//最高价
	m_strCloseingTmp = exchangeParam.m_strCloseingTmp;//Closeing//收盘价
	m_strRefPriceTmp = exchangeParam.m_strRefPriceTmp;//Ref Price//参考价

	return *this;
}

void CQuotesInfo::_ClearData()
{
	m_strExchangeName.clear();//Exchange Name//ExchangeName//交易所
	m_strInstrumentCode.clear();//Contract Name//InstrumentCode//合约名称
	m_nBidVolume = 0;//Bid Volume//BidVolume//买量
	m_fBidPrice = 0;//Bid//BidPrice//买价
	m_fAskPrice = 0;//Offer//AskPrice//卖价
	m_nAskVolume = 0;//Offer Volume//AskVolume//卖量
	m_fLastPrice = 0;//Last//LastPrice//成交价
	m_nLastVolume = 0;//Last Volume//LastVolume//成交量
	m_strChangeTmp.clear();//Change//变动
	m_strYDSPTmp.clear();//YDSP//昨收盘
	m_nMarketStatus = 0;//Status//MarketStatus//市场状态
	m_fOpeningPrice = 0;//Opening//OpeningPrice//开市价
	m_strBidTotalTmp.clear();//Bid Total//买累计
	m_strOfferTotalTmp.clear();//Offer Total//卖累计
	m_fLowPrice = 0;//Low//LowPrice//最低价
	m_fHighPrice = 0;//High//HighPrice//最高价
	m_strCloseingTmp.clear();//Closeing//收盘价
	m_strRefPriceTmp.clear();//Ref Price//参考价
	m_timeUpdateTime = 0;
	m_strGetupdateTime.clear();

}


void CQuotesInfo::setValue( const Instrument &instrument)
{
	_ClearData();

	m_fOpeningPrice  = instrument.getOpeningPrice();
	m_fOpeningPrice = m_pUtilityFun->checkFloatNanValue(m_fOpeningPrice);

	m_fLastPrice = instrument.getLastPrice();
	m_fLastPrice = m_pUtilityFun->checkFloatNanValue(m_fLastPrice);

	if (m_fLastPrice > m_fOpeningPrice)
	{
		m_nInstrumentPriceChange = IconDelegate::InstrumentPriceChange_Increase;
	}
	else if (m_fLastPrice < m_fOpeningPrice)
	{
		m_nInstrumentPriceChange = IconDelegate::InstrumentPriceChange_Reduction;
	}
	//else if (fabs(m_fLastPrice - m_fOpeningPrice) <= EPSILON)//判断浮点数是否相等
	else
	{
		m_nInstrumentPriceChange = IconDelegate::InstrumentPriceChange_NoQuotes;
	}


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
	m_strGetupdateTime = m_pUtilityFun->dataTimeToStr(m_timeUpdateTime);
	//strGetupdateTime  = instrument.getInstrumentID();

	m_fValuePerPoint  = instrument.getValuePerPoint();
	m_nLegSize = instrument.getLegSize();
	//m_nLegSecurityID  = instrument.getLegSecurityID();
	m_nMarketStatus = instrument.getMarketStatus();
	m_nSecurityType = instrument.getSecurityType();
	m_nOrderTypes  = instrument.getOrderTypes();

}






unsigned int CQuotesInfo::getInstrumentID() const
{
	return m_nInstrumentID;
}
void CQuotesInfo::logInfo( const QString& strLogInfo ) const
{
	LOG_DEBUG<<strLogInfo.toStdString()
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strExchangeName="<<m_strExchangeName.toStdString()
		<<" "<<"m_strUnderlyingCode="<<m_strUnderlyingCode.toStdString()
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode.toStdString();
}

QString CQuotesInfo::getInstrumentCode() const
{
	return m_strInstrumentCode;
}

void CQuotesInfo::setDefaultValue()
{
	m_nInstrumentID = 1;
	m_strExchangeName = "AAAA";
	m_strUnderlyingCode = "BB";
	m_strInstrumentCode = "AAAA_BB_CC";
}

QVariant CQuotesInfo::getValueByName( const QString& strName )
{
	QVariant varValueRes;
	QStringList strlstClumnNameShow;

	strlstClumnNameShow.push_back(strName);




	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentID = "InstrumentID";
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentID.c_str())))
	{
		varValueRes = QVariant(this->m_nInstrumentID);
		return varValueRes;
	}
	

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange = "Change";//Change//变动//价格变化颜色
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str())))
	{
		varValueRes = QVariant(this->m_nInstrumentPriceChange);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName = "Exchange Name";//ExchangeName//交易所
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName.c_str())))
	{
		varValueRes = QVariant(this->m_strExchangeName);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode = "Contract Name";//InstrumentCode//合约名称
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode.c_str())))
	{
		varValueRes = QVariant(this->m_strInstrumentCode);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidVolume = "Bid Volume";//BidVolume//买量
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_BidVolume.c_str())))
	{
		varValueRes = QVariant(this->m_nBidVolume);
		return varValueRes;
	}



	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidPrice = "Bid";//BidPrice//买价
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_BidPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fBidPrice);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskVolume = "Offer Volume";//AskVolume//卖量
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_AskVolume.c_str())))
	{
		varValueRes = QVariant(this->m_nAskVolume);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskPrice = "Offer";//AskPrice//卖价
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_AskPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fAskPrice);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastVolume = "Last Volume";//LastVolume//成交量
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LastVolume.c_str())))
	{
		varValueRes = QVariant(this->m_nLastVolume);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastPrice = "Last";//LastPrice//成交价
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LastPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fLastPrice);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_YDSP = "YDSP";//YDSP//昨收盘
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_YDSP.c_str())))
	{
		varValueRes = QVariant(this->m_strYDSPTmp);
		return varValueRes;
	}



	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus = "Status";//MarketStatus//市场状态
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus.c_str())))
	{
		varValueRes = QVariant(this->m_nMarketStatus);
		return varValueRes;
	}



	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice = "Opening";//OpeningPrice//开市价
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fOpeningPrice);
		return varValueRes;
	}



	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidTotal = "Bid Total";//Bid Total//买累计
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_BidTotal.c_str())))
	{
		varValueRes = QVariant(this->m_strBidTotalTmp);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal = "Offer Total";//Offer Total//卖累计
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal.c_str())))
	{
		varValueRes = QVariant(this->m_strOfferTotalTmp);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LowPrice = "Low";//LowPrice//最低价
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LowPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fLowPrice);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_HighPrice = "High";//HighPrice//最高价
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_HighPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fHighPrice);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_Closeing = "Closeing";//Closeing//收盘价
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_Closeing.c_str())))
	{
		varValueRes = QVariant(this->m_strCloseingTmp);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_RefPrice = "Ref Price";//Ref Price//参考价
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_RefPrice.c_str())))
	{
		varValueRes = QVariant(this->m_strRefPriceTmp);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime = "UpdateTime";//更新时间
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime.c_str())))
	{
		varValueRes = QVariant(this->m_strGetupdateTime.c_str());
		return varValueRes;
	}

	return varValueRes;
}


//QT_END_NAMESPACE





