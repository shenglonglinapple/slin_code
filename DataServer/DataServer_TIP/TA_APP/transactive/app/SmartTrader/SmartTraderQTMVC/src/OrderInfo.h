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
	void setDefaultValue();
	QVariant getValueByName(const QString& strName);
	unsigned int getKey();
private:
	void _ClearData();

private:
	CProjectUtilityFun* m_pUtilityFun;
public:
	unsigned int m_nKey;

public:
	Order::Side m_side;
	int m_cumQty;
	int m_lastQty;
	int m_orderQty;
	int m_leavesQty;
	int m_rejectReason;

	float m_price;
	float m_price2;
	float m_lastPx;
	float m_avgPrice;
	Order::OrderType m_orderType;
	Order::OrderStatus m_orderStatus;

	unsigned int m_userID;
	unsigned int m_orderID;
	unsigned int m_clOrdID;
	unsigned int m_strategyID;
	unsigned int m_transactTime;
	unsigned int m_orderInfoMasks;

	unsigned int m_nAccountID;	
	unsigned int m_nInstrumentID;

	double m_fees;
	double m_margin;

	std::string m_text;
}; 


//QT_END_NAMESPACE


#endif//__CLASS_ORDER_INFO_HH__



