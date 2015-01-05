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
	m_pServerMsgProcesser = NULL;
	m_pServerMsgProcesser = new CMsgProcesser();

}

CMsgManager::~CMsgManager()
{
	if (NULL != m_pServerMsgProcesser)
	{
		delete m_pServerMsgProcesser;
		m_pServerMsgProcesser = NULL;
	}
}


void CMsgManager::slotProcessMessage( QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CMsgManager"
		<<" "<<"slot:"<<" "<<"slotProcessMessage"
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;

	if (NULL == pMessage)
	{
		return;
	}
	QDataStream readMessageBuffer(*pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType
	
	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;

	if (CReqLogin::checkMsgDataType(nMessageType, nDataType))
	{
		CReqLogin* pReqLogin = NULL;
		CAckLogin* pAckLogin = NULL;
		QByteArray* pByteArray = NULL;
		pReqLogin = new CReqLogin();
		pReqLogin->setValue(pMessage);

		pAckLogin = m_pServerMsgProcesser->processReq(pReqLogin);
		pByteArray = pAckLogin->getMessage();

		emit signalWriteMessage(pByteArray);

		if (NULL != pReqLogin)
		{
			delete pReqLogin;
			pReqLogin = NULL;
		}
		if (NULL != pAckLogin)
		{
			delete pAckLogin;
			pAckLogin = NULL;
		}
	}
	else if (CAckLogin::checkMsgDataType(nMessageType, nDataType))
	{
		CAckLogin* pAckLogin = NULL;
		pAckLogin = new CAckLogin();
		pAckLogin->setValue(pMessage);
		if (CTcpComProtocol::DataType_LoginResult_OK == pAckLogin->m_nLoginResult)
		{
			int nOk = 0;
		}
		if (NULL != pAckLogin)
		{
			delete pAckLogin;
			pAckLogin = NULL;
		}

	}
	else if (CReqLogout::checkMsgDataType(nMessageType, nDataType))
	{
		CReqLogout* pReqLogout = NULL;
		CAckLogout* pAckLogout = NULL;
		QByteArray* pByteArray = NULL;
		pReqLogout = new CReqLogout();
		pReqLogout->setValue(pMessage);

		pAckLogout = m_pServerMsgProcesser->processReq(pReqLogout);
		pByteArray = pAckLogout->getMessage();

		emit signalWriteMessage(pByteArray);

		if (NULL != pReqLogout)
		{
			delete pReqLogout;
			pReqLogout = NULL;
		}
		if (NULL != pAckLogout)
		{
			delete pAckLogout;
			pAckLogout = NULL;
		}
	}



	if (NULL != pMessage)
	{
		delete pMessage;
		pMessage = NULL;
	}
}