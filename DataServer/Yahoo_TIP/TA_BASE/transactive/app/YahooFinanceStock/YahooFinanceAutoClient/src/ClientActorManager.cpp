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

	clientActorParam.setServerValue(strServerIP, nServerPort);
	clientActorParam.setUserValue(strUserName, strPassWord);
	clientActorParam.setHandleValue(m_nHandleAuto--);
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

void CClientActorManager::send_req_ReqCreateUser(qint32 nHandle)
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->send_req_ReqCreateUser();
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager send_req_ReqCreateUser"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}

void CClientActorManager::send_req_ReqLogin(qint32 nHandle)
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->send_req_ReqLogin();
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager send_req_ReqLogin"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}

void CClientActorManager::send_req_ReqDownLoadStock( qint32 nHandle )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->send_req_ReqDownLoadStock();
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager send_req_ReqDownLoadStock"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}
//////////////////////////////////////////////////////////////////////////
void CClientActorManager::resetAllStockInfo(qint32 nHandle, const QList<CStockInfo*>& lstData )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->resetAllStockInfo(lstData);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager resetSymbolUse"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}



void CClientActorManager::send_req_ReqStockMinTimeMaxTime( qint32 nHandle, const QString& strSymbolUse )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->send_req_ReqStockMinTimeMaxTime(strSymbolUse);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager send_req_ReqStockMinTimeMaxTime"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}

void CClientActorManager::send_req_ReqHistoryTrade(
	qint32 nHandle, const QString& strSymbolUse, CTcpComProtocol::ETradeType nTradeType )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->send_req_ReqHistoryTrade(strSymbolUse, nTradeType);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager send_req_ReqHistoryTrade"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}

void CClientActorManager::send_req_ReqUserAccount( qint32 nHandle, const QString& strTime )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->send_req_ReqUserAccount(strTime);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager send_req_ReqUserAccount"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}


void CClientActorManager::send_req_ReqUserHoldAccount( qint32 nHandle, const QString& strSymbolUse )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->send_req_ReqUserHoldAccount(strSymbolUse);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager send_req_ReqUserHoldAccount"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}
void CClientActorManager::send_req_ReqSynYahoo( qint32 nHandle, const QString& strSymbolUse )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->send_req_ReqSynYahoo(strSymbolUse);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager send_req_ReqSynYahoo"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}
//////////////////////////////////////////////////////////////////////////

void CClientActorManager::resetDataSymbolMinMaxTime( qint32 nHandle, const CStockMinTimeMaxTime* pData )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->resetDataSymbolMinMaxTime(pData);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager resetDataSymbolMinMaxTime"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}

void CClientActorManager::resetHistoryData( qint32 nHandle, const QString& strSymbolUse, const QList<CHistoryData*>& lstData )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->resetHistoryData(strSymbolUse, lstData);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager resetHistoryData"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}

void CClientActorManager::insertUserTradeInfo( qint32 nHandle, const QList<CUserTradeInfo*>& LstData )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->insertUserTradeInfo(LstData);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager insertUserTradeInfo"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}

void CClientActorManager::insertUserTradeInfo( qint32 nHandle, const CUserTradeInfo* pData )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->insertUserTradeInfo(pData);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager insertUserTradeInfo"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}
void CClientActorManager::insertUserAccount(qint32 nHandle, const CUserAccount* pData )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->insertUserAccount(pData);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager insertUserAccount"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}
void CClientActorManager::resetUserAccount( qint32 nHandle, const CUserAccount* pData )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->resetUserAccount(pData);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager resetUserAccount"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}

void CClientActorManager::resetUserHoldAccount( qint32 nHandle, const QList<CUserHoldAccount*>& lstData )
{
	QMutexLocker lock(&m_mutex_MapClientActor);	
	QMap<qint32, CClientWorker*>::iterator iterMap;
	CClientWorker* pClientActor = NULL;

	iterMap = m_MapClientActor.find(nHandle);
	if (iterMap != m_MapClientActor.end())
	{
		pClientActor = iterMap.value();
		pClientActor->resetUserHoldAccount(lstData);
	}
	else
	{
		MYLOG4CPP_ERROR<<"CClientActorManager resetUserHoldAccount"
			<<" "<<"nHandle="<<nHandle
			<<" "<<"not find hanle";
	}
}



