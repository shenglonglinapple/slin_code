#include "ServerManager.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "StockDataManager.h"
#include "TcpServerWorker.h"
#include "ConfigInfo.h"
#include "ProjectSQLManager.h"
#include "UserInfo.h"
#include "UserAccount.h"
#include "UserTradeInfo.h"
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
	CProjectSQLManager::getInstance();
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
	CProjectSQLManager::removeInstance();

}

void CServerManager::createServer()
{
	quint16 nListenPort = 0;
	nListenPort = CConfigInfo::getInstance().getServerPort();
	MYLOG4CPP_DEBUG<<"createServer nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);	
	CTcpServerWorker* pData = NULL;
	pData = new CTcpServerWorker(nListenPort, NULL);
	pData->start();
	m_MapTcpServerWorker.insert(nListenPort, pData);
	pData = NULL;

}
void CServerManager::destoryServer()
{
	quint16 nListenPort = 0;
	nListenPort = CConfigInfo::getInstance().getServerPort();
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


qint32 CServerManager::selectUserInfo(quint16 nListenPort,const QString & strUSERNAME, const QString& strPASSWORD, CUserInfo** ppData)
{
	qint32 nFunRes = 0;
	MYLOG4CPP_DEBUG<<"CServerManager getUserInfo nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pData = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);

	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pData = iterMap.value();
		nFunRes = pData->selectUserInfo(nListenPort, strUSERNAME, strPASSWORD, ppData);
	}//if
	else
	{
		nFunRes = -1;
	}

	return nFunRes;
}


qint32 CServerManager::updateUserInfo(quint16 nListenPort, const CUserInfo* pData)
{
	qint32 nFunRes = 0;
	MYLOG4CPP_DEBUG<<"CServerManager updateUserInfo nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pWorker = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);

	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pWorker = iterMap.value();
		nFunRes = pWorker->updateUserInfo(nListenPort, pData);
	}//if
	else
	{
		nFunRes = -1;
	}

	return nFunRes;
}


qint32 CServerManager::createUserInfo(quint16 nListenPort, const CUserInfo* pData)
{
	qint32 nFunRes = 0;
	MYLOG4CPP_DEBUG<<"CServerManager insertUserInfo nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pWorker = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);

	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pWorker = iterMap.value();
		nFunRes = pWorker->createUserInfo(nListenPort, pData);
	}//if
	else
	{
		nFunRes = -1;
	}

	return nFunRes;
}

qint32 CServerManager::processUserTradeInfo( quint16 nListenPort, const CUserTradeInfo* pData )
{
	qint32 nFunRes = 0;
	MYLOG4CPP_DEBUG<<"CServerManager processUserTradeInfo nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pWorker = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);

	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pWorker = iterMap.value();
		nFunRes = pWorker->processUserTradeInfo(nListenPort, pData);
	}//if
	else
	{
		nFunRes = -1;
	}

	return nFunRes;
}


void CServerManager::sendMessage( quint16 nListenPort, qint32 handle, QByteArray* pMessage )
{
	qint32 nFunRes = 0;
	MYLOG4CPP_DEBUG<<"CServerManager sendMessage nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pWorker = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);
	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pWorker = iterMap.value();
		pWorker->sendMessage(handle, pMessage);
	}//if
	else
	{
		nFunRes = -1;
	}

}



qint32 CServerManager::selectUserTradeInfo( quint16 nListenPort, QList<CUserTradeInfo*>& lstData, const QString& strUserID, const QString& strSymbolUse )
{
	qint32 nFunRes = 0;
	MYLOG4CPP_DEBUG<<"CServerManager selectUserTradeInfo nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pData = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);

	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pData = iterMap.value();
		nFunRes = pData->selectUserTradeInfo(nListenPort, lstData, strUserID, strSymbolUse);
	}//if
	else
	{
		nFunRes = -1;
	}

	return nFunRes;
}
qint32 CServerManager::selectUserHoldAccount( quint16 nListenPort, QList<CUserHoldAccount*>& lstData, const QString& strUserID, const QString& strSymbolUse )
{
	qint32 nFunRes = 0;
	MYLOG4CPP_DEBUG<<"CServerManager selectUserHoldAccount nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pData = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);

	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pData = iterMap.value();
		nFunRes = pData->selectUserHoldAccount(nListenPort, lstData, strUserID, strSymbolUse);
	}//if
	else
	{
		nFunRes = -1;
	}

	return nFunRes;
}
qint32 CServerManager::createUserAmount( quint16 nListenPort, const CUserAccount* pData )
{
	qint32 nFunRes = 0;
	MYLOG4CPP_DEBUG<<"CServerManager createUserAmount nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pWorker = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);

	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pWorker = iterMap.value();
		nFunRes = pWorker->createUserAmount(nListenPort, pData);
	}//if
	else
	{
		nFunRes = -1;
	}

	return nFunRes;
}

qint32 CServerManager::processUserAccount( quint16 nListenPort, const QString& strUserID, const QString& strTime, CUserAccount** ppData)
{
	qint32 nFunRes = 0;
	MYLOG4CPP_DEBUG<<"CServerManager processUserAccount nListenPort="<<nListenPort;

	QMutexLocker lock(&m_mutex_MapTcpServerWorker);
	QMap<quint16, CTcpServerWorker*>::iterator iterMap;
	CTcpServerWorker* pWorker = NULL;

	iterMap = m_MapTcpServerWorker.find(nListenPort);

	if (iterMap != m_MapTcpServerWorker.end())
	{
		//nListenPort = iterMap.key();
		pWorker = iterMap.value();
		nFunRes = pWorker->processUserAccount(nListenPort, strUserID, strTime, ppData);
	}//if
	else
	{
		nFunRes = -1;
	}

	return nFunRes;
}


