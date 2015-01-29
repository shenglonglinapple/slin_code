#include "UserAccount.h"
#include "QtTimeHelper.h"
#include "UserTradeInfo.h"
#include "AckAccount.h"

static const int DEF_VALUE_INT_INIT_AMOUNT = 10000*1000;


CUserAccount::CUserAccount()
{
	_Init();
}

CUserAccount::~CUserAccount()
{
	
}

CUserAccount& CUserAccount::operator=( const CUserAccount& objectCopy )
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


void CUserAccount::_Init()
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

void CUserAccount::resetUpdateTime()
{
	CQtTimeHelper timehelper;
	m_strUpdateTime = timehelper.getCurrentTimeStr();
}

void CUserAccount::updateLeftAmount( double fLeftAmount, const QString& strTime )
{
	m_fLeftAmount = fLeftAmount;
	m_fFloatingProfitLoss = m_fLeftAmount + m_fHoldAmount - m_fInitAmount;
	m_fFloatingProfitLossPersentage = m_fFloatingProfitLoss/m_fInitAmount;
	m_strUpdateTime = strTime;
}



void CUserAccount::updateHoldAmount( double fHoldAmount, const QString& strTime )
{
	m_fHoldAmount = fHoldAmount;
	m_fFloatingProfitLoss = m_fLeftAmount + m_fHoldAmount - m_fInitAmount;
	m_fFloatingProfitLossPersentage = m_fFloatingProfitLoss/m_fInitAmount;
	m_strUpdateTime = strTime;
}

void CUserAccount::setValue( const CAckAccount* pData )
{
	if (NULL == pData)
	{
		return;
	}
	m_strUserID = pData->m_strUserID;
	m_fInitAmount = pData->m_fInitAmount;
	m_fLeftAmount = pData->m_fLeftAmount;
	m_fHoldAmount = pData->m_fHoldAmount;
	m_fFloatingProfitLoss = pData->m_fFloatingProfitLoss;
	m_fFloatingProfitLossPersentage = pData->m_fFloatingProfitLossPersentage;
	m_strUpdateTime = pData->m_strUpdateTime;

}
