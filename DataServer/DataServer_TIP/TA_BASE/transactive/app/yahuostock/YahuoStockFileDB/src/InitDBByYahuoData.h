#ifndef __CLASS_INIT_DB_BY_YAHUO_DATA_H__
#define __CLASS_INIT_DB_BY_YAHUO_DATA_H__

#include <map>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CStockData;
class CInitYahuoDataToFile;
class CProcessFileDataToDB;

class CInitDBByYahuoData 
{
public:
	static CInitDBByYahuoData& getInstance();
	static void removeInstance();

private:
	static CInitDBByYahuoData* m_pInstance;
	static QMutex m_mutexInstance;


private:
	//strSymbolUse  CStockData
	typedef std::map<std::string, CStockData*>                      MapStockDataItemT;
	typedef std::map<std::string, CStockData*>::iterator            MapStockDataItemIterT;
	typedef std::map<std::string, CStockData*>::value_type          MapStockDataItemValueTypeT;

private:
	CInitDBByYahuoData();
	virtual ~CInitDBByYahuoData();
public:
	void doWork_initTotalStocksYahuoDataToFile();
	void doWork_ProcessFileToSQliteDb();

private:
	void _FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData);
	void _FreeData_MapStockDataItemT_Total();
	void _LoadData_MapStockDataItemT_Total();

private:
	void qSleep(int nMilliseconds);
	void qWait(int nMilliseconds);
private:
	QMutex m_mutexMapStockDataItemT_Total;
	MapStockDataItemT m_MapStockDataItemT_Total;
private:
	CInitYahuoDataToFile* m_pInitYahuoDataToFile;
	CProcessFileDataToDB* m_pProcessFileDataToDB;
};


#endif //__CLASS_INIT_DB_BY_YAHUO_DATA_H__
