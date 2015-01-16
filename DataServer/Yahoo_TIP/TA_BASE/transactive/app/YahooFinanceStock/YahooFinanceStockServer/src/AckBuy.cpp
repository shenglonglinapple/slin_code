#include "AckBuy.h"
#include <QtCore/QDataStream>
#include "ReqBuy.h"
#include "UserTradeInfo.h"
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

	m_strUseID.clear();
	m_strTradeUUID.clear();
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
		<<" "<<"m_strUseID="<<m_strUseID
		<<" "<<"m_strTradeUUID="<<m_strTradeUUID
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
	writeToByteArray<<(m_strUseID);
	writeToByteArray<<(m_strTradeUUID);
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
	readMessageBuffer>>m_strUseID;
	readMessageBuffer>>m_strTradeUUID;
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

void CAckBuy::setValue(const CReqBuy* pReq, const CUserTradeInfo* pUserTradeInfo)
{
	_Clear();

	//this->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	//this->m_nDataType = CTcpComProtocol::DataType_Buy;
	this->m_strACKUUID = CTcpComProtocol::getUUID();
	this->m_strReqUUID = pReq->m_strReqUUID;
	this->m_strUserName = pReq->m_strUserName;
	this->m_strPassword = pReq->m_strPassword;
	
	if (NULL != pUserTradeInfo)
	{
		this->m_strUseID = pUserTradeInfo->m_strUseID;
		this->m_strTradeUUID = pUserTradeInfo->m_strTradeUUID;
		this->m_strSymbolUse = pUserTradeInfo->m_strSymbolUse;
		this->m_strTradeTime = pUserTradeInfo->m_strTradeTime;
		this->m_strTradePrice = QString("%1").arg(pUserTradeInfo->m_fTradePrice);
		this->m_strTradeVolume = QString("%1").arg(pUserTradeInfo->m_nTradeVolume);
		this->m_strFees = QString("%1").arg(pUserTradeInfo->m_fTradeFees);
		this->m_strTradeAmount = QString("%1").arg(pUserTradeInfo->m_fTradeAmount);
		this->m_strTotalTradeFee = QString("%1").arg(pUserTradeInfo->m_fTotalTradeFee);
		this->m_strTotalTradeAmount = QString("%1").arg(pUserTradeInfo->m_fTotalTradeAmount);
	}

}
