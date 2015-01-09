#include "StockTcpClientActor.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

#include "ClientComWorker.h"
#include "BaseException.h"

#include "TcpSocketHelper.h"
#include "MessageManager.h"
#include "SocketInfo.h"

#include "Log4cppLogger.h"

CDistributeTaskWorker::CDistributeTaskWorker( const QString& strServerIP, quint16 nServerPort, QObject* parent/*=0*/ )
{
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
	MYLOG4CPP_DEBUG<<"CStockTcpClientActor::run()";

	m_pComWorker = new CClientComWorker(m_strServerIP, m_nServerPort, this);
	QObject::connect(m_pComWorker, SIGNAL(signalDisconnected()), this, SLOT(slotDisconnected()), Qt::AutoConnection);
	QObject::connect(m_pComWorker, SIGNAL(signalConnected()), this, SLOT(slotConnected()), Qt::AutoConnection);
	QObject::connect(this, SIGNAL(signalConnectToServer()), m_pComWorker, SLOT(slotConnectToServer()), Qt::AutoConnection);

	//
	m_pMessageManager = new CMessageManager(this);
	QObject::connect(m_pComWorker, SIGNAL(signalProcessMessage(QByteArray*)), m_pMessageManager, SLOT(slotProcessMessage(QByteArray*)), Qt::AutoConnection);
	QObject::connect(m_pMessageManager, SIGNAL(signalWriteMessage(QByteArray*)), m_pComWorker, SLOT(slotWriteMessage(QByteArray*)), Qt::AutoConnection);

	m_pComWorker->start();

	m_WorkerState = WORK_STATE_BEGIN;
	m_WorkerState = WORK_STATE_WORKING;

	//QThread::exec() waits until QThread::exit() called
	exec();


	if (NULL != m_pComWorker)
	{
		m_pComWorker->terminateAndWait();
		delete m_pComWorker;
		m_pComWorker = NULL;
	}

	if (NULL != m_pMessageManager)
	{
		delete m_pMessageManager;
		m_pMessageManager = NULL;
	}

	m_WorkerState = WORK_STATE_END;

}

void CDistributeTaskWorker::terminate()
{
	return;
}


void CDistributeTaskWorker::slotDisconnected()
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpClientActor"
		<<" "<<"slot:"<<" "<<"slotDisconnected";
	//TODO.
	this->msleep(1000*10);

	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpClientActor"
		<<" "<<"fun:"<<" "<<"slotDisconnected"
		<<" "<<"emit signalConnectToServer()";

	emit signalConnectToServer();
}

void CDistributeTaskWorker::slotConnected()
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpClientActor"
		<<" "<<"slot:"<<" "<<"slotConnected";

	m_pMsgManager->send_login_req();
	//m_pMsgManager->send_logout_req();
	//m_pMsgManager->send_SynYahoo_req();
}


/*

void CTestMyThreadManager::do_test_mythread_2()
{
	CSampleMyQtThread* pMyThreadTest = NULL;
	pMyThreadTest = new CSampleMyQtThread();

	pMyThreadTest->start();

	pMyThreadTest->join();
	pMyThreadTest->my_msleep(1000* 10);

	pMyThreadTest->terminateAndWait();

	delete pMyThreadTest;
	pMyThreadTest = NULL;
}
*/


