#include "MessageProcesser.h"

#include <QtCore/QDataStream>
#include <QtCore/QList>

#include "TcpComProtocol.h"
#include "ReqLogin.h"
#include "ReqLogout.h"
#include "ReqSynYahoo.h"
#include "ReqDownLoadStock.h"
#include "ReqStockMinTimeMaxTime.h"
#include "ReqStockHistoryData.h"
#include "ReqCreateUser.h"
#include "ReqTrade.h"
#include "ReqHistoryTrade.h"
#include "ReqAccount.h"

#include "AckLogin.h"
#include "AckLogout.h"
#include "AckSynYahoo.h"
#include "AckDownLoadStock.h"
#include "AckStockMinTimeMaxTime.h"
#include "AckStockHistoryData.h"
#include "AckCreateUser.h"
#include "AckTrade.h"
#include "AckHistoryTrade.h"
#include "AckAccount.h"

#include "Log4cppLogger.h"

#include "ProjectEnvironment.h"
#include "YahooDataLoader.h"
#include "StockDataManager.h"
#include "ServerManager.h"
#include "StockMinTimeMaxTime.h"
#include "HistoryData.h"
#include "WorkTime.h"
#include "UserInfo.h"
#include "UserTradeInfo.h"
#include "UserHold.h"
#include "UserAccount.h"
#include "ConfigInfo.h"


CMessageProcesser::CMessageProcesser( qint32 nHanle )
{
	m_nHanle = 0;

	m_nHanle = nHanle;
}

CMessageProcesser::~CMessageProcesser()
{

}


//////////////////////////////////////////////////////////////////////////

void CMessageProcesser::processReq(const CReqLogin* pReq )
{
	CAckLogin* pAckLogin = NULL;
	QByteArray* pByteArray = NULL;
	CUserInfo* pGetUserInfo = NULL;
	quint16 nListenPort = 0;
	qint32 nFunRes = 0;
	pAckLogin = new CAckLogin();

	CTcpComProtocol::EDataTypeLoginResult nLoginResult = CTcpComProtocol::DataType_LoginResult_OK;
	nListenPort = CConfigInfo::getInstance().getServerPort();
	nFunRes = CServerManager::getInstance().selectUserInfo(nListenPort, pReq->m_strUserName, pReq->m_strPassword, &pGetUserInfo);
	if (NULL == pGetUserInfo)
	{
		nLoginResult = CTcpComProtocol::DataType_LoginResult_ERROR;
	}
	else
	{
		nLoginResult = CTcpComProtocol::DataType_LoginResult_OK;

		pGetUserInfo->resetLoginTime();
		pGetUserInfo->m_nLoginCount++;
		pGetUserInfo->m_nState = CUserInfo::UserState_ONLINE;
		nFunRes = CServerManager::getInstance().updateUserInfo(nListenPort, pGetUserInfo);

		pAckLogin->m_strUserID = pGetUserInfo->m_strUserID;
		pAckLogin->m_strUserName = pGetUserInfo->m_strUserName;
		pAckLogin->m_strPassword = pGetUserInfo->m_strPassWord;
		pAckLogin->m_strLastLoginTime = pGetUserInfo->m_strLastLoginTime;
		pAckLogin->m_nLoginCount = pGetUserInfo->m_nLoginCount;
		pAckLogin->m_nState = pGetUserInfo->m_nState;
	}

	pAckLogin->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAckLogin->m_nDataType = CTcpComProtocol::DataType_Login;
	pAckLogin->m_strACKUUID = CTcpComProtocol::getUUID();
	pAckLogin->m_strReqUUID = pReq->m_strReqUUID;
	pAckLogin->m_nLoginResult = nLoginResult;

	if (NULL != pGetUserInfo)
	{
		delete pGetUserInfo;
		pGetUserInfo = NULL;
	}

	pByteArray = pAckLogin->getMessage();
	pAckLogin->logInfo(__FILE__, __LINE__);
	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);

	pByteArray = NULL;
	if (NULL != pAckLogin)
	{
		delete pAckLogin;
		pAckLogin = NULL;
	}
	
}

void CMessageProcesser::processReq( const CReqLogout* pReq )
{
	CAckLogout* pAckLogout = NULL;
	QByteArray* pByteArray = NULL;

	pAckLogout = new CAckLogout();

	pAckLogout->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAckLogout->m_nDataType = CTcpComProtocol::DataType_LogOut;
	pAckLogout->m_strACKUUID = CTcpComProtocol::getUUID();
	pAckLogout->m_strReqUUID = pReq->m_strReqUUID;
	pAckLogout->m_strUserName = pReq->m_strUserName;
	pAckLogout->m_strPassword = pReq->m_strPassword;
	pAckLogout->m_nLogoutResult = CTcpComProtocol::DataType_LogoutResult_OK;

	pByteArray = pAckLogout->getMessage();
	pAckLogout->logInfo(__FILE__, __LINE__);

	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);


	pByteArray = NULL;
	if (NULL != pAckLogout)
	{
		delete pAckLogout;
		pAckLogout = NULL;
	}
}

void CMessageProcesser::processReq( const CReqSynYahoo* pReq )
{
	CAckSynYahoo* pAck = NULL;
	QByteArray* pByteArray = NULL;
	CYahooDataLoader* pYahooDataLoader = NULL;
	CTcpComProtocol::EDataTypeSynYahooResult nSynYahooResult = CTcpComProtocol::DataType_SynYahooResult_SynYahooStart;

	pYahooDataLoader = new CYahooDataLoader(pReq->m_strSymbolUse);

	pAck = new CAckSynYahoo();
	pAck->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAck->m_nDataType = CTcpComProtocol::DataType_SynYahoo;
	pAck->m_strReqUUID = pReq->m_strReqUUID;
	pAck->m_strACKUUID = CTcpComProtocol::getUUID();
	pAck->m_nResult = nSynYahooResult;
	pAck->logInfo(__FILE__, __LINE__);
	pByteArray = pAck->getMessage();
	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);
	pYahooDataLoader->synDataWithYahoo();

	while (1)
	{
		CProjectEnviroment::getInstance().qtWaitTime(300);
		nSynYahooResult = pYahooDataLoader->getState_SynDataWithYahoo();
		pAck->m_strACKUUID = CTcpComProtocol::getUUID();
		pAck->m_nResult = nSynYahooResult;
		pAck->logInfo(__FILE__, __LINE__);
		pByteArray = pAck->getMessage();
		CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);
		pByteArray = NULL;

		if (CTcpComProtocol::DataType_SynYahooResult_SynYahooFinished == nSynYahooResult
			|| CTcpComProtocol::DataType_SynYahooResult_ERROR == nSynYahooResult)
		{
			break;//while
		}
	}//while

	if (NULL != pYahooDataLoader)
	{
		delete pYahooDataLoader;
		pYahooDataLoader = NULL;
	}
	
	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}


}

void CMessageProcesser::processReq(const CReqDownLoadStock* pReq)
{
	CAckDownLoadStock* pAck = NULL;
	QByteArray* pByteArray = NULL;

	pAck = new CAckDownLoadStock();
	pAck->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAck->m_nDataType = CTcpComProtocol::DataType_DownLoadStock;
	pAck->m_strReqUUID = pReq->m_strReqUUID;
	pAck->m_strACKUUID = CTcpComProtocol::getUUID();
	CStockDataManager::getInstance().doWork_getStockSymbolUse(pAck->m_LstStock);
	pAck->m_nStockCount = pAck->m_LstStock.size();
	pAck->logInfo(__FILE__, __LINE__);
	pByteArray = pAck->getMessage();
	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);

	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}

}

void CMessageProcesser::processReq( const CReqStockMinTimeMaxTime* pReq )
{
	CAckStockMinTimeMaxTime* pAck = NULL;
	QByteArray* pByteArray = NULL;
	CStockMinTimeMaxTime* pValueGet = NULL;
	
	CStockDataManager::getInstance().doWork_getStockMinTimeMaxTime(pReq->m_strSymbolUse, &pValueGet);

	if (NULL == pValueGet)
	{
		//not get data
		MYLOG4CPP_ERROR<<"_ProcessReq CReqStockMinTimeMaxTime"
			<<" "<<"not get data for pReq->m_strSymbolUse="<<pReq->m_strSymbolUse;
		return;
	}
	else
	{

	}

	pAck = new CAckStockMinTimeMaxTime();
	pAck->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAck->m_nDataType = CTcpComProtocol::DataType_StockMinTimeMaxTime;
	pAck->m_strReqUUID = pReq->m_strReqUUID;
	pAck->m_strACKUUID = CTcpComProtocol::getUUID();
	pAck->m_strSymbolUse = pValueGet->m_strSymbolUse;
	pAck->m_strMinTime = pValueGet->m_strMinTime;
	pAck->m_strMaxTime = pValueGet->m_strMaxTime;
	pAck->m_nCount = pValueGet->m_nCount;

	if (NULL == pValueGet)
	{
		delete pValueGet;
		pValueGet = NULL;
	}

	pAck->logInfo(__FILE__, __LINE__);
	pByteArray = pAck->getMessage();
	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);

	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}

}

void CMessageProcesser::processReq( const CReqStockHistoryData* pReq )
{
	CAckStockHistoryData* pAck = NULL;
	QByteArray* pByteArray = NULL;
	QList<CHistoryData*> lstData;
	
	CStockDataManager::getInstance().doWork_HistoryData(pReq->m_strSymbolUse, pReq->m_strTimeFrom, pReq->m_strTimeTo, lstData);

	pAck = new CAckStockHistoryData();
	pAck->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAck->m_nDataType = CTcpComProtocol::DataType_HistoryData;
	pAck->m_strReqUUID = pReq->m_strReqUUID;
	pAck->m_strACKUUID = CTcpComProtocol::getUUID();
	pAck->m_strSymbolUse = pReq->m_strSymbolUse;
	pAck->m_nDataCount = lstData.size();
	pAck->m_LstHistoryData.append(lstData);
	lstData.clear();

	pAck->logInfo(__FILE__, __LINE__);
	pByteArray = pAck->getMessage();
	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);

	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageProcesser::processReq( const CReqCreateUser* pReq )
{
	CAckCreateUser* pAck = NULL;
	QByteArray* pByteArray = NULL;
	CUserInfo* pGetUserInfo = NULL;
	CUserAccount* pUserAmount = NULL;
	quint16 nListenPort = 0;
	qint32 nFunRes = 0;
	nListenPort = CConfigInfo::getInstance().getServerPort();
	nFunRes = CServerManager::getInstance().selectUserInfo(nListenPort, pReq->m_strUserName, pReq->m_strPassword, &pGetUserInfo);
	if (NULL == pGetUserInfo)
	{
		pGetUserInfo = new CUserInfo();
		pGetUserInfo->setUseID(pReq->m_strUserName, pReq->m_strPassword);
		nFunRes = CServerManager::getInstance().createUserInfo(nListenPort, pGetUserInfo);
		pGetUserInfo->resetLoginTime();
		pGetUserInfo->m_nLoginCount = 0;
		pGetUserInfo->m_nState = (qint32)CUserInfo::UserState_OFFLINE;
		nFunRes = CServerManager::getInstance().updateUserInfo(nListenPort, pGetUserInfo);

		{
			pUserAmount = new CUserAccount();
			pUserAmount->m_strUserID = pGetUserInfo->m_strUserID;
			nFunRes = CServerManager::getInstance().createUserAmount(nListenPort, pUserAmount);
			if (NULL != pUserAmount)
			{
				delete pUserAmount;
				pUserAmount = NULL;
			}
		}
	}//if

	pAck = new CAckCreateUser();
	pAck->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAck->m_nDataType = CTcpComProtocol::DataType_CreateUser;
	pAck->m_strACKUUID = CTcpComProtocol::getUUID();
	pAck->m_strReqUUID = pReq->m_strReqUUID;
	pAck->m_strUserName = pGetUserInfo->m_strUserName;
	pAck->m_strPassword = pGetUserInfo->m_strPassWord;

	if (NULL != pGetUserInfo)
	{
		delete pGetUserInfo;
		pGetUserInfo = NULL;
	}

	pByteArray = pAck->getMessage();
	pAck->logInfo(__FILE__, __LINE__);
	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);


	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageProcesser::processReq( const CReqTrade* pReq )
{
	CAckTrade* pAck = NULL;
	QByteArray* pByteArray = NULL;
	quint16 nListenPort = 0;
	qint32 nFunRes = 0;
	CUserTradeInfo* pUserTradeInfo = NULL;
	CUserHold* pUserHold = NULL;
	nListenPort = CConfigInfo::getInstance().getServerPort();
	pAck = new CAckTrade();
	pUserTradeInfo = new CUserTradeInfo();
	pUserTradeInfo->setValue(pReq->m_strUserID, pReq);
	nFunRes = CServerManager::getInstance().processUserTradeInfo(nListenPort, pUserTradeInfo);
	if (0 == nFunRes)
	{
		pAck->setValue(pReq, pUserTradeInfo);
	}
	//set ack
	if (NULL != pUserTradeInfo)
	{
		delete pUserTradeInfo;
		pUserTradeInfo = NULL;
	}

	pByteArray = pAck->getMessage();
	pAck->logInfo(__FILE__, __LINE__);
	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);

	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}



void CMessageProcesser::processReq( const CReqHistoryTrade* pReq )
{
	CAckHistoryTrade* pAck = NULL;
	QByteArray* pByteArray = NULL;
	quint16 nListenPort = 0;
	CUserTradeInfo* pUserTradeInfo = NULL;
	QList<CUserTradeInfo*> lstData;
	nListenPort = CConfigInfo::getInstance().getServerPort();

	pAck = new CAckHistoryTrade();
	CServerManager::getInstance().selectUserTradeInfo(nListenPort, lstData, pReq->m_strUserID, pReq->m_strSymbolUse);

	{
		pAck->m_strACKUUID = CTcpComProtocol::getUUID();
		pAck->m_strReqUUID = pReq->m_strReqUUID;
		pAck->m_strUserID = pReq->m_strUserID;
		pAck->m_nTradeType = pReq->m_nTradeType;
		pAck->m_strSymbolUse = pReq->m_strSymbolUse;
		pAck->m_nLstDataCount = lstData.size();
		pAck->m_LstData.append(lstData);
		lstData.clear();
	}

	pByteArray = pAck->getMessage();
	pAck->logInfo(__FILE__, __LINE__);
	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);

	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;//will delete QList
		pAck = NULL;
	}
}

void CMessageProcesser::processReq( const CReqAccount* pReq )
{
	CAckAccount* pAck = NULL;
	CUserAccount* pUserAmount = NULL;
	QByteArray* pByteArray = NULL;
	quint16 nListenPort = 0;
	qint32 nFunRes = 0;
	nListenPort = CConfigInfo::getInstance().getServerPort();
	pAck = new CAckAccount();
	nFunRes = CServerManager::getInstance().processUserAccount(nListenPort, pReq->m_strUserID, pReq->m_strTime, &pUserAmount);
	pAck->setValue(pUserAmount);
	pByteArray = pAck->getMessage();
	pAck->logInfo(__FILE__, __LINE__);
	CServerManager::getInstance().sendMessage(CConfigInfo::getInstance().getServerPort(), m_nHanle, pByteArray);
	pByteArray = NULL;
	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
void CMessageProcesser::processAck( const CAckLogin* pAck )
{
	return;
}

void CMessageProcesser::processAck( const CAckLogout* pAck )
{
	return;
}

void CMessageProcesser::processAck( const CAckSynYahoo* pAck )
{
	return;
}

void CMessageProcesser::processAck(const CAckDownLoadStock* pAck)
{
	return;
}

void CMessageProcesser::processAck( const CAckStockMinTimeMaxTime* pAck )
{
	return;
}

void CMessageProcesser::processAck( const CAckStockHistoryData* pAck )
{

}

void CMessageProcesser::processAck( const CAckCreateUser* pAck )
{

}

void CMessageProcesser::processAck( const CAckTrade* pAck )
{

}



void CMessageProcesser::processAck( const CAckHistoryTrade* pAck )
{

}

void CMessageProcesser::processAck( const CAckAccount* pAck )
{

}
