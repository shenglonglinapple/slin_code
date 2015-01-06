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
		QObject::connect(pActor, SIGNAL(signalDeleteConnection(CStockTcpServerActor*)), 
			this, SLOT(slotDeleteConnection(CStockTcpServerActor*)), Qt::AutoConnection);
		pActor->start();
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
	
}

void CStockTcpServer::slotDeleteConnection( CStockTcpServerActor* pActor )
{
	if (NULL != pActor)
	{
		pActor->terminateAndWait();
		delete pActor;
		pActor = NULL;
	}
}
