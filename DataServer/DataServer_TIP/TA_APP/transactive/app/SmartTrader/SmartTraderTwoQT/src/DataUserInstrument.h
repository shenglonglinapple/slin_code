#ifndef __CLASS_DATA_USER_INSTRUMENT__HH__
#define __CLASS_DATA_USER_INSTRUMENT__HH__

#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CItemUserInstrument;
class CItemUserInstrumentHelper;

class CDataUserInstrument
{
public:
	static CDataUserInstrument& getInstance();
	static void removeInstance();

private:
	static CDataUserInstrument* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CDataUserInstrument(void);
	~CDataUserInstrument(void);
public:
	CItemUserInstrument*  getRootItem();
	void addUserInstrument(unsigned int nInstrumentID);
	void updateDataUserInstrument( unsigned int nInstrumentID );
	void removeUserInstrument( unsigned int nInstrumentID );
private:
	QMutex m_mutex_ItemUserInstrument_Root;
	CItemUserInstrument* m_pItemUserInstrument_Root;
	CItemUserInstrumentHelper* m_pItemUserInstrumentHelper;
	//QList<unsigned int> m_LstInstrumentID;
};

//QT_END_NAMESPACE

#endif //__CLASS_DATA_USER_INSTRUMENT__HH__


