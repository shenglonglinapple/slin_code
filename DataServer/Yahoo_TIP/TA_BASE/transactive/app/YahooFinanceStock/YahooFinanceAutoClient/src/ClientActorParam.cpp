#include "ClientActorParam.h"
#include "Log4cppLogger.h"

static const char* Class_Def_String_UserName = "UserNameValuelsl";
static const char* Class_Def_String_PassWord = "PassWordValuelsl";
static const char* Class_Def_String_ServerIP = "127.0.0.1";
static const int   Class_Def_Int_ServerPort = 5000;
static const int   Class_Def_Int_SocketHandle = 0;


CClientActorParam::CClientActorParam()
{
	_Init();
}

CClientActorParam::~CClientActorParam()
{

}

CClientActorParam& CClientActorParam::operator=( const CClientActorParam& objCopy )
{
	m_strUserName = objCopy.m_strUserName;
	m_strPassWord = objCopy.m_strPassWord;
	m_strServerIP = objCopy.m_strServerIP;
	m_nServerPort = objCopy.m_nServerPort;
	m_nHandle = objCopy.m_nHandle;

	return *this;
}

void CClientActorParam::_Init()
{
	m_strUserName = Class_Def_String_UserName;
	m_strPassWord = Class_Def_String_PassWord;
	m_strServerIP = Class_Def_String_ServerIP;
	m_nServerPort = Class_Def_Int_ServerPort;
	m_nHandle = Class_Def_Int_SocketHandle;
}

void CClientActorParam::setValue( const QString& strServerIP, quint16 nServerPort, const QString& strUserName, const QString& strPassWord )
{
	m_strUserName = strUserName;
	m_strPassWord = strPassWord;
	m_strServerIP = strServerIP;
	m_nServerPort = nServerPort;
	m_nHandle = Class_Def_Int_SocketHandle;
}

void CClientActorParam::logInfo( const QString& file, qint32 line )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<file<<":"<<line<<"]"<<" "
		<<" "<<"CClientActorParam:"
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassWord="<<m_strPassWord
		<<" "<<"m_strServerIP="<<m_strServerIP
		<<" "<<"m_nServerPort="<<m_nServerPort
		<<" "<<"m_nHandle="<<m_nHandle;
}

qint32 CClientActorParam::getHandle()
{
	return m_nHandle;
}

void CClientActorParam::setValue( qint32 nHandle )
{
	m_nHandle = nHandle;
}











