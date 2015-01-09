#include "ServerManager.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "StockDataManager.h"
#include "TcpServerWorker.h"
#include "ConfigInfo.h"
#include "Log4cppLogger.h"

CServerManager* CServerManager::m_pInstance = 0;
QMutex CServerManager::m_mutexInstance;

CServerManager& CServerManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CServerManager();
	}
	return (*m_pInstance);
}

void CServerManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CServerManager::CServerManager()
{
	QMutexLocker lock(&m_mutex_MapTcpServerWorker);	

	m_MapTcpServerWorker.clear();
	CStockDataManager::getInstance();
	CConfigInfo::getInstance();
}

CServerManager::~CServerManager()
{

	{
		QMutexLocker lock(&m_mutex_MapTcpServerWorker);	
		QMap<quint16, CTcpServerWorker*>::iterator iterMap;
		quint16 nListenPort = 0;
		CTcpServerWorker* pData = NULL;

		iterMap = m_MapTcpServerWorker.begin();

		while (iterMap != m_MapTcpServerWorker.end())
		{
			nListenPort = iterMap.key();
			pData = iterMap.value();

			pData->terminateAndWait();
			delete pData;
			pData = NULL;

			iterMap++;
		}//while
		m_MapTcpServerWorker.clear();
	}
	CStockDataManager::removeInstance();
	CConfigInfo::removeInstance();

}

void CServerManager::createServer( quint16 nListenPort )
{
	MYLOG4CPP_DEBUG<<"createServer nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);	
	CTcpServerWorker* pData = NULL;
	pData = new CTcpServerWorker(nListenPort, NULL);
	pData->start();
	m_MapTcpServerWorker.insert(nListenPort, pData);
	pData = NULL;

}
void CServerManager::destoryServer( quint16 nListenPort )
{
	MYLOG4CPP_DEBUG<<"destoryServer nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pData = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);

	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pData = iterMap.value();

		pData->terminateAndWait();
		delete pData;
		pData = NULL;

		m_MapTcpServerWorker.erase(iterMap);
	}//while

	
}