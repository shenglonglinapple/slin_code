#ifndef __CLASS_MY_INSTRUMENT_HH__
#define __CLASS_MY_INSTRUMENT_HH__

//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>



class CStockData;
class CMyMarketData;
class CHistoryData;

class CMyInstrument
{ 
public: 
	CMyInstrument();
	virtual ~CMyInstrument(); 
public: 
	CMyInstrument& operator=(const CMyInstrument& objCopy);

public: 
	/// Get the unique ID of the instrument
	virtual unsigned int getInstrumentID() const;

	/// Get the unique name of the instrument
	virtual const std::string & getInstrumentCode() const;

	/// Get the unique name of the underlying of the instrument
	virtual const std::string & getUnderlyingCode() const;

	/// Get the unique name of the exchange of the instrument
	virtual const std::string & getExchangeName() const;

	/// Get the decimal place of the instrument
	virtual char getDecimalPlace() const;

	/// Get the tick size of the instrument
	virtual float getTickSize() const;

	/// Get the tick value of the instrument
	virtual float getTickValue() const;

	/// Get current best bid volume 
	virtual int getBidVolume() const;

	/// Get the current best ask volume
	virtual int getAskVolume() const;

	/// Get the last traded volume
	virtual int getLastVolume() const;

	/// Get the total traded volume intra day
	virtual int getTotalVolume() const;

	/// Get current best bid price
	virtual float getBidPrice() const;

	/// Get current best ask price
	virtual float getAskPrice() const;

	/// Get the lowest price intro day
	virtual float getLowPrice() const;

	/// Get the highest price intro day
	virtual float getHighPrice() const;

	/// Get the price of latest deal
	virtual float getLastPrice() const;

	/// Get latest opening price 
	virtual float getOpeningPrice() const;

	/// Get the latest settlement price
	virtual float getSettlementPrice() const;

	/// Get the bid price with depth level
	virtual float getBidPrice(int level) const;

	/// Get the ask price with depth level
	virtual float getAskPrice(int level) const;

	/// Get bid volume with depth level
	virtual int getBidVolume(int level) const;

	/// Get ask volume with depth level
	virtual int getAskVolume(int level) const;

	/// Get Update Timestamp
	virtual unsigned int getUpdateTime() const;

	/// Get Value Per Point
	virtual double getValuePerPoint() const;

	/// Get Number of Legs
	virtual int getLegSize() const;

	/// Get Leg Ratio
	virtual int getLegRatio(int index) const;

	/// Get Leg Security ID
	virtual unsigned int getLegSecurityID(int index) const;


	/// Get Market Status
	virtual int getMarketStatus() const;

	/// Get Security Type
	virtual int getSecurityType() const;

	/// Get Order Types
	virtual unsigned int getOrderTypes() const;
public:
	void logInfo(const std::string& file, int line);
	float checkFloatNanValue(const float& fValueTmp);
	template<typename T> bool uti_isinf(T value);
	template<typename T> bool uti_isnan(T value);

public:
	void setDefaultValue();
	void setValue(const CStockData* pStockData);
	void setValue(const CMyMarketData* pMyMarketData);
	void setValue(const CHistoryData* pHistoryData);

private:
	void _ClearData();
public:
	std::string m_strExchangeName;//Exchange Name//ExchangeName//交易所
	std::string m_strInstrumentCode;//Contract Name//InstrumentCode//合约名称

	int m_nBidVolume;//Bid Volume//BidVolume//买量
	float m_fBidPrice;//Bid//BidPrice//买价

	float m_fAskPrice;//Offer//AskPrice//卖价
	int m_nAskVolume;//Offer Volume//AskVolume//卖量

	float m_fLastPrice;//Last//LastPrice//成交价
	int m_nLastVolume;//Last Volume//LastVolume//成交量

	std::string m_strChangeTmp;//Change//变动
	std::string m_strYDSPTmp;//YDSP//昨收盘

	int m_nMarketStatus;//Status//MarketStatus//市场状态
	float m_fOpeningPrice;//Opening//OpeningPrice//开市价

	std::string m_strBidTotalTmp;//Bid Total//买累计
	std::string m_strOfferTotalTmp;//Offer Total//卖累计

	float m_fLowPrice;//Low//LowPrice//最低价
	float m_fHighPrice;//High//HighPrice//最高价

	std::string m_strCloseingTmp;//Closeing//收盘价
	std::string m_strRefPriceTmp;//Ref Price//参考价

	unsigned int m_timeUpdateTime;//更新时间
	std::string m_strGetupdateTime;

public:
	unsigned int m_nInstrumentID;
	std::string m_strUnderlyingCode;

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
	int m_nLegRatio;
}; 


//QT_END_NAMESPACE


#endif//__CLASS_MY_INSTRUMENT_HH__


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

