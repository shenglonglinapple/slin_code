#ifndef __CLASS_STOCK_TCP_SERVER_ACTOR_H__
#define __CLASS_STOCK_TCP_SERVER_ACTOR_H__

#include <QtCore/QThread>
#include <QtNetwork/QTcpSocket>

class CStockTcpServerActor : public QObject
{
    Q_OBJECT

public:
    CStockTcpServerActor(qint32 handle, QObject* parent=0);
	~CStockTcpServerActor();

signals:
	void signalDeleteMe();
private slots:
	void slotError(QAbstractSocket::SocketError nSocketError);
	void slotReadyRead();
	void writeAck();
	void slotDisconnected();
private:
	void _Unit();
	void _Init();
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

#endif//__CLASS_STOCK_TCP_SERVER_ACTOR_H__
