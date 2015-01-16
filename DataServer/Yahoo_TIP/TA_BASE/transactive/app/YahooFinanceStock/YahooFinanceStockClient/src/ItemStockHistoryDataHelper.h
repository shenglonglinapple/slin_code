#ifndef __CLASS_ITEM_STOCK_HISTORY_DATA_HELPER_HH__
#define __CLASS_ITEM_STOCK_HISTORY_DATA_HELPER_HH__

//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QStringList>

class CHistoryData;

class CItemStockHistoryDataHelper 
{ 
public: 
	CItemStockHistoryDataHelper();

	virtual ~CItemStockHistoryDataHelper(); 
	CItemStockHistoryDataHelper& operator=(const CItemStockHistoryDataHelper& objCopy);

public:
	void setValue(const CHistoryData* pData);
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
public:
	QString m_strDate;
	QString m_strOpen;
	QString m_strHigh;
	QString m_strLow;
	QString m_strClose;
	QString m_strVolume;
	QString m_strAdjClose;

}; 


#endif//__CLASS_ITEM_STOCK_HISTORY_DATA_HELPER_HH__



