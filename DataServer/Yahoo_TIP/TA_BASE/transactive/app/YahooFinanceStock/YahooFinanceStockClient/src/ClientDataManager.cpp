#include "ClientDataManager.h"

#include <QtCore/QStringList>
#include <QtCore/QByteArray>

#include "ClientWorkerManager.h"
#include "StockDataManager.h"
#include "DataStockMinTimeMaxTime.h"

#include "TcpComProtocol.h"
#include "ReqLogin.h"
#include "ReqLogout.h"
#include "ReqSynYahoo.h"
#include "ReqDownLoadStock.h"
#include "ReqStockMinTimeMaxTime.h"

#include "AckLogin.h"
#include "AckLogout.h"
#include "AckSynYahoo.h"
#include "AckDownLoadStock.h"
#include "AckStockMinTimeMaxTime.h"

#include "SignalSlotManager.h"

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
	CDataStockMinTimeMaxTime::getInstance();

	CSignalSlotManager::getInstance().set_Signal_ShownMessage(this);
}

CClientDataManager::~CClientDataManager(void)
{
	CDataStockMinTimeMaxTime::removeInstance();
	CStockDataManager::removeInstance();
	CClientWorkerManager::removeInstance();

}

void CClientDataManager::connectedToServer( qint32 nHandle, 
QString strServerIP, quint16 nServerPort, 
QString strUserName, QString strPassWord )
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
	
	CSignalSlotManager::getInstance().emit_ShownMessage("connected To Server "+
		QString("nHandle=%1 strServerIP=%2 nServerPort=%3").arg(nHandle).arg(strServerIP).arg(nServerPort)
		);

	send_req_CReqLogin(nHandle, m_strUserName, m_strPassWord);
}

void CClientDataManager::loginedToServer( qint32 nHandle, QString strUserName, QString strPassWord )
{
	MYLOG4CPP_DEBUG<<"CClientDataManager loginedToServer"
		<<" "<<"nHandle="<<nHandle
		<<" "<<"m_strServerIP="<<m_strServerIP
		<<" "<<"m_nServerPort="<<m_nServerPort
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassWord="<<m_strPassWord;

	CSignalSlotManager::getInstance().emit_ShownMessage("logined To Server "+
		QString("nHandle=%1 strUserName=%2 strPassWord=%3").arg(nHandle).arg(strUserName).arg(strPassWord)
		);
	send_req_ReqDownLoadStock(nHandle);

}

void CClientDataManager::downLoadStockFromServer( qint32 nHandle )
{
	MYLOG4CPP_DEBUG<<"CClientDataManager downLoadStockFromServer"
		<<" "<<"nHandle="<<nHandle;

	CSignalSlotManager::getInstance().emit_ShownMessage("downLoad Stock From Server "+
		QString("nHandle=%1").arg(nHandle)
		);

	QList<QString> lstSymbolUse;
	QList<QString>::iterator iterLst;
	//TODO. for Test
	CStockDataManager::getInstance().getAllStockData(lstSymbolUse);

	iterLst = lstSymbolUse.begin();
	while (iterLst != lstSymbolUse.end())
	{
		//send_req_ReqSynYahoo(nHandle, (*iterLst));
		send_req_ReqStockMinTimeMaxTime(nHandle, (*iterLst));
		iterLst++;
	}//while



}

void CClientDataManager::send_req_ReqSynYahoo(qint32 nHandle, const QString& strSymbolUse)
{
	CReqSynYahoo* pReq = NULL;
	QByteArray* pByteArray = NULL;
	pReq = new CReqSynYahoo();

	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strSymbolUse = strSymbolUse;//"000001.SZ";
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




void CClientDataManager::send_req_ReqDownLoadStock(qint32 nHandle)
{
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


void CClientDataManager::send_req_CReqLogin(qint32 nHandle, const QString& strUserName, const QString& strPassWord)
{
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



void CClientDataManager::send_req_ReqStockMinTimeMaxTime(qint32 nHandle, const QString& strSymbolUse)
{
	CReqStockMinTimeMaxTime* pReq = NULL;
	QByteArray* pByteArray = NULL;
	pReq = new CReqStockMinTimeMaxTime();

	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strSymbolUse = strSymbolUse;//"000001.SZ";
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
