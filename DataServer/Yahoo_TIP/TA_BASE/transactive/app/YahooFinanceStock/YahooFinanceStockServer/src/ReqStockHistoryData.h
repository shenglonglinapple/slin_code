#ifndef __CLASS_REQ_STOCK_HISTORY_DATA_H__
#define __CLASS_REQ_STOCK_HISTORY_DATA_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"

class CReqStockHistoryData
{
public:
    CReqStockHistoryData(void);
	~CReqStockHistoryData(void);
private:
	void _Clear();
public:
	static bool checkMsgDataType(qint32 nMessageType, qint32 nDataType);
	void setValue(const QByteArray* pMessage );
	QByteArray* getMessage();
	void logInfo( const QString& fileName, qint32 lineNumber );
public:
	CTcpComProtocol::EMsgType m_nMessageType;//CTcpComProtocol::MsgType_Req
	CTcpComProtocol::EDataType m_nDataType;//CTcpComProtocol::EDataType
	QString m_strReqUUID;//37
	QString m_strACKUUID;//37
	QString m_strSymbolUse;
	QString m_strTimeFrom;
	QString m_strTimeTo;
};

#endif//__CLASS_REQ_STOCK_HISTORY_DATA_H__
