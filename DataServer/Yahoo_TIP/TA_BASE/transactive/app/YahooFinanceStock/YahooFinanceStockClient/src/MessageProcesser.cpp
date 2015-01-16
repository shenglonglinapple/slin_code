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
#include "ReqBuy.h"

#include "AckLogin.h"
#include "AckLogout.h"
#include "AckSynYahoo.h"
#include "AckDownLoadStock.h"
#include "AckStockMinTimeMaxTime.h"
#include "AckStockHistoryData.h"
#include "AckCreateUser.h"
#include "AckBuy.h"


#include "ClientDataManager.h"
#include "StockDataManager.h"
#include "ClientDBManager.h"
#include "DataStockMinTimeMaxTime.h"
#include "StockMinTimeMaxTime.h"
#include "HistoryData.h"
#include "DataStockHistoryData.h"
#include "DataUserTrade.h"
#include "WorkTime.h"
#include "UserTradeInfo.h"

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

void CMessageProcesser::processReq( const CReqBuy* pReq )
{
	return;
}

//////////////////////////////////////////////////////////////////////////
void CMessageProcesser::processAck( const CAckLogin* pAck )
{
	//TODO.For.Test
	//pMessageManagerRef->sendReqLogin(m_nHanle, "UserName", "PassWord");
	//pMessageManagerRef->sendReqSynYahoo(m_nHanle, "000001.SZ");
	//pMessageManagerRef->sendReqDownLoadStock(m_nHanle);
	//CClientDBManager::getInstance().opendb(pAck->m_strUserName, pAck->m_strPassword);
	CClientDataManager::getInstance().loginedToServer(m_nHanle, pAck->m_strUserName, pAck->m_strPassword);
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
	CClientDataManager::getInstance().downLoadStockFromServer(m_nHanle);
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

	CDataStockMinTimeMaxTime::getInstance().appendOrUpdate(pData);
	if (NULL != pData)
	{
		delete pData;
		pData = NULL;
	}

	return;
}


void CMessageProcesser::processAck( const CAckStockHistoryData* pAck )
{
	CDataStockHistoryData::getInstance().setData(pAck->m_strSymbolUse, pAck->m_LstHistoryData);
	return;
}

void CMessageProcesser::processAck( const CAckCreateUser* pAck )
{

}

void CMessageProcesser::processAck( const CAckBuy* pAck )
{
	CUserTradeInfo* pUserTradeInfo = NULL;
	pUserTradeInfo = new CUserTradeInfo();
	pUserTradeInfo->setValue(pAck);
	CDataUserTrade::getInstance().appendOrUpdate(pUserTradeInfo);
	pUserTradeInfo = NULL;
}

