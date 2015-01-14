#ifndef __CLASS_DATA_STOCK_HISTORY_DATA_HH__
#define __CLASS_DATA_STOCK_HISTORY_DATA_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include <QtCore/QString>


class CQtTimeHelper;
class CHistoryData;
class CItemStockHistoryData;
class CItemStockHistoryDataHelper;

class CDataStockHistoryData 
{ 
public:
	static CDataStockHistoryData& getInstance();
	static void removeInstance();

private:
	static CDataStockHistoryData* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataStockHistoryData(); 
	virtual ~CDataStockHistoryData(); 
public:
	void setData(const QString& strSymbolUse, const QList<CHistoryData*>& lstData);
public:
	CItemStockHistoryData* getRootItem();

private:
	void _FreeData();
	void _ReSetRoot();
private:
	QMutex m_mutexForMapData;
	QMap<qint32, CHistoryData*> m_MapData;
	QString m_strSymbolUse;
private:
	QMutex m_mutexForRoot;
	CItemStockHistoryData* m_pItem_Root;
	CItemStockHistoryDataHelper* m_pItemDataHelper;

private:
	CQtTimeHelper* m_pQtTimeHelper;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_STOCK_HISTORY_DATA_HH__



