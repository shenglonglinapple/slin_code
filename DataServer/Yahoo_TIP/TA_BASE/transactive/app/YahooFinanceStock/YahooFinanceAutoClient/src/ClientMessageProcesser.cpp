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
void CClientMessageProcesser::processAck( const CAckLogin* pAck )
{
	return;
}

void CClientMessageProcesser::processAck( const CAckLogout* pAck )
{
	return;
}

void CClientMessageProcesser::processAck( const CAckSynYahoo* pAck )
{
	return;
}
void CClientMessageProcesser::processAck( const CAckDownLoadStock* pAck )
{
	return;
}

void CClientMessageProcesser::processAck( const CAckStockMinTimeMaxTime* pAck )
{
	return;
}


void CClientMessageProcesser::processAck( const CAckStockHistoryData* pAck )
{		
	return;
}

void CClientMessageProcesser::processAck( const CAckCreateUser* pAck )
{
	return;
}

void CClientMessageProcesser::processAck( const CAckTrade* pAck )
{
	return;
}

void CClientMessageProcesser::processAck( const CAckHistoryTrade* pAck )
{
	return;
}

void CClientMessageProcesser::processAck( const CAckAccount* pAck )
{
	return;
}

void CClientMessageProcesser::processAck( const CAckHoldAccount* pAck )
{
	return;
}
