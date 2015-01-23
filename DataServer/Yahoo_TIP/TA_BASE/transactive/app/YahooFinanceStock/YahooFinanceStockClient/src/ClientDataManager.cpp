#include "ClientDataManager.h"

#include <QtCore/QStringList>
#include <QtCore/QByteArray>

#include "ProjectCommonDef.h"

#include "ClientDBManager.h"
#include "ClientWorkerManager.h"
#include "StockDataManager.h"
#include "StockMinTimeMaxTime.h"
#include "UserTradeInfo.h"

#include "TcpComProtocol.h"
#include "ReqLogin.h"
#include "ReqLogout.h"
#include "ReqSynYahoo.h"
#include "ReqDownLoadStock.h"
#include "ReqStockMinTimeMaxTime.h"
#include "ReqStockHistoryData.h"
#include "ReqTrade.h"
#include "ReqHistoryTrade.h"

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
	m_strUserID.clear();
	m_strUserName.clear();
	m_strPassWord.clear();
	m_nHandle = 0;
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();

	CConfigInfo::getInstance();
	CClientWorkerManager::getInstance();
	CStockDataManager::getInstance();
	CClientDBManager::getInstance();

	CSignalSlotManager::getInstance().set_Signal_ShownMessage(this);
	CSignalSlotManager::getInstance().set_Signal_DataChange_StockHistoryData(this);
	CSignalSlotManager::getInstance().set_Signal_DataChange_StockMinTimeMaxTime(this);
	CSignalSlotManager::getInstance().set_Signal_DataChange_UserTrade(this);


}

CClientDataManager::~CClientDataManager(void)
{
	CStockDataManager::removeInstance();
	CClientWorkerManager::removeInstance();
	CConfigInfo::removeInstance();
	CClientDBManager::removeInstance();

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

	send_req_ReqLogin(nHandle, m_strUserName, m_strPassWord);
}

void CClientDataManager::loginedToServer(qint32 nHandle, const QString& strUserID)
{
	m_strUserID = strUserID;
	MYLOG4CPP_DEBUG<<"CClientDataManager loginedToServer"
		<<" "<<"nHandle="<<nHandle
		<<" "<<"m_strServerIP="<<m_strServerIP
		<<" "<<"m_nServerPort="<<m_nServerPort
		<<" "<<"m_strUserID="<<m_strUserID
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassWord="<<m_strPassWord;

	QString strShowMsg = "logined To Server ";
	strShowMsg=strShowMsg + QString("nHandle=%1 strUserName=%2 strPassWord=%3 strUserID=%4")
		.arg(nHandle).arg(m_strUserName).arg(m_strPassWord).arg(m_strUserID);

	CSignalSlotManager::getInstance().emit_ShownMessage(strShowMsg);
	send_req_ReqDownLoadStock(nHandle);
}

void CClientDataManager::downLoadStockFromServer( qint32 nHandle )
{
	QString strSymbolUse;
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
		strSymbolUse = (*iterLst);
		//TODO.forTest
		//send_req_ReqSynYahoo(nHandle, strSymbolUse);
		send_req_ReqStockMinTimeMaxTime(nHandle, strSymbolUse);
		iterLst++;
	}//while

	//TODO.forTest
	send_req_ReqHistoryTrade(strSymbolUse, CTcpComProtocol::ETradeType_Buy);


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


void CClientDataManager::send_req_ReqLogin(qint32 nHandle, const QString& strUserName, const QString& strPassWord)
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

void CClientDataManager::send_req_NewOrder( const CUserTradeInfo* pData )
{
	QByteArray* pByteArray = NULL;
	CReqTrade* pReq = NULL;
	pReq = new CReqTrade();
	pReq->setValue(pData);
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserID = m_strUserID;//set User ID
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
void CClientDataManager::send_req_ReqHistoryTrade( const QString& strSymbolUse, CTcpComProtocol::ETradeType nTradeType )
{
	QByteArray* pByteArray = NULL;
	CReqHistoryTrade* pReq = NULL;
	pReq = new CReqHistoryTrade();
	pReq->m_strReqUUID = CTcpComProtocol::getUUID();
	pReq->m_strACKUUID = "NULL";
	pReq->m_strUserID = m_strUserID;//set User ID
	pReq->m_nTradeType = (CTcpComProtocol::ETradeType)nTradeType;
	pReq->m_strSymbolUse = strSymbolUse;
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
//////////////////////////////////////////////////////////////////////////
void CClientDataManager::resetDataHistory( const QString& strSymbolUse, const QList<CHistoryData*>& lstData )
{
	CClientDBManager::getInstance().resetDataHistory(strSymbolUse, lstData);
	CSignalSlotManager::getInstance().emit_DataChange_StockHistoryData();
}


void CClientDataManager::resetDataSymbolMinMaxTime(const CStockMinTimeMaxTime* pData )
{
	CStockMinTimeMaxTime* pFind = NULL;

	CClientDBManager::getInstance().selectSymbolMinMaxTime(pData->m_strSymbolUse, &pFind);

	if (NULL == pFind)
	{
		CClientDBManager::getInstance().insertSymbolMinMaxTime(pData);
	}
	else
	{
		CClientDBManager::getInstance().updateSymbolMinMaxTime(pData);

		delete pFind;
		pFind = NULL;
	}

	CSignalSlotManager::getInstance().emit_DataChange_StockMinTimeMaxTime();
}


void CClientDataManager::insertUserTradeInfo(const CUserTradeInfo* pData)
{
	CClientDBManager::getInstance().insertUserTradeInfo(pData);
	CSignalSlotManager::getInstance().emit_DataChange_UserTrade();
}




