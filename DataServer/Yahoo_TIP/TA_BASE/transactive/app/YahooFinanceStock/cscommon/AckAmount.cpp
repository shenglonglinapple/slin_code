#include "AckAmount.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CAckAmount::CAckAmount( void )
{
	_Clear();
}

CAckAmount::~CAckAmount( void )
{
	_Clear();
}

void CAckAmount::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_Amount;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserID.clear();
	m_fInitAmount = 0;
	m_fUseAmount = 0;
	m_fLeftAmount = 0;
	m_fFloatingProfitLoss = 0;
	m_fFloatingProfitLossPersentage = 0;
	m_fFloatingAmount = 0;
	m_strUpdateTime.clear();
}

void CAckAmount::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckAmount:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID		
		<<" "<<"m_strUserID="<<m_strUserID
		<<" "<<"m_fInitAmount="<<m_fInitAmount
		<<" "<<"m_fUseAmount="<<m_fUseAmount
		<<" "<<"m_fLeftAmount="<<m_fLeftAmount
		<<" "<<"m_fFloatingProfitLoss="<<m_fFloatingProfitLoss
		<<" "<<"m_fFloatingProfitLossPersentage="<<m_fFloatingProfitLossPersentage		
		<<" "<<"m_fFloatingAmount="<<m_fFloatingAmount
		<<" "<<"m_strUpdateTime="<<m_strUpdateTime;

}
//static
bool CAckAmount::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_Amount == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckAmount::getMessage()
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
	writeToByteArray<<(m_fUseAmount);
	writeToByteArray<<(m_fLeftAmount);
	writeToByteArray<<(m_fFloatingProfitLoss);
	writeToByteArray<<(m_fFloatingProfitLossPersentage);
	writeToByteArray<<(m_fFloatingAmount);
	writeToByteArray<<(m_strUpdateTime);

	return pMessage;	
}

void CAckAmount::setValue(const QByteArray* pMessage )
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
	readMessageBuffer>>m_fUseAmount;
	readMessageBuffer>>m_fLeftAmount;
	readMessageBuffer>>m_fFloatingProfitLoss;
	readMessageBuffer>>m_fFloatingProfitLossPersentage;	
	readMessageBuffer>>m_fFloatingAmount;	
	readMessageBuffer>>m_strUpdateTime;	

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
	
}