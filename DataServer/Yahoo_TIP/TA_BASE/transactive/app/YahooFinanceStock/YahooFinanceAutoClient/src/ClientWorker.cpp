#include "ClientWorker.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QThreadPool>

#include "WorkTime.h"
#include "BaseException.h"
#include "TcpSocketHelper.h"
#include "SocketInfo.h"
#include "Log4cppLogger.h"

#include "ClientActorParam.h"
#include "ClientComWorker.h"
#include "ClientMessageRunnable.h"
#include "ClientActorManager.h"
#include "CreateReqHelper.h"
#include "ClientDbOper.h"
#include "StockMinTimeMaxTime.h"

CClientWorker::CClientWorker(const CClientActorParam& param, QObject* parent/*=0*/)
{
	m_ClientActorParam = param;
	m_pComWorker = NULL;
	m_pThreadPool = NULL;
	m_pCreateReqHelper = NULL;

	{
		QMutexLocker lock(&m_mutex_ClientDbOper);	
		m_pClientDbOper = NULL;
		m_pClientDbOper = new CClientDbOper(m_ClientActorParam.getUserID());
	}
	m_pCreateReqHelper = new CCreateReqHelper();
	m_pThreadPool = new QThreadPool(this);
	//How many threads I want at any given time
	//If there are more connections, they will be queued until a threads is closed
	m_pThreadPool->setMaxThreadCount(3);

	m_WorkerState = WORK_STATE_BEGIN;
}



CClientWorker::~CClientWorker()
{
	{
		QMutexLocker lock(&m_mutex_ClientDbOper);	
		if (NULL != m_pClientDbOper)
		{
			delete m_pClientDbOper;
			m_pClientDbOper = NULL;
		}
	}

	if (NULL != m_pCreateReqHelper)
	{
		delete m_pCreateReqHelper;
		m_pCreateReqHelper = NULL;
	}
	if (NULL != m_pThreadPool)
	{
		delete m_pThreadPool;
		m_pThreadPool = NULL;
	}
}

void CClientWorker::run()
{
	MYLOG4CPP_DEBUG<<"CClientWorker::run() begin";

	m_pComWorker = new CClientComWorker(m_ClientActorParam.getServerIP(), m_ClientActorParam.getServerPort(), this);
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

	m_ClientActorParam.setHandleValue(nHandle);
	CClientActorManager::getInstance().resetHanleValue(this, nHandle);
	send_req_ReqCreateUser();
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



//////////////////////////////////////////////////////////////////////////
qint32 CClientWorker::resetSymbolUse( const QList<QString>& lstData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);	
	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->resetSymbolUse(lstData);
	}
	return nFunRes;
}

qint32 CClientWorker::getSymbolUseLst(QList<QString>& lstData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);	
	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->getSymbolUseLst(lstData);
	}
	return nFunRes;
}
void CClientWorker::resetDataSymbolMinMaxTime( const CStockMinTimeMaxTime* pData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);	
	qint32 nFunRes = 0;
	CStockMinTimeMaxTime* pFind = NULL;

	if (NULL != m_pClientDbOper)
	{
		m_pClientDbOper->selectSymbolMinMaxTime(pData->m_strSymbolUse, &pFind);

		if (NULL == pFind)
		{
			m_pClientDbOper->insertSymbolMinMaxTime(pData);
		}
		else
		{
			m_pClientDbOper->updateSymbolMinMaxTime(pData);
			delete pFind;
			pFind = NULL;
		}
	}
	return;
}
void CClientWorker::resetHistoryData( const QString& strSymbolUse, const QList<CHistoryData*>& lstData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	CWorkTimeNoLock workTime(0);
	workTime.workBegin();
	MYLOG4CPP_DEBUG<<"CClientWorker::resetDataHistory() begin";

	if (NULL != m_pClientDbOper)
	{
		m_pClientDbOper->resetHistoryData(strSymbolUse, lstData);
	}
	workTime.workEnd();
	MYLOG4CPP_DEBUG<<"CClientWorker::resetDataHistory() end getWorkTime="<<workTime.getWorkTime()<<" "<<"ms";

	return;
}
void CClientWorker::insertUserTradeInfo( const QList<CUserTradeInfo*>& LstData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);
	QList<CUserTradeInfo*>::const_iterator iterLst;
	const CUserTradeInfo* pData = NULL;
	iterLst = LstData.constBegin();
	while (iterLst != LstData.constEnd())
	{
		pData = NULL;
		pData = (*iterLst);
		if (NULL != m_pClientDbOper)
		{
			m_pClientDbOper->insertUserTradeInfo(pData);
		}
		iterLst++;
	}//while
	return;
}

void CClientWorker::insertUserTradeInfo( const CUserTradeInfo* pData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	if (NULL != m_pClientDbOper)
	{
		m_pClientDbOper->insertUserTradeInfo(pData);
	}

	return;
}

void CClientWorker::resetUserAccount( const CUserAccount* pData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);
	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->resetUserAccount(pData);
	}
	return;
}

void CClientWorker::resetUserHoldAccount( const QList<CUserHoldAccount*>& lstData )
{
	QMutexLocker lock(&m_mutex_ClientDbOper);

	qint32 nFunRes = 0;
	if (NULL != m_pClientDbOper)
	{
		nFunRes = m_pClientDbOper->resetUserHoldAccount(lstData);
	}
	return;
}
//////////////////////////////////////////////////////////////////////////
void CClientWorker::send_req_ReqCreateUser()
{
	QByteArray* pByteArray = NULL;
	pByteArray = m_pCreateReqHelper->create_req_ReqCreateUser(
		m_ClientActorParam.getUserName(), 
		m_ClientActorParam.getUserPWD());
	this->sendMessage(m_ClientActorParam.getHandle(), pByteArray);
	pByteArray = NULL;
}
void CClientWorker::send_req_ReqLogin()
{
	QByteArray* pByteArray = NULL;
	pByteArray = m_pCreateReqHelper->create_req_ReqLogin(
		m_ClientActorParam.getUserName(), 
		m_ClientActorParam.getUserPWD());

	this->sendMessage(m_ClientActorParam.getHandle(), pByteArray);
	pByteArray = NULL;
}

void CClientWorker::send_req_ReqDownLoadStock()
{
	QByteArray* pByteArray = NULL;
	pByteArray = m_pCreateReqHelper->create_req_ReqDownLoadStock();
	this->sendMessage(m_ClientActorParam.getHandle(), pByteArray);
	pByteArray = NULL;
}

void CClientWorker::send_req_ReqStockMinTimeMaxTime( const QString& strSymbolUse )
{
	QByteArray* pByteArray = NULL;
	pByteArray = m_pCreateReqHelper->create_req_ReqStockMinTimeMaxTime(strSymbolUse);
	this->sendMessage(m_ClientActorParam.getHandle(), pByteArray);
	pByteArray = NULL;
}

void CClientWorker::send_req_ReqHistoryTrade( 
	const QString& strSymbolUse, CTcpComProtocol::ETradeType nTradeType )
{
	QByteArray* pByteArray = NULL;
	pByteArray = m_pCreateReqHelper->create_req_ReqHistoryTrade(
		m_ClientActorParam.getUserID(), strSymbolUse, nTradeType);
	this->sendMessage(m_ClientActorParam.getHandle(), pByteArray);
	pByteArray = NULL;
}

void CClientWorker::send_req_ReqUserAccount( const QString& strTime )
{
	QByteArray* pByteArray = NULL;
	pByteArray = m_pCreateReqHelper->create_req_ReqUserAccount(
		m_ClientActorParam.getUserID(), strTime);
	this->sendMessage(m_ClientActorParam.getHandle(), pByteArray);
	pByteArray = NULL;
}

void CClientWorker::send_req_ReqUserHoldAccount( const QString& strSymbolUse )
{
	QByteArray* pByteArray = NULL;
	pByteArray = m_pCreateReqHelper->create_req_ReqUserHoldAccount(
		m_ClientActorParam.getUserID(), strSymbolUse);
	this->sendMessage(m_ClientActorParam.getHandle(), pByteArray);
	pByteArray = NULL;
}

void CClientWorker::send_req_ReqSynYahoo( const QString& strSymbolUse )
{
	QByteArray* pByteArray = NULL;
	pByteArray = m_pCreateReqHelper->create_req_ReqSynYahoo(strSymbolUse);
	this->sendMessage(m_ClientActorParam.getHandle(), pByteArray);
	pByteArray = NULL;
}









