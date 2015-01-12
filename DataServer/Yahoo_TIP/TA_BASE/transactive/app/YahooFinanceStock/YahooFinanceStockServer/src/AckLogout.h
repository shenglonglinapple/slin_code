#ifndef __CLASS_ACK_LOGOUT_H__
#define __CLASS_ACK_LOGOUT_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"


class CAckLogout
{
public:
    CAckLogout(void);
	~CAckLogout(void);
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
	QString m_strUserName;//65
	QString m_strPassword;//65

	CTcpComProtocol::EDataTypeLogoutResult m_nLogoutResult;
};

#endif//__CLASS_ACK_LOGOUT_H__
