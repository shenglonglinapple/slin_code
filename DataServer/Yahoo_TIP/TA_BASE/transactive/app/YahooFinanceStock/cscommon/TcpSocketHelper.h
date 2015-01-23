#ifndef __CLASS_TCP_SOCKET_HELPER_H__
#define __CLASS_TCP_SOCKET_HELPER_H__


#include <QtCore/QString>
#include <QtNetwork/QTcpSocket>


class CTcpSocketHelper
{
public:
	CTcpSocketHelper();
	virtual ~CTcpSocketHelper();
public:
	static QString getStringValue(QAbstractSocket::SocketType nValue);
	static QString getStringValue(QAbstractSocket::NetworkLayerProtocol nValue);
	static QString getStringValue(QAbstractSocket::SocketError nValue);
	static QString getStringValue(QAbstractSocket::SocketState nValue);
	static QString getStringValue(QAbstractSocket::SocketOption nValue);



};





#endif //__CLASS_TCP_SOCKET_HELPER_H__
