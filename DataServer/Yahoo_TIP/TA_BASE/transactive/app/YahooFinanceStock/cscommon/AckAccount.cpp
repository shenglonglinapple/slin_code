#include "AckAccount.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"
#include "UserAccount.h"

CAckAccount::CAckAccount( void )
{
	_Clear();
}

CAckAccount::~CAckAccount( void )
{
	_Clear();
}

void CAckAccount::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_Account;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserID.clear();
	m_fInitAmount = 0;
	m_fLeftAmount = 0;
	m_fHoldAmount = 0;
	m_fFloatingProfitLoss = 0;
	m_fFloatingProfitLossPersentage = 0;
	m_strUpdateTime.clear();
}

void CAckAccount::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckAccount:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID		
		<<" "<<"m_strUserID="<<m_strUserID
		<<" "<<"m_fInitAmount="<<m_fInitAmount
		<<" "<<"m_fLeftAmount="<<m_fLeftAmount
		<<" "<<"m_fHoldAmount="<<m_fHoldAmount
		<<" "<<"m_fFloatingProfitLoss="<<m_fFloatingProfitLoss
		<<" "<<"m_fFloatingProfitLossPersentage="<<m_fFloatingProfitLossPersentage		
		<<" "<<"m_strUpdateTime="<<m_strUpdateTime;

}
//static
bool CAckAccount::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_Account == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckAccount::getMessage()
{
	QByteArray* pMessage = NULL;
	//QByteArray &append(const char *s, int len);
	pMessage = new QByteArray();

	QDataStream writeToByteArray(pMessage, QIODevice::WriteOnly);
	writeToByteArray.setVersion(QDataStream::Qt_4_0);

	writeToByteArray<<(qint32)(m_nMessageType);
	writeToByteArray<<(qint32)(m_nDataType);
	writeToByteArray<<(m_strReqUUID);
	writeToByteArray<<(m_strACKUUID);
	writeToByteArray<<(m_strUserID);
	writeToByteArray<<(m_fInitAmount);
	writeToByteArray<<(m_fLeftAmount);
	writeToByteArray<<(m_fHoldAmount);
	writeToByteArray<<(m_fFloatingProfitLoss);
	writeToByteArray<<(m_fFloatingProfitLossPersentage);
	writeToByteArray<<(m_strUpdateTime);

	return pMessage;	
}

void CAckAccount::setValue(const QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<"setValue"
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;
	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType
	QDataStream readMessageBuffer(*pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;
	readMessageBuffer>>m_strReqUUID;
	readMessageBuffer>>m_strACKUUID;
	readMessageBuffer>>m_strUserID;
	readMessageBuffer>>m_fInitAmount;
	readMessageBuffer>>m_fLeftAmount;
	readMessageBuffer>>m_fHoldAmount;
	readMessageBuffer>>m_fFloatingProfitLoss;
	readMessageBuffer>>m_fFloatingProfitLossPersentage;	
	readMessageBuffer>>m_strUpdateTime;	

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
	
}

void CAckAccount::setValue( const CUserAccount* pData )
{
	if (NULL == pData)
	{
		return;
	}
	m_strUserID = pData->m_strUserID;
	m_fInitAmount = pData->m_fInitAmount;
	m_fLeftAmount = pData->m_fLeftAmount;
	m_fHoldAmount = pData->m_fHoldAmount;
	m_fFloatingProfitLoss = pData->m_fFloatingProfitLoss;
	m_fFloatingProfitLossPersentage = pData->m_fFloatingProfitLossPersentage;
	m_strUpdateTime = pData->m_strUpdateTime;

}
