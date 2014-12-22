#ifndef __CLASS_DATA_WAITING_INSTRUMENT__HH__
#define __CLASS_DATA_WAITING_INSTRUMENT__HH__

#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CItemWaitingInstrument;
class CItemWaitingInstrumentHelper;

class CDataWaitingInstrument
{
public:
	static CDataWaitingInstrument& getInstance();
	static void removeInstance();

private:
	static CDataWaitingInstrument* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CDataWaitingInstrument(void);
	~CDataWaitingInstrument(void);
public:
	CItemWaitingInstrument*  getRootItem();
	void addInstrument(unsigned int nInstrumentID);
	void removeInstrument( unsigned int nInstrumentID );
private:
	QMutex m_mutex_ItemWaitingInstrument_Root;
	CItemWaitingInstrument* m_pItemWaitInstrument_Root;
	CItemWaitingInstrumentHelper* m_pItemWaitingInstrumentHelper;
	//QList<unsigned int> m_LstInstrumentID;
};

//QT_END_NAMESPACE

#endif //__CLASS_DATA_WAITING_INSTRUMENT__HH__


