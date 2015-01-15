#include "AckStockHistoryData.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

#include "HistoryData.h"
#include "WorkTime.h"

CAckStockHistoryData::CAckStockHistoryData( void )
{
	_Clear();
}

CAckStockHistoryData::~CAckStockHistoryData( void )
{
	_Clear();
}

void CAckStockHistoryData::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_HistoryData;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strSymbolUse.clear();
	freeData();
	m_nDataCount = 0;
	m_LstHistoryData.clear();
}

void CAckStockHistoryData::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckStockHistoryData:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_nDataCount="<<m_nDataCount;
}
//static
bool CAckStockHistoryData::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_HistoryData == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}
void CAckStockHistoryData::freeData()
{
	foreach (CHistoryData* pData, m_LstHistoryData)
	{
		delete pData;
		pData = NULL;
	}
	m_LstHistoryData.clear();
}
QByteArray* CAckStockHistoryData::getMessage()
{
	CWorkTimeNoLock workTime(0);
	workTime.workBegin();
	MYLOG4CPP_DEBUG<<"CAckStockHistoryData::getMessage begin";
	QByteArray* pMessage = NULL;
	//QByteArray &append(const char *s, int len);
	pMessage = new QByteArray();

	m_nDataCount = m_LstHistoryData.size();

	QDataStream writeToByteArray(pMessage, QIODevice::WriteOnly);
	writeToByteArray.setVersion(QDataStream::Qt_4_0);

	writeToByteArray<<(quint32)(m_nMessageType);
	writeToByteArray<<(quint32)(m_nDataType);
	writeToByteArray<<(m_strReqUUID);
	writeToByteArray<<(m_strACKUUID);
	writeToByteArray<<(m_strSymbolUse);
	writeToByteArray<<(quint32)(m_nDataCount);

	foreach (CHistoryData* pData, m_LstHistoryData)
	{
		writeToByteArray<<pData->m_strDate;
		writeToByteArray<<pData->m_strOpen;
		writeToByteArray<<pData->m_strHigh;
		writeToByteArray<<pData->m_strLow;
		writeToByteArray<<pData->m_strClose;
		writeToByteArray<<pData->m_strVolume;
		writeToByteArray<<pData->m_strAdjClose;

	}

	freeData();
	workTime.workEnd();
	MYLOG4CPP_DEBUG<<"CAckStockHistoryData::getMessage end getWorkTime="<<workTime.getWorkTime()<<" "<<"ms";

	return pMessage;	
}

void CAckStockHistoryData::setValue(const QByteArray* pMessage )
{
	CWorkTimeNoLock workTime(0);
	workTime.workBegin();
	MYLOG4CPP_DEBUG<<"CAckStockHistoryData::setValue begin";

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
	readMessageBuffer>>m_strSymbolUse;
	readMessageBuffer>>m_nDataCount;
	m_LstHistoryData.clear();

	for (qint32 nIndex = 0; nIndex < m_nDataCount; nIndex++)
	{
		CHistoryData* pData = NULL;
		pData = new CHistoryData();

		readMessageBuffer>>pData->m_strDate;
		readMessageBuffer>>pData->m_strOpen;
		readMessageBuffer>>pData->m_strHigh;
		readMessageBuffer>>pData->m_strLow;
		readMessageBuffer>>pData->m_strClose;
		readMessageBuffer>>pData->m_strVolume;
		readMessageBuffer>>pData->m_strAdjClose;

		pData->resetDateValue();

		m_LstHistoryData.push_back(pData);
		pData = NULL;
	}

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);

	workTime.workEnd();
	MYLOG4CPP_DEBUG<<"CAckStockHistoryData::setValue end getWorkTime="<<workTime.getWorkTime()<<" "<<"ms";

}


