#include "ReqDownLoadStock.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CReqDownLoadStock::CReqDownLoadStock( void )
{
	_Clear();
}

CReqDownLoadStock::~CReqDownLoadStock( void )
{
	_Clear();
}

void CReqDownLoadStock::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Req;
	m_nDataType = CTcpComProtocol::DataType_DownLoadStock;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
}
//static
bool CReqDownLoadStock::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Req == nMsgTypeTmp
		&& CTcpComProtocol::DataType_DownLoadStock == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

void CReqDownLoadStock::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CReqDownLoadStock:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID;

}

void CReqDownLoadStock::setValue(const QByteArray* pMessage )
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

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);

}

QByteArray* CReqDownLoadStock::getMessage()
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

	return pMessage;
}