#ifndef __CLASS_SERVER_MANAGER_HH__
#define __CLASS_SERVER_MANAGER_HH__


#include <QtCore/QObject>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtCore/QMap>
#include <QtCore/QList>


class CTcpServerWorker;
class CUserInfo;
class CUserTradeInfo;
class QByteArray;
class CUserHold;
class CUserAmount;

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
	qint32 selectUserInfo(quint16 nListenPort,const QString & strUSERNAME, const QString& strPASSWORD, CUserInfo** ppData);
	qint32 updateUserInfo(quint16 nListenPort, const CUserInfo* pData);
	qint32 createUserInfo(quint16 nListenPort, const CUserInfo* pData);
	qint32 createUserAmount(quint16 nListenPort, const CUserAmount* pData);
	qint32 createUserTradeInfo( quint16 nListenPort, const CUserTradeInfo* pData );
	qint32 createUserHold( quint16 nListenPort, const CUserHold* pData );
public:
	qint32 selectUserTradeInfo(quint16 nListenPort, QList<CUserTradeInfo*>& lstData, const QString& strUserID);


public:
	void sendMessage(quint16 nListenPort, qint32 handle, QByteArray* pMessage);

private:
	QMutex m_mutex_MapTcpServerWorker;
	QMap<quint16, CTcpServerWorker*> m_MapTcpServerWorker;

};
#endif  // __CLASS_SERVER_MANAGER_HH__



