#ifndef __CLASS_ACK_AMOUNT_H__
#define __CLASS_ACK_AMOUNT_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"


class CAckAmount
{
public:
    CAckAmount(void);
	~CAckAmount(void);
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

	QString m_strUserID;//65
	double m_fInitAmount;
	double m_fUseAmount;
	double m_fLeftAmount;
	double m_fFloatingProfitLoss;
	double m_fFloatingProfitLossPersentage;
	double m_fFloatingAmount;
	QString m_strUpdateTime;

	
};

#endif//__CLASS_ACK_AMOUNT_H__
