#ifndef __CLASS_CLIENT_WORKER_MANAGER_H__
#define __CLASS_CLIENT_WORKER_MANAGER_H__

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

class QByteArray;

class CClientLoginParam;
class CDistributeTaskWorker;

class CClientWorkerManager 
{
public:
	static CClientWorkerManager& getInstance();
	static void removeInstance();

private:
	static CClientWorkerManager* m_pInstance;
	static QMutex m_mutexInstance;

private:
    CClientWorkerManager(void);
	~CClientWorkerManager(void);
public:	
	void createClient(const CClientLoginParam* pParam);
	void resetHanleValue( const CDistributeTaskWorker* pWorker, qint32 nHandle);
	void sendMessage(qint32 nHandle, QByteArray* pMessage);
private:
	QMutex m_mutex_MapClient;
	QMap<qint32, CDistributeTaskWorker*> m_MapClient;
};

#endif//__CLASS_CLIENT_WORKER_MANAGER_H__
