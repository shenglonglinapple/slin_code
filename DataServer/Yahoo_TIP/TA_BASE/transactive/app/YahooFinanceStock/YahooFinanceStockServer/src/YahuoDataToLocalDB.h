#ifndef __CLASS_YAHUO_DATA_TO_LOCAL_DB_H__
#define __CLASS_YAHUO_DATA_TO_LOCAL_DB_H__

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CStockData;
class CProcessYahuoDataToLocalDB;

class CYahuoDataToLocalDB 
{
public:
	static CYahuoDataToLocalDB& getInstance();
	static void removeInstance();

private:
	static CYahuoDataToLocalDB* m_pInstance;
	static QMutex m_mutexInstance;


private:
	//strSymbolUse  CStockData
	typedef std::map<QString, CStockData*>                      MapStockDataItemT;
	typedef std::map<QString, CStockData*>::iterator            MapStockDataItemIterT;
	typedef std::map<QString, CStockData*>::value_type          MapStockDataItemValueTypeT;

private:
	CYahuoDataToLocalDB();
	virtual ~CYahuoDataToLocalDB();
public:
	//yahuo data to  C:\LSL\LSL_DATA\SaveDataFile\000001.SS file
	void doWork_YahuoDataToLocalDB();

	//C:\LSL\LSL_DATA\SaveDataFile\000001.SS file to C:\LSL\LSL_DATA\SaveDataSqliteDB\000001.SS sqlite db file
	//void doWork_Local_FileDB_To_SQLiteDB();
public:
	void doWork_getStockID(std::list<int>& LstStockID);
	void doWork_getStockSymbolUse(std::list<QString >& LstStockSymbolUse);
private:
	void _FreeData_MapStockDataItemT_Total();
	void _LoadData_MapStockDataItemT_Total();

private:
	void qSleep(int nMilliseconds);
	void qWait(int nMilliseconds);
private:
	QMutex m_mutexMapStockDataItemT_Total;
	MapStockDataItemT m_MapStockDataItemT_Total;
private:
	CProcessYahuoDataToLocalDB* m_pProcessYahuoDataToLocalDB;
};


#endif //__CLASS_YAHUO_DATA_TO_LOCAL_DB_H__
