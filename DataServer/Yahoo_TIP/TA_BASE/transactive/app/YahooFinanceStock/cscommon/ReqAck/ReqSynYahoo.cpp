#include "ReqSynYahoo.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CReqSynYahoo::CReqSynYahoo( void )
{
	_Clear();
}

CReqSynYahoo::~CReqSynYahoo( void )
{
	_Clear();
}

void CReqSynYahoo::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Req;
	m_nDataType = CTcpComProtocol::DataType_SynYahoo;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strSymbolUse.clear();
}
//static
bool CReqSynYahoo::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Req == nMsgTypeTmp
		&& CTcpComProtocol::DataType_SynYahoo == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

void CReqSynYahoo::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CReqSynYahoo:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse;
}

void CReqSynYahoo::setValue(const QByteArray* pMessage )
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
	
	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);

}

QByteArray* CReqSynYahoo::getMessage()
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

	return pMessage;
}
