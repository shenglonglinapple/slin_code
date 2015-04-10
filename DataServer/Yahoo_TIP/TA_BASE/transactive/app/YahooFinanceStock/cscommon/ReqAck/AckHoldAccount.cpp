#include "AckHoldAccount.h"
#include <QtCore/QDataStream>
#include "UserHoldAccount.h"
#include "Log4cppLogger.h"

CAckHoldAccount::CAckHoldAccount( void )
{
	_Clear();
}

CAckHoldAccount::~CAckHoldAccount( void )
{
	_Clear();
}

void CAckHoldAccount::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_HoldAccount;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserID.clear();
	m_strSymbolUse.clear();
	_ClearLst();
	m_nLstDataCount = 0;
	m_LstData.clear();

}
void CAckHoldAccount::_ClearLst()
{
	QList<CUserHoldAccount*>::iterator iterLst;
	CUserHoldAccount* pData = NULL;
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

void CAckHoldAccount::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckHoldAccount:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strUserID="<<m_strUserID
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_nLstDataCount="<<m_nLstDataCount;

}
//static
bool CAckHoldAccount::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_HoldAccount == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckHoldAccount::getMessage()
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
	writeToByteArray<<(m_strSymbolUse);
	writeToByteArray<<(m_nLstDataCount);

	QList<CUserHoldAccount*>::iterator iterLst;
	CUserHoldAccount* pData = NULL;
	iterLst = m_LstData.begin();
	while (iterLst != m_LstData.end())
	{
		pData = (*iterLst);

		writeToByteArray<<(pData->m_strUserID);
		writeToByteArray<<(pData->m_strSymbolUse);
		writeToByteArray<<(pData->m_fPrice);
		writeToByteArray<<(pData->m_nVolume);
		writeToByteArray<<(pData->m_strTime);
		writeToByteArray<<(pData->m_fHoldAccount);

		iterLst++;
	}//while
	
	return pMessage;	
}

void CAckHoldAccount::setValue(const QByteArray* pMessage )
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
	readMessageBuffer>>m_strUserID;
	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_nLstDataCount;
	
	for (qint32 nIndex = 0; nIndex < m_nLstDataCount; nIndex++)
	{
		CUserHoldAccount* pData = NULL;
		pData = new CUserHoldAccount();

		readMessageBuffer>>(pData->m_strUserID);
		readMessageBuffer>>(pData->m_strSymbolUse);
		readMessageBuffer>>(pData->m_fPrice);
		readMessageBuffer>>(pData->m_nVolume);
		readMessageBuffer>>(pData->m_strTime);
		readMessageBuffer>>(pData->m_fHoldAccount);
	
		m_LstData.push_back(pData);
		pData = NULL;
	}

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);

}

