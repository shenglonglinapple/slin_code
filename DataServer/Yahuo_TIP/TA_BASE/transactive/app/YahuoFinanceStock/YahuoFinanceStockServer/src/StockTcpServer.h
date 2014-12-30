#ifndef __CLASS_STOCK_TCP_SERVER_H__
#define __CLASS_STOCK_TCP_SERVER_H__

#include <QtNetwork/QTcpServer>

class CStockTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    CStockTcpServer(QObject *parent = 0);
	virtual ~CStockTcpServer();
protected:
    void incomingConnection(int socketDescriptor);
public:
	quint16 m_nServerPort;
};


#endif//__CLASS_STOCK_TCP_SERVER_H__
