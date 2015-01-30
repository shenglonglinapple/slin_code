#include "AckHistoryTrade.h"
#include <QtCore/QDataStream>
#include "UserTradeInfo.h"
#include "Log4cppLogger.h"

CAckHistoryTrade::CAckHistoryTrade( void )
{
	_Clear();
}

CAckHistoryTrade::~CAckHistoryTrade( void )
{
	_Clear();
}

void CAckHistoryTrade::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_HistoryTrade;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserID.clear();
	m_nTradeType = CTcpComProtocol::ETradeType_Buy;
	m_strSymbolUse.clear();
	_ClearLst();
	m_nLstDataCount = 0;
	m_LstData.clear();

}
void CAckHistoryTrade::_ClearLst()
{
	QList<CUserTradeInfo*>::iterator iterLst;
	CUserTradeInfo* pData = NULL;
	iterLst = m_LstData.begin();
	while (iterLst != m_LstData.end())
	{
		pData = (*iterLst);
		delete pData;
		pData = NULL;
		iterLst++;
	}
	m_LstData.clear();
}

void CAckHistoryTrade::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckHistoryTrade:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strUserID="<<m_strUserID
		<<" "<<"m_nTradeType="<<CTcpComProtocol::getStringValue(m_nTradeType)
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_nLstDataCount="<<m_nLstDataCount;

}
//static
bool CAckHistoryTrade::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_HistoryTrade == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckHistoryTrade::getMessage()
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
	writeToByteArray<<(m_nLstDataCount);

	QList<CUserTradeInfo*>::iterator iterLst;
	CUserTradeInfo* pData = NULL;
	iterLst = m_LstData.begin();
	while (iterLst != m_LstData.end())
	{
		pData = (*iterLst);

		writeToByteArray<<(pData->m_strUserID);
		writeToByteArray<<(pData->m_strTradeUUID);
		writeToByteArray<<(pData->m_strTradeTime);

		writeToByteArray<<(qint32)(pData->m_nTradeType);
		writeToByteArray<<(pData->m_strSymbolUse);
		writeToByteArray<<(pData->m_fTradePrice);

		writeToByteArray<<(pData->m_nTradeVolume);
		writeToByteArray<<(pData->m_fTradeAmount);
		writeToByteArray<<(pData->m_fTradeFees);

		writeToByteArray<<(pData->m_fTotalTradeFee);
		writeToByteArray<<(pData->m_fUseAccount);

		iterLst++;
	}//while
	
	return pMessage;	
}

void CAckHistoryTrade::setValue(const QByteArray* pMessage )
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
	m_nTradeType = (CTcpComProtocol::ETradeType)nTradeType;

	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_nLstDataCount;
	
	for (qint32 nIndex = 0; nIndex < m_nLstDataCount; nIndex++)
	{
		CUserTradeInfo* pData = NULL;
		pData = new CUserTradeInfo();

		readMessageBuffer>>(pData->m_strUserID);
		readMessageBuffer>>(pData->m_strTradeUUID);
		readMessageBuffer>>(pData->m_strTradeTime);

		readMessageBuffer>>(nTradeType);
		pData->m_nTradeType = (CTcpComProtocol::ETradeType)nTradeType;
		readMessageBuffer>>(pData->m_strSymbolUse);
		readMessageBuffer>>(pData->m_fTradePrice);

		readMessageBuffer>>(pData->m_nTradeVolume);
		readMessageBuffer>>(pData->m_fTradeAmount);
		readMessageBuffer>>(pData->m_fTradeFees);

		readMessageBuffer>>(pData->m_fTotalTradeFee);
		readMessageBuffer>>(pData->m_fUseAccount);
		
		m_LstData.push_back(pData);
		pData = NULL;
	}

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);

}

