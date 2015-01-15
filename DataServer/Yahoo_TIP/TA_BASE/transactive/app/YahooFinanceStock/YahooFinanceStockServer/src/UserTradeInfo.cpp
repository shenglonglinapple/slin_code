#include "UserTradeInfo.h"
#include "QtTimeHelper.h"



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
	m_nTradeType = -1;
	m_strSymbolUse.clear();
	m_fTradePrice = 0;
	m_nTradeVolume = 0;
	m_fTradeAmount = 0;
	m_fTradeFees = 0;
	m_fTotalTradeFee = 0;
	m_fTotalTradeAmount = 0;

}

void CUserTradeInfo::setOtherValue()
{
	getTradeAmount();
	getTotalTradeFee();
	getTotalTradeAmount();

}

double CUserTradeInfo::getTradeAmount()
{
	m_fTradeAmount = m_fTradePrice*m_nTradeVolume;
	return m_fTradeAmount;
}

double CUserTradeInfo::getTotalTradeFee()
{
	m_fTotalTradeFee = m_fTradeAmount*m_fTradeFees;
	return m_fTotalTradeFee;
}

double CUserTradeInfo::getTotalTradeAmount()
{
	m_fTotalTradeAmount = m_fTradeAmount + m_fTotalTradeFee
	return m_fTotalTradeAmount;
}


