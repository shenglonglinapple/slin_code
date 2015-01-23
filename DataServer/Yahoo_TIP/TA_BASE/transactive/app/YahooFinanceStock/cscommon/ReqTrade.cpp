#include "ReqTrade.h"
#include <QtCore/QDataStream>
#include <QtCore/QVariant>
#include "UserTradeInfo.h"
#include "Log4cppLogger.h"

CReqTrade::CReqTrade( void )
{
	_Clear();
}

CReqTrade::~CReqTrade( void )
{
	_Clear();
}

void CReqTrade::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Req;
	m_nDataType = CTcpComProtocol::DataType_Trade;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserID.clear();
	m_nTradeType = CTcpComProtocol::ETradeType_Buy;
	m_strSymbolUse.clear();
	m_strTradeTime.clear();
	m_strTradePrice.clear();
	m_strTradeVolume.clear();
}
//static
bool CReqTrade::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Req == nMsgTypeTmp
		&& CTcpComProtocol::DataType_Trade == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

void CReqTrade::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CReqBuy:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strUserID="<<m_strUserID
		<<" "<<"m_nTradeType="<<CTcpComProtocol::getStringValue(m_nTradeType)
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strTradeTime="<<m_strTradeTime
		<<" "<<"m_strTradePrice="<<m_strTradePrice
		<<" "<<"m_strTradeVolume="<<m_strTradeVolume;
}

void CReqTrade::setValue(const QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<"setValue"
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;
	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType
	qint32 nTradeType = 0;//CTcpComProtocol::EDataType

	QDataStream readMessageBuffer(*pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;
	readMessageBuffer>>m_strReqUUID;
	readMessageBuffer>>m_strACKUUID;
	readMessageBuffer>>m_strUserID;
	readMessageBuffer>>nTradeType;
	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_strTradeTime;
	readMessageBuffer>>m_strTradePrice;
	readMessageBuffer>>m_strTradeVolume;

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
	m_nTradeType = (CTcpComProtocol::ETradeType)(nTradeType);

}



QByteArray* CReqTrade::getMessage()
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
	writeToByteArray<<(qint32)(m_nTradeType);
	writeToByteArray<<(m_strSymbolUse);
	writeToByteArray<<(m_strTradeTime);
	writeToByteArray<<(m_strTradePrice);
	writeToByteArray<<(m_strTradeVolume);

	return pMessage;
}


void CReqTrade::setValue( const CUserTradeInfo* pData )
{
	m_nTradeType = pData->m_nTradeType;
	m_strSymbolUse = pData->m_strSymbolUse;
	m_strTradeTime = pData->m_strTradeTime;
	m_strTradePrice = QVariant(pData->m_fTradePrice).toString();
	m_strTradeVolume = QVariant(pData->m_nTradeVolume).toString();
}