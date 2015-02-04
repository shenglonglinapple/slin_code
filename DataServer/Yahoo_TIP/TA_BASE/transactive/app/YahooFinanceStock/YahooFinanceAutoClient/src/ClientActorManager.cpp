#include "ClientActorManager.h"
#include "ClientActorParam.h"
#include "ClientWorker.h"
#include "Log4cppLogger.h"


CClientActorManager* CClientActorManager::m_pInstance = 0;
QMutex CClientActorManager::m_mutexInstance;

CClientActorManager& CClientActorManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CClientActorManager();
	}
	return (*m_pInstance);
}

void CClientActorManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CClientActorManager::CClientActorManager(void)
{
	QMutexLocker lock(&m_mutex_MapClientActor);	

	m_nHandleAuto = -10000;//socket handle should not be -10000;
	m_MapClientActor.clear();
}

CClientActorManager::~CClientActorManager( void )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	

	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.begin();
	while (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->terminateAndWait();
		delete pClientActor;
		pClientActor = NULL;

		iterMap++;
	}//while
	m_MapClientActor.clear();

}

void CClientActorManager::createClient( const QString& strServerIP, quint16 nServerPort, const QString& strUserName, const QString& strPassWord )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	CClientWorker* pClientActor = NULL;
	CClientActorParam clientActorParam;
	qint32 nHanleTmp = 0;

	clientActorParam.setValue(strServerIP, nServerPort, strUserName, strPassWord);
	clientActorParam.setValue(m_nHandleAuto--);
	clientActorParam.logInfo(__FILE__, __LINE__);
	nHanleTmp = clientActorParam.getHandle();
	pClientActor = new CClientWorker(clientActorParam);
	
	//check and append
	if (m_MapClientActor.contains(nHanleTmp))
	{
		MYLOG4CPP_ERROR<<"error! find same Client";
		delete pClientActor;
		pClientActor = NULL;
	}
	else
	{
		pClientActor->start();
		m_MapClientActor.insert(nHanleTmp, pClientActor);
		pClientActor = NULL;
	}
}

void CClientActorManager::resetHanleValue( const CClientWorker* pActor,  qint32 nHandle)
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;
	bool bFindAndReset = true;
	MYLOG4CPP_DEBUG<<"resetHanleValue pActor=0x"<<pActor<<" "<<"nHandle="<<nHandle;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		MYLOG4CPP_WARNING<<"resetHanleValue pActor=0x"<<pActor<<" "<<"nHandle="<<nHandle
			<<" "<<"Map have same nHandle, check pActor and delete old one";
		pClientActor = iterMap.value();
		if (pClientActor == pActor)
		{
			MYLOG4CPP_WARNING<<"resetHanleValue pActor=0x"<<pActor<<" "<<"nHandle="<<nHandle
				<<" "<<"Map have same nHandle, pActor is same too, do nothing, usr don't need reset";
			bFindAndReset = false;
		}
		else
		{
			MYLOG4CPP_WARNING<<"resetHanleValue pActor=0x"<<pActor<<" "<<"nHandle="<<nHandle
				<<" "<<"Map have same nHandle, pActor is not same, delete old one";
			pClientActor->terminateAndWait();
			delete pClientActor;
			pClientActor = NULL;
			m_MapClientActor.erase(iterMap);
			m_MapClientActor.insert(nHandle, (CClientWorker*)pActor);
			bFindAndReset = false;
		}
	}//if (iterMap != m_MapClientActor.end())

	//find and reset
	if (bFindAndReset)
	{
		iterMap = m_MapClientActor.begin();
		while (iterMap != m_MapClientActor.end())
		{
			pClientActor = iterMap.value();
			if (pClientActor == pActor)
			{
				iterMap.value() = NULL;
				m_MapClientActor.erase(iterMap);
				m_MapClientActor.insert(nHandle, pClientActor);
				break;
			}
			iterMap++;
		}//while
	}//	if (bFindAndReset)


}//resetHanleValue



void CClientActorManager::sendMessage(qint32 nHandle, QByteArray* pMessage)
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;
	MYLOG4CPP_DEBUG<<"CClientActorManager sendMessage"
		<<" "<<"nHandle="<<nHandle
		<<" "<<"pMessage=0x"<<pMessage;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->sendMessage(nHandle, pMessage);
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

