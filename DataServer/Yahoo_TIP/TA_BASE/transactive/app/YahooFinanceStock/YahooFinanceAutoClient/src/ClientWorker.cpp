#include "ClientWorker.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "TcpSocketHelper.h"
#include "SocketInfo.h"
#include "Log4cppLogger.h"

#include "ClientComWorker.h"
#include "ClientMessagePostOffice.h"

CClientWorker::CClientWorker(const QString& strServerIP, quint16 nServerPort, QObject* parent/*=0*/ )
{
	m_strServerIP = strServerIP;
	m_nServerPort = nServerPort;

	m_pComWorker = NULL;
	m_pMessageManager = NULL;

	m_WorkerState = WORK_STATE_BEGIN;

}

CClientWorker::~CClientWorker()
{

}

void CClientWorker::run()
{
	MYLOG4CPP_DEBUG<<"CClientWorker::run() begin";

	m_pComWorker = new CClientComWorker(m_strServerIP, m_nServerPort, this);
	QObject::connect(m_pComWorker, SIGNAL(signalDisconnected(qint32)), this, SLOT(slotDisconnected(qint32)), Qt::AutoConnection);
	QObject::connect(m_pComWorker, SIGNAL(signalConnected(qint32)), this, SLOT(slotConnected(qint32)), Qt::AutoConnection);
	QObject::connect(this, SIGNAL(signalConnectToServer()), m_pComWorker, SLOT(slotConnectToServer()), Qt::AutoConnection);

	//
	m_pMessageManager = new CClientMessagePostOffice(this);
	QObject::connect(m_pComWorker, SIGNAL(signalRecvMessage(qint32, QByteArray*)), m_pMessageManager, SLOT(slotRecvMessage(qint32, QByteArray*)), Qt::AutoConnection);
	QObject::connect(m_pMessageManager, SIGNAL(signalSendMessage(qint32, QByteArray*)), m_pComWorker, SLOT(slotSendMessage(qint32, QByteArray*)), Qt::AutoConnection);

	m_pComWorker->start();

	m_WorkerState = WORK_STATE_BEGIN;
	m_WorkerState = WORK_STATE_WORKING;

	//QThread::exec() waits until QThread::exit() called
	MYLOG4CPP_DEBUG<<"CClientWorker::run() exec begin";
	exec();
	MYLOG4CPP_DEBUG<<"CClientWorker::run() exec end";

	m_pComWorker->terminateAndWait();

	//disconnected
	QObject::disconnect(this, SIGNAL(signalConnectToServer()), this, SLOT(slotConnectToServer()));
	QObject::disconnect(m_pComWorker, SIGNAL(signalDisconnected(qint32)), this, SLOT(slotDisconnected(qint32)));
	QObject::disconnect(m_pComWorker, SIGNAL(signalConnected(qint32)), this, SLOT(slotConnected(qint32)));
	QObject::disconnect(m_pComWorker, SIGNAL(signalRecvMessage(qint32, QByteArray*)), m_pMessageManager, SLOT(slotRecvMessage(qint32, QByteArray*)));
	QObject::disconnect(m_pMessageManager, SIGNAL(signalSendMessage(qint32, QByteArray*)), m_pComWorker, SLOT(slotSendMessage(qint32, QByteArray*)));

	if (NULL != m_pComWorker)
	{
		delete m_pComWorker;
		m_pComWorker = NULL;
	}
	if (NULL != m_pMessageManager)
	{
		delete m_pMessageManager;
		m_pMessageManager = NULL;
	}
	m_WorkerState = WORK_STATE_END;
	MYLOG4CPP_DEBUG<<"CClientWorker::run() end";

}

void CClientWorker::terminate()
{
	MYLOG4CPP_DEBUG<<"CClientWorker::terminate() begin";

	MYLOG4CPP_DEBUG<<"CClientWorker::terminate() end";
}


void CClientWorker::slotDisconnected(qint32 nHandle)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CClientWorker"
		<<" "<<"slot:"<<" "<<"slotDisconnected"
		<<" "<<"nHandle="<<nHandle;

	emit signalDisConnected(nHandle);
}

void CClientWorker::slotConnected(qint32 nHandle)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CClientWorker"
		<<" "<<"slot:"<<" "<<"slotConnected"
		<<" "<<"nHandle="<<nHandle;

	emit signalConnected(nHandle);
}


void CClientWorker::sendMessage(qint32 handle, QByteArray* pMessage)
{
	if (NULL != m_pMessageManager)
	{
		m_pMessageManager->sendMessage(handle, pMessage);
	}
	else
	{
		delete pMessage;
		pMessage = NULL;
	}
}

void CClientWorker::slotConnectToServer()
{
	emit signalConnectToServer();
}


