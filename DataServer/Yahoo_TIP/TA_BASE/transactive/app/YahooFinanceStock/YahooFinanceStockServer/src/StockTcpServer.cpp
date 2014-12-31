#include "StockTcpServer.h"

#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "StockTcpServerActor.h"


CStockTcpServer::CStockTcpServer(QObject *parent)
    : QTcpServer(parent)
{
	m_nServerPort = 5000;
}


CStockTcpServer::~CStockTcpServer()
{
}

void CStockTcpServer::startListen()
{
	if (false == this->listen(QHostAddress::Any, m_nServerPort)) 
	{
		MYLOG4CPP_ERROR<<"Unable to Start Server TCP Listen Port="<<m_nServerPort;

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
	CStockTcpServerActor* pActor = NULL;

	try
	{
		pActor = new CStockTcpServerActor(handle, this);
	}
	catch (CBaseException& e)
	{
		e.logInfo(__FILE__, __LINE__);
		if (NULL != pActor)
		{
			delete pActor;
			pActor = NULL;
		}
	}
	
	//CStockTcpServerActor* pActor = new CStockTcpServerActor(handle, this);
	//QObject::connect(pActor, SIGNAL(signalDeleteMe()), pActor, SLOT(deleteLater()));
}
