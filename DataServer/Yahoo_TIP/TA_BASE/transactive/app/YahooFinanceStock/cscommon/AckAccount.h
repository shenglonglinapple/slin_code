#ifndef __CLASS_ACK_ACCOUNT_H__
#define __CLASS_ACK_ACCOUNT_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"

class CUserAccount;

class CAckAccount
{
public:
    CAckAccount(void);
	~CAckAccount(void);
private:
	void _Clear();
public:
	static bool checkMsgDataType(qint32 nMessageType, qint32 nDataType);
	void setValue(const QByteArray* pMessage );
	QByteArray* getMessage();
	void logInfo( const QString& fileName, qint32 lineNumber );
public:
	void setValue(const CUserAccount* pData);
public:
	CTcpComProtocol::EMsgType m_nMessageType;//CTcpComProtocol::EMsgType
	CTcpComProtocol::EDataType m_nDataType;//CTcpComProtocol::EDataType
	QString m_strReqUUID;//37
	QString m_strACKUUID;//37

	QString m_strUserID;//65
	double m_fInitAmount;
	double m_fLeftAmount;
	double m_fHoldAmount;
	double m_fFloatingProfitLoss;
	double m_fFloatingProfitLossPersentage;
	QString m_strUpdateTime;

	
};

#endif//__CLASS_ACK_ACCOUNT_H__
