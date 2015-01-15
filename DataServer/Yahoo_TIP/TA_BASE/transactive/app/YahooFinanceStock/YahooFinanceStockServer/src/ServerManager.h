#ifndef __CLASS_SERVER_MANAGER_HH__
#define __CLASS_SERVER_MANAGER_HH__


#include <QtCore/QObject>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtCore/QMap>


class CTcpServerWorker;
class CUserInfo;
class CUserTradeInfo;

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
	void createServer();
	void destoryServer();
public:
	qint32 getUserInfo(quint16 nListenPort,const QString & strUSERNAME, const QString& strPASSWORD, CUserInfo** ppData);
	qint32 updateUserInfo(quint16 nListenPort, const CUserInfo* pData);
	qint32 createUserInfo(quint16 nListenPort, const CUserInfo* pData);
	qint32 createUserTradeInfo( quint16 nListenPort, const CUserTradeInfo* pData );

private:
	QMutex m_mutex_MapTcpServerWorker;
	QMap<quint16, CTcpServerWorker*> m_MapTcpServerWorker;

};
#endif  // __CLASS_SERVER_MANAGER_HH__



