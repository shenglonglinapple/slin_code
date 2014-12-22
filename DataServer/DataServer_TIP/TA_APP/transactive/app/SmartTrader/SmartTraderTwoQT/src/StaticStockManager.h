#ifndef __CLASS_STATIC_STOCK_MANAGER_H__
#define __CLASS_STATIC_STOCK_MANAGER_H__

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CStockData;

class CStaticStockManager 
{
public:
	static CStaticStockManager& getInstance();
	static void removeInstance();

private:
	static CStaticStockManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	typedef std::map<std::string, CStockData*>                      MapStockDataItemT;
	typedef std::map<std::string, CStockData*>::iterator            MapStockDataItemIterT;
	typedef std::map<std::string, CStockData*>::value_type          MapStockDataItemValueTypeT;
private:
	CStaticStockManager();
	virtual ~CStaticStockManager();
public:
	void doWork_getStockID(std::list<int>& LstStockID);
	void doWork_getStockSymbolUse(std::list<std::string>& LstStockSymbolUse);
	void doWork_getStockData(std::list<CStockData*>& LstStockData);
public:
	const CStockData* find_StockData_BySymbolUse(const std::string& strSymbolUse);
	const CStockData* find_StockData_BySymbolUse(int nStockID);
private:
	void _FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData);
	void _FreeData_MapStockDataItemT_Total();
	void _LoadData_MapStockDataItemT_Total();

private:
	QMutex m_mutexMapStockDataItemT_Total;
	MapStockDataItemT m_MapStockDataItemT_Total;
};


#endif //__CLASS_STATIC_STOCK_MANAGER_H__
