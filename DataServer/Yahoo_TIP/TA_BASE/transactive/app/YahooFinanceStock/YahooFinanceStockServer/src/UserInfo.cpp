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
	m_strUSEID = objectCopy.m_strUSEID;
	m_strUSERNAME = objectCopy.m_strUSERNAME;
	m_strPASSWORD = objectCopy.m_strPASSWORD;
	m_strLASTLOGINTIME = objectCopy.m_strLASTLOGINTIME;
	m_nLOGINCOUNT = objectCopy.m_nLOGINCOUNT;
	m_nSTATE = objectCopy.m_nSTATE;
	
	return *this;
}


void CUserInfo::_Init()
{
	m_strUSEID.clear();
	m_strUSERNAME.clear();
	m_strPASSWORD.clear();
	
	m_strLASTLOGINTIME.clear();

	m_nLOGINCOUNT = 0;
	m_nSTATE = 0;
}

void CUserInfo::resetUseID()
{
	m_strUSEID = QString("%1_%2").arg(m_strUSERNAME).arg(m_strPASSWORD);
	resetLoginTime();
	m_nLOGINCOUNT = 0;
	m_nSTATE = UserState_OFFLINE;//
}

void CUserInfo::resetLoginTime()
{
	CQtTimeHelper timehelper;
	m_strLASTLOGINTIME = timehelper.getCurrentTimeStr();
}

