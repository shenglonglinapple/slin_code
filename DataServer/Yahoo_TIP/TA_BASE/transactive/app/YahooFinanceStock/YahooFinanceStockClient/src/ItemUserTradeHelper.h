#ifndef __CLASS_ITEM_USER_TRADE_HELPER_HH__
#define __CLASS_ITEM_USER_TRADE_HELPER_HH__

//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QStringList>

class CUserTradeInfo;

class CItemUserTradeHelper 
{ 
public: 
	CItemUserTradeHelper();

	virtual ~CItemUserTradeHelper(); 
	CItemUserTradeHelper& operator=(const CItemUserTradeHelper& objCopy);

public:
	void setValue(const CUserTradeInfo* pData);

public:
	void logInfo(const QString& file, qint32 line, const QString& strLog);
public:
	QVariant getColumnValueByName(const QString& strName);
public:
	void getLstClumnName(QStringList& lstClumnName );
	void getLstClumnName(QList<QVariant>& lstClumnName);
	void getItemNodeData(QList<QVariant>& itemDataTmp);

private:
	void _ClearData();
public:
	QString m_strUseID;
	QString m_strTradeUUID;
	QString m_strTradeTime;
	qint32 m_nTradeType;
	QString m_strSymbolUse;
	double m_fTradePrice;
	qint32 m_nTradeVolume;
	double m_fTradeAmount;
	double m_fTradeFees;
	double m_fTotalTradeFee;
	double m_fTotalTradeAmount;

}; 


#endif//__CLASS_ITEM_USER_TRADE_HELPER_HH__



