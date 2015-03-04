#ifndef __CLASS_PROJECT_DBSTATUS_MANAGER_H__
#define __CLASS_PROJECT_DBSTATUS_MANAGER_H__

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include <QtCore/QList>



class CSQLStringXmlParser;

class CProjectDBStatusManager 
{
public:
	static CProjectDBStatusManager& getInstance();
	static void removeInstance();
private:
	static CProjectDBStatusManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
    CProjectDBStatusManager(void);
	~CProjectDBStatusManager(void);

};

#endif//__CLASS_PROJECT_DBSTATUS_MANAGER_H__
