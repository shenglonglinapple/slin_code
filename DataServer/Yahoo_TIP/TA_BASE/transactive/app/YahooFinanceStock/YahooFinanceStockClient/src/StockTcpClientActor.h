#ifndef __CLASS_STOCK_TCP_CLIENT_ACTOR_H__
#define __CLASS_STOCK_TCP_CLIENT_ACTOR_H__

#include <QtCore/QThread>
#include <QtNetwork/QTcpSocket>

class CStockTcpClientActor : public QObject
{
    Q_OBJECT

public:
    CStockTcpClientActor(QObject* parent=0);
	~CStockTcpClientActor();

signals:
	void signalDeleteMe();
private slots:
	void slotError(QAbstractSocket::SocketError nSocketError);
	void slotReadyRead();
	void slotDisconnected();
	void slotConnected();
public:
	void connectToServer(const QString& strServerIP, quint16 nServerPort);
	void disConnectToServer();

	void send_req();
private:
	void _GetSocketInfo();
private:
	QString m_strlocalAddress;
	quint16 m_nLocalPort;
	QString m_strPeerAddress;
	QString m_strPeerName;
	quint16 m_nPeerPort;
private:
    qint32 m_nHandle;
	QTcpSocket* m_pSocketHandle;


};

#endif//__CLASS_STOCK_TCP_CLIENT_ACTOR_H__
