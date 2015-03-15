#ifndef __CLASS_ACK_STOCK_MIN_TIME_MAX_TIME_H__
#define __CLASS_ACK_STOCK_MIN_TIME_MAX_TIME_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"


class CAckStockMinTimeMaxTime
{
public:
    CAckStockMinTimeMaxTime(void);
	~CAckStockMinTimeMaxTime(void);
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
	QString m_strSymbolUse;
	QString m_strMinTime;
	QString m_strMaxTime;
	qint32 m_nCount;
	double m_fLow;
	double m_fHigh;
	double m_fCurrent;
	//%.8lf  const float EPSINON = 0.0000001;  if((x >= - EPSINON) && (x <= EPSINON) (equal)
	double m_fCurrentPercentage;//(m_fCurrent-m_fLow)/(m_fHigh-m_fLow)  no 0 

};

#endif//__CLASS_ACK_STOCK_MIN_TIME_MAX_TIME_H__
