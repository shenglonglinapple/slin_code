#include "ServerComManager.h"

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "ServerComWorker.h"

#include "Log4cppLogger.h"



CServerComManager::CServerComManager( QObject* parent /*= 0*/ )
{
	QMutexLocker lock(&m_mutex_MapServerComWorker);	
	m_MapServerComWorker.clear();

}

CServerComManager::~CServerComManager()
{
	QMutexLocker lock(&m_mutex_MapServerComWorker);	
	QMap<qint32, CServerComWorker*>::iterator iterMap;
	//qint32 nSocketHandle = 0;
	CServerComWorker* pData = NULL;

	iterMap = m_MapServerComWorker.begin();

	while (iterMap != m_MapServerComWorker.end())
	{
		//nSocketHandle = iterMap.key();
		pData = iterMap.value();

		pData->terminateAndWait();
		delete pData;
		pData = NULL;

		iterMap++;
	}//while

	m_MapServerComWorker.clear();
}

void CServerComManager::incomingConnection( qint32 handle )
{
	QMutexLocker lock(&m_mutex_MapServerComWorker);	

	qint32 nSocketHandle = 0;
	CServerComWorker* pComWorker = NULL;

	nSocketHandle = handle;
	pComWorker = new CServerComWorker(nSocketHandle, this);
	QObject::connect(pComWorker, SIGNAL(signalRecvMessage(qint32, QByteArray*)), this, SLOT(slotRecvMessage(qint32, QByteArray*)), Qt::AutoConnection);
	QObject::connect(pComWorker, SIGNAL(signalDisconnected(qint32)), this, SLOT(slotDisconnected(qint32)), Qt::AutoConnection);

	
	pComWorker->start();
	m_MapServerComWorker.insert(nSocketHandle, pComWorker);
	pComWorker = NULL;

}

void CServerComManager::slotRecvMessage( qint32 handle, QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CServerActorManager"
		<<" "<<"fun:"<<" "<<"slotRecvMessage"
		<<" "<<"emit:"<<" "<<"signalRecvMessage"
		<<" "<<"param:"<<" "<<"handle="<<handle
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;

	emit signalRecvMessage(handle, pMessage);
}

void CServerComManager::slotDisconnected( qint32 handle )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CServerActorManager"
		<<" "<<"fun:"<<" "<<"slotDisconnected"
		<<" "<<"param:"<<" "<<"handle="<<handle;

	QMutexLocker lock(&m_mutex_MapServerComWorker);	
	QMap<qint32, CServerComWorker*>::iterator iterMap;
	CServerComWorker* pData = NULL;
	iterMap = m_MapServerComWorker.find(handle);
	if (iterMap != m_MapServerComWorker.end())
	{
		//nSocketHandle = iterMap.key();
		pData = iterMap.value();

		pData->terminateAndWait();
		delete pData;
		pData = NULL;
		m_MapServerComWorker.erase(iterMap);
	}//

}

void CServerComManager::slotSendMessage( qint32 handle, QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CServerActorManager"
		<<" "<<"fun:"<<" "<<"slotSendMessage"
		<<" "<<"emit:"<<" "<<"signalSendMessage"
		<<" "<<"param:"<<" "<<"handle="<<handle
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;

	QMutexLocker lock(&m_mutex_MapServerComWorker);	
	QMap<qint32, CServerComWorker*>::iterator iterMap;
	CServerComWorker* pData = NULL;
	iterMap = m_MapServerComWorker.find(handle);
	if (iterMap != m_MapServerComWorker.end())
	{
		//nSocketHandle = iterMap.key();
		pData = iterMap.value();
		pData->sendMessage(handle, pMessage);
	}//
	else
	{
		MYLOG4CPP_ERROR<<" "<<"CServerActorManager::slotSendMessage not find handle="<<handle;

		delete pMessage;
		pMessage = NULL;
	}

}
