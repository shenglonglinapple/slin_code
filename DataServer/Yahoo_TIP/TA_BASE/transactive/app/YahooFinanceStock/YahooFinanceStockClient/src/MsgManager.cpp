#include "MsgManager.h"

#include <QtCore/QDataStream>
#include "ReqLogin.h"
#include "AckLogin.h"
#include "ReqLogout.h"
#include "AckLogout.h"

#include "MsgProcesser.h"
#include "Log4cppLogger.h"

CMsgManager::CMsgManager( QObject* parent/*=0*/ )
{
	m_pMsgProcesser = NULL;
	m_pMsgProcesser = new CMsgProcesser();

}

CMsgManager::~CMsgManager()
{
	if (NULL != m_pMsgProcesser)
	{
		delete m_pMsgProcesser;
		m_pMsgProcesser = NULL;
	}
}


void CMsgManager::slotProcessMessage( QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CMsgManager"
		<<" "<<"slot:"<<" "<<"slotProcessMessage"
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;

	QDataStream readMessageBuffer(*pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType
	
	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;

	if (CAckLogin::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckLogin(pMessage);
	}	
	else if (CAckLogout::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckLogout(pMessage);
	}


	if (NULL != pMessage)
	{
		delete pMessage;
		pMessage = NULL;
	}
}

void CMsgManager::_ProcessMessage_AckLogin(const QByteArray* pMessage )
{
	CAckLogin* pAckLogin = NULL;
	pAckLogin = new CAckLogin();
	pAckLogin->setValue(pMessage);
	pAckLogin->logInfo(__FILE__, __LINE__);

	if (CTcpComProtocol::DataType_LoginResult_OK == pAckLogin->m_nLoginResult)
	{
		int nOk = 0;
		send_logout_req();
	}
	if (NULL != pAckLogin)
	{
		delete pAckLogin;
		pAckLogin = NULL;
	}
}

void CMsgManager::_ProcessMessage_AckLogout(const QByteArray* pMessage )
{
	CAckLogout* pAckLogout = NULL;
	pAckLogout = new CAckLogout();
	pAckLogout->setValue(pMessage);
	pAckLogout->logInfo(__FILE__, __LINE__);

	if (CTcpComProtocol::DataType_LogoutResult_OK == pAckLogout->m_nLogoutResult)
	{
		int nOk = 0;
		send_login_req();
	}
	if (NULL != pAckLogout)
	{
		delete pAckLogout;
		pAckLogout = NULL;
	}
}


void CMsgManager::send_logout_req()
{
	MYLOG4CPP_INFO<<"send_logout_req";

	CReqLogout* pReqLogout = NULL;
	pReqLogout = new CReqLogout();

	pReqLogout->m_strReqUUID = CTcpComProtocol::getUUID();
	pReqLogout->m_strUserName = "UserName";
	pReqLogout->m_strPassword = "Password";
	pReqLogout->logInfo(__FILE__, __LINE__);

	emit signalWriteMessage(pReqLogout->getMessage());


	if (NULL != pReqLogout)
	{
		delete pReqLogout;
		pReqLogout= NULL;
	}
}


void CMsgManager::send_login_req()
{
	MYLOG4CPP_INFO<<"send_login_req";

	CReqLogin* pReqLogin = NULL;
	pReqLogin = new CReqLogin();

	pReqLogin->m_strReqUUID = CTcpComProtocol::getUUID();
	pReqLogin->m_strUserName = "UserName";
	pReqLogin->m_strPassword = "Password";
	pReqLogin->logInfo(__FILE__, __LINE__);

	emit signalWriteMessage(pReqLogin->getMessage());

	if (NULL != pReqLogin)
	{
		delete pReqLogin;
		pReqLogin= NULL;
	}
}