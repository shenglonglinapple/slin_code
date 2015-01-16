#include "MessageManager.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtCore/QThreadPool>

#include "MessageRunnable.h"
#include "ReqLogin.h"
#include "ReqSynYahoo.h"
#include "ReqDownLoadStock.h"
#include "Log4cppLogger.h"



CMessageManager::CMessageManager( QObject* parent /*= 0*/ )
{
	m_pThreadPool = NULL;
	m_pThreadPool = new QThreadPool(this);


	//How many threads I want at any given time
	//If there are more connections, they will be queued until a threads is closed
	m_pThreadPool->setMaxThreadCount(20);
}

CMessageManager::~CMessageManager()
{

	if (NULL != m_pThreadPool)
	{
		delete m_pThreadPool;
		m_pThreadPool = NULL;
	}
}


void CMessageManager::slotRecvMessage( qint32 handle, QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CMessageManager"
		<<" "<<"fun:"<<" "<<"slotRecvMessage"
		<<" "<<"param:"<<" "<<"handle="<<handle
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;

	CMessageRunnable* pMessageRunnable = NULL;
	pMessageRunnable = new CMessageRunnable(handle, pMessage);
	//Delete that object when you're done (instead of using signals and slots)
	pMessageRunnable->setAutoDelete(true);

	MYLOG4CPP_DEBUG<<" "<<"m_pThreadPool begin start()";

	m_pThreadPool->start(pMessageRunnable);
	pMessageRunnable = NULL;

	MYLOG4CPP_DEBUG<<" "<<"m_pThreadPool end start()";
}

void CMessageManager::sendMessage( qint32 handle, QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CMessageManager"
		<<" "<<"fun:"<<" "<<"sendMessage"
		<<" "<<"emit:"<<" "<<"signalSendMessage"
		<<" "<<"param:"<<" "<<"handle="<<handle
		<<" "<<"param:"<<" "<<"pMessage=0x"<<pMessage;

	emit signalSendMessage(handle, pMessage);
}

void CMessageManager::sendReqLogin( qint32 handle, const QString& strUserName, const QString& strPassWord )
{
	CReqLogin* pReq = NULL;
	QByteArray* pByteArray = NULL;
	pReq = new CReqLogin();

	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserName = strUserName;
	pReq->m_strPassword = strPassWord;
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();

	this->sendMessage(handle, pByteArray);

	pByteArray = NULL;

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}

void CMessageManager::sendReqSynYahoo( qint32 handle, const QString& strSymbolUse)
{	
	CReqSynYahoo* pReq = NULL;
	QByteArray* pByteArray = NULL;
	pReq = new CReqSynYahoo();

	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strSymbolUse = strSymbolUse;//"000001.SZ";
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();

	this->sendMessage(handle, pByteArray);

	pByteArray = NULL;

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}

void CMessageManager::sendReqDownLoadStock(qint32 handle)
{
	CReqDownLoadStock* pReq = NULL;
	QByteArray* pByteArray = NULL;
	pReq = new CReqDownLoadStock();

	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();

	this->sendMessage(handle, pByteArray);

	pByteArray = NULL;

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}
