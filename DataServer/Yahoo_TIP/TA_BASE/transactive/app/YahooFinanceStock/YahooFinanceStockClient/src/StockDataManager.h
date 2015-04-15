#ifndef __CLASS_STOCK_DATA_MANAGER_HH_
#define __CLASS_STOCK_DATA_MANAGER_HH_

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include <QtCore/QList>

#include "TcpComProtocol.h"

class CStockDataActor;
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
private:
	void _FreeData_SSSZ_Stocks();

private:
	void qSleep(int nMilliseconds);
	void qWait(int nMilliseconds);
	void _FreeLstData(QList<CStockInfo*>& lstData);

public:
	void addStockData(const QList<CStockInfo*>* pLstStockInfoData);
	void getAllStockData(QList<QString>& LstStock);
private:
	QMutex m_mutexMapStockDataItemT_Total;
	QList<CStockInfo*> m_lstStockInfoData; 
};


#endif //__CLASS_STOCK_DATA_MANAGER_HH_
