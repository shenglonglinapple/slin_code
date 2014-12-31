#include "StockTcpServerActor.h"

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtSql/QtSql>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

CStockTcpServerActor::CStockTcpServerActor(qint32 handle, QObject* parent/*=0*/ )
:QObject(parent)
{
	m_nHandle = 0;
	m_pSocketHandle = NULL;
	m_strlocalAddress.clear();
	m_nLocalPort = 0;
	m_strPeerAddress.clear();
	m_strPeerName.clear();
	m_nPeerPort = 0;

	m_nHandle = handle;
	_Init();
	QObject::connect(this, SIGNAL(signalDeleteMe()), this, SLOT(deleteLater()));

}

CStockTcpServerActor::~CStockTcpServerActor()
{
	_Unit();
}

void CStockTcpServerActor::_Init()
{
	if (NULL != m_pSocketHandle)
	{
		_Unit();
	}

	m_pSocketHandle = new QTcpSocket();

	QObject::connect(m_pSocketHandle, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
	QObject::connect(m_pSocketHandle, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	QObject::connect(m_pSocketHandle, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

	if (false == m_pSocketHandle->setSocketDescriptor(m_nHandle))
	{
		throw CBaseException(__FILE__, __LINE__, m_pSocketHandle->errorString());
	}
	else
	{
		m_strlocalAddress = m_pSocketHandle->localAddress().toString();
		m_nLocalPort = m_pSocketHandle->localPort();
		m_strPeerAddress = m_pSocketHandle->peerAddress().toString();
		m_strPeerName = m_pSocketHandle->peerName();
		m_nPeerPort = m_pSocketHandle->peerPort();

		MYLOG4CPP_INFO<<"new client"
			<<" "<<"m_strlocalAddress="<<m_strlocalAddress
			<<" "<<"m_nLocalPort="<<m_nLocalPort
			<<" "<<"m_strPeerAddress="<<m_strPeerAddress
			<<" "<<"m_strPeerName="<<m_strPeerName
			<<" "<<"m_strlocalAddress="<<m_strlocalAddress
			<<" "<<"m_nPeerPort="<<m_nPeerPort;
	}
}

void CStockTcpServerActor::_Unit()
{
	if (NULL != m_pSocketHandle)
	{
		m_pSocketHandle->waitForDisconnected();
		m_pSocketHandle->close();
		delete m_pSocketHandle;
		m_pSocketHandle = NULL;
	}
}


void CStockTcpServerActor::slotError(QAbstractSocket::SocketError nSocketError)
{
	QString strError;

	switch (nSocketError) 
	{
	case QAbstractSocket::RemoteHostClosedError:
		strError = "QAbstractSocket::RemoteHostClosedError";
		break;
	case QAbstractSocket::HostNotFoundError:
		strError = "QAbstractSocket::HostNotFoundError";
		break;
	case QAbstractSocket::ConnectionRefusedError:
		strError = "QAbstractSocket::ConnectionRefusedError";
		break;
	default:
		strError = "error:"+m_pSocketHandle->errorString();
	}

}


void CStockTcpServerActor::slotReadyRead()
{
	quint16 nHeaderDataValue = 0;
	QDataStream in(m_pSocketHandle);
	in.setVersion(QDataStream::Qt_4_0);

	if (nHeaderDataValue == 0) 
	{
		if (m_pSocketHandle->bytesAvailable() < (int)sizeof(quint16))
		{
			return;
		}
		in >> nHeaderDataValue;
	}

	if (m_pSocketHandle->bytesAvailable() < nHeaderDataValue)
	{
		return;
	}

	QString strReq;
	in >> strReq;

	if (strReq == "Req_Type_1")
	{
		writeAck();
	}
}
void CStockTcpServerActor::writeAck()
{
	QByteArray block;
	QString strACK = "ACK_Type_1";

	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint16)(strACK.size());
	out << strACK;

	m_pSocketHandle->write(block);

}


void CStockTcpServerActor::slotDisconnected()
{
	MYLOG4CPP_INFO<<"client Disconnected"
		<<" "<<"m_strlocalAddress="<<m_strlocalAddress
		<<" "<<"m_nLocalPort="<<m_nLocalPort
		<<" "<<"m_strPeerAddress="<<m_strPeerAddress
		<<" "<<"m_strPeerName="<<m_strPeerName
		<<" "<<"m_strlocalAddress="<<m_strlocalAddress
		<<" "<<"m_nPeerPort="<<m_nPeerPort;

	emit signalDeleteMe();
}



