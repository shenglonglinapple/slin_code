#include "UserAccount.h"
#include "QtTimeHelper.h"
#include "UserTradeInfo.h"
#include "AckAccount.h"

static const int DEF_VALUE_INT_INIT_AMOUNT = 10000*10;


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
	m_fInitAccount = objectCopy.m_fInitAccount;
	m_fLeftAccount = objectCopy.m_fLeftAccount;
	m_fHoldAccount = objectCopy.m_fHoldAccount;
	m_fFloatingProfitLoss = objectCopy.m_fFloatingProfitLoss;

	m_fFloatingProfitLossPersentage = objectCopy.m_fFloatingProfitLossPersentage;
	m_strUpdateTime = objectCopy.m_strUpdateTime;

	return *this;
}


void CUserAccount::_Init()
{
	m_strUserID.clear();
	m_fInitAccount = DEF_VALUE_INT_INIT_AMOUNT;
	m_fLeftAccount = m_fInitAccount;
	m_fHoldAccount = 0;

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

void CUserAccount::updateLeftAccount( double fLeftAmount, const QString& strTime )
{
	m_fLeftAccount = fLeftAmount;
}



void CUserAccount::updateHoldAccount( double fHoldAmount, const QString& strTime )
{
	m_fHoldAccount = fHoldAmount;
	m_fFloatingProfitLoss = m_fLeftAccount + m_fHoldAccount - m_fInitAccount;
	m_fFloatingProfitLossPersentage = m_fFloatingProfitLoss/m_fInitAccount;
	m_strUpdateTime = strTime;
}

void CUserAccount::setValue( const CAckAccount* pData )
{
	if (NULL == pData)
	{
		return;
	}
	m_strUserID = pData->m_strUserID;
	m_fInitAccount = pData->m_fInitAmount;
	m_fLeftAccount = pData->m_fLeftAmount;
	m_fHoldAccount = pData->m_fHoldAmount;
	m_fFloatingProfitLoss = pData->m_fFloatingProfitLoss;
	m_fFloatingProfitLossPersentage = pData->m_fFloatingProfitLossPersentage;
	m_strUpdateTime = pData->m_strUpdateTime;

}
