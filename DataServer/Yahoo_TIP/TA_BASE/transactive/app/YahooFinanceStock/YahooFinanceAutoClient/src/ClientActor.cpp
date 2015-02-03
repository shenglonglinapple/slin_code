#include "ClientActor.h"
#include "ClientActorParam.h"
#include "Log4cppLogger.h"
#include "ClientWorker.h"
#include "ClientActorManager.h"

CClientActor::CClientActor(const CClientActorParam& param, QObject* parent)
{
	m_pClientWorker = NULL;
	m_ClientActorParam = param;
}

CClientActor::~CClientActor()
{
	m_pClientWorker = NULL;
}



void CClientActor::run()
{
	MYLOG4CPP_DEBUG<<"CClientActor::run() begin";

	m_pClientWorker = new CClientWorker(m_ClientActorParam.m_strServerIP, m_ClientActorParam.m_nServerPort);
	QObject::connect(m_pClientWorker, SIGNAL(signalConnected(qint32)), this, SLOT(slotConnected(qint32)), Qt::AutoConnection);
	QObject::connect(m_pClientWorker, SIGNAL(signalDisConnected(qint32)), this, SLOT(slotDisconnected(qint32)), Qt::AutoConnection);
	QObject::connect(this, SIGNAL(signalConnectToServer()), m_pClientWorker, SLOT(slotConnectToServer()), Qt::AutoConnection);
	m_pClientWorker->start();

	m_WorkerState = WORK_STATE_BEGIN;
	m_WorkerState = WORK_STATE_WORKING;

	//QThread::exec() waits until QThread::exit() called
	MYLOG4CPP_DEBUG<<"CClientActor::run() exec begin";
	exec();
	MYLOG4CPP_DEBUG<<"CClientActor::run() exec end";
	QObject::disconnect(this, SIGNAL(signalConnectToServer()), m_pClientWorker, SLOT(slotConnectToServer()));
	QObject::disconnect(m_pClientWorker, SIGNAL(signalConnected(qint32)), this, SLOT(slotConnected(qint32)));
	QObject::disconnect(m_pClientWorker, SIGNAL(signalDisConnected(qint32)), this, SLOT(slotDisconnected(qint32)));
	if (NULL != m_pClientWorker)
	{
		m_pClientWorker->terminateAndWait();
		delete m_pClientWorker;
		m_pClientWorker = NULL;
	}

	m_WorkerState = WORK_STATE_END;
	MYLOG4CPP_DEBUG<<"CClientActor::run() end";

}

void CClientActor::terminate()
{
	MYLOG4CPP_DEBUG<<"CClientActor::terminate() begin";

	MYLOG4CPP_DEBUG<<"CClientActor::terminate() end";
}
void CClientActor::sendMessage( qint32 nHandle, QByteArray* pMessage )
{
	if (NULL != m_pClientWorker)
	{
		m_pClientWorker->sendMessage(nHandle, pMessage);
	}
	else
	{
		delete pMessage;
		pMessage = NULL;
	}
}

void CClientActor::slotConnected( qint32 nHandle )
{
	CClientActorManager::getInstance().resetHanleValue(this, nHandle);
}

void CClientActor::slotDisconnected( qint32 nHandle )
{
	this->msleep(1000*2);
	emit signalConnectToServer();
}

