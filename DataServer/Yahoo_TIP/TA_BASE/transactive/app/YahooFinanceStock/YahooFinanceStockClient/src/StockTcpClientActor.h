#ifndef __CLASS_STOCK_TCP_CLIENT_ACTOR_H__
#define __CLASS_STOCK_TCP_CLIENT_ACTOR_H__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtNetwork/QTcpSocket>

class CMsgManager;

class CStockTcpClientActor : public QObject
{
    Q_OBJECT

public:
    CStockTcpClientActor(QObject* parent=0);
	~CStockTcpClientActor();

signals:
	void signalDeleteMe();
	void signalProcessMessage(QByteArray* pMessage);
private slots:
	void slotConnected();
	void slotError(QAbstractSocket::SocketError nSocketError);
	void slotReadyRead();
	void slotDisconnected();
private slots:
	void _ProcessRecvBuffer();
public slots:
	void slotWriteMessage(QByteArray* pByteArray);
public:
	void connectToServer( const QString& strServerIP, quint16 nServerPort );
	void disConnectToServer();
public:
	void send_login_req();
	void send_logout_req();


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
private:
	CMsgManager* m_pMsgManager;
};

#endif//__CLASS_STOCK_TCP_CLIENT_ACTOR_H__
