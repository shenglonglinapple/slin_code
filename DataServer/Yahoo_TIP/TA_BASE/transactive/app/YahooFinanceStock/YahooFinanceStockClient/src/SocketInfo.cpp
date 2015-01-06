#include "SocketInfo.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

#include "Log4cppLogger.h"

CSocketInfo::CSocketInfo( void )
{
	_Clear();
}

CSocketInfo::~CSocketInfo( void )
{
	_Clear();
}

void CSocketInfo::_Clear()
{
	m_nSocketHandle = 0;
	m_nLocalPort = 0;
	m_nPeerPort = 0;
	m_strlocalAddress.clear();
	m_strPeerAddress.clear();
	m_strPeerName.clear();
	m_strID.clear();
}

void CSocketInfo::setValue( const QTcpSocket* pSocketHandle )
{
	m_nSocketHandle = pSocketHandle->socketDescriptor();
	m_strlocalAddress = pSocketHandle->localAddress().toString();
	m_nLocalPort = pSocketHandle->localPort();
	m_strPeerAddress = pSocketHandle->peerAddress().toString();
	m_strPeerName = pSocketHandle->peerName();
	m_nPeerPort = pSocketHandle->peerPort();
	m_strID = QString("[%1-%2:%3-%4:%5]").
		arg(m_nSocketHandle).
		arg(m_strlocalAddress).arg(m_nLocalPort).
		arg(m_strPeerAddress).arg(m_nPeerPort);


}

void CSocketInfo::logInfo( const QString& fileName, qint32 lineNumber )
{
	/*
	MYLOG4CPP_DEBUG_Base<<"SocketInfo:"
		<<" "<<"m_nSocketHandle="<<m_nSocketHandle
		<<" "<<"m_strlocalAddress="<<m_strlocalAddress
		<<" "<<"m_nLocalPort="<<m_nLocalPort
		<<" "<<"m_strPeerAddress="<<m_strPeerAddress
		<<" "<<"m_strPeerName="<<m_strPeerName
		<<" "<<"m_nPeerPort="<<m_nPeerPort
		<<" "<<"m_strID="<<m_strID;
*/
	// " "<<"["<<__FILE__<<":"<<__LINE__<<"]"<<" "
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"SocketInfo:"
		<<" "<<"m_strID="<<m_strID;
}

