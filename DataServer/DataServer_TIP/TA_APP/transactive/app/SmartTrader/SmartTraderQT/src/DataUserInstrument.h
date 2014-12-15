#ifndef __CLASS_DATA_USER_INSTRUMENT__HH__
#define __CLASS_DATA_USER_INSTRUMENT__HH__

#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CItemUserInstrument;

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
private:
	CItemUserInstrument* m_pItemUserInstrument;

};

//QT_END_NAMESPACE

#endif //__CLASS_DATA_USER_INSTRUMENT__HH__


