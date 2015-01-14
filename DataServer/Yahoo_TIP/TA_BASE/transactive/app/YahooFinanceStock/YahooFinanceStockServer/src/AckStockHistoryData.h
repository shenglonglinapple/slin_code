#ifndef __CLASS_ACK_STOCK_HISTORY_DATA_H__
#define __CLASS_ACK_STOCK_HISTORY_DATA_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QList>

#include "TcpComProtocol.h"

class CHistoryData;

class CAckStockHistoryData
{
public:
    CAckStockHistoryData(void);
	~CAckStockHistoryData(void);
private:
	void _Clear();
public:
	static bool checkMsgDataType(qint32 nMessageType, qint32 nDataType);
	void setValue(const QByteArray* pMessage );
	QByteArray* getMessage();
	void logInfo( const QString& fileName, qint32 lineNumber );
	void freeData();
public:
	CTcpComProtocol::EMsgType m_nMessageType;//CTcpComProtocol::EMsgType
	CTcpComProtocol::EDataType m_nDataType;//CTcpComProtocol::EDataType
	QString m_strReqUUID;//37
	QString m_strACKUUID;//37
	QString m_strSymbolUse;
	qint32 m_nDataCount;
	QList<CHistoryData*> m_LstHistoryData;

};

#endif//__CLASS_ACK_STOCK_HISTORY_DATA_H__



