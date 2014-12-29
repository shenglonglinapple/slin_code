#ifndef __CLASS_REAL_TIME_STOCK_MANAGER_H__
#define __CLASS_REAL_TIME_STOCK_MANAGER_H__

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>



class CStockData;
class CMyMarketData;
class CMyInstrument;
class CQtTimeHelper;

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
	void removeRealTimeReq(const std::string& strSymbolUse);
	void getRealTime_MarketDataList(std::list<CMyMarketData*>& lstMyMarketData);
	void getRealTimeData_MyInstrument(const std::string& strSymbolUse, CMyInstrument** ppMyInstrument);
private:
	std::string _GetRealTime_Base(const std::string& strSymbolUse);
	void _GetRealTime_MarketData(const std::string& strSymbolUse, CMyMarketData** ppMyMarketData );

private:
	void _FreeData_MapStockDataItemT_RealTime();
	void _FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData);
public:
	void historyAddOneDay();
	void getHistory_MarketDataList( std::list<CMyMarketData*>& lstMyMarketData );
	void getHistory_MyInstrument( const std::string& strSymbolUse, CMyInstrument** ppMyInstrument );

private:
	void _GetHistory_MarketData(const std::string& strSymbolUse, CMyMarketData** ppMyMarketData );
private:
	QMutex m_mutexMapStockDataItemT_RealTime;
	MapStockDataItemT m_MapStockDataItemT_RealTime;
private:
	unsigned int m_nTimeHistoryFrom;
	unsigned int m_nTimeHistoryTo;
	std::string m_strTimeHistoryFrom;
	std::string m_strTimeHistoryTo;
	CQtTimeHelper* m_pQtTimeHelper;
};


#endif //__CLASS_REAL_TIME_STOCK_MANAGER_H__
