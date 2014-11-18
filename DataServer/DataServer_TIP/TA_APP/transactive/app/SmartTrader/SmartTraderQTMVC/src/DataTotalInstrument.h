#ifndef __CLASS_DATA_TOTAL_INSTRUEMENT_HH__
#define __CLASS_DATA_TOTAL_INSTRUEMENT_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include "Instrument.h"

class CProjectLogHelper;



class CDataTotalInstrument 
{ 
public:
	static CDataTotalInstrument& getInstance();
	static void removeInstance();

private:
	static CDataTotalInstrument* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataTotalInstrument(); 
	virtual ~CDataTotalInstrument(); 
public:
	void onInstrumentDownloaded( const Instrument& instrument );
	void onMarketDataUpdate(const Instrument& instrument);
	Instrument* findInstrumentByID(unsigned int nInstrumentID);
public:
	void _Test();
private:
	QMutex m_mutexForMapInstrumentIDData;
	QMap<unsigned int, Instrument*> m_MapInstrumentIDData;
private:
	CProjectLogHelper* m_pProjectLogHelper;

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_TOTAL_INSTRUEMENT_HH__



