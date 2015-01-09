#include "StockTcpServer.h"

#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "StockTcpServerActor.h"


CStockTcpServer::CStockTcpServer(quint16 nListenPort, QObject *parent)
    : QTcpServer(parent)
{
	m_nListenPort = nListenPort;
}


CStockTcpServer::~CStockTcpServer()
{
}

void CStockTcpServer::startListen()
{
	if (false == this->listen(QHostAddress::Any, m_nListenPort)) 
	{
		MYLOG4CPP_ERROR<<"Unable to Start Server TCP Listen Port="<<m_nListenPort;

		//Unable to start the server
		throw CBaseException(__FILE__, __LINE__, this->errorString());
	}
	else
	{
		MYLOG4CPP_INFO<<"Server TCP Listen"
			<<" "<<"serverAddress="<<this->serverAddress().toString()
			<<" "<<"serverPort="<<this->serverPort();
	}

}

void CStockTcpServer::stopListen()
{
	this->close();
}

void CStockTcpServer::incomingConnection(qint32 handle)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServer"
		<<" "<<"fun:"<<" "<<"incomingConnection"
		<<" "<<"emit:"<<" "<<"signalIncomingConnection"
		<<" "<<"param:"<<" "<<"handle="<<handle;

	emit signalIncomingConnection(handle);
}

