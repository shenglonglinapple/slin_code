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

CClientLoginParam& CClientLoginParam::operator=( const CClientLoginParam& objCopy )
{
	m_strUserName = objCopy.m_strUserName;
	m_strPassWord = objCopy.m_strPassWord;
	m_strServerIP = objCopy.m_strServerIP;
	m_nServerPort = objCopy.m_nServerPort;
	m_nHandle = objCopy.m_nHandle;

	return *this;
}

void CClientLoginParam::setDefaultValue()
{
	m_strUserName = DEFVALUE_String_UserName;
	m_strPassWord = DEFVALUE_String_PassWord;
	m_strServerIP = DEFVALUE_String_ServerIP;
	m_nServerPort = DEFVALUE_Int_ServerPort;
	m_nHandle = 1;
}

void CClientLoginParam::setValue(
const QString& strUserName,
const QString& strPassWord ,
const QString& strServerIP,
const qint32& nServerPort)
{
	m_strUserName = strUserName;
	m_strPassWord = strPassWord;
	m_strServerIP = strServerIP;
	m_nServerPort = nServerPort;
	m_nHandle = 1;
}

void CClientLoginParam::logInfo( const QString& file, qint32 line )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<file<<":"<<line<<"]"<<" "
		<<" "<<"CClientLoginParam:"
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassWord="<<m_strPassWord
		<<" "<<"m_strServerIP="<<m_strServerIP
		<<" "<<"m_nServerPort="<<m_nServerPort
		<<" "<<"m_nHandle="<<m_nHandle;
}

qint32 CClientLoginParam::getHandle()
{
	return m_nHandle;
}

//QT_END_NAMESPACE










