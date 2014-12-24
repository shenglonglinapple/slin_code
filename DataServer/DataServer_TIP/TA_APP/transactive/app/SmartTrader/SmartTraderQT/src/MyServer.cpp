#include "MyServer.h"

#include "DataWorker.h"
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
	m_pDataWorker = NULL;
	m_pDataWorker = new CDataWorker();
	m_pDataWorker->setDataProcessHandle(NULL);
	m_pDataWorker->start();

	m_pDataRealTimeWorker = NULL;
	m_pDataRealTimeWorker = new CDataRealTimeWorker();
	m_pDataRealTimeWorker->setDataProcessHandle(NULL);
	m_pDataRealTimeWorker->start();

	m_pDataProcessOrderWorker = NULL;
	m_pDataProcessOrderWorker = new CDataProcessOrderWorker();
	m_pDataProcessOrderWorker->setDataProcessHandle(NULL);
	m_pDataProcessOrderWorker->start();
}

CMyServer::~CMyServer( void )
{
	if (NULL != m_pDataProcessOrderWorker)
	{
		m_pDataProcessOrderWorker->setDataProcessHandle(NULL);
		m_pDataProcessOrderWorker->terminateAndWait();
		delete m_pDataProcessOrderWorker;
		m_pDataProcessOrderWorker = NULL;
	}

	if (NULL != m_pDataRealTimeWorker)
	{
		m_pDataRealTimeWorker->setDataProcessHandle(NULL);
		m_pDataRealTimeWorker->terminateAndWait();
		delete m_pDataRealTimeWorker;
		m_pDataRealTimeWorker = NULL;
	}

	if (NULL != m_pDataWorker)
	{
		m_pDataWorker->setDataProcessHandle(NULL);
		m_pDataWorker->terminateAndWait();
		delete m_pDataWorker;
		m_pDataWorker = NULL;
	}
}

void CMyServer::send_req( CReqData* pReqData )
{
	m_pDataWorker->append_req(pReqData);
}

void CMyServer::setHandle( const CMyTradeClient* pHandleRef )
{
	m_pDataWorker->setDataProcessHandle(pHandleRef);
	m_pDataRealTimeWorker->setDataProcessHandle(pHandleRef);
	m_pDataProcessOrderWorker->setDataProcessHandle(pHandleRef);

}

