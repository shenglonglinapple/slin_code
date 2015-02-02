#include "UserTradeInfo.h"
#include "QtTimeHelper.h"
#include "TcpComProtocol.h"
#include "ReqTrade.h"
#include "AckTrade.h"
#include "Log4cppLogger.h"

static const double  DEF_VALUE_DOUBLE_TRADE_FEES = 0.007;

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
	m_fUseAccount = objectCopy.m_fUseAccount;
		
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
	m_fUseAccount = 0;

}


void CUserTradeInfo::setValue(const QString& strUserID, const CReqTrade* pReq )
{
	clear();
	m_strUserID = strUserID;

	this->m_strTradeUUID = CTcpComProtocol::getUUID();
	this->m_strTradeTime = pReq->m_strTradeTime;
	this->m_nTradeType = pReq->m_nTradeType;
	this->m_strSymbolUse = pReq->m_strSymbolUse;
	this->m_fTradePrice = pReq->m_fTradePrice;
	this->m_nTradeVolume = pReq->m_nTradeVolume;
	this->m_fTradeFees = DEF_VALUE_DOUBLE_TRADE_FEES;

	m_fTradeAmount = m_fTradePrice * m_nTradeVolume;
	m_fTotalTradeFee = m_fTradeAmount * m_fTradeFees;

	if (CTcpComProtocol::ETradeType_Buy == pReq->m_nTradeType)
	{
		m_fUseAccount = m_fTradeAmount + m_fTotalTradeFee;//buy=A+B
	}
	else
	{		
		m_fUseAccount = m_fTradeAmount - m_fTotalTradeFee;//sell=A-B
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
	m_fTradePrice = pAck->m_fTradePrice;//.toDouble();
	m_nTradeVolume = pAck->m_nTradeVolume;//.toInt();
	m_fTradeAmount = pAck->m_fTradeAmount;//.toDouble();
	m_fTradeFees = pAck->m_fFees;//.toDouble();
	m_fTotalTradeFee = pAck->m_fTotalTradeFee;//.toDouble();
	m_fUseAccount = pAck->m_fUserAccount;//.toDouble();

}

void CUserTradeInfo::setValue_Buy( const QString& strTime, const QString& strSymbolUse, double fPrice, qint32 nVolume )
{
	clear();

	m_strTradeTime = strTime;
	m_strSymbolUse = strSymbolUse;
	m_nTradeType = CTcpComProtocol::ETradeType_Buy;
	m_fTradePrice = fPrice;
	m_nTradeVolume = nVolume;
	m_fTradeFees = DEF_VALUE_DOUBLE_TRADE_FEES;
	m_fTradeAmount = m_fTradePrice * m_nTradeVolume;
	m_fTotalTradeFee = m_fTradeAmount * m_fTradeFees;
	m_fUseAccount = m_fTradeAmount + m_fTotalTradeFee;//buy=A+B

}


void CUserTradeInfo::setValue_Sell( const QString& strTime, const QString& strSymbolUse, double fPrice, qint32 nVolume )
{
	clear();

	m_strTradeTime = strTime;
	m_strSymbolUse = strSymbolUse;
	m_nTradeType = CTcpComProtocol::ETradeType_Sell;
	m_fTradePrice = fPrice;
	m_nTradeVolume = nVolume;
	m_fTradeFees = DEF_VALUE_DOUBLE_TRADE_FEES;
	m_fTradeAmount = m_fTradePrice * m_nTradeVolume;
	m_fTotalTradeFee = m_fTradeAmount * m_fTradeFees;
	m_fUseAccount = m_fTradeAmount - m_fTotalTradeFee;//sell=A-B

}

void CUserTradeInfo::logInfo( const QString& fileName, qint32 lineNumber ) const
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"m_strTradeUUID="<<m_strTradeUUID
		<<" "<<"m_strTradeTime="<<m_strTradeTime
		<<" "<<"m_strUserID="<<m_strUserID
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_nTradeType="<<CTcpComProtocol::getStringValue(m_nTradeType)
		<<" "<<"m_fTradePrice="<<m_fTradePrice
		<<" "<<"m_nTradeVolume="<<m_nTradeVolume
		<<" "<<"m_fTradeAmount="<<m_fTradeAmount
		<<" "<<"m_fTradeFees="<<m_fTradeFees
		<<" "<<"m_fTotalTradeFee="<<m_fTotalTradeFee
		<<" "<<"m_fUseAccount="<<m_fUseAccount;
}





