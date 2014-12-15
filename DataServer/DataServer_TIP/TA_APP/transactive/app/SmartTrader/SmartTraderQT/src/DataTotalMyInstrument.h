#ifndef __CLASS_DATA_TOTAL_MY_INSTRUEMENT_HH__
#define __CLASS_DATA_TOTAL_MY_INSTRUEMENT_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include "MyInstrument.h"

class CProjectLogHelper;
class CQtTimeHelper;

class CDataTotalMyInstrument 
{ 
public:
	static CDataTotalMyInstrument& getInstance();
	static void removeInstance();

private:
	static CDataTotalMyInstrument* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataTotalMyInstrument(); 
	virtual ~CDataTotalMyInstrument(); 
public:
	void onInstrumentDownloaded( const CMyInstrument& instrument );
	void onMarketDataUpdate( const CMyMarketData &marketData );
	CMyInstrument* findInstrumentByID(unsigned int nInstrumentID);
private:
	void _FreeData_MapInstrumentIDData();
private:
	QMutex m_mutexForMapInstrumentIDData;
	QMap<unsigned int, CMyInstrument*> m_MapInstrumentIDData;
private:
	CProjectLogHelper* m_pProjectLogHelper;
	CQtTimeHelper* m_pQtTimeHelper;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_TOTAL_MY_INSTRUEMENT_HH__



