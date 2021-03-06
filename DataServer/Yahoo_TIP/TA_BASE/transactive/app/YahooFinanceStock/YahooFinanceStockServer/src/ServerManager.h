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
class CUserAccount;
class CUserHoldAccount;

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
	qint32 createUserAmount(quint16 nListenPort, const CUserAccount* pData);
public:
	qint32 selectUserTradeInfo(quint16 nListenPort, QList<CUserTradeInfo*>& lstData, const QString& strUserID, const QString& strSymbolUse);
	qint32 selectUserHoldAccount(quint16 nListenPort, QList<CUserHoldAccount*>& lstData, const QString& strUserID, const QString& strSymbolUse);

public:
	qint32 processUserTradeInfo( quint16 nListenPort, const CUserTradeInfo* pData );
	qint32 processUserAccount(quint16 nListenPort, const QString& strUserID, const QString& strTime, CUserAccount** ppData);

public:
	void sendMessage(quint16 nListenPort, qint32 handle, QByteArray* pMessage);
private:
	QMutex m_mutex_MapTcpServerWorker;
	QMap<quint16, CTcpServerWorker*> m_MapTcpServerWorker;

};
#endif  // __CLASS_SERVER_MANAGER_HH__



