#ifndef __CLASS_CLIENT_WORKER_H__
#define __CLASS_CLIENT_WORKER_H__

#include "ClientActorParam.h"
#include "MyQtThread.h"
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "TcpComProtocol.h"

class QByteArray;
class QThreadPool;

class CClientDbOper;
class CClientComWorker;
class CCreateReqHelper;
class CStockMinTimeMaxTime;
class CHistoryData;
class CUserTradeInfo;
class CUserAccount;
class CUserHoldAccount;
class CStockInfo;

class CClientWorker : public CMyQtThread
{
    Q_OBJECT
public:
	CClientWorker(const CClientActorParam& param, QObject* parent=0);
	~CClientWorker();
signals:
	void signalConnectToServer();
	void signalSendMessage(qint32 handle, QByteArray* pMessage);
public slots:
	void slotRecvMessage(qint32 handle, QByteArray* pMessage);
	void slotDisconnected(qint32 nHandle);
	void slotConnected(qint32 nHandle);
public:
	void sendMessage(qint32 handle, QByteArray* pMessage);
public:
	virtual void run();	
	virtual void terminate();
//////////////////////////////////////////////////////////////////////////
signals:
	void signalDeleteConnection(CClientWorker* pActor);
public:
	void send_req_ReqCreateUser();
	void send_req_ReqLogin();
	void send_req_ReqDownLoadStock();
	void send_req_ReqStockMinTimeMaxTime(const QString& strSymbolUse);
	void send_req_ReqHistoryTrade(const QString& strSymbolUse, CTcpComProtocol::ETradeType nTradeType );
	void send_req_ReqUserAccount(const QString& strTime);
	void send_req_ReqUserHoldAccount( const QString& strSymbolUse );
	void send_req_ReqSynYahoo(const QString& strSymbolUse);

public:
	qint32 resetAllStockInfo( const QList<CStockInfo*>& lstData );
	void resetDataSymbolMinMaxTime(const CStockMinTimeMaxTime* pData );
	void resetHistoryData(const QString& strSymbolUse, const QList<CHistoryData*>& lstData );
	void insertUserTradeInfo(const QList<CUserTradeInfo*>& LstData );
	void insertUserTradeInfo(const CUserTradeInfo* pData);
	void insertUserAccount(const CUserAccount* pData );
	void resetUserAccount(const CUserAccount* pData);
	void resetUserHoldAccount(const QList<CUserHoldAccount*>& lstData );

private:
	CClientActorParam m_ClientActorParam;
	CClientComWorker* m_pComWorker;
	CCreateReqHelper* m_pCreateReqHelper;
private:
	QMutex m_mutex_ClientDbOper;
	CClientDbOper* m_pClientDbOper;
private:
	QThreadPool* m_pThreadPool;//Post Office Worker

};

#endif//__CLASS_CLIENT_WORKER_H__
