#ifndef __CLASS_CLIENT_DATA_MAMAGER__HH__
#define __CLASS_CLIENT_DATA_MAMAGER__HH__

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>


class CClientDataManager
{
public:
	static CClientDataManager& getInstance();
	static void removeInstance();

private:
	static CClientDataManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CClientDataManager(void);
	~CClientDataManager(void);
public:
	void startAllClient();
};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER__HH__


