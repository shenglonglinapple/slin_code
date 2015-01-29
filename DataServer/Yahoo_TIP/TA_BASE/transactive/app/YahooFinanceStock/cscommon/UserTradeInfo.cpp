#include "UserTradeInfo.h"
#include "QtTimeHelper.h"
#include "TcpComProtocol.h"
#include "ReqTrade.h"
#include "AckTrade.h"

CUserTradeInfo::CUserTradeInfo()
{
	clear();
}

CUserTradeInfo::~CUserTradeInfo()
{
	
}

CUserTradeInfo& CUserTradeInfo::operator=( const CUserTradeInfo& objectCopy )
{
	m_strUserID = objectCopy.m_strUserID;
	m_strTradeUUID = objectCopy.m_strTradeUUID;
	m_strTradeTime = objectCopy.m_strTradeTime;
	m_nTradeType = objectCopy.m_nTradeType;
	m_strSymbolUse = objectCopy.m_strSymbolUse;
	m_fTradePrice = objectCopy.m_fTradePrice;
	m_nTradeVolume = objectCopy.m_nTradeVolume;
	m_fTradeAmount = objectCopy.m_fTradeAmount;
	m_fTradeFees = objectCopy.m_fTradeFees;
	m_fTotalTradeFee = objectCopy.m_fTotalTradeFee;
	m_fTotalTradeAmount = objectCopy.m_fTotalTradeAmount;
		
	return *this;
}


void CUserTradeInfo::clear()
{
	m_strUserID.clear();
	m_strTradeTime.clear();
	m_strTradeUUID.clear();
	m_nTradeType = CTcpComProtocol::ETradeType_Buy;
	m_strSymbolUse.clear();
	m_fTradePrice = 0;
	m_nTradeVolume = 0;
	m_fTradeAmount = 0;
	m_fTradeFees = 0;
	m_fTotalTradeFee = 0;
	m_fTotalTradeAmount = 0;

}


void CUserTradeInfo::setValue(const QString& strUserID, const CReqTrade* pReq )
{
	clear();
	m_strUserID = strUserID;

	this->m_strTradeUUID = CTcpComProtocol::getUUID();
	this->m_strTradeTime = pReq->m_strTradeTime;
	this->m_nTradeType = pReq->m_nTradeType;
	this->m_strSymbolUse = pReq->m_strSymbolUse;
	this->m_fTradePrice = pReq->m_strTradePrice.toDouble();
	this->m_nTradeVolume = pReq->m_strTradeVolume.toInt();
	this->m_fTradeFees = 0.007;

	m_fTradeAmount = m_fTradePrice*m_nTradeVolume;
	m_fTotalTradeFee = m_fTradeAmount*m_fTradeFees;

	if (CTcpComProtocol::ETradeType_Buy == pReq->m_nTradeType)
	{
		m_fTotalTradeAmount = m_fTradeAmount + m_fTotalTradeFee;
	}
	else
	{
		//sell
		m_fTotalTradeAmount = m_fTradeAmount - m_fTotalTradeFee;
	}
}


void CUserTradeInfo::setValue( const CAckTrade* pAck )
{
	clear();
	m_strUserID = pAck->m_strUserID;
	m_strTradeUUID = pAck->m_strTradeUUID;
	m_strTradeTime = pAck->m_strTradeTime;
	m_nTradeType = pAck->m_nTradeType;
	m_strSymbolUse = pAck->m_strSymbolUse;
	m_fTradePrice = pAck->m_strTradePrice.toDouble();
	m_nTradeVolume = pAck->m_strTradeVolume.toInt();
	m_fTradeAmount = pAck->m_strTradeAmount.toDouble();
	m_fTradeFees = pAck->m_strFees.toDouble();
	m_fTotalTradeFee = pAck->m_strTotalTradeFee.toDouble();
	m_fTotalTradeAmount = pAck->m_strTotalTradeAmount.toDouble();

}



