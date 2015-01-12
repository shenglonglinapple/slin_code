#ifndef __CLASS_STOCK_DATA_MANAGER_HH_
#define __CLASS_STOCK_DATA_MANAGER_HH_

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
private:
	void _FreeData_SSSZ_Stocks();

private:
	void qSleep(int nMilliseconds);
	void qWait(int nMilliseconds);
public:
	void addStockData(const QList<QString>* LstStock);
	void getAllStockData(QList<QString>& LstStock);
private:
	QMutex m_mutexMapStockDataItemT_Total;
	QMap<QString,CStockDataActor*> m_MapStockDataItemT_Total;
};


#endif //__CLASS_STOCK_DATA_MANAGER_HH_
