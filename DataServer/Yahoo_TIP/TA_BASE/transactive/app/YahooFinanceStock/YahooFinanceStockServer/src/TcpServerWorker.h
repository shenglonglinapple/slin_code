#ifndef __CLASS_TCP_SERVER_WORKER_H__
#define __CLASS_TCP_SERVER_WORKER_H__

#include "MyQtThread.h"

#include <QtCore/QList>

class CStockTcpServer;
class CServerDistributeTaskWorker;
class CServerDbOper;
class CUserInfo;
class CUserTradeInfo;
class CUserHold;
class CUserAccount;
class CUserHoldAccount;

class QByteArray;

class CTcpServerWorker : public CMyQtThread
{
    Q_OBJECT
public:
    CTcpServerWorker(quint16 nListenPort, QObject* parent=0);
	~CTcpServerWorker();
public:
	virtual void run();	
	virtual void terminate();
signals:

private slots:
public:
	void sendMessage(qint32 handle, QByteArray* pMessage);
public:
	qint32 selectUserInfo(quint16 nListenPort,const QString & strUSERNAME, const QString& strPASSWORD, CUserInfo** ppData);
	qint32 updateUserInfo(quint16 nListenPort, const CUserInfo* pData);
	qint32 createUserInfo(quint16 nListenPort, const CUserInfo* pData);
	qint32 createUserAmount( quint16 nListenPort, const CUserAccount* pData );
public:
	qint32 selectUserTradeInfo( quint16 nListenPort, QList<CUserTradeInfo*>& lstData, const QString& strUserID, const QString& strSymbolUse );
	qint32 processUserTradeInfo( quint16 nListenPort, const CUserTradeInfo* pData );
	double getUserHoldAmount(const QString& strUserID, const QString& strTime);
	qint32 processUserAccount( quint16 nListenPort, const QString& strUserID, const QString& strTime, CUserAccount** ppData);
public:
	qint32 selectUserHoldAccount( quint16 nListenPort, QList<CUserHoldAccount*>& lstData, const QString& strUserID, const QString& strSymbolUse );
private:	
	bool _CheckTrade(const CUserTradeInfo* pData );
private:
	quint16 m_nListenPort;
	CStockTcpServer* m_pStockTcpServer;
	CServerDistributeTaskWorker* m_pServerDistributeTaskWorker;
	CServerDbOper* m_pServerDbOper;
};

#endif//__CLASS_TCP_SERVER_WORKER_H__
