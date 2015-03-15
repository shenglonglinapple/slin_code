#include "ClientMessageProcesser.h"

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

#include "StockMinTimeMaxTime.h"
#include "HistoryData.h"
#include "WorkTime.h"
#include "UserTradeInfo.h"
#include "UserAccount.h"
#include "ClientActorManager.h"

#include "Log4cppLogger.h"

CClientMessageProcesser::CClientMessageProcesser(qint32 nHanle)
{
	m_nHanle = 0;

	m_nHanle = nHanle;
}

CClientMessageProcesser::~CClientMessageProcesser()
{

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void CClientMessageProcesser::processReq(const CReqLogin* pReq )
{
	return;	
}

void CClientMessageProcesser::processReq( const CReqLogout* pReq )
{
	return;
}

void CClientMessageProcesser::processReq( const CReqSynYahoo* pReq )
{
	return;
}

void CClientMessageProcesser::processReq(const CReqDownLoadStock* pReq)
{
	return;
}

void CClientMessageProcesser::processReq( const CReqStockMinTimeMaxTime* pReq )
{
	return;
}

void CClientMessageProcesser::processReq( const CReqStockHistoryData* pReq )
{
	return;
}

void CClientMessageProcesser::processReq( const CReqCreateUser* pReq )
{
	return;
}

void CClientMessageProcesser::processReq( const CReqTrade* pReq )
{
	return;
}

void CClientMessageProcesser::processReq( const CReqHistoryTrade* pReq )
{

}

void CClientMessageProcesser::processReq( const CReqAccount* pReq )
{

}
void CClientMessageProcesser::processReq( const CReqHoldAccount* pReq )
{

}

//////////////////////////////////////////////////////////////////////////
void CClientMessageProcesser::processAck( const CAckCreateUser* pAck )
{
	CClientActorManager::getInstance().send_req_ReqLogin(m_nHanle);
	return;
}
void CClientMessageProcesser::processAck( const CAckLogin* pAck )
{
	QString strUserID;
	strUserID = pAck->m_strUserID;//TODO
	CClientActorManager::getInstance().send_req_ReqDownLoadStock(m_nHanle);
	return;
}
void CClientMessageProcesser::processAck( const CAckDownLoadStock* pAck )
{
	QList<QString>::const_iterator iterLst;
	QString strSymbolUse;
	CClientActorManager::getInstance().resetSymbolUse(m_nHanle, pAck->m_LstStock);
	iterLst = pAck->m_LstStock.constBegin();
	while (iterLst != pAck->m_LstStock.constEnd())
	{
		strSymbolUse = (*iterLst);
		CClientActorManager::getInstance().send_req_ReqSynYahoo(m_nHanle, strSymbolUse);
		iterLst++;
	}//while

	CClientActorManager::getInstance().send_req_ReqUserAccount(m_nHanle, "");//first load account info
	CClientActorManager::getInstance().send_req_ReqUserHoldAccount(m_nHanle, "");
	return;
}

void CClientMessageProcesser::processAck( const CAckLogout* pAck )
{
	return;
}

void CClientMessageProcesser::processAck( const CAckSynYahoo* pAck )
{
	CClientActorManager::getInstance().send_req_ReqStockMinTimeMaxTime(m_nHanle, pAck->m_strSymbolUse);
	CClientActorManager::getInstance().send_req_ReqHistoryTrade(m_nHanle, pAck->m_strSymbolUse, CTcpComProtocol::ETradeType_Buy);

	return;
}


void CClientMessageProcesser::processAck( const CAckStockMinTimeMaxTime* pAck )
{
	CStockMinTimeMaxTime* pData = NULL;
	pData = new CStockMinTimeMaxTime();
	pData->m_strSymbolUse = pAck->m_strSymbolUse;
	pData->m_strMinTime = pAck->m_strMinTime;
	pData->m_strMaxTime = pAck->m_strMaxTime;
	pData->m_nCount = pAck->m_nCount;
	pData->m_fLow = pAck->m_fLow;
	pData->m_fHigh = pAck->m_fHigh;
	pData->m_fCurrent = pAck->m_fCurrent;
	pData->m_fCurrentPercentage = pAck->m_fCurrentPercentage;

	CClientActorManager::getInstance().resetDataSymbolMinMaxTime(m_nHanle, pData);
	if (NULL != pData)
	{
		delete pData;
		pData = NULL;
	}

	return;
}


void CClientMessageProcesser::processAck( const CAckStockHistoryData* pAck )
{		
	CClientActorManager::getInstance().resetHistoryData(m_nHanle, pAck->m_strSymbolUse, pAck->m_LstHistoryData);
	return;
}



void CClientMessageProcesser::processAck( const CAckTrade* pAck )
{
	CUserTradeInfo* pUserTradeInfo = NULL;
	pUserTradeInfo = new CUserTradeInfo();
	pUserTradeInfo->setValue(pAck);
	CClientActorManager::getInstance().insertUserTradeInfo(m_nHanle, pUserTradeInfo);	

	if (NULL != pUserTradeInfo)
	{
		delete pUserTradeInfo;
		pUserTradeInfo = NULL;
	}
	return;
}

void CClientMessageProcesser::processAck( const CAckHistoryTrade* pAck )
{
	CClientActorManager::getInstance().insertUserTradeInfo(m_nHanle, pAck->m_LstData);	
	return;
}

void CClientMessageProcesser::processAck( const CAckAccount* pAck )
{
	CUserAccount* pUserAmount = NULL;
	pUserAmount = new CUserAccount();
	pUserAmount->setValue(pAck);
	CClientActorManager::getInstance().resetUserAccount(m_nHanle, pUserAmount);

	if (NULL != pUserAmount)
	{
		delete pUserAmount;
		pUserAmount = NULL;
	}
	return;
}

void CClientMessageProcesser::processAck( const CAckHoldAccount* pAck )
{
	if (0 >= pAck->m_nLstDataCount)
	{
		return;
	}
	CClientActorManager::getInstance().resetUserHoldAccount(m_nHanle, pAck->m_LstData);
	return;
}
