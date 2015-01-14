#ifndef __CLASS_ITEM_STOCK_MIN_TIME_MAX_TIME_HELPER_HH__
#define __CLASS_ITEM_STOCK_MIN_TIME_MAX_TIME_HELPER_HH__

//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QStringList>

class CStockMinTimeMaxTime;

class CItemStockMinTimeMaxTimeHelper 
{ 
public: 
	CItemStockMinTimeMaxTimeHelper();

	virtual ~CItemStockMinTimeMaxTimeHelper(); 
	CItemStockMinTimeMaxTimeHelper& operator=(const CItemStockMinTimeMaxTimeHelper& objCopy);

public:
	void setValue( const CStockMinTimeMaxTime* pData);

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
	QString m_strSymbolUse;
	QString m_strMinTime;
	QString m_strMaxTime;
	qint32 m_nCount;

}; 


#endif//__CLASS_ITEM_STOCK_MIN_TIME_MAX_TIME_HELPER_HH__



