#include "MsgProcesser.h"

#include "ReqLogin.h"
#include "AckLogin.h"
#include "ReqLogout.h"
#include "AckLogout.h"

#include "TcpComProtocol.h"
#include "Log4cppLogger.h"

CMsgProcesser::CMsgProcesser( void )
{

}

CMsgProcesser::~CMsgProcesser( void )
{

}

CAckLogin* CMsgProcesser::processReq(const CReqLogin* pReqLogin )
{
	CAckLogin* pAckLogin = NULL;
	pAckLogin = new CAckLogin();

	pAckLogin->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAckLogin->m_nDataType = CTcpComProtocol::DataType_Login;
	pAckLogin->m_strACKUUID = CTcpComProtocol::getUUID();
	pAckLogin->m_strReqUUID = pReqLogin->m_strReqUUID;
	pAckLogin->m_nLoginResult = CTcpComProtocol::DataType_LoginResult_OK;

	return pAckLogin;
}

CAckLogout* CMsgProcesser::processReq( const CReqLogout* pReqLogout )
{
	CAckLogout* pAckLogout = NULL;
	pAckLogout = new CAckLogout();

	pAckLogout->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	pAckLogout->m_nDataType = CTcpComProtocol::DataType_LogOut;
	pAckLogout->m_strACKUUID = CTcpComProtocol::getUUID();
	pAckLogout->m_strReqUUID = pReqLogout->m_strReqUUID;
	pAckLogout->m_nLogoutResult = CTcpComProtocol::DataType_LogoutResult_OK;

	return pAckLogout;
}
