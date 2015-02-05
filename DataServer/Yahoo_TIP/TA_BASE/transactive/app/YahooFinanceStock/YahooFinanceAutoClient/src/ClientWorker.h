#ifndef __CLASS_CLIENT_WORKER_H__
#define __CLASS_CLIENT_WORKER_H__

#include "ClientActorParam.h"
#include "MyQtThread.h"


class QByteArray;
class QThreadPool;

class CClientComWorker;
class CCreateReqHelper;

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
private:
	CClientActorParam m_ClientActorParam;
	CClientComWorker* m_pComWorker;
	CCreateReqHelper* m_pCreateReqHelper;
private:
	QThreadPool* m_pThreadPool;//Post Office Worker
private:
	void send_req_ReqLogin(qint32 nHandle, const QString& strUserName, const QString& strPassWord);
};

#endif//__CLASS_CLIENT_WORKER_H__
