#ifndef __CLASS_DATA_STOCK_HISTORY_DATA_HH__
#define __CLASS_DATA_STOCK_HISTORY_DATA_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QString>


class CQtTimeHelper;
class CHistoryData;

class CDataStockHistoryData 
{ 
public:
	static CDataStockHistoryData& getInstance();
	static void removeInstance();

private:
	static CDataStockHistoryData* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataStockHistoryData(); 
	virtual ~CDataStockHistoryData(); 
public:
	void setData(const QString& strSymbolUse, const QList<CHistoryData*>& lstData);
private:
	QString m_strSymbolUse;
private:
	CQtTimeHelper* m_pQtTimeHelper;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_STOCK_HISTORY_DATA_HH__



