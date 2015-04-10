#ifndef __CLASS_ACK_HOLD_ACCOUNT_H__
#define __CLASS_ACK_HOLD_ACCOUNT_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>
#include <Qtcore/QList>

#include "TcpComProtocol.h"

class CUserHoldAccount;

class CAckHoldAccount
{
public:
    CAckHoldAccount(void);
	~CAckHoldAccount(void);
private:
	void _Clear();
	void _ClearLst();

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

	QString m_strUserID;
	QString m_strSymbolUse;

	qint32 m_nLstDataCount;
	QList<CUserHoldAccount*> m_LstData;
};

#endif//__CLASS_ACK_HOLD_ACCOUNT_H__
