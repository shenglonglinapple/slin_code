#ifndef __CLASS_ITEM_USER_ORDER_HELPER_HH__
#define __CLASS_ITEM_USER_ORDER_HELPER_HH__



//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QStringList>

#include "OrderData.h"

class CQtTimeHelper;

class CItemUserOrderHelper 
{ 
public: 
	CItemUserOrderHelper();

	virtual ~CItemUserOrderHelper(); 
	CItemUserOrderHelper& operator=(const CItemUserOrderHelper& objCopy);

public:
	void setData(const COrderData& order);
public:
	unsigned int getInstrumentID() const;
	QString getInstrumentCode() const;

	void logInfo(const std::string& file, int line, const QString& strLogInfo);
public:
	QVariant getColumnValueByName(const QString& strName);
public:
	void getLstClumnName(QStringList& lstClumnName );
	void getLstClumnName(QList<QVariant>& lstClumnName);
	void getItemNodeData(QList<QVariant>& itemDataTmp);

private:
	void _ClearData();
public:
	unsigned int m_Column_InstrumentID;
	QString m_Column_InstrumentCode;//Contract Name//InstrumentCode//合约名称
	QString m_Column_Side;//Buy
	QString m_Column_OrderType;//Market
	QString m_Column_OrderStatus;//FILLED
	QString m_Column_TransactTime;
	float m_Column_TransactPrice;
	float m_Column_Fees;
	QString m_Column_CurrentTime;
	float m_Column_CurrentPrice;
	float m_Column_Total;
public:
	COrderData::ESide m_nSide;//Buy sell
	QString m_strExchangeName;//Exchange Name//ExchangeName//交易所
	COrderData::EOrderType m_orderType;//Market
	COrderData::EOrderStatus m_nOrderStatus;
	unsigned int m_nTransactTime;
	unsigned int m_nCurrentTime;
public:
	QString m_strOrderUUID;
private:
	CQtTimeHelper* m_pQtTimeHelper;
}; 


//QT_END_NAMESPACE


#endif//__CLASS_ITEM_USER_ORDER_HELPER_HH__



