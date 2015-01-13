#ifndef __CLASS_ACK_STOCK_MIN_TIME_MAX_TIME_H__
#define __CLASS_ACK_STOCK_MIN_TIME_MAX_TIME_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"


class CAckStockMinTimeMaxTime
{
public:
    CAckStockMinTimeMaxTime(void);
	~CAckStockMinTimeMaxTime(void);
private:
	void _Clear();
public:
	static bool checkMsgDataType(qint32 nMessageType, qint32 nDataType);
	void setValue(const QByteArray* pMessage );
	QByteArray* getMessage();
	void logInfo( const QString& fileName, qint32 lineNumber );
public:
	CTcpComProtocol::EMsgType m_nMessageType;//CTcpComProtocol::EMsgType
	CTcpComProtocol::EDataType m_nDataType;//CTcpComProtocol::EDataType
	QString m_strReqUUID;//37
	QString m_strACKUUID;//37
	QString m_strSymbolUse;
	QString m_strMinTime;
	QString m_strMaxTime;
	qint32 m_nCount;

};

#endif//__CLASS_ACK_STOCK_MIN_TIME_MAX_TIME_H__
