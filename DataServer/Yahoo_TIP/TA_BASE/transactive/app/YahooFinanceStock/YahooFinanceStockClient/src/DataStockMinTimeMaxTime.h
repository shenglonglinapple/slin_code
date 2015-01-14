#ifndef __CLASS_DATA_STOCK_MIN_TIME_MAX_TIME_HH__
#define __CLASS_DATA_STOCK_MIN_TIME_MAX_TIME_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>


class CQtTimeHelper;
class CStockMinTimeMaxTime;
class CItemStockMinTimeMaxTime;
class CItemStockMinTimeMaxTimeHelper;

class CDataStockMinTimeMaxTime 
{ 
public:
	static CDataStockMinTimeMaxTime& getInstance();
	static void removeInstance();

private:
	static CDataStockMinTimeMaxTime* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataStockMinTimeMaxTime(); 
	virtual ~CDataStockMinTimeMaxTime(); 
public:
	void appendOrUpdate(CStockMinTimeMaxTime* pData);
public:
	CItemStockMinTimeMaxTime* getRootItem();

private:
	void _FreeData();
	void addNode(const CStockMinTimeMaxTime* pData );
	void updateNode(const CStockMinTimeMaxTime* pData );
	CStockMinTimeMaxTime* findNode(const QString& strSymbolUse);
private:
	QMutex m_mutexForMapData;
	QMap<QString, CStockMinTimeMaxTime*> m_MapData;

	QMutex m_mutexForRoot;
	CItemStockMinTimeMaxTime* m_pItem_Root;
	CItemStockMinTimeMaxTimeHelper* m_pItemDataHelper;

private:
	CQtTimeHelper* m_pQtTimeHelper;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_STOCK_MIN_TIME_MAX_TIME_HH__



