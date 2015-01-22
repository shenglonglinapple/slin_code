#include "AckDownLoadTrade.h"
#include <QtCore/QDataStream>
#include "UserHold.h"
#include "Log4cppLogger.h"

CAckDownLoadTrade::CAckDownLoadTrade( void )
{
	_Clear();
}

CAckDownLoadTrade::~CAckDownLoadTrade( void )
{
	_Clear();
}

void CAckDownLoadTrade::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_DownLoadTrade;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserID.clear();
	m_nTradeType = CTcpComProtocol::ETradeType_Buy;
	m_strSymbolUse.clear();
	_ClearLst();
	m_nLstDataCount = 0;
	m_LstData.clear();

}
void CAckDownLoadTrade::_ClearLst()
{
	QList<CUserHold*>::iterator iterLst;
	CUserHold* pData = NULL;
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

void CAckDownLoadTrade::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckBuy:"
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
bool CAckDownLoadTrade::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_DownLoadTrade == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckDownLoadTrade::getMessage()
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

	QList<CUserHold*>::iterator iterLst;
	CUserHold* pData = NULL;
	iterLst = m_LstData.begin();
	while (iterLst != m_LstData.end())
	{
		pData = (*iterLst);
		writeToByteArray<<(pData->m_strUseID);
		writeToByteArray<<(pData->m_strSymbolUse);
		writeToByteArray<<(pData->m_strBuyUUID);

		writeToByteArray<<(pData->m_strBuyTime);
		writeToByteArray<<(pData->m_fBuyPrice);
		writeToByteArray<<(pData->m_nBuyVolume);

		writeToByteArray<<(pData->m_fBuyFees);
		writeToByteArray<<(pData->m_fBuyAmount);
		writeToByteArray<<(pData->m_strCurrentTime);

		writeToByteArray<<(pData->m_fCurrentPrice);
		writeToByteArray<<(pData->m_fCurrentFees);
		writeToByteArray<<(pData->m_fCurrentAmount);

		writeToByteArray<<(pData->m_fProfitLoss);
		writeToByteArray<<(pData->m_fProfitLossPersentage);

		iterLst++;
	}//while
	
	return pMessage;	
}

void CAckDownLoadTrade::setValue(const QByteArray* pMessage )
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
	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_nLstDataCount;
	
	for (qint32 nIndex = 0; nIndex < m_nLstDataCount; nIndex++)
	{
		CUserHold* pData = NULL;
		pData = new CUserHold();

		readMessageBuffer>>(pData->m_strUseID);
		readMessageBuffer>>(pData->m_strSymbolUse);
		readMessageBuffer>>(pData->m_strBuyUUID);

		readMessageBuffer>>(pData->m_strBuyTime);
		readMessageBuffer>>(pData->m_fBuyPrice);
		readMessageBuffer>>(pData->m_nBuyVolume);

		readMessageBuffer>>(pData->m_fBuyFees);
		readMessageBuffer>>(pData->m_fBuyAmount);
		readMessageBuffer>>(pData->m_strCurrentTime);


		readMessageBuffer>>(pData->m_fCurrentPrice);
		readMessageBuffer>>(pData->m_fCurrentFees);
		readMessageBuffer>>(pData->m_fCurrentAmount);

		readMessageBuffer>>(pData->m_fProfitLoss);
		readMessageBuffer>>(pData->m_fProfitLossPersentage);

		m_LstData.push_back(pData);
		pData = NULL;
	}

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
	m_nTradeType = (CTcpComProtocol::ETradeType)nTradeType;

}

