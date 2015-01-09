#ifndef __CLASS_SERVER_MANAGER_HH__
#define __CLASS_SERVER_MANAGER_HH__


#include <QtCore/QObject>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtCore/QMap>


class CTcpServerWorker;

class CServerManager
{
public:
	static CServerManager& getInstance();
	static void removeInstance();

private:
	static CServerManager* m_pInstance;
	static QMutex m_mutexInstance;

private:
	CServerManager();
	~CServerManager();
public:
	void createServer(quint16 nListenPort);
	void destoryServer( quint16 nListenPort );
private:
	QMutex m_mutex_MapTcpServerWorker;
	QMap<quint16, CTcpServerWorker*> m_MapTcpServerWorker;

};
#endif  // __CLASS_SERVER_MANAGER_HH__



