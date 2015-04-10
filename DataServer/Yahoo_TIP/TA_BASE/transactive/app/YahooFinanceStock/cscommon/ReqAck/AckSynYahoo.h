#ifndef __CLASS_ACK_SYN_YAHOO_H__
#define __CLASS_ACK_SYN_YAHOO_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"


class CAckSynYahoo
{
public:
    CAckSynYahoo(void);
	~CAckSynYahoo(void);
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
	QString m_strACKUUID;
	QString m_strSymbolUse;
	CTcpComProtocol::EDataTypeSynYahooResult m_nResult;
};

#endif//__CLASS_ACK_SYN_YAHOO_H__
