#include "ReqStockHistoryData.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CReqStockHistoryData::CReqStockHistoryData( void )
{
	_Clear();
}

CReqStockHistoryData::~CReqStockHistoryData( void )
{
	_Clear();
}

void CReqStockHistoryData::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Req;
	m_nDataType = CTcpComProtocol::DataType_HistoryData;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strSymbolUse.clear();
	m_strTimeFrom.clear();
	m_strTimeTo.clear();


}
//static
bool CReqStockHistoryData::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Req == nMsgTypeTmp
		&& CTcpComProtocol::DataType_HistoryData == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

void CReqStockHistoryData::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CReqStockHistoryData:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strTimeFrom="<<m_strTimeFrom
		<<" "<<"m_strTimeTo="<<m_strTimeTo;
}

void CReqStockHistoryData::setValue(const QByteArray* pMessage )
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
	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_strTimeFrom;
	readMessageBuffer>>m_strTimeTo;
	
	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);

}

QByteArray* CReqStockHistoryData::getMessage()
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
	writeToByteArray<<(m_strTimeFrom);
	writeToByteArray<<(m_strTimeTo);


	return pMessage;
}
