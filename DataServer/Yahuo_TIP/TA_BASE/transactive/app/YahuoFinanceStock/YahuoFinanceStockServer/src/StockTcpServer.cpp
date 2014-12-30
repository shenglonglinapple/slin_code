#include "StockTcpServer.h"

CStockTcpServer::CStockTcpServer(QObject *parent)
    : QTcpServer(parent)
{
	m_nServerPort = 5000;
}


CStockTcpServer::~CStockTcpServer()
{

}

void CStockTcpServer::incomingConnection(int socketDescriptor)
{
//     QString fortune = fortunes.at(qrand() % fortunes.size());
//     FortuneThread *thread = new FortuneThread(socketDescriptor, fortune, this);
//     connect(thread, SIGNAL(clientDisconnetcd()), thread, SLOT(deleteLater()));
}
