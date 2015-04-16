#ifndef __CLASS_STOCK_DATA_MANAGER_HH_
#define __CLASS_STOCK_DATA_MANAGER_HH_

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include <QtCore/QList>

#include "TcpComProtocol.h"

class CStockDataDBActor;
class CStockMinTimeMaxTime;
class CHistoryData;
class CUserHold;
class CStocksDbOper;
class CStockInfo;

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
	void doWork_UpdateFailedCount(const QString& strSymbolUse); 
	int doWork_Select_FailedCount(const QString& strSymbolUse, int& nFailedCount );
	void doWork_getMaxTime(const QString& strSymbolUse, QString& strMaxTime);

public:
	void doWork_getAllStockInfo(QList<CStockInfo*>& LstStockInfo);
	void doWork_getStockMinTimeMaxTime(const QString& strSymbolUse, CStockMinTimeMaxTime** ppValueGet);
	void doWork_HistoryData(const QString& strSymbolUse, const QString& strFrom, const QString& strTo, QList<CHistoryData*>& lstData);
private:
	void _FreeData_SSSZ_Stocks();
	void _LoadData_SSSZ_Stocks();
	void _LoadData_SSSZ_Stocks_FromDB();
private:
	void qSleep(int nMilliseconds);
	void qWait(int nMilliseconds);

private:
	QMutex m_mutexMapStockDataItemT_Total;
	QMap<QString,CStockDataDBActor*> m_MapStockDataItemT_Total;
	CStocksDbOper* m_pCStocksDbOper;
	QList<CStockInfo*> m_lstStockInfoData; 
};


#endif //__CLASS_STOCK_DATA_MANAGER_HH_
