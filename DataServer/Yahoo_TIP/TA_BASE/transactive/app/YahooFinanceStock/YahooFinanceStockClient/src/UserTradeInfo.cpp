#include "UserTradeInfo.h"
#include "QtTimeHelper.h"
#include "TcpComProtocol.h"
#include "ReqBuy.h"
#include "AckBuy.h"

CUserTradeInfo::CUserTradeInfo()
{
	_Init();
}

CUserTradeInfo::~CUserTradeInfo()
{
	
}

CUserTradeInfo& CUserTradeInfo::operator=( const CUserTradeInfo& objectCopy )
{
	m_strUseID = objectCopy.m_strUseID;
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


void CUserTradeInfo::_Init()
{
	m_strUseID.clear();
	m_strTradeTime.clear();
	m_strTradeUUID.clear();
	m_nTradeType = -1;
	m_strSymbolUse.clear();
	m_fTradePrice = 0;
	m_nTradeVolume = 0;
	m_fTradeAmount = 0;
	m_fTradeFees = 0;
	m_fTotalTradeFee = 0;
	m_fTotalTradeAmount = 0;

}


void CUserTradeInfo::setValue(const QString& strUseID, const CReqBuy* pReq )
{
	_Init();
	m_strUseID = strUseID;

	this->m_strTradeUUID = CTcpComProtocol::getUUID();
	this->m_strTradeTime = pReq->m_strTradeTime;
	this->m_nTradeType = (qint32)pReq->m_nDataType;//CTcpComProtocol::DataType_Buy;
	this->m_strSymbolUse = pReq->m_strSymbolUse;
	this->m_fTradePrice = pReq->m_strTradePrice.toDouble();
	this->m_nTradeVolume = pReq->m_strTradeVolume.toInt();
	this->m_fTradeFees = 0.07;

	m_fTradeAmount = m_fTradePrice*m_nTradeVolume;
	m_fTotalTradeFee = m_fTradeAmount*m_fTradeFees;
	m_fTotalTradeAmount = m_fTradeAmount + m_fTotalTradeFee;
}


void CUserTradeInfo::setValue( const CAckBuy* pAck )
{
	_Init();
	m_strUseID = pAck->m_strUseID;
	m_strTradeUUID = pAck->m_strTradeUUID;
	m_strTradeTime = pAck->m_strTradeTime;
	m_nTradeType = (qint32)pAck->m_nDataType;
	m_strSymbolUse = pAck->m_strSymbolUse;
	m_fTradePrice = pAck->m_strTradePrice.toDouble();
	m_nTradeVolume = pAck->m_strTradeVolume.toInt();
	m_fTradeAmount = pAck->m_strTradeAmount.toDouble();
	m_fTradeFees = pAck->m_strFees.toDouble();
	m_fTotalTradeFee = pAck->m_strTotalTradeFee.toDouble();
	m_fTotalTradeAmount = pAck->m_strTotalTradeAmount.toDouble();

}


