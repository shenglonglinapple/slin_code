#ifndef __CLASS_ACK_DOWNLOAD_STOCK_H__
#define __CLASS_ACK_DOWNLOAD_STOCK_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QList>

#include "TcpComProtocol.h"


class CAckDownLoadStock
{
public:
    CAckDownLoadStock(void);
	~CAckDownLoadStock(void);
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
	qint32 m_nStockCount;
	QList<QString> m_LstStock;

};

#endif//__CLASS_ACK_DOWNLOAD_STOCK_H__



