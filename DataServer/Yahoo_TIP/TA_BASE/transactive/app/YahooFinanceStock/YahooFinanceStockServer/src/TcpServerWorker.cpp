#include "TcpServerWorker.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "StockTcpServer.h"
#include "ServerDistributeTaskWorker.h"


CTcpServerWorker::CTcpServerWorker( quint16 nListenPort, QObject* parent/*=0*/ )
{
	m_nListenPort = 0;
	m_pStockTcpServer = NULL;
	m_pServerDistributeTaskWorker = NULL;


	m_nListenPort = nListenPort;
	
}

CTcpServerWorker::~CTcpServerWorker()
{

}

void CTcpServerWorker::run()
{
	MYLOG4CPP_DEBUG<<"CTcpServerWorker::run() begin";

	m_pStockTcpServer = new CStockTcpServer(m_nListenPort, this);
	m_pServerDistributeTaskWorker = new CServerDistributeTaskWorker(this);

	QObject::connect(m_pStockTcpServer, SIGNAL(signalIncomingConnection(qint32)), 
		m_pServerDistributeTaskWorker, SLOT(slotIncomingConnection(qint32)), Qt::AutoConnection);


	try
	{
		m_pStockTcpServer->startListen();
		m_pServerDistributeTaskWorker->start();

		MYLOG4CPP_DEBUG<<"CTcpServerWorker::run() exec() begin";
		exec();
		MYLOG4CPP_DEBUG<<"CTcpServerWorker::run() exec() end";

	}
	catch (CBaseException& e)
	{
		e.logInfo(__FILE__, __LINE__);
	}


	if (NULL != m_pServerDistributeTaskWorker)
	{
		m_pServerDistributeTaskWorker->terminateAndWait();
		delete m_pServerDistributeTaskWorker;
		m_pServerDistributeTaskWorker = NULL;
	}

	if (NULL != m_pStockTcpServer)
	{
		m_pStockTcpServer->stopListen();
		delete m_pStockTcpServer;
		m_pStockTcpServer = NULL;
	}

	MYLOG4CPP_DEBUG<<"CTcpServerWorker::run() end";
}

void CTcpServerWorker::terminate()
{
	MYLOG4CPP_DEBUG<<"CTcpServerWorker::terminate() begin";


	MYLOG4CPP_DEBUG<<"CTcpServerWorker::terminate() end";
}
