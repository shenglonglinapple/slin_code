#ifndef __CLASS_SERVER_COM_WORKER_H__
#define __CLASS_SERVER_COM_WORKER_H__

#include "MyQtThread.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtNetwork/QTcpSocket>

class CSocketInfo;

class CServerComWorker : public CMyQtThread
{
    Q_OBJECT
public:
    CServerComWorker(qint32 handle, QObject* parent=0);
	~CServerComWorker();
public:
	virtual void run();	
	virtual void terminate();
//////////////////////////////////////////////////////////////////////////
signals:
	void signalRecvMessage(qint32 handle, QByteArray* pMessage);
	void signalSendMessage(qint32 handle, QByteArray* pMessage);

	void signalProcessRecvData(QByteArray* pData);
	void signalDisconnected(qint32 handle);

private slots:
	void slotError(QAbstractSocket::SocketError nSocketError);
	void slotReadyRead();
	void slotDisconnected();
private slots:
	void slotProcessRecvData(QByteArray* pData);
	void slotSendMessage(qint32 handle, QByteArray* pMessage);

public:
	void sendMessage(qint32 handle, QByteArray* pMessage);

private:
	QMutex m_mutex_SocketW;
    qint32 m_nSocketHandle;
	CSocketInfo* m_pSocketInfo;
	QTcpSocket* m_pSocketHandle;

	QMutex m_mutex_SocketBuffer;
	QByteArray* m_pSocketBuffer;
};

#endif//__CLASS_SERVER_COM_WORKER_H__
