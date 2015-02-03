#ifndef __CLASS_CLIENT_COM_WORKER_H__
#define __CLASS_CLIENT_COM_WORKER_H__

#include "MyQtThread.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtNetwork/QTcpSocket>

class CSocketInfo;

class CClientComWorker : public CMyQtThread
{
    Q_OBJECT
public:
	CClientComWorker(const QString& strServerIP, quint16 nServerPort, QObject* parent=0);
	~CClientComWorker();
public:
	virtual void run();	
	virtual void terminate();
//////////////////////////////////////////////////////////////////////////
signals:
	void signalRecvMessage(qint32 handle, QByteArray* pMessage);
	void signalDisconnected(qint32 handle);
	void signalConnected(qint32 handle);
signals:
	void signalProcessRecvData(QByteArray* pData);
	void signalSendMessage(qint32 handle, QByteArray* pMessage);

private slots:
	void slotError(QAbstractSocket::SocketError nSocketError);
	void slotReadyRead();
	void slotDisconnected();
	void slotConnected();

private slots:
	void slotProcessRecvData(QByteArray* pData);

public slots:
	void slotSendMessage(qint32 handle, QByteArray* pByteArray);
	void slotConnectToServer();

public:
	void sendMessage(qint32 handle, QByteArray* pMessage);

private:
	QMutex m_mutex_SocketW;
	CSocketInfo* m_pSocketInfo;
	QTcpSocket* m_pSocketHandle;
	QString m_strServerIP;// = "127.0.0.1";
	quint16 m_nServerPort;// = 5000;
	qint32 m_nHandle;

	QMutex m_mutex_SocketBuffer;
	QByteArray* m_pSocketBuffer;
};

#endif//__CLASS_CLIENT_COM_WORKER_H__
