#ifndef __CLASS_ORDER_DATA_HH__
#define __CLASS_ORDER_DATA_HH__



//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include "Order.h"

class CItemUserInstrument;

class COrderData 
{ 
public:
	enum OrderCheckRes
	{
		OrderCheckRes_OK,
		OrderCheckRes_Cancel,
	};
public: 
	COrderData();
	virtual ~COrderData(); 
public: 
	COrderData& operator=(const COrderData& cParam);
public:
	void setDataByItem(CItemUserInstrument* pData);
private:
	void _ClearData();
public:
	unsigned int m_nInstrumentID ;
	QString m_strInstrumentCode;
	float m_fLastPrice;
	int m_nQuantity;
public:
	CMyOrder::Side m_nSide;
	CMyOrder::OrderType m_nOrderType;
public:
	OrderCheckRes m_nCheckRes;
}; 


//QT_END_NAMESPACE


#endif//__CLASS_USER_ORDER_INFO_HH__



