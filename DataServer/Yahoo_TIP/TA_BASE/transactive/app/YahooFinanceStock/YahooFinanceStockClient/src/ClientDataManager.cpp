#include "ClientDataManager.h"

#include <QtCore/QStringList>
#include <QtCore/QByteArray>

#include "ClientWorkerManager.h"
#include "StockDataManager.h"


#include "TcpComProtocol.h"
#include "ReqLogin.h"
#include "ReqLogout.h"
#include "ReqSynYahoo.h"
#include "ReqDownLoadStock.h"

#include "AckLogin.h"
#include "AckLogout.h"
#include "AckSynYahoo.h"
#include "AckDownLoadStock.h"


#include "Log4cppLogger.h"

CClientDataManager* CClientDataManager::m_pInstance = 0;
QMutex CClientDataManager::m_mutexInstance;

CClientDataManager& CClientDataManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CClientDataManager();
	}
	return (*m_pInstance);
}

void CClientDataManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CClientDataManager::CClientDataManager(void)
{
	CClientWorkerManager::getInstance();
	CStockDataManager::getInstance();

}

CClientDataManager::~CClientDataManager(void)
{
	CStockDataManager::removeInstance();
	CClientWorkerManager::removeInstance();

}

void CClientDataManager::connectedToServer( qint32 nHandle, QString strServerIP, quint16 nServerPort, QString strUserName, QString strPassWord )
{
	m_strServerIP = strServerIP;
	m_nServerPort = nServerPort;
	m_strUserName = strUserName;
	m_strPassWord = strPassWord;
	MYLOG4CPP_DEBUG<<"CClientDataManager connectedToServer"
		<<" "<<"nHandle="<<nHandle
		<<" "<<"m_strServerIP="<<m_strServerIP
		<<" "<<"m_nServerPort="<<m_nServerPort
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassWord="<<m_strPassWord;

	CReqLogin* pReq = NULL;
	QByteArray* pByteArray = NULL;
	pReq = new CReqLogin();

	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserName = m_strUserName;
	pReq->m_strPassword = m_strPassWord;
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();

	CClientWorkerManager::getInstance().sendMessage(nHandle, pByteArray);

	pByteArray = NULL;

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}

void CClientDataManager::loginedToServer( qint32 nHandle, QString strUserName, QString strPassWord )
{
	MYLOG4CPP_DEBUG<<"CClientDataManager loginedToServer"
		<<" "<<"nHandle="<<nHandle
		<<" "<<"m_strServerIP="<<m_strServerIP
		<<" "<<"m_nServerPort="<<m_nServerPort
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassWord="<<m_strPassWord;

	CReqDownLoadStock* pReq = NULL;
	QByteArray* pByteArray = NULL;
	pReq = new CReqDownLoadStock();

	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();

	CClientWorkerManager::getInstance().sendMessage(nHandle, pByteArray);

	pByteArray = NULL;

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}

}

void CClientDataManager::downLoadStockFromServer( qint32 nHandle )
{
	MYLOG4CPP_DEBUG<<"CClientDataManager downLoadStockFromServer"
		<<" "<<"nHandle="<<nHandle;
	QList<QString> lstSymbolUse;
	QList<QString>::iterator iterLst;
	CStockDataManager::getInstance().getAllStockData(lstSymbolUse);

	iterLst = lstSymbolUse.begin();
	while (iterLst != lstSymbolUse.end())
	{
		CReqSynYahoo* pReq = NULL;
		QByteArray* pByteArray = NULL;
		pReq = new CReqSynYahoo();

		pReq->m_strReqUUID = CTcpComProtocol::getUUID();
		pReq->m_strACKUUID = "NULL";
		pReq->m_strSymbolUse = (*iterLst);//"000001.SZ";
		pReq->logInfo(__FILE__, __LINE__);
		pByteArray = pReq->getMessage();

		CClientWorkerManager::getInstance().sendMessage(nHandle, pByteArray);

		pByteArray = NULL;

		if (NULL != pReq)
		{
			delete pReq;
			pReq = NULL;
		}

		iterLst++;
	}//while



}


