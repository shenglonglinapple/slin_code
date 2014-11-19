#ifndef __CLASS_DATA_CONTRACT_HH__
#define __CLASS_DATA_CONTRACT_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include "Instrument.h"

class CProjectLogHelper;
class CContractInfo;
class CTreeItemContract;

class CDataContract 
{ 
public:
	static CDataContract& getInstance();
	static void removeInstance();

private:
	static CDataContract* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataContract(); 
	virtual ~CDataContract(); 

private: 
	void _InitMVCDataForContract();
	void _UnInitMVCDataForContract();
public:
	void onInstrumentDownloaded( const Instrument& instrument );
	void addByData(Instrument* pInstrument);
	void removeByData(Instrument* pInstrument);
	CTreeItemContract* getRootHandle();
	void _Test();
private:
	QMutex m_mutexForNodeRootContract;
	CContractInfo* m_pContractInfo;
	CTreeItemContract* m_pTreeItemContract_Root;//total
private:
	CProjectLogHelper* m_pProjectLogHelper;

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_CONTRACT_HH__



