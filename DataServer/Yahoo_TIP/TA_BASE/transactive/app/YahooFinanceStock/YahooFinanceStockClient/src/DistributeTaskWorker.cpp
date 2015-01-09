#include "DistributeTaskWorker.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

#include "ClientComWorker.h"
#include "BaseException.h"

#include "TcpSocketHelper.h"
#include "MessageManager.h"
#include "SocketInfo.h"

#include "Log4cppLogger.h"
#include "ProjectEnvironment.h"

CDistributeTaskWorker::CDistributeTaskWorker(
	const QString& strUserName,
	const QString& strPassWord,
	const QString& strServerIP, 
	quint16 nServerPort, 
	QObject* parent/*=0*/ )
{
	m_strUserName = strUserName;
	m_strPassWord = strPassWord;

	m_strServerIP = strServerIP;
	m_nServerPort = nServerPort;

	m_pComWorker = NULL;
	m_pMessageManager = NULL;

	m_WorkerState = WORK_STATE_BEGIN;

}

CDistributeTaskWorker::~CDistributeTaskWorker()
{

}

void CDistributeTaskWorker::run()
{
	MYLOG4CPP_DEBUG<<"CDistributeTaskWorker::run()";

	m_pComWorker = new CClientComWorker(m_strServerIP, m_nServerPort, this);
	QObject::connect(m_pComWorker, SIGNAL(signalDisconnected(qint32)), this, SLOT(slotDisconnected(qint32)), Qt::AutoConnection);
	QObject::connect(m_pComWorker, SIGNAL(signalConnected(qint32)), this, SLOT(slotConnected(qint32)), Qt::AutoConnection);
	QObject::connect(this, SIGNAL(signalConnectToServer()), m_pComWorker, SLOT(slotConnectToServer()), Qt::AutoConnection);


	//
	m_pMessageManager = new CMessageManager(this);
	QObject::connect(m_pComWorker, SIGNAL(signalRecvMessage(qint32, QByteArray*)), m_pMessageManager, SLOT(slotRecvMessage(qint32, QByteArray*)), Qt::AutoConnection);
	QObject::connect(m_pMessageManager, SIGNAL(signalSendMessage(qint32, QByteArray*)), m_pComWorker, SLOT(slotSendMessage(qint32, QByteArray*)), Qt::AutoConnection);

	m_pComWorker->start();

	m_WorkerState = WORK_STATE_BEGIN;
	m_WorkerState = WORK_STATE_WORKING;

	//QThread::exec() waits until QThread::exit() called
	exec();

	if (NULL != m_pMessageManager)
	{
		delete m_pMessageManager;
		m_pMessageManager = NULL;
	}

	if (NULL != m_pComWorker)
	{
		m_pComWorker->terminateAndWait();
		delete m_pComWorker;
		m_pComWorker = NULL;
	}



	m_WorkerState = WORK_STATE_END;

}

void CDistributeTaskWorker::terminate()
{
	return;
}


void CDistributeTaskWorker::slotDisconnected(qint32 nHandle)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CDistributeTaskWorker"
		<<" "<<"slot:"<<" "<<"slotDisconnected"
		<<" "<<"nHandle="<<nHandle;

	//TODO.For.Test
	CProjectEnviroment::getInstance().qtWaitTime(1000*2);

	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CDistributeTaskWorker"
		<<" "<<"fun:"<<" "<<"slotDisconnected"
		<<" "<<"emit signalConnectToServer()";

	emit signalConnectToServer();
}

void CDistributeTaskWorker::slotConnected(qint32 nHandle)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CDistributeTaskWorker"
		<<" "<<"slot:"<<" "<<"slotConnected"
		<<" "<<"nHandle="<<nHandle;

	//TODO.For.Test
	//send login req
	m_pMessageManager->sendReqLogin(nHandle, m_strUserName, m_strPassWord);
}




