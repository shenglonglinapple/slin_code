#ifndef __CLASS_CLIENT_ACTOR_MANAGER_H__
#define __CLASS_CLIENT_ACTOR_MANAGER_H__

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

class QByteArray;
class CClientActor;

class CClientActorManager 
{
public:
	static CClientActorManager& getInstance();
	static void removeInstance();

private:
	static CClientActorManager* m_pInstance;
	static QMutex m_mutexInstance;

private:
    CClientActorManager(void);
	~CClientActorManager(void);
public:	
	void createClient(const QString& strServerIP, quint16 nServerPort,
		 const QString& strUserName, const QString& strPassWord);
public:	
	void resetHanleValue( const CClientActor* pActor, qint32 nHandle);
	void sendMessage(qint32 nHandle, QByteArray* pMessage);
private:
	QMutex m_mutex_MapClientActor;
	QMap<qint32, CClientActor*> m_MapClientActor;
	qint32 m_nHandleAuto;
};

#endif//__CLASS_CLIENT_ACTOR_MANAGER_H__
