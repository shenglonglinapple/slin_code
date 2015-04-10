#include "AckTrade.h"
#include <QtCore/QDataStream>
#include "ReqTrade.h"
#include "UserTradeInfo.h"
#include "Log4cppLogger.h"

CAckTrade::CAckTrade( void )
{
	_Clear();
}

CAckTrade::~CAckTrade( void )
{
	_Clear();
}

void CAckTrade::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_Trade;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserID.clear();
	m_nTradeType = CTcpComProtocol::ETradeType_Buy;
	m_strTradeUUID.clear();
	m_strSymbolUse.clear();
	m_strTradeTime.clear();
	m_fTradePrice = 0;
	m_nTradeVolume = 0;
	m_fFees = 0;
	m_fTradeAmount = 0;
	m_fTotalTradeFee = 0;
	m_fUserAccount = 0;

}

void CAckTrade::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckTrade:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strUserID="<<m_strUserID
		<<" "<<"m_nTradeType="<<CTcpComProtocol::getStringValue(m_nTradeType)
		<<" "<<"m_strTradeUUID="<<m_strTradeUUID
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strTradeTime="<<m_strTradeTime
		<<" "<<"m_fTradePrice="<<m_fTradePrice
		<<" "<<"m_nTradeVolume="<<m_nTradeVolume
		<<" "<<"m_fFees="<<m_fFees
		<<" "<<"m_fTradeAmount="<<m_fTradeAmount
		<<" "<<"m_fTotalTradeFee="<<m_fTotalTradeFee
		<<" "<<"m_fUserAccount="<<m_fUserAccount;
	

}
//static
bool CAckTrade::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_Trade == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckTrade::getMessage()
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
	writeToByteArray<<(quint32)(m_nTradeType);
	writeToByteArray<<(m_strTradeUUID);
	writeToByteArray<<(m_strSymbolUse);
	writeToByteArray<<(m_strTradeTime);
	writeToByteArray<<(m_fTradePrice);
	writeToByteArray<<(m_nTradeVolume);
	writeToByteArray<<(m_fFees);
	writeToByteArray<<(m_fTradeAmount);
	writeToByteArray<<(m_fTotalTradeFee);
	writeToByteArray<<(m_fUserAccount);
	

	return pMessage;	
}

void CAckTrade::setValue(const QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<"setValue"
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;
	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType
	qint32 nTradeType = 0;//CTcpComProtocol::ETradeType

	qint32 nLoginResult = 0;
	QDataStream readMessageBuffer(*pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;
	readMessageBuffer>>m_strReqUUID;
	readMessageBuffer>>m_strACKUUID;
	readMessageBuffer>>m_strUserID;
	readMessageBuffer>>nTradeType;
	readMessageBuffer>>m_strTradeUUID;
	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_strTradeTime;
	readMessageBuffer>>m_fTradePrice;
	readMessageBuffer>>m_nTradeVolume;
	readMessageBuffer>>m_fFees;
	readMessageBuffer>>m_fTradeAmount;
	readMessageBuffer>>m_fTotalTradeFee;
	readMessageBuffer>>m_fUserAccount;

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
	m_nTradeType = (CTcpComProtocol::ETradeType)nTradeType;

}

void CAckTrade::setValue(const CReqTrade* pReq, const CUserTradeInfo* pUserTradeInfo)
{
	_Clear();

	//this->m_nMessageType = CTcpComProtocol::MsgType_Ack;
	//this->m_nDataType = CTcpComProtocol::DataType_Trade;
	this->m_strACKUUID = CTcpComProtocol::getUUID();
	this->m_strReqUUID = pReq->m_strReqUUID;
	
	if (NULL != pUserTradeInfo)
	{
		this->m_nTradeType = pReq->m_nTradeType;

		this->m_strUserID = pUserTradeInfo->m_strUserID;
		this->m_strTradeUUID = pUserTradeInfo->m_strTradeUUID;
		this->m_strSymbolUse = pUserTradeInfo->m_strSymbolUse;
		this->m_strTradeTime = pUserTradeInfo->m_strTradeTime;
		this->m_fTradePrice = pUserTradeInfo->m_fTradePrice;
		this->m_nTradeVolume = pUserTradeInfo->m_nTradeVolume;
		this->m_fFees = pUserTradeInfo->m_fTradeFees;
		this->m_fTradeAmount = pUserTradeInfo->m_fTradeAmount;
		this->m_fTotalTradeFee = pUserTradeInfo->m_fTotalTradeFee;
		this->m_fUserAccount = pUserTradeInfo->m_fUseAccount;

// 		this->m_fTradePrice = QString("%1").arg(pUserTradeInfo->m_fTradePrice);

	}

}
