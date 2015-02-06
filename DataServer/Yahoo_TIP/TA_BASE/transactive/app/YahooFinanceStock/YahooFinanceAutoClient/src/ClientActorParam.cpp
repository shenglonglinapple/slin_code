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
	m_strUserID = objCopy.m_strUserID;

	return *this;
}

void CClientActorParam::_Init()
{
	m_strUserName = Class_Def_String_UserName;
	m_strPassWord = Class_Def_String_PassWord;
	m_strServerIP = Class_Def_String_ServerIP;
	m_nServerPort = Class_Def_Int_ServerPort;
	m_nHandle = Class_Def_Int_SocketHandle;
	_InitUserID();
}

void CClientActorParam::setServerValue(const QString& strServerIP, quint16 nServerPort)
{
	m_strServerIP = strServerIP;
	m_nServerPort = nServerPort;
}
void CClientActorParam::setUserValue(const QString& strUserName, const QString& strPassWord)
{
	m_strUserName = strUserName;
	m_strPassWord = strPassWord;
}
void CClientActorParam::setHandleValue( qint32 nHandle )
{
	m_nHandle = nHandle;
}


void CClientActorParam::logInfo( const QString& file, qint32 line )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<file<<":"<<line<<"]"<<" "
		<<" "<<"CClientActorParam:"
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassWord="<<m_strPassWord
		<<" "<<"m_strServerIP="<<m_strServerIP
		<<" "<<"m_nServerPort="<<m_nServerPort
		<<" "<<"m_nHandle="<<m_nHandle
		<<" "<<"m_strUserID="<<m_strUserID;
	
}

qint32 CClientActorParam::getHandle()
{
	return m_nHandle;
}
QString CClientActorParam::getServerIP()
{
	return m_strServerIP;
}
quint16 CClientActorParam::getServerPort()
{
	return m_nServerPort;
}
QString CClientActorParam::getUserName()
{
	return m_strUserName;
}
QString CClientActorParam::getUserPWD()
{
	return m_strPassWord;
}

QString CClientActorParam::getUserID()
{
	return m_strUserID;
}

void CClientActorParam::_InitUserID()
{
	m_strUserID = m_strUserName + "_" + m_strPassWord;
}












