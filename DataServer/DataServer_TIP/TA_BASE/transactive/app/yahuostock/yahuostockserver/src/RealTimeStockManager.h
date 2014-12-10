#ifndef __CLASS_REAL_TIME_STOCK_MANAGER_H__
#define __CLASS_REAL_TIME_STOCK_MANAGER_H__

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>



class CStockData;

class CRealTimeStockManager
{
public:
	static CRealTimeStockManager& getInstance();
	static void removeInstance();

private:
	static CRealTimeStockManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	typedef std::map<std::string, CStockData*>                      MapStockDataItemT;
	typedef std::map<std::string, CStockData*>::iterator            MapStockDataItemIterT;
	typedef std::map<std::string, CStockData*>::value_type          MapStockDataItemValueTypeT;
private:
	CRealTimeStockManager();
	virtual ~CRealTimeStockManager();
public:
	void addRealTimeReq(const CStockData* pStockData);
	void addRealTimeReq(const std::string& strSymbolUse);

public:
	void subscribeMarketData(const std::string& strSymbolUse);

private:
	void _FreeData_MapStockDataItemT_RealTime();
	void _FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData);
private:
	QMutex m_mutexMapStockDataItemT_RealTime;
	MapStockDataItemT m_MapStockDataItemT_RealTime;
};


#endif //__CLASS_REAL_TIME_STOCK_MANAGER_H__
