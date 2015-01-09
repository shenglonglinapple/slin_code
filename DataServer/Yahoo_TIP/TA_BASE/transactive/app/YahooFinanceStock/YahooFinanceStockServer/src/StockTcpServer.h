#ifndef __CLASS_STOCK_TCP_SERVER_H__
#define __CLASS_STOCK_TCP_SERVER_H__

#include <QtNetwork/QTcpServer>

class CStockTcpServerActor;

class CStockTcpServer : public QTcpServer
{
    Q_OBJECT

public:
	CStockTcpServer(quint16 nListenPort, QObject *parent);
	~CStockTcpServer();
signals:
	void signalIncomingConnection(qint32 handle);
public:
	void startListen();
	void stopListen();
protected:
    void incomingConnection(qint32 handle);
private:
	quint16 m_nListenPort;
};


#endif//__CLASS_STOCK_TCP_SERVER_H__
