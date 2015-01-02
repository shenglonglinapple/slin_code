#ifndef __CLASS_STOCK_TCP_SERVER_ACTOR_H__
#define __CLASS_STOCK_TCP_SERVER_ACTOR_H__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtNetwork/QTcpSocket>

class CStockTcpServerActor : public QObject
{
    Q_OBJECT

public:
    CStockTcpServerActor(qint32 handle, QObject* parent=0);
	~CStockTcpServerActor();

signals:
	void signalDeleteMe();
	void signalProcessRecvBuffer();
	void signalProcessMessage(QByteArray* pMessage);
private slots:
	void slotError(QAbstractSocket::SocketError nSocketError);
	void slotReadyRead();
	void slotDisconnected();
private slots:
	void slotProcessRecvBuffer();
	void slotProcessMessage(QByteArray* pMessage);

public:
	void writeAck();

private:
	void _GetSocketInfo();
private:
	QString m_strlocalAddress;
	quint16 m_nLocalPort;
	QString m_strPeerAddress;
	QString m_strPeerName;
	quint16 m_nPeerPort;
private:
	QMutex m_mutex_SocketW;
    qint32 m_nSocketHandle;
	QTcpSocket* m_pSocketHandle;

	QMutex m_mutex_SocketBuffer;
	QByteArray* m_pSocketBuffer;

};

#endif//__CLASS_STOCK_TCP_SERVER_ACTOR_H__
