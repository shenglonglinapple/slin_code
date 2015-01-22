#include "UserHold.h"
#include "QtTimeHelper.h"
#include "TcpComProtocol.h"
#include "UserTradeInfo.h"

CUserHold::CUserHold()
{
	clear();
}

CUserHold::~CUserHold()
{
	
}

CUserHold& CUserHold::operator=( const CUserHold& objectCopy )
{
	m_strUseID = objectCopy.m_strUseID;
	m_strSymbolUse = objectCopy.m_strSymbolUse;

	m_strBuyUUID = objectCopy.m_strBuyUUID;
	m_strBuyTime = objectCopy.m_strBuyTime;
	m_fBuyPrice = objectCopy.m_fBuyPrice;
	m_nBuyVolume = objectCopy.m_nBuyVolume;
	m_fBuyFees = objectCopy.m_fBuyFees;
	m_fBuyAmount = objectCopy.m_fBuyAmount;

	m_strCurrentTime = objectCopy.m_strCurrentTime;
	m_fCurrentPrice = objectCopy.m_fCurrentPrice;
	m_fCurrentFees = objectCopy.m_fCurrentFees;		
	m_fCurrentAmount = objectCopy.m_fCurrentAmount;

	m_fProfitLoss = objectCopy.m_fProfitLoss;
	m_fProfitLossPersentage = objectCopy.m_fProfitLossPersentage;

	return *this;
}


void CUserHold::clear()
{
	m_strUseID.clear();
	m_strSymbolUse.clear();
	m_strBuyUUID.clear();
	m_strBuyTime.clear();
	m_fBuyPrice = 0;
	m_nBuyVolume= 0;
	m_fBuyFees = 0;
	m_fBuyAmount= 0;

	m_strCurrentTime.clear();
	m_fCurrentPrice= 0;
	m_fCurrentFees= 0;
	m_fCurrentAmount= 0;

	m_fProfitLoss = 0;
	m_fProfitLossPersentage= 0;


}

void CUserHold::setValue( const CUserTradeInfo* pData )
{
	clear();
	if (CTcpComProtocol::ETradeType_Buy == pData->m_nTradeType)
	{
		m_strUseID = pData->m_strUseID;
		m_strSymbolUse = pData->m_strSymbolUse;
		m_strBuyUUID = pData->m_strTradeUUID;
		m_strBuyTime = pData->m_strTradeTime;
		m_fBuyPrice = pData->m_fTradePrice;
		m_nBuyVolume =  pData->m_nTradeVolume;
		m_fBuyFees =  pData->m_fTradeFees;
		m_fBuyAmount =  (m_fBuyPrice * m_nBuyVolume)*(1 + m_fBuyFees);

		m_strCurrentTime =  pData->m_strTradeTime;
		m_fCurrentPrice =  pData->m_fTradePrice;
		m_fCurrentFees =  pData->m_fTradeFees;
		m_fCurrentAmount = (m_fCurrentPrice * m_nBuyVolume)*(1 - m_fCurrentFees);

		m_fProfitLoss =  m_fCurrentAmount - m_fBuyAmount;
		m_fProfitLossPersentage = (m_fCurrentAmount-m_fBuyAmount)/m_fBuyAmount;
	}
}


