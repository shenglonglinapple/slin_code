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
#include "ReqHoldAccount.h"

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
#include "AckHoldAccount.h"

#include "ClientDataManager.h"
#include "StockDataManager.h"
#include "ClientDBManager.h"
#include "StockMinTimeMaxTime.h"
#include "HistoryData.h"
#include "WorkTime.h"
#include "UserTradeInfo.h"
#include "UserAccount.h"

#include "Log4cppLogger.h"

CMessageProcesser::CMessageProcesser(qint32 nHanle)
{
	m_nHanle = 0;

	m_nHanle = nHanle;
}

CMessageProcesser::~CMessageProcesser()
{

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void CMessageProcesser::processReq(const CReqLogin* pReq )
{
	return;	
}

void CMessageProcesser::processReq( const CReqLogout* pReq )
{
	return;
}

void CMessageProcesser::processReq( const CReqSynYahoo* pReq )
{
	return;
}

void CMessageProcesser::processReq(const CReqDownLoadStock* pReq)
{
	return;
}

void CMessageProcesser::processReq( const CReqStockMinTimeMaxTime* pReq )
{
	return;
}

void CMessageProcesser::processReq( const CReqStockHistoryData* pReq )
{
	return;
}

void CMessageProcesser::processReq( const CReqCreateUser* pReq )
{
	return;
}

void CMessageProcesser::processReq( const CReqTrade* pReq )
{
	return;
}

void CMessageProcesser::processReq( const CReqHistoryTrade* pReq )
{

}

void CMessageProcesser::processReq( const CReqAccount* pReq )
{

}
void CMessageProcesser::processReq( const CReqHoldAccount* pReq )
{

}

//////////////////////////////////////////////////////////////////////////
void CMessageProcesser::processAck( const CAckLogin* pAck )
{
	//TODO.For.Test
	//pMessageManagerRef->sendReqLogin(m_nHanle, "UserName", "PassWord");
	//pMessageManagerRef->sendReqSynYahoo(m_nHanle, "000001.SZ");
	//pMessageManagerRef->sendReqDownLoadStock(m_nHanle);
	//CClientDBManager::getInstance().opendb(pAck->m_strUserName, pAck->m_strPassword);
	CClientDataManager::getInstance().loginToServer_OK(m_nHanle, pAck->m_strUserID);
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
void CMessageProcesser::processAck( const CAckDownLoadStock* pAck )
{
	CStockDataManager::getInstance().addStockData(&(pAck->m_LstStock));
	CClientDataManager::getInstance().dowork_downLoadStockBaseIinfo(m_nHanle);
	return;
}

void CMessageProcesser::processAck( const CAckStockMinTimeMaxTime* pAck )
{
	CStockMinTimeMaxTime* pData = NULL;
	pData = new CStockMinTimeMaxTime();
	pData->m_strSymbolUse = pAck->m_strSymbolUse;
	pData->m_strMinTime = pAck->m_strMinTime;
	pData->m_strMaxTime = pAck->m_strMaxTime;
	pData->m_nCount = pAck->m_nCount;

	CClientDataManager::getInstance().resetDataSymbolMinMaxTime(pData);
	if (NULL != pData)
	{
		delete pData;
		pData = NULL;
	}

	return;
}


void CMessageProcesser::processAck( const CAckStockHistoryData* pAck )
{	
	CClientDataManager::getInstance().resetDataHistory(pAck->m_strSymbolUse, pAck->m_LstHistoryData);
	return;
}

void CMessageProcesser::processAck( const CAckCreateUser* pAck )
{
	CClientDataManager::getInstance().createUser_OK(m_nHanle, pAck->m_strUserName, pAck->m_strPassword);
}

void CMessageProcesser::processAck( const CAckTrade* pAck )
{
	CUserTradeInfo* pUserTradeInfo = NULL;
	pUserTradeInfo = new CUserTradeInfo();
	pUserTradeInfo->setValue(pAck);
	CClientDataManager::getInstance().insertUserTradeInfo(pUserTradeInfo);
	pUserTradeInfo = NULL;
}

void CMessageProcesser::processAck( const CAckHistoryTrade* pAck )
{
	QList<CUserTradeInfo*>::const_iterator iterLst;
	const CUserTradeInfo* pData = NULL;

	iterLst = pAck->m_LstData.constBegin();
	while (iterLst != pAck->m_LstData.constEnd())
	{
		pData = NULL;
		pData = (*iterLst);
		CClientDataManager::getInstance().insertUserTradeInfo(pData);

		iterLst++;
	}//while

}

void CMessageProcesser::processAck( const CAckAccount* pAck )
{
	CUserAccount* pUserAmount = NULL;
	pUserAmount = new CUserAccount();
	pUserAmount->setValue(pAck);
	CClientDataManager::getInstance().resetUserAccount(pUserAmount);

	if (NULL != pUserAmount)
	{
		delete pUserAmount;
		pUserAmount = NULL;
	}
	
}

void CMessageProcesser::processAck( const CAckHoldAccount* pAck )
{
	if (0 >= pAck->m_nLstDataCount)
	{
		return;
	}
	CClientDataManager::getInstance().resetUserHoldAccount(pAck->m_LstData);
}
