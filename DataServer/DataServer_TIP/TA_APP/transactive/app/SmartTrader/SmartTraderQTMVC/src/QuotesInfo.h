#ifndef __CLASS_QUOTES_INFO_HH__
#define __CLASS_QUOTES_INFO_HH__



//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include "Instrument.h"
#include "IconDelegate.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CProjectUtilityFun;

/*
Exchange Name//ExchangeName//交易所
Contract Name//InstrumentCode//合约名称

Bid Volume//BidVolume//买量
Bid//BidPrice//买价

Offer//AskPrice//卖价
Offer Volume//AskVolume//卖量

Last//LastPrice//成交价
Last Volume//LastVolume//成交量

Change//变动
YDSP//昨收盘

Status//MarketStatus//市场状态
Opening//OpeningPrice//开市价

Bid Total//买累计
Offer Total//卖累计

High//HighPrice//最高价
Low//LowPrice//最低价

Closeing//收盘价
Ref Price//参考价

*/

class CQuotesInfo 
{ 
public: 
	CQuotesInfo();

	virtual ~CQuotesInfo(); 
	CQuotesInfo& operator=(const CQuotesInfo& exchangeParam);

public:
	void setValue( const Instrument &instrument);

	unsigned int getInstrumentID() const;
	QString getInstrumentCode() const;

	void logInfo(const QString& strLogInfo) const;
public:
	void setDefaultValue();
	QVariant getValueByName(const QString& strName);
private:
	void _ClearData();
public:
	IconDelegate::enInstrumentPriceChange m_nInstrumentPriceChange;
public:
	QString m_strExchangeName;//Exchange Name//ExchangeName//交易所
	QString m_strInstrumentCode;//Contract Name//InstrumentCode//合约名称

	int m_nBidVolume;//Bid Volume//BidVolume//买量
	float m_fBidPrice;//Bid//BidPrice//买价

	float m_fAskPrice;//Offer//AskPrice//卖价
	int m_nAskVolume;//Offer Volume//AskVolume//卖量

	float m_fLastPrice;//Last//LastPrice//成交价
	int m_nLastVolume;//Last Volume//LastVolume//成交量

	QString m_strChangeTmp;//Change//变动
	QString m_strYDSPTmp;//YDSP//昨收盘

	int m_nMarketStatus;//Status//MarketStatus//市场状态
	float m_fOpeningPrice;//Opening//OpeningPrice//开市价

	QString m_strBidTotalTmp;//Bid Total//买累计
	QString m_strOfferTotalTmp;//Offer Total//卖累计

	float m_fLowPrice;//Low//LowPrice//最低价
	float m_fHighPrice;//High//HighPrice//最高价

	QString m_strCloseingTmp;//Closeing//收盘价
	QString m_strRefPriceTmp;//Ref Price//参考价

	unsigned int m_timeUpdateTime;//更新时间
	std::string m_strGetupdateTime;

public:
	unsigned int m_nInstrumentID;
	QString m_strUnderlyingCode;

	char m_chDecimalPlace;
	float m_fTickSize;
	float m_fTickValue;

	int m_nTotalVolume;
	
	float m_fSettlementPrice;

	double m_fValuePerPoint;
	int m_nLegSize;
	unsigned int m_nLegSecurityID;
	int m_nSecurityType;
	unsigned int m_nOrderTypes;
private:
	CProjectUtilityFun* m_pUtilityFun;
}; 


//QT_END_NAMESPACE


#endif//__CLASS_CONTRACT_INFO_HH__



