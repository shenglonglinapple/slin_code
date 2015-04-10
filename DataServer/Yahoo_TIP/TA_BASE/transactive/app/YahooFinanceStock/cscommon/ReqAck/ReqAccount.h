#ifndef __CLASS_REQ_ACCOUNT_H__
#define __CLASS_REQ_ACCOUNT_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"

class CReqAccount
{
public:
    CReqAccount(void);
	~CReqAccount(void);
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

	QString m_strUserID;
	QString m_strTime;
};

#endif//__CLASS_REQ_ACCOUNT_H__
