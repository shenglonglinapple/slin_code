#include "MyServer.h"

#include "ServerComManager.h"
#include "ServerProcessRequestWorker.h"
#include "DataRealTimeWorker.h"
#include "DataProcessOrderWorker.h"

#include "Log4cppLogger.h"



CMyServer* CMyServer::m_pInstance = 0;
QMutex CMyServer::m_mutexInstance;

CMyServer& CMyServer::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CMyServer();
	}
	return (*m_pInstance);
}

void CMyServer::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;
}
CMyServer::CMyServer()
{
	CServerComManager::getInstance();
	m_pServerProcessRequestWorker = NULL;
	m_pServerProcessRequestWorker = new CServerProcessRequestWorker();
	m_pServerProcessRequestWorker->start();

	m_pDataRealTimeWorker = NULL;
	m_pDataRealTimeWorker = new CDataRealTimeWorker();
	m_pDataRealTimeWorker->start();

	m_pDataProcessOrderWorker = NULL;
	m_pDataProcessOrderWorker = new CDataProcessOrderWorker();
	m_pDataProcessOrderWorker->start();
}

CMyServer::~CMyServer( void )
{
	if (NULL != m_pDataProcessOrderWorker)
	{
		m_pDataProcessOrderWorker->terminateAndWait();
		delete m_pDataProcessOrderWorker;
		m_pDataProcessOrderWorker = NULL;
	}

	if (NULL != m_pDataRealTimeWorker)
	{
		m_pDataRealTimeWorker->terminateAndWait();
		delete m_pDataRealTimeWorker;
		m_pDataRealTimeWorker = NULL;
	}

	if (NULL != m_pServerProcessRequestWorker)
	{
		m_pServerProcessRequestWorker->terminateAndWait();
		delete m_pServerProcessRequestWorker;
		m_pServerProcessRequestWorker = NULL;
	}
	CServerComManager::removeInstance();

}

void CMyServer::recv_req( CReqData* pReqData )
{
	m_pServerProcessRequestWorker->append_req(pReqData);
}

void CMyServer::setHandle( const CMyTradeClient* pHandleRef )
{
	CServerComManager::getInstance().setDataProcessHandle(pHandleRef);

}

