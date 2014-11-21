#ifndef __CLASS_DATA_INSTRUMENT_HH__
#define __CLASS_DATA_INSTRUMENT_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include "Instrument.h"

class CProjectLogHelper;
class CInstrumentInfoHelper;
class CItemInstrumentInfo;

class CDataInstrument 
{ 
public:
	static CDataInstrument& getInstance();
	static void removeInstance();

private:
	static CDataInstrument* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataInstrument(); 
	virtual ~CDataInstrument(); 

private: 
	void _InitMVCDataForContract();
	void _UnInitMVCDataForContract();
public:
	void onInstrumentDownloaded( const Instrument& instrument );
	void addByData(Instrument* pInstrument);
	void removeByData(Instrument* pInstrument);
	CItemInstrumentInfo* getRootHandle();
	void _Test();
private:
	QMutex m_mutexForNodeRootContract;
	CInstrumentInfoHelper* m_pContractInfo;
	CItemInstrumentInfo* m_pTreeItemContract_Root;//total
private:
	CProjectLogHelper* m_pProjectLogHelper;

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_INSTRUMENT_HH__



