#ifndef __CLASS_DISTRIBUTE_TASK_WORKER_H__
#define __CLASS_DISTRIBUTE_TASK_WORKER_H__

#include "MyQtThread.h"


class CMessageManager;
class CClientComWorker;

class CDistributeTaskWorker : public CMyQtThread
{
    Q_OBJECT
public:
	CDistributeTaskWorker(
		const QString& strUserName,
		const QString& strPassWord,
		const QString& strServerIP, 
		quint16 nServerPort, 
		QObject* parent=0);

	~CDistributeTaskWorker();
signals:
	void signalConnectToServer();
public slots:
	void slotDisconnected(qint32 nHandle);
	void slotConnected(qint32 nHandle);
public:
	virtual void run();	
	virtual void terminate();
//////////////////////////////////////////////////////////////////////////
signals:
	void signalDeleteConnection(CDistributeTaskWorker* pActor);
public:
	void sendMessage(qint32 handle, QByteArray* pMessage);

private:
	QString m_strServerIP;// = "127.0.0.1";
	quint16 m_nServerPort;// = 5000;
	QString m_strUserName;
	QString m_strPassWord;

	CClientComWorker* m_pComWorker;
	CMessageManager* m_pMessageManager;
};

#endif//__CLASS_DISTRIBUTE_TASK_WORKER_H__
