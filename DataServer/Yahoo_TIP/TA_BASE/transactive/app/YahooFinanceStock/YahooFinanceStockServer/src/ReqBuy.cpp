#include "ReqBuy.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CReqBuy::CReqBuy( void )
{
	_Clear();
}

CReqBuy::~CReqBuy( void )
{
	_Clear();
}

void CReqBuy::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Req;
	m_nDataType = CTcpComProtocol::DataType_Buy;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserName.clear();
	m_strPassword.clear();
}
//static
bool CReqBuy::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Req == nMsgTypeTmp
		&& CTcpComProtocol::DataType_Buy == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

void CReqBuy::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CReqBuy:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassword="<<m_strPassword
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strTradeTime="<<m_strTradeTime
		<<" "<<"m_strTradePrice="<<m_strTradePrice
		<<" "<<"m_strTradeVolume="<<m_strTradeVolume;
}

void CReqBuy::setValue(const QByteArray* pMessage )
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
	readMessageBuffer>>m_strUserName;
	readMessageBuffer>>m_strPassword;
	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_strTradeTime;
	readMessageBuffer>>m_strTradePrice;
	readMessageBuffer>>m_strTradeVolume;

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);

}

QByteArray* CReqBuy::getMessage()
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
	writeToByteArray<<(m_strUserName);
	writeToByteArray<<(m_strPassword);
	writeToByteArray<<(m_strSymbolUse);
	writeToByteArray<<(m_strTradeTime);
	writeToByteArray<<(m_strTradePrice);
	writeToByteArray<<(m_strTradeVolume);

	return pMessage;
}
