#include "TcpSocketHelper.h"

CTcpSocketHelper::CTcpSocketHelper()
{

}

CTcpSocketHelper::~CTcpSocketHelper()
{

}

QString CTcpSocketHelper::getSocketType( QAbstractSocket::SocketType nValue )
{
	QString strValue;
	switch (nValue)
	{
	case QAbstractSocket::TcpSocket:
		strValue = "QAbstractSocket::TcpSocket";
		break;
	case QAbstractSocket::UdpSocket:
		strValue = "QAbstractSocket::UdpSocket";
		break;
	case QAbstractSocket::UnknownSocketType:
		strValue = "QAbstractSocket::UnknownSocketType";
		break;
	}
	return strValue;
}

QString CTcpSocketHelper::getNetworkLayerProtocol( QAbstractSocket::NetworkLayerProtocol nValue )
{
	QString strValue;
	switch (nValue)
	{
	case QAbstractSocket::IPv4Protocol:
		strValue = "QAbstractSocket::IPv4Protocol";
		break;
	case QAbstractSocket::IPv6Protocol:
		strValue = "QAbstractSocket::IPv6Protocol";
		break;
	case QAbstractSocket::UnknownNetworkLayerProtocol:
		strValue = "QAbstractSocket::UnknownNetworkLayerProtocol";
		break;
	}
	return strValue;
}

QString CTcpSocketHelper::getSocketError( QAbstractSocket::SocketError nValue )
{
	QString strValue;
	switch (nValue)
	{
	case QAbstractSocket::ConnectionRefusedError:
		strValue = "QAbstractSocket::ConnectionRefusedError";
		break;
	case QAbstractSocket::RemoteHostClosedError:
		strValue = "QAbstractSocket::RemoteHostClosedError";
		break;
	case QAbstractSocket::HostNotFoundError:
		strValue = "QAbstractSocket::HostNotFoundError";
		break;
	case QAbstractSocket::SocketAccessError:
		strValue = "QAbstractSocket::SocketAccessError";
		break;
	case QAbstractSocket::SocketResourceError:
		strValue = "QAbstractSocket::SocketResourceError";
		break;
	case QAbstractSocket::SocketTimeoutError:
		strValue = "QAbstractSocket::SocketTimeoutError";
		break;
	case QAbstractSocket::DatagramTooLargeError:
		strValue = "QAbstractSocket::DatagramTooLargeError";
		break;
	case QAbstractSocket::NetworkError:
		strValue = "QAbstractSocket::NetworkError";
		break;
	case QAbstractSocket::AddressInUseError:
		strValue = "QAbstractSocket::AddressInUseError";
		break;
	case QAbstractSocket::SocketAddressNotAvailableError:
		strValue = "QAbstractSocket::SocketAddressNotAvailableError";
		break;
	case QAbstractSocket::UnsupportedSocketOperationError:
		strValue = "QAbstractSocket::UnsupportedSocketOperationError";
		break;
	case QAbstractSocket::UnfinishedSocketOperationError:
		strValue = "QAbstractSocket::UnfinishedSocketOperationError";
		break;
	case QAbstractSocket::ProxyAuthenticationRequiredError:
		strValue = "QAbstractSocket::ProxyAuthenticationRequiredError";
		break;
	case QAbstractSocket::SslHandshakeFailedError:
		strValue = "QAbstractSocket::SslHandshakeFailedError";
		break;
	case QAbstractSocket::ProxyConnectionRefusedError:
		strValue = "QAbstractSocket::ProxyConnectionRefusedError";
		break;
	case QAbstractSocket::ProxyConnectionTimeoutError:
		strValue = "QAbstractSocket::ProxyConnectionTimeoutError";
		break;
	case QAbstractSocket::ProxyNotFoundError:
		strValue = "QAbstractSocket::ProxyNotFoundError";
		break;
	case QAbstractSocket::ProxyProtocolError:
		strValue = "QAbstractSocket::ProxyProtocolError";
		break;
	case QAbstractSocket::UnknownSocketError:
		strValue = "QAbstractSocket::UnknownSocketError";
		break;
	}
	return strValue;
}

QString CTcpSocketHelper::getSocketState( QAbstractSocket::SocketState nValue )
{
	QString strValue;
	switch (nValue)
	{
	case QAbstractSocket::UnconnectedState:
		strValue = "QAbstractSocket::UnconnectedState";
		break;
	case QAbstractSocket::HostLookupState:
		strValue = "QAbstractSocket::HostLookupState";
		break;
	case QAbstractSocket::ConnectingState:
		strValue = "QAbstractSocket::ConnectingState";
		break;
	case QAbstractSocket::ConnectedState:
		strValue = "QAbstractSocket::ConnectedState";
		break;
	case QAbstractSocket::BoundState:
		strValue = "QAbstractSocket::BoundState";
		break;
	case QAbstractSocket::ListeningState:
		strValue = "QAbstractSocket::ListeningState";
		break;
	case QAbstractSocket::ClosingState:
		strValue = "QAbstractSocket::ClosingState";
		break;
	}
	return strValue;
}

QString CTcpSocketHelper::getSocketOption( QAbstractSocket::SocketOption nValue )
{
	QString strValue;
	switch (nValue)
	{
	case QAbstractSocket::LowDelayOption:
		strValue = "QAbstractSocket::LowDelayOption";
		break;
	case QAbstractSocket::KeepAliveOption:
		strValue = "QAbstractSocket::KeepAliveOption";
		break;
	case QAbstractSocket::MulticastTtlOption:
		strValue = "QAbstractSocket::MulticastTtlOption";
		break;
	case QAbstractSocket::MulticastLoopbackOption:
		strValue = "QAbstractSocket::MulticastLoopbackOption";
		break;
	}
	return strValue;
}
