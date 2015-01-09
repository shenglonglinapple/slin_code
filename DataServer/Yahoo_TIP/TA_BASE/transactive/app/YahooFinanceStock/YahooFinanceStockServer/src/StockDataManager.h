#ifndef __CLASS_YAHUO_DATA_TO_LOCAL_DB_H__
#define __CLASS_YAHUO_DATA_TO_LOCAL_DB_H__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include <QtCore/QList>

#include "TcpComProtocol.h"

class CStockDataActor;

class CStockDataManager 
{
public:
	static CStockDataManager& getInstance();
	static void removeInstance();

private:
	static CStockDataManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CStockDataManager();
	virtual ~CStockDataManager();
public:
	//yahuo data to  C:\LSL\LSL_DATA\SaveDataFile\000001.SS file
	void doWork_Save_HistoryData(const QString& strSymbolUse, const QString& strHistoryData); 
	//C:\LSL\LSL_DATA\SaveDataFile\000001.SS file to C:\LSL\LSL_DATA\SaveDataSqliteDB\000001.SS sqlite db file
	//void doWork_Local_FileDB_To_SQLiteDB();
public:
	void doWork_getStockSymbolUse(QList<QString >& LstStockSymbolUse);
private:
	void _FreeData_SSSZ_Stocks();
	void _LoadData_SSSZ_Stocks();

private:
	void qSleep(int nMilliseconds);
	void qWait(int nMilliseconds);
private:
	QMutex m_mutexMapStockDataItemT_Total;
	QMap<QString,CStockDataActor*> m_MapStockDataItemT_Total;
};


#endif //__CLASS_YAHUO_DATA_TO_LOCAL_DB_H__