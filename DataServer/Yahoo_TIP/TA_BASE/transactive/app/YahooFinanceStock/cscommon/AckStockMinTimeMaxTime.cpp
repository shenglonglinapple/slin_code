#include "AckStockMinTimeMaxTime.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CAckStockMinTimeMaxTime::CAckStockMinTimeMaxTime( void )
{
	_Clear();
}

CAckStockMinTimeMaxTime::~CAckStockMinTimeMaxTime( void )
{
	_Clear();
}

void CAckStockMinTimeMaxTime::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_StockMinTimeMaxTime;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strSymbolUse.clear();
	m_strMinTime.clear();
	m_strMaxTime.clear();
	m_nCount = 0;
	m_fLow = 0;
	m_fHigh = 0;
	m_fCurrent = 0;
	m_fCurrentPercentage = 0;
}

void CAckStockMinTimeMaxTime::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckStockMinTimeMaxTime:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strMinTime="<<m_strMinTime
		<<" "<<"m_strMaxTime="<<m_strMaxTime
		<<" "<<"m_nCount="<<m_nCount
		<<" "<<"m_fLow="<<m_fLow
		<<" "<<"m_fHigh="<<m_fHigh
		<<" "<<"m_fCurrent="<<m_fCurrent
		<<" "<<"m_fCurrentPercentage="<<m_fCurrentPercentage;
}
//static
bool CAckStockMinTimeMaxTime::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_StockMinTimeMaxTime == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckStockMinTimeMaxTime::getMessage()
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
	writeToByteArray<<(m_strSymbolUse);
	writeToByteArray<<(m_strMinTime);
	writeToByteArray<<(m_strMaxTime);
	writeToByteArray<<(m_nCount);
	writeToByteArray<<(m_fLow);
	writeToByteArray<<(m_fHigh);
	writeToByteArray<<(m_fCurrent);
	writeToByteArray<<(m_fCurrentPercentage);

	return pMessage;	
}

void CAckStockMinTimeMaxTime::setValue(const QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<"setValue"
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;
	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType
	qint32 nResult = 0;
	QDataStream readMessageBuffer(*pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;
	readMessageBuffer>>m_strReqUUID;
	readMessageBuffer>>m_strACKUUID;
	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_strMinTime;
	readMessageBuffer>>m_strMaxTime;
	readMessageBuffer>>m_nCount;
	readMessageBuffer>>m_fLow;
	readMessageBuffer>>m_fHigh;
	readMessageBuffer>>m_fCurrent;
	readMessageBuffer>>m_fCurrentPercentage;

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
	
}