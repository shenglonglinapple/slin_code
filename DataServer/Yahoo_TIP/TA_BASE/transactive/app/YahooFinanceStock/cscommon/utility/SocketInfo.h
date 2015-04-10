#ifndef __CLASS_SOCKET_INFO_H__
#define __CLASS_SOCKET_INFO_H__

#include <QtNetwork/QTcpSocket>

class CSocketInfo
{
public:
    CSocketInfo(void);
	~CSocketInfo(void);
private:
	void _Clear();
public:
	void setValue(const QTcpSocket* pSocketHandle );
	void logInfo( const QString& fileName, qint32 lineNumber );
public:
	qint32 m_nSocketHandle;
	QString m_strlocalAddress;
	quint16 m_nLocalPort;
	QString m_strPeerAddress;
	QString m_strPeerName;
	quint16 m_nPeerPort;
public:
	QString m_strID;
};

#endif//__CLASS_SOCKET_INFO_H__
