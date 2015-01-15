#include "AckBuy.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CAckBuy::CAckBuy( void )
{
	_Clear();
}

CAckBuy::~CAckBuy( void )
{
	_Clear();
}

void CAckBuy::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_Buy;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserName.clear();
	m_strPassword.clear();

	m_strSymbolUse.clear();
	m_strTradeTime.clear();
	m_strTradePrice.clear();
	m_strTradeVolume.clear();
	m_strFees.clear();
	m_strTradeAmount.clear();
	m_strTotalTradeFee.clear();
	m_strTotalTradeAmount.clear();

}

void CAckBuy::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckBuy:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassword="<<m_strPassword
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strTradeTime="<<m_strTradeTime
		<<" "<<"m_strTradePrice="<<m_strTradePrice
		<<" "<<"m_strTradeVolume="<<m_strTradeVolume
		<<" "<<"m_strFees="<<m_strFees
		<<" "<<"m_strTradeAmount="<<m_strTradeAmount
		<<" "<<"m_strTotalTradeFee="<<m_strTotalTradeFee
		<<" "<<"m_strTotalTradeAmount="<<m_strTotalTradeAmount;
	

}
//static
bool CAckBuy::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_Buy == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckBuy::getMessage()
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
	writeToByteArray<<(m_strFees);
	writeToByteArray<<(m_strTradeAmount);
	writeToByteArray<<(m_strTotalTradeFee);
	writeToByteArray<<(m_strTotalTradeAmount);
	

	return pMessage;	
}

void CAckBuy::setValue(const QByteArray* pMessage )
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
	readMessageBuffer>>m_strUserName;
	readMessageBuffer>>m_strPassword;
	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_strTradeTime;
	readMessageBuffer>>m_strTradePrice;
	readMessageBuffer>>m_strTradeVolume;
	readMessageBuffer>>m_strFees;
	readMessageBuffer>>m_strTradeAmount;
	readMessageBuffer>>m_strTotalTradeFee;
	readMessageBuffer>>m_strTotalTradeAmount;

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);

}