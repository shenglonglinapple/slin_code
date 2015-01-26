#include "ClientWorkerManager.h"
#include "DistributeTaskWorker.h"
#include "ClientLoginParam.h"

#include "Log4cppLogger.h"


CClientWorkerManager* CClientWorkerManager::m_pInstance = 0;
QMutex CClientWorkerManager::m_mutexInstance;

CClientWorkerManager& CClientWorkerManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CClientWorkerManager();
	}
	return (*m_pInstance);
}

void CClientWorkerManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CClientWorkerManager::CClientWorkerManager(void)
{

}

CClientWorkerManager::~CClientWorkerManager( void )
{

}

void CClientWorkerManager::createClient( const CClientLoginParam* pParam )
{
	QMutexLocker lock(&m_mutex_MapClient);	

	MYLOG4CPP_DEBUG<<"createClient pParam=0x"<<pParam;

	CDistributeTaskWorker* pActor = NULL;
	qint32 nHandle = 0;
	nHandle = pParam->m_nHandle;
	pActor = new CDistributeTaskWorker(
		pParam->m_strServerIP,
		pParam->m_nServerPort);
	pActor->start();

	m_MapClient.insert(nHandle, pActor);
	pActor = NULL;
}

void CClientWorkerManager::resetHanleValue( const CDistributeTaskWorker* pWorker,  qint32 nHandle)
{
	QMutexLocker lock(&m_mutex_MapClient);	
	QMap<qint32, CDistributeTaskWorker*>::iterator iterMapl;
	CDistributeTaskWorker* pActorTemp = NULL;
	MYLOG4CPP_DEBUG<<"resetHanleValue pWorker=0x"<<pWorker<<" "<<"nHandle="<<nHandle;

	iterMapl = m_MapClient.find(nHandle);
	if (iterMapl != m_MapClient.end())
	{
		MYLOG4CPP_WARNING<<"resetHanleValue pWorker=0x"<<pWorker
			<<" "<<"nHandle="<<nHandle
			<<" "<<"is exist in map";
		pActorTemp = iterMapl.value();
	}
	else
	{
		iterMapl = m_MapClient.begin();
		while (iterMapl != m_MapClient.end())
		{
			pActorTemp = iterMapl.value();
			if (pActorTemp == pWorker)
			{
				iterMapl.value() = NULL;
				m_MapClient.erase(iterMapl);
				m_MapClient.insert(nHandle, pActorTemp);
				break;
			}

			iterMapl++;
		}//while
	}
}



void CClientWorkerManager::sendMessage(qint32 nHandle, QByteArray* pMessage)
{
	QMutexLocker lock(&m_mutex_MapClient);	
	QMap<qint32, CDistributeTaskWorker*>::iterator iterMapl;
	CDistributeTaskWorker* pActorTemp = NULL;
	MYLOG4CPP_DEBUG<<"CClientWorkerManager sendMessage"
		<<" "<<"nHandle="<<nHandle
		<<" "<<"pMessage=0x"<<pMessage;

	iterMapl = m_MapClient.find(nHandle);
	if (iterMapl != m_MapClient.end())
	{
		pActorTemp = iterMapl.value();
		pActorTemp->sendMessage(nHandle, pMessage);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientWorkerManager sendMessage"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"pMessage=0x"<<pMessage
			<<" "<<"not find hanle";

		if (NULL != pMessage)
		{
			delete pMessage;
			pMessage = NULL;
		}
	}
}//sendMessage

