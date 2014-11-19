#ifndef __CLASS_DATA__USR_CONTRACT_HH__
#define __CLASS_DATA__USR_CONTRACT_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include "Instrument.h"

class CProjectLogHelper;
class CQuotesInfo;
class CTreeItemQuotes;

class CDataUserContract 
{ 
public:
	static CDataUserContract& getInstance();
	static void removeInstance();

private:
	static CDataUserContract* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataUserContract(); 
	virtual ~CDataUserContract(); 
private:
	void _InitMVCDataForQuotes();
	void _UnInitMVCDataForQuotes();
public:
	CTreeItemQuotes* getRootHandle();
	void onMarketDataUpdate(const Instrument& instrument);
	void addByData(Instrument* pInstrument);
	void removeByData(Instrument* pInstrument);
	void _Test();

private:
	QMutex m_mutexForNodeRootQuotes;
	CQuotesInfo* m_pQuotesInfo;
	CTreeItemQuotes* m_pTreeItemQuotes_Root;//submarket
private:
	CProjectLogHelper* m_pProjectLogHelper;

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA__USR_CONTRACT_HH__



