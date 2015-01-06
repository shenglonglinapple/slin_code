#ifndef __CLASS_STOCK_TCP_SERVER_H__
#define __CLASS_STOCK_TCP_SERVER_H__

#include <QtNetwork/QTcpServer>

class CStockTcpServerActor;

class CStockTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    CStockTcpServer(QObject* parent = 0);
	virtual ~CStockTcpServer();
public slots:
	void slotDeleteConnection(CStockTcpServerActor* pActor);
public:
	void startListen();
	void stopListen();

protected:
    void incomingConnection(qint32 handle);
public:
	quint16 m_nServerPort;
};


#endif//__CLASS_STOCK_TCP_SERVER_H__
