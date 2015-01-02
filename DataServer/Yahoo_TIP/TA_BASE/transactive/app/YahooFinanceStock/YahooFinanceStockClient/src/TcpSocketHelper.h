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
	QString getSocketType(QAbstractSocket::SocketType nValue);
	QString getNetworkLayerProtocol(QAbstractSocket::NetworkLayerProtocol nValue);
	QString getSocketError(QAbstractSocket::SocketError nValue);
	QString getSocketState(QAbstractSocket::SocketState nValue);
	QString getSocketOption(QAbstractSocket::SocketOption nValue);



};





#endif //__CLASS_TCP_SOCKET_HELPER_H__
