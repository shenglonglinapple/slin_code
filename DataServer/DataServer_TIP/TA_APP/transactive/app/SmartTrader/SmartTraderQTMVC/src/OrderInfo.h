#ifndef __CLASS_ORDER_INFO_HH__
#define __CLASS_ORDER_INFO_HH__



//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include "Instrument.h"
#include "Order.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CProjectUtilityFun;

/*

*/

class COrderInfo 
{ 
public: 
	COrderInfo();

	virtual ~COrderInfo(); 
	COrderInfo& operator=(const COrderInfo& exchangeParam);

public:
	void setValue( const Order &newValue);

	void logInfo(const QString& strLogInfo) const;
public:
	QString getStrOrderType(Order::OrderType nOrderType);
	Order::OrderType getEnumOrderType(const QString& strOrderType);

	QString getStrOrderStatus(Order::OrderStatus nOrderStatus);
	QString getStrOrderSide(Order::Side nSide);
	int getColumnValueIsOrderFilled(Order::OrderStatus nOrderStatus);

public:
	void setDefaultValue();
	QVariant getValueByName(const QString& strName);
	unsigned int getKey();
private:
	void _ClearData();
private:
	CProjectUtilityFun* m_pUtilityFun;
public:
	unsigned int m_nKey;
	unsigned int m_orderID;
	Order::OrderType m_orderType;
	QString m_str_Column_OrderType;//Limit
	QString m_str_Column_TIF;//有效时间
	Order::OrderStatus m_orderStatus;
	QString m_str_Column_OrderStatus;//NEW
	QString m_strExchangeName;
	QString m_strInstrumentCode;
	QString m_str_Column_Account;//"CTS007"
	Order::Side m_side;
	QString m_str_Column_BuyOrSell;//
	int m_orderQty;
	int m_n_Column_Lots;//"Lots"
	float m_price;
	float m_price2;
	int m_n_Column_Filled;//"Filled"//0 1
	float m_avgPrice;
	unsigned int m_transactTime;
	QString m_str_Column_Time;
	int m_rejectReason;
	std::string m_text;//RejectReason
	double m_fees;
	double m_margin;
	QString m_Column_Contract;//合约//"SHFE/ag1409"
	QString m_Column_Currency;// = "Currency";//货币//"CNY"
}; 


//QT_END_NAMESPACE


#endif//__CLASS_ORDER_INFO_HH__



