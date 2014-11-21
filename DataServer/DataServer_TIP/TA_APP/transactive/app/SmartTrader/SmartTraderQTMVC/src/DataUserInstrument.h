#ifndef __CLASS_DATA__USR_INSTRUMENT_HH__
#define __CLASS_DATA__USR_INSTRUMENT_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include "Instrument.h"

class CProjectLogHelper;
class CUserInstrumentInfoHelper;
class CItemUserInstrumentInfo;

class CDataUserInstrument 
{ 
public:
	static CDataUserInstrument& getInstance();
	static void removeInstance();

private:
	static CDataUserInstrument* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataUserInstrument(); 
	virtual ~CDataUserInstrument(); 
private:
	void _InitMVCDataForQuotes();
	void _UnInitMVCDataForQuotes();
public:
	CItemUserInstrumentInfo* getRootHandle();
	void onMarketDataUpdate(const Instrument& instrument);
	void addByData(Instrument* pInstrument);
	void removeByData(Instrument* pInstrument);
	void _Test();

private:
	QMutex m_mutexForNodeRootQuotes;
	CUserInstrumentInfoHelper* m_pQuotesInfo;
	CItemUserInstrumentInfo* m_pTreeItemQuotes_Root;//submarket
private:
	CProjectLogHelper* m_pProjectLogHelper;

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA__USR_INSTRUMENT_HH__



