#include "ServerDistributeTaskWorker.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "StockTcpServer.h"
#include "ServerComManager.h"
#include "MessageManager.h"

CServerDistributeTaskWorker::CServerDistributeTaskWorker(QObject* parent/*=0*/ )
{
	m_pServerComManager = NULL;
	m_pMessageManager = NULL;
}

CServerDistributeTaskWorker::~CServerDistributeTaskWorker()
{

}

void CServerDistributeTaskWorker::run()
{
	MYLOG4CPP_DEBUG<<"CServerDistributeTaskWorker::run() begin";

	m_pServerComManager = new CServerComManager(this);
	m_pMessageManager = new CMessageManager(this);

	QObject::connect(m_pServerComManager, SIGNAL(signalRecvMessage(qint32, QByteArray*)), 
		m_pMessageManager, SLOT(slotRecvMessage(qint32, QByteArray*)),  Qt::AutoConnection);

	QObject::connect(m_pMessageManager, SIGNAL(signalSendMessage(qint32, QByteArray*)), 
		m_pServerComManager, SLOT(slotSendMessage(qint32, QByteArray*)),  Qt::AutoConnection);


	MYLOG4CPP_DEBUG<<"CServerDistributeTaskWorker::run() exec() begin";
	exec();
	MYLOG4CPP_DEBUG<<"CServerDistributeTaskWorker::run() exec() end";

	if (NULL != m_pMessageManager)
	{
		delete m_pMessageManager;
		m_pMessageManager = NULL;
	}

	if (NULL != m_pServerComManager)
	{
		delete m_pServerComManager;
		m_pServerComManager = NULL;
	}



	MYLOG4CPP_DEBUG<<"CServerDistributeTaskWorker::run() end";
}

void CServerDistributeTaskWorker::terminate()
{
	MYLOG4CPP_DEBUG<<"CServerDistributeTaskWorker::terminate() begin";


	MYLOG4CPP_DEBUG<<"CServerDistributeTaskWorker::terminate() end";
}

void CServerDistributeTaskWorker::slotIncomingConnection( qint32 handle )
{

	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CServerDistributeTaskWorker"
		<<" "<<"slot:"<<" "<<"slotIncomingConnection"
		<<" "<<"param:"<<" "<<"handle="<<handle;

	if (NULL != m_pServerComManager)
	{
		m_pServerComManager->incomingConnection(handle);
	}
	else
	{
		MYLOG4CPP_ERROR<<"m_pServerComManager is NULL! CServerDistributeTaskWorker is not runing ";
	}
}

void CServerDistributeTaskWorker::sendMessage( qint32 handle, QByteArray* pMessage )
{
	if (NULL != m_pMessageManager)
	{
		m_pMessageManager->sendMessage(handle, pMessage);
	}
	else
	{
		MYLOG4CPP_ERROR<<"m_pMessageManager is NULL! CServerDistributeTaskWorker is not runing ";
		delete pMessage;
		pMessage = NULL;
	}
	
}
