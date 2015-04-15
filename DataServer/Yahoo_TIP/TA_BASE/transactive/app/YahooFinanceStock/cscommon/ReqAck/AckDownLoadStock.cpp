#include "AckDownLoadStock.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"
#include "StockInfo.h"

CAckDownLoadStock::CAckDownLoadStock( void )
{
	_Clear();
}

CAckDownLoadStock::~CAckDownLoadStock( void )
{
	_Clear();
}

void CAckDownLoadStock::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_DownLoadStock;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_nStockCount = 0;

	foreach (CStockInfo* pData, m_lstStockInfoData)
	{
		delete pData;
		pData = NULL;
	}
	m_lstStockInfoData.clear();
}

void CAckDownLoadStock::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckDownLoadStock:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_nStockCount="<<m_nStockCount;
}
//static
bool CAckDownLoadStock::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_DownLoadStock == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckDownLoadStock::getMessage()
{
	QByteArray* pMessage = NULL;
	//QByteArray &append(const char *s, int len);
	pMessage = new QByteArray();

	m_nStockCount = m_lstStockInfoData.size();

	QDataStream writeToByteArray(pMessage, QIODevice::WriteOnly);
	writeToByteArray.setVersion(QDataStream::Qt_4_0);

	writeToByteArray<<(qint32)(m_nMessageType);
	writeToByteArray<<(qint32)(m_nDataType);
	writeToByteArray<<(m_strReqUUID);
	writeToByteArray<<(m_strACKUUID);
	writeToByteArray<<(qint32)(m_nStockCount);

	foreach (CStockInfo* pData, m_lstStockInfoData)
	{
		writeToByteArray<<pData->m_strSymbolUse;
		writeToByteArray<<pData->m_strNamePinYinFirst;
		writeToByteArray<<pData->m_strNamePinYinFull0;
		writeToByteArray<<pData->m_strNamePinYinFull4;
		writeToByteArray<<pData->m_strNameUtf8;
	}

	return pMessage;	
}

void CAckDownLoadStock::setValue(const QByteArray* pMessage )
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
	readMessageBuffer>>m_nStockCount;
	
	foreach (CStockInfo* pData, m_lstStockInfoData)
	{
		delete pData;
		pData = NULL;
	}
	m_lstStockInfoData.clear();
	//
	for (qint32 nIndex = 0; nIndex < m_nStockCount; nIndex++)
	{
		CStockInfo* pDataNew = new CStockInfo();
		readMessageBuffer>>pDataNew->m_strSymbolUse;
		readMessageBuffer>>pDataNew->m_strNamePinYinFirst;
		readMessageBuffer>>pDataNew->m_strNamePinYinFull0;
		readMessageBuffer>>pDataNew->m_strNamePinYinFull4;
		readMessageBuffer>>pDataNew->m_strNameUtf8;		
		m_lstStockInfoData.push_back(pDataNew);
	}

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
}


