#include "StockTcpClientActor.h"

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtSql/QtSql>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"
#include "TcpSocketHelper.h"


CStockTcpClientActor::CStockTcpClientActor(QObject* parent/*=0*/ )
:QObject(parent)
{
	m_nHandle = 0;
	m_pSocketHandle = NULL;
	m_strlocalAddress.clear();
	m_nLocalPort = 0;
	m_strPeerAddress.clear();
	m_strPeerName.clear();
	m_nPeerPort = 0;

	//
	m_pSocketHandle = new QTcpSocket(NULL);
	//
	QObject::connect(m_pSocketHandle, SIGNAL(connected()), this, SLOT(slotConnected()));
	QObject::connect(m_pSocketHandle, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
	QObject::connect(m_pSocketHandle, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	QObject::connect(m_pSocketHandle, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
	//
	QObject::connect(this, SIGNAL(signalDeleteMe()), this, SLOT(deleteLater()));

}

CStockTcpClientActor::~CStockTcpClientActor()
{

	if (NULL != m_pSocketHandle)
	{
		delete m_pSocketHandle;
		m_pSocketHandle = NULL;
	}

}




void CStockTcpClientActor::slotError(QAbstractSocket::SocketError nSocketError)
{
	MYLOG4CPP_INFO<<"slotError";

	QString strSocketError;
	QString strErrorString;
	CTcpSocketHelper tcpSocketHelper;

	strSocketError = tcpSocketHelper.getSocketError(nSocketError);
	strErrorString = m_pSocketHandle->errorString();

}


void CStockTcpClientActor::slotReadyRead()
{
	MYLOG4CPP_INFO<<"slotReadyRead";

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
		
	}

}


void CStockTcpClientActor::slotDisconnected()
{
	MYLOG4CPP_INFO<<"Disconnected to server"
		<<" "<<"m_strlocalAddress="<<m_strlocalAddress
		<<" "<<"m_nLocalPort="<<m_nLocalPort
		<<" "<<"m_strPeerAddress="<<m_strPeerAddress
		<<" "<<"m_strPeerName="<<m_strPeerName
		<<" "<<"m_nPeerPort="<<m_nPeerPort;

	emit signalDeleteMe();
}

void CStockTcpClientActor::slotConnected()
{
	_GetSocketInfo();

	send_req();
}


void CStockTcpClientActor::_GetSocketInfo()
{
	m_nHandle = m_pSocketHandle->socketDescriptor();

	m_strlocalAddress = m_pSocketHandle->localAddress().toString();
	m_nLocalPort = m_pSocketHandle->localPort();
	m_strPeerAddress = m_pSocketHandle->peerAddress().toString();
	m_strPeerName = m_pSocketHandle->peerName();
	m_nPeerPort = m_pSocketHandle->peerPort();

	MYLOG4CPP_INFO<<"connectToHost to server ok!"
		<<" "<<"m_nHandle="<<m_nHandle
		<<" "<<"m_strlocalAddress="<<m_strlocalAddress
		<<" "<<"m_nLocalPort="<<m_nLocalPort
		<<" "<<"m_strPeerAddress="<<m_strPeerAddress
		<<" "<<"m_strPeerName="<<m_strPeerName
		<<" "<<"m_nPeerPort="<<m_nPeerPort;

}

void CStockTcpClientActor::connectToServer( const QString& strServerIP, quint16 nServerPort )
{
	bool bConnected = false;
	//Aborts the current connection and resets the socket.
	m_pSocketHandle->abort();

	MYLOG4CPP_INFO<<"begin connect to server"
		<<" "<<"strServerIP="<<strServerIP
		<<" "<<"nServerPort="<<nServerPort;

	m_pSocketHandle->connectToHost(strServerIP, nServerPort);
	//只有使用waitForConnected()后,QTcpSocket才真正尝试连接服务器，并返回是否连接的结果
	bConnected = m_pSocketHandle->waitForConnected();

	MYLOG4CPP_INFO<<"end connect to server"
		<<" "<<"strServerIP="<<strServerIP
		<<" "<<"nServerPort="<<nServerPort
		<<" "<<"bConnected="<<bConnected;

}


void CStockTcpClientActor::send_req()
{
	MYLOG4CPP_INFO<<"send_req to server";

	qint64 nWriteDataLen = 0;
	bool bwaitForBytesWritten = false;
	QString strReq = "Req_Type_1";
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	out << (quint16)(strReq.size());
	out << strReq;

	nWriteDataLen = m_pSocketHandle->write(block);
	bwaitForBytesWritten = m_pSocketHandle->waitForBytesWritten();

}

void CStockTcpClientActor::disConnectToServer()
{
	MYLOG4CPP_INFO<<"disConnectToServer";

	if (NULL != m_pSocketHandle)
	{
		m_pSocketHandle->disconnectFromHost();
		m_pSocketHandle->waitForDisconnected();
		delete m_pSocketHandle;
		m_pSocketHandle = NULL;
	}
}

