#include "ClientDataManager.h"

#include <QtCore/QStringList>
#include <QtCore/QByteArray>

#include "ProjectCommonDef.h"

#include "ClientWorkerManager.h"
#include "StockDataManager.h"
#include "DataStockMinTimeMaxTime.h"
#include "DataStockHistoryData.h"

#include "TcpComProtocol.h"
#include "ReqLogin.h"
#include "ReqLogout.h"
#include "ReqSynYahoo.h"
#include "ReqDownLoadStock.h"
#include "ReqStockMinTimeMaxTime.h"
#include "ReqStockHistoryData.h"

#include "AckLogin.h"
#include "AckLogout.h"
#include "AckSynYahoo.h"
#include "AckDownLoadStock.h"
#include "AckStockMinTimeMaxTime.h"
#include "AckStockHistoryData.h"

#include "SignalSlotManager.h"
#include "QtTimeHelper.h"
#include "ConfigInfo.h"
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
	m_strServerIP.clear();
	m_nServerPort = 0;
	m_strUserName.clear();
	m_strPassWord.clear();
	m_nHandle = 0;
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();

	CConfigInfo::getInstance();
	CClientWorkerManager::getInstance();
	CStockDataManager::getInstance();
	CDataStockMinTimeMaxTime::getInstance();
	CDataStockHistoryData::getInstance();

	CSignalSlotManager::getInstance().set_Signal_ShownMessage(this);
}

CClientDataManager::~CClientDataManager(void)
{
	CDataStockHistoryData::removeInstance();
	CDataStockMinTimeMaxTime::removeInstance();
	CStockDataManager::removeInstance();
	CClientWorkerManager::removeInstance();
	CConfigInfo::removeInstance();

	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}
}

void CClientDataManager::connectedToServer( qint32 nHandle, 
QString strServerIP, quint16 nServerPort, 
QString strUserName, QString strPassWord )
{
	m_nHandle = nHandle;
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
		//TODO.forTest
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


void CClientDataManager::send_req_ReqStockHistoryData(const QString& strSymbolUse, const QString& strTimeFrom, const QString& strTimeTo)
{
	CReqStockHistoryData* pReq = NULL;
	QByteArray* pByteArray = NULL;
	//quint32 nCurrentTime;
	//quint32 nFromTime;
	//nCurrentTime = m_pQtTimeHelper->getCurrentTime();
	//nFromTime = nCurrentTime - TimeBaseSecond::TIME_BASE_S_1YEAR;

	pReq = new CReqStockHistoryData();

	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strSymbolUse = strSymbolUse;//"000001.SZ";
	pReq->m_strTimeFrom = strTimeFrom;
	pReq->m_strTimeTo = strTimeTo;
	//pReq->m_strTimeFrom = m_pQtTimeHelper->getStringValue(nFromTime);
	//pReq->m_strTimeTo = m_pQtTimeHelper->getStringValue(nCurrentTime);
	pReq->logInfo(__FILE__, __LINE__);
	pByteArray = pReq->getMessage();

	CClientWorkerManager::getInstance().sendMessage(m_nHandle, pByteArray);

	pByteArray = NULL;

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}

}
