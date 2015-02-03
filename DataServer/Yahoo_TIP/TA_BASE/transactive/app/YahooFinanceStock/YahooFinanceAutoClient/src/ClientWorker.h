#ifndef __CLASS_CLIENT_WORKER_H__
#define __CLASS_CLIENT_WORKER_H__

#include "MyQtThread.h"


class CClientMessagePostOffice;
class CClientComWorker;

class CClientWorker : public CMyQtThread
{
    Q_OBJECT
public:
	CClientWorker(const QString& strServerIP, quint16 nServerPort, QObject* parent=0);
	~CClientWorker();
signals:
	void signalConnected(qint32 nHandle);
	void signalDisConnected(qint32 nHandle);
	void signalConnectToServer();
public slots:
	void slotDisconnected(qint32 nHandle);
	void slotConnected(qint32 nHandle);
	void slotConnectToServer();

public:
	virtual void run();	
	virtual void terminate();
//////////////////////////////////////////////////////////////////////////
signals:
	void signalDeleteConnection(CClientWorker* pActor);
public:
	void sendMessage(qint32 handle, QByteArray* pMessage);

private:
	QString m_strServerIP;// = "127.0.0.1";
	quint16 m_nServerPort;// = 5000;

	CClientComWorker* m_pComWorker;
	CClientMessagePostOffice* m_pMessageManager;
};

#endif//__CLASS_CLIENT_WORKER_H__
