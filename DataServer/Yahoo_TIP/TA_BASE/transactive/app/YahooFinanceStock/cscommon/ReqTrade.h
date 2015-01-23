#ifndef __CLASS_REQ_TRADE_H__
#define __CLASS_REQ_TRADE_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"

class CUserTradeInfo;

class CReqTrade
{
public:
    CReqTrade(void);
	~CReqTrade(void);
private:
	void _Clear();
public:
	static bool checkMsgDataType(qint32 nMessageType, qint32 nDataType);
	void setValue(const QByteArray* pMessage );
	QByteArray* getMessage();
	void logInfo( const QString& fileName, qint32 lineNumber );
public:
	void setValue(const CUserTradeInfo* pData);
public:
	CTcpComProtocol::EMsgType m_nMessageType;//CTcpComProtocol::MsgType_Req
	CTcpComProtocol::EDataType m_nDataType;//CTcpComProtocol::EDataType
	QString m_strReqUUID;//37
	QString m_strACKUUID;//37

	QString m_strUserID;

	CTcpComProtocol::ETradeType m_nTradeType;
	QString m_strSymbolUse;
	QString m_strTradeTime;
	QString m_strTradePrice;
	QString m_strTradeVolume;

};

#endif//__CLASS_REQ_TRADE_H__
