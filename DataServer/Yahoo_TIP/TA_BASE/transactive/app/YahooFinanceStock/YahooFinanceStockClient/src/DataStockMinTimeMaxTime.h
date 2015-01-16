#ifndef __CLASS_DATA_STOCK_MIN_TIME_MAX_TIME_HH__
#define __CLASS_DATA_STOCK_MIN_TIME_MAX_TIME_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>


class CQtTimeHelper;
class CStockMinTimeMaxTime;

class CDataStockMinTimeMaxTime 
{ 
public:
	static CDataStockMinTimeMaxTime& getInstance();
	static void removeInstance();

private:
	static CDataStockMinTimeMaxTime* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataStockMinTimeMaxTime(); 
	virtual ~CDataStockMinTimeMaxTime(); 
public:
	void appendOrUpdate(const CStockMinTimeMaxTime* pData );
private:
	CQtTimeHelper* m_pQtTimeHelper;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_STOCK_MIN_TIME_MAX_TIME_HH__



