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
}; 


//QT_END_NAMESPACE


#endif//__CLASS_ORDER_INFO_HH__



