#include "ClientLoginParam.h"

#include "ProjectCommonData.h"
#include "Log4cppLogger.h"
//

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE





CClientLoginParam::CClientLoginParam()
{
	setDefaultValue();
}

CClientLoginParam::~CClientLoginParam()
{

}

CClientLoginParam& CClientLoginParam::operator=( const CClientLoginParam& clinetLoginParam )
{
	m_strUserName = clinetLoginParam.m_strUserName;
	m_strPassWord = clinetLoginParam.m_strPassWord;
	m_bEnableDebug = clinetLoginParam.m_bEnableDebug;
	m_strServerIP = clinetLoginParam.m_strServerIP;
	m_nServerPort = clinetLoginParam.m_nServerPort;
	m_bSynchronous = clinetLoginParam.m_bSynchronous;
	return *this;
}

void CClientLoginParam::setDefaultValue()
{
	m_strUserName = DEFVALUE_String_UserName;
	m_strPassWord = DEFVALUE_String_PassWord;
	m_bEnableDebug = DEFVALUE_Bool_EnableDebug;
	m_strServerIP = DEFVALUE_String_ServerIP;
	m_nServerPort = DEFVALUE_Int_ServerPort;
	m_bSynchronous = DEFVALUE_Bool_Synchronous;
}

void CClientLoginParam::logInfo( const std::string& file, int line )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<file<<":"<<line<<"]"<<" "
		<<" "<<"CClientLoginParam:"
		<<" "<<"m_strUserName:"<<m_strUserName
		<<" "<<"m_strPassWord:"<<m_strPassWord
		<<" "<<"m_bEnableDebug:"<<m_bEnableDebug
		<<" "<<"m_strServerIP:"<<m_strServerIP
		<<" "<<"m_nServerPort:"<<m_nServerPort
		<<" "<<"m_bSynchronous:"<<m_bSynchronous;
}

//QT_END_NAMESPACE










