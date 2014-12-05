#ifndef __CLASS_INIT_DB_BY_YAHUO_DATA_H__
#define __CLASS_INIT_DB_BY_YAHUO_DATA_H__

#include <map>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CStockData;

class CInitDBByYahuoData 
{
private:
	//strSymbolUse  CStockData
	typedef std::map<std::string, CStockData*>                      MapStockDataItemT;
	typedef std::map<std::string, CStockData*>::iterator            MapStockDataItemIterT;
	typedef std::map<std::string, CStockData*>::value_type          MapStockDataItemValueTypeT;

public:
	CInitDBByYahuoData();
	virtual ~CInitDBByYahuoData();
public:
	void dowork();
private:
	void _FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData);
	void _FreeData_MapStockDataItemT_Total();
	void _LoadData_MapStockDataItemT_Total();
	void _GetAndSaveHistoryData(const std::string& strSymbolUse);
	void _ProcessTotalStocks();
	void _SaveDataToFile(const std::string& strSymbolUse, const std::string& strData);

private:
	void qSleep(int nMilliseconds);
	void qWait(int nMilliseconds);
private:
	QMutex m_mutexMapStockDataItemT_Total;
	MapStockDataItemT m_MapStockDataItemT_Total;
};


#endif //__CLASS_INIT_DB_BY_YAHUO_DATA_H__
