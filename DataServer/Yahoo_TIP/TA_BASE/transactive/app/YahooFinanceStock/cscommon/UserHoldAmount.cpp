#include "UserHoldAmount.h"
#include "QtTimeHelper.h"
#include "UserTradeInfo.h"

CUserHoldAmount::CUserHoldAmount()
{
	_Init();
}

CUserHoldAmount::~CUserHoldAmount()
{
	
}

CUserHoldAmount& CUserHoldAmount::operator=( const CUserHoldAmount& objectCopy )
{
	m_strUserID = objectCopy.m_strUserID;
	m_strSymbolUse = objectCopy.m_strSymbolUse;
	m_fPrice = objectCopy.m_fPrice;
	m_nVolume = objectCopy.m_nVolume;
	m_strTime = objectCopy.m_strTime;
	m_fAmount = objectCopy.m_fAmount;

	return *this;
}


void CUserHoldAmount::_Init()
{
	m_strUserID.clear();
	m_strSymbolUse.clear();
	m_fPrice = 0;
	m_nVolume = 0;
	m_strTime.clear();
	m_fAmount = 0;

}


void CUserHoldAmount::setValue_FirstBuy( const CUserTradeInfo* pData )
{
	_Init();
	if (CTcpComProtocol::ETradeType_Buy == pData->m_nTradeType)
	{
		m_strUserID = pData->m_strUserID;
		m_strSymbolUse = pData->m_strSymbolUse;
// 		m_fPrice = pData->m_fTradePrice;
// 		m_nVolume = pData->m_nTradeVolume;
// 		m_strTime = pData->m_strTradeTime;
// 		m_fAmount = pData->m_fTradeAmount;
		m_fPrice = 0;
		m_nVolume = 0;
		m_strTime = pData->m_strTradeTime;
		m_fAmount = 0;
	}
}

void CUserHoldAmount::updateValue( const CUserTradeInfo* pData )
{
	//
	if (CTcpComProtocol::ETradeType_Buy == pData->m_nTradeType)
	{
		m_nVolume = m_nVolume + pData->m_nTradeVolume;
	}
	else //if (CTcpComProtocol::ETradeType_Sell == pData->m_nTradeType)
	{
		m_nVolume = m_nVolume - pData->m_nTradeVolume;
	}
	m_fPrice = pData->m_fTradePrice;
	m_fAmount = m_fPrice * m_nVolume;
	m_strTime = pData->m_strTradeTime;
}

void CUserHoldAmount::updatePrice( double fNewPrice, const QString& strTime)
{
	m_fPrice = fNewPrice;
	m_fAmount = m_fPrice * m_nVolume;
	m_strTime = strTime;
}

