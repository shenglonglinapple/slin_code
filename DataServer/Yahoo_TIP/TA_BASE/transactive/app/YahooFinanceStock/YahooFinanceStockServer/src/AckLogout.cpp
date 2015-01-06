#include "AckLogout.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CAckLogout::CAckLogout( void )
{
	_Clear();
}

CAckLogout::~CAckLogout( void )
{
	_Clear();
}

void CAckLogout::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_LogOut;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_nLogoutResult = CTcpComProtocol::DataType_LogoutResult_OK;
}

void CAckLogout::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckLogout:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_nLogoutResult="<<CTcpComProtocol::getStringValue(m_nLogoutResult);
}

//static
bool CAckLogout::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_LogOut == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckLogout::getMessage()
{
	QByteArray* pMessage = NULL;
	//QByteArray &append(const char *s, int len);
	pMessage = new QByteArray();

	QDataStream writeToByteArray(pMessage, QIODevice::WriteOnly);
	writeToByteArray.setVersion(QDataStream::Qt_4_0);

	writeToByteArray<<(quint32)(m_nMessageType);
	writeToByteArray<<(quint32)(m_nDataType);
	writeToByteArray<<(m_strReqUUID);
	writeToByteArray<<(m_strACKUUID);
	writeToByteArray<<(quint32)(m_nLogoutResult);

	return pMessage;	
}

void CAckLogout::setValue(const QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<"setValue"
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;
	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType
	qint32 nLoginResult = 0;
	QDataStream readMessageBuffer(*pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;
	readMessageBuffer>>m_strReqUUID;
	readMessageBuffer>>m_strACKUUID;
	readMessageBuffer>>nLoginResult;

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
	m_nLogoutResult = (CTcpComProtocol::EDataTypeLogoutResult)nLoginResult;
	
}