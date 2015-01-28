#include "UserAmount.h"
#include "QtTimeHelper.h"
#include "UserTradeInfo.h"

static const int DEF_VALUE_INT_INIT_AMOUNT = 10000*1000;


CUserAmount::CUserAmount()
{
	_Init();
}

CUserAmount::~CUserAmount()
{
	
}

CUserAmount& CUserAmount::operator=( const CUserAmount& objectCopy )
{
	m_strUserID = objectCopy.m_strUserID;
	m_fInitAmount = objectCopy.m_fInitAmount;
	m_fLeftAmount = objectCopy.m_fLeftAmount;
	m_fHoldAmount = objectCopy.m_fHoldAmount;
	m_fFloatingProfitLoss = objectCopy.m_fFloatingProfitLoss;

	m_fFloatingProfitLossPersentage = objectCopy.m_fFloatingProfitLossPersentage;
	m_strUpdateTime = objectCopy.m_strUpdateTime;

	return *this;
}


void CUserAmount::_Init()
{
	m_strUserID.clear();
	m_fInitAmount = DEF_VALUE_INT_INIT_AMOUNT;
	m_fLeftAmount = m_fInitAmount;
	m_fHoldAmount = 0;

	m_fFloatingProfitLoss = 0;
	m_fFloatingProfitLossPersentage = 0;
	m_strUpdateTime.clear();
	resetUpdateTime();
}

void CUserAmount::resetUpdateTime()
{
	CQtTimeHelper timehelper;
	m_strUpdateTime = timehelper.getCurrentTimeStr();
}

void CUserAmount::updateLeftAmount( double fLeftAmount, const QString& strTime )
{
	m_fLeftAmount = fLeftAmount;
	m_fFloatingProfitLoss = m_fLeftAmount + m_fHoldAmount - m_fInitAmount;
	m_fFloatingProfitLossPersentage = m_fFloatingProfitLoss/m_fInitAmount;
	m_strUpdateTime = strTime;
}



void CUserAmount::updateHoldAmount( double fHoldAmount, const QString& strTime )
{
	m_fHoldAmount = fHoldAmount;
	m_fFloatingProfitLoss = m_fLeftAmount + m_fHoldAmount - m_fInitAmount;
	m_fFloatingProfitLossPersentage = m_fFloatingProfitLoss/m_fInitAmount;
	m_strUpdateTime = strTime;
}
