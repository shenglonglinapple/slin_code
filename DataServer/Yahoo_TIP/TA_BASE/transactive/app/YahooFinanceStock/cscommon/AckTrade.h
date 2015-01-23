#ifndef __CLASS_ACK_TRADE_H__
#define __CLASS_ACK_TRADE_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"

class CReqTrade;
class CUserTradeInfo;

class CAckTrade
{
public:
    CAckTrade(void);
	~CAckTrade(void);
private:
	void _Clear();
public:
	static bool checkMsgDataType(qint32 nMessageType, qint32 nDataType);
	void setValue(const QByteArray* pMessage );
	QByteArray* getMessage();
	void logInfo( const QString& fileName, qint32 lineNumber );
public:
	void setValue(const CReqTrade* pReq, const CUserTradeInfo* pUserTradeInfo);
public:
	CTcpComProtocol::EMsgType m_nMessageType;//CTcpComProtocol::EMsgType
	CTcpComProtocol::EDataType m_nDataType;//CTcpComProtocol::EDataType
	QString m_strReqUUID;//37
	QString m_strACKUUID;//37

	QString m_strUserID;
	CTcpComProtocol::ETradeType m_nTradeType;
	QString m_strTradeUUID;//37

	QString m_strSymbolUse;
	QString m_strTradeTime;
	QString m_strTradePrice;
	QString m_strTradeVolume;
	QString m_strFees;//0.007
	QString m_strTradeAmount;
	QString m_strTotalTradeFee;//m_strTradeAmount*m_strFees
	QString m_strTotalTradeAmount;

};

#endif//__CLASS_ACK_TRADE_H__
