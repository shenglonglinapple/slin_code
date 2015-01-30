#include "UserHoldAccount.h"
#include "QtTimeHelper.h"
#include "UserTradeInfo.h"

CUserHoldAccount::CUserHoldAccount()
{
	_Init();
}

CUserHoldAccount::~CUserHoldAccount()
{
	
}

CUserHoldAccount& CUserHoldAccount::operator=( const CUserHoldAccount& objectCopy )
{
	m_strUserID = objectCopy.m_strUserID;
	m_strSymbolUse = objectCopy.m_strSymbolUse;
	m_fPrice = objectCopy.m_fPrice;
	m_nVolume = objectCopy.m_nVolume;
	m_strTime = objectCopy.m_strTime;
	m_fHoldAccount = objectCopy.m_fHoldAccount;

	return *this;
}


void CUserHoldAccount::_Init()
{
	m_strUserID.clear();
	m_strSymbolUse.clear();
	m_fPrice = 0;
	m_nVolume = 0;
	m_strTime.clear();
	m_fHoldAccount = 0;

}


void CUserHoldAccount::setValue_FirstBuy( const CUserTradeInfo* pData )
{
	_Init();
	if (CTcpComProtocol::ETradeType_Buy == pData->m_nTradeType)
	{
		m_strUserID = pData->m_strUserID;
		m_strSymbolUse = pData->m_strSymbolUse;
		m_fPrice = 0;
		m_nVolume = 0;
		m_strTime = pData->m_strTradeTime;
		m_fHoldAccount = 0;
	}
}

void CUserHoldAccount::updateHoldAmountValue( const CUserTradeInfo* pData )
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
	m_fHoldAccount = m_fPrice * m_nVolume;
	m_strTime = pData->m_strTradeTime;
}

void CUserHoldAccount::updatePrice( double fNewPrice, const QString& strTime)
{
	m_fPrice = fNewPrice;
	m_fHoldAccount = m_fPrice * m_nVolume;
	m_strTime = strTime;
}

