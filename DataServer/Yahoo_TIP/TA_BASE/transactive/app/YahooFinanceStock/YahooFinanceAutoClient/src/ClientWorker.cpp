#include "ClientWorker.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QThreadPool>

#include "BaseException.h"
#include "TcpSocketHelper.h"
#include "SocketInfo.h"
#include "Log4cppLogger.h"

#include "ClientActorParam.h"
#include "ClientComWorker.h"
#include "ClientMessageRunnable.h"
#include "ClientActorManager.h"


CClientWorker::CClientWorker(const CClientActorParam& param, QObject* parent/*=0*/)
{
	m_ClientActorParam = param;
	m_pComWorker = NULL;
	m_pThreadPool = NULL;
	m_pThreadPool = new QThreadPool(this);
	//How many threads I want at any given time
	//If there are more connections, they will be queued until a threads is closed
	m_pThreadPool->setMaxThreadCount(3);

	m_WorkerState = WORK_STATE_BEGIN;
}



CClientWorker::~CClientWorker()
{
	if (NULL != m_pThreadPool)
	{
		delete m_pThreadPool;
		m_pThreadPool = NULL;
	}
}

void CClientWorker::run()
{
	MYLOG4CPP_DEBUG<<"CClientWorker::run() begin";

	m_pComWorker = new CClientComWorker(m_ClientActorParam.m_strServerIP, m_ClientActorParam.m_nServerPort, this);
	QObject::connect(m_pComWorker, SIGNAL(signalDisconnected(qint32)), this, SLOT(slotDisconnected(qint32)), Qt::AutoConnection);
	QObject::connect(m_pComWorker, SIGNAL(signalConnected(qint32)), this, SLOT(slotConnected(qint32)), Qt::AutoConnection);
	QObject::connect(m_pComWorker, SIGNAL(signalRecvMessage(qint32, QByteArray*)), this, SLOT(slotRecvMessage(qint32, QByteArray*)), Qt::AutoConnection);
	QObject::connect(this, SIGNAL(signalSendMessage(qint32, QByteArray*)), m_pComWorker, SLOT(slotSendMessage(qint32, QByteArray*)), Qt::AutoConnection);
	QObject::connect(this, SIGNAL(signalConnectToServer()), m_pComWorker, SLOT(slotConnectToServer()), Qt::AutoConnection);
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
	QObject::disconnect(m_pComWorker, SIGNAL(signalRecvMessage(qint32, QByteArray*)), this, SLOT(slotRecvMessage(qint32, QByteArray*)));
	QObject::disconnect(this, SIGNAL(signalSendMessage(qint32, QByteArray*)), m_pComWorker, SLOT(slotSendMessage(qint32, QByteArray*)));

	if (NULL != m_pComWorker)
	{
		delete m_pComWorker;
		m_pComWorker = NULL;
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

	emit signalConnectToServer();
}

void CClientWorker::slotConnected(qint32 nHandle)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CClientWorker"
		<<" "<<"slot:"<<" "<<"slotConnected"
		<<" "<<"nHandle="<<nHandle;

	CClientActorManager::getInstance().resetHanleValue(this, nHandle);

}
void CClientWorker::sendMessage(qint32 handle, QByteArray* pMessage)
{
	if (NULL != m_pComWorker)
	{
		MYLOG4CPP_DEBUG<<" "
			<<" "<<"class:"<<" "<<"CClientWorker"
			<<" "<<"fun:"<<" "<<"sendMessage"
			<<" "<<"emit:"<<" "<<"signalSendMessage"
			<<" "<<"param:"<<" "<<"handle="<<handle
			<<" "<<"param:"<<" "<<"pMessage=0x"<<pMessage;

		emit signalSendMessage(handle, pMessage);
	}
	else
	{
		delete pMessage;
		pMessage = NULL;
	}
}

void CClientWorker::slotRecvMessage(qint32 handle, QByteArray* pMessage)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CClientWorker"
		<<" "<<"fun:"<<" "<<"slotRecvMessage"
		<<" "<<"param:"<<" "<<"handle="<<handle
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;

	CClientMessageRunnable* pMessageRunnable = NULL;
	pMessageRunnable = new CClientMessageRunnable(handle, pMessage);
	//Delete that object when you're done (instead of using signals and slots)
	pMessageRunnable->setAutoDelete(true);
	MYLOG4CPP_DEBUG<<" "<<"m_pThreadPool begin start()";
	m_pThreadPool->start(pMessageRunnable);
	pMessageRunnable = NULL;
	MYLOG4CPP_DEBUG<<" "<<"m_pThreadPool end start()";
}

void CClientWorker::send_req_ReqLogin(qint32 nHandle, const QString& strUserName, const QString& strPassWord)
{
	CReqLogin* pReq = NULL;
	QByteArray* pByteArray = NULL;
	pReq = new CReqLogin();

	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserName = m_strUserName;
	pReq->m_strPassword = m_strPassWord;
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();

	CClientWorkerManager::getInstance().sendMessage(nHandle, pByteArray);

	pByteArray = NULL;

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}


