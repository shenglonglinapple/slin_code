#ifndef __CLASS_USER_ORDER_INFO_HH__
#define __CLASS_USER_ORDER_INFO_HH__



//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include "Instrument.h"
#include "Order.h"



class CProjectUtilityFun;
class COrderInfo;
class CTreeItemQuotes;


class CUserOrderInfo 
{ 
public:
	enum OrderCheckRes
	{
		OrderCheckRes_OK,
		OrderCheckRes_Cancel,
	};
public: 
	CUserOrderInfo();
	virtual ~CUserOrderInfo(); 
public: 
	CUserOrderInfo& operator=(const CUserOrderInfo& cParam);
public:
	void setDataByItem(CTreeItemQuotes* pData);
private:
	void _ClearData();
private:
	COrderInfo* m_pOrderInfo;
public:
	unsigned int m_nInstrumentID ;
	QString m_strExchangeName;
	QString m_strInstrumentCode;
	float m_fLastPrice;
	int m_nQuantity;
public:
	Order::Side m_nSide;
	Order::OrderType m_nOrderType;
public:
	OrderCheckRes m_nCheckRes;
}; 


//QT_END_NAMESPACE


#endif//__CLASS_USER_ORDER_INFO_HH__



