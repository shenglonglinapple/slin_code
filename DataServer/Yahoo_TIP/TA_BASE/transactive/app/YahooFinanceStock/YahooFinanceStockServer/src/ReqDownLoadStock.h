#ifndef __CLASS_REQ_DOWNLOAD_STOCK_H__
#define __CLASS_REQ_DOWNLOAD_STOCK_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"

class CReqDownLoadStock
{
public:
    CReqDownLoadStock(void);
	~CReqDownLoadStock(void);
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

};

#endif//__CLASS_REQ_DOWNLOAD_STOCK_H__
