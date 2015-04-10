#include "UserInfo.h"
#include "QtTimeHelper.h"



CUserInfo::CUserInfo()
{
	_Init();
}

CUserInfo::~CUserInfo()
{
	
}

CUserInfo& CUserInfo::operator=( const CUserInfo& objectCopy )
{
	m_strUserID = objectCopy.m_strUserID;
	m_strUserName = objectCopy.m_strUserName;
	m_strPassWord = objectCopy.m_strPassWord;
	m_strLastLoginTime = objectCopy.m_strLastLoginTime;
	m_nLoginCount = objectCopy.m_nLoginCount;
	m_nState = objectCopy.m_nState;
	
	return *this;
}


void CUserInfo::_Init()
{
	m_strUserID.clear();
	m_strUserName.clear();
	m_strPassWord.clear();
	
	m_strLastLoginTime.clear();

	m_nLoginCount = 0;
	m_nState = 0;
}


void CUserInfo::setUseID( const QString& strUserName, const QString& strPassWord )
{
	m_strUserName = strUserName;
	m_strPassWord = strPassWord;
	m_strUserID = QString("%1_%2").arg(m_strUserName).arg(m_strPassWord);
	resetLoginTime();
	m_nLoginCount = 0;
	m_nState = UserState_OFFLINE;//
}

void CUserInfo::resetLoginTime()
{
	CQtTimeHelper timehelper;
	m_strLastLoginTime = timehelper.getCurrentTimeStr();
}

