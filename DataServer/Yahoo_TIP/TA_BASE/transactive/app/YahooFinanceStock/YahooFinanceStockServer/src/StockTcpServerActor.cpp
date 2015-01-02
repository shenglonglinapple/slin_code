#include "StockTcpServerActor.h"

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtSql/QtSql>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "TcpSocketHelper.h"

CStockTcpServerActor::CStockTcpServerActor(qint32 handle, QObject* parent/*=0*/ )
:QObject(parent)
{
	m_nSocketHandle = 0;
	m_pSocketHandle = NULL;
	m_strlocalAddress.clear();
	m_nLocalPort = 0;
	m_strPeerAddress.clear();
	m_strPeerName.clear();
	m_nPeerPort = 0;
	m_pSocketBuffer = NULL;

	{
		QMutexLocker lock(&m_mutex_SocketW);
		m_nSocketHandle = handle;
		m_pSocketHandle = new QTcpSocket();
	}

	{
		QMutexLocker lock(&m_mutex_SocketBuffer);	
		m_pSocketBuffer = new QByteArray();
	}



	QObject::connect(m_pSocketHandle, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
	QObject::connect(m_pSocketHandle, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	QObject::connect(m_pSocketHandle, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

	//
	QObject::connect(this, SIGNAL(signalDeleteMe()), this, SLOT(deleteLater()));
	QObject::connect(this, SIGNAL(signalProcessRecvBuffer()), this, SLOT(slotProcessRecvBuffer()));
	QObject::connect(this, SIGNAL(signalProcessMessage(QByteArray*)), this, SLOT(slotProcessMessage(QByteArray*)));

	//
	if (false == m_pSocketHandle->setSocketDescriptor(m_nSocketHandle))
	{
		throw CBaseException(__FILE__, __LINE__, m_pSocketHandle->errorString());
	}
	_GetSocketInfo();
}

CStockTcpServerActor::~CStockTcpServerActor()
{
	{
		QMutexLocker lock(&m_mutex_SocketBuffer);	
		if (NULL != m_pSocketBuffer)
		{
			delete m_pSocketBuffer;
			m_pSocketBuffer = NULL;
		}
	}

	{
		QMutexLocker lock(&m_mutex_SocketW);
		if (NULL != m_pSocketHandle)
		{
			m_pSocketHandle->waitForDisconnected();
			m_pSocketHandle->close();
			delete m_pSocketHandle;
			m_pSocketHandle = NULL;
		}
	}

}

void CStockTcpServerActor::_GetSocketInfo()
{
	QMutexLocker lock(&m_mutex_SocketW);

	m_strlocalAddress = m_pSocketHandle->localAddress().toString();
	m_nLocalPort = m_pSocketHandle->localPort();
	m_strPeerAddress = m_pSocketHandle->peerAddress().toString();
	m_strPeerName = m_pSocketHandle->peerName();
	m_nPeerPort = m_pSocketHandle->peerPort();

	MYLOG4CPP_INFO<<"new client"
		<<" "<<"m_nHandle="<<m_nSocketHandle
		<<" "<<"m_strlocalAddress="<<m_strlocalAddress
		<<" "<<"m_nLocalPort="<<m_nLocalPort
		<<" "<<"m_strPeerAddress="<<m_strPeerAddress
		<<" "<<"m_strPeerName="<<m_strPeerName
		<<" "<<"m_nPeerPort="<<m_nPeerPort;

}



void CStockTcpServerActor::slotError(QAbstractSocket::SocketError nSocketError)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
		<<" "<<"slot:"<<" "<<"slotError";

	QMutexLocker lock(&m_mutex_SocketW);

	QString strSocketError;
	QString strErrorString;
	CTcpSocketHelper tcpSocketHelper;

	strSocketError = tcpSocketHelper.getSocketError(nSocketError);
	strErrorString = m_pSocketHandle->errorString();

}


void CStockTcpServerActor::slotReadyRead()
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
		<<" "<<"slot:"<<" "<<"slotReadyRead";

	QMutexLocker lock(&m_mutex_SocketBuffer);	

	qint64 nBytesAvailable = 0;
	QDataStream readFromSocket(m_pSocketHandle);
	readFromSocket.setVersion(QDataStream::Qt_4_0);

	nBytesAvailable = m_pSocketHandle->bytesAvailable();
	if (nBytesAvailable > 0)
	{
		readFromSocket>>(*m_pSocketBuffer);
	}


	{
		MYLOG4CPP_DEBUG<<" "
			<<" "<<"class:"<<" "<<"CStockTcpServerActor"
			<<" "<<"fun:"<<" "<<"slotReadyRead"
			<<" "<<"emit:"<<" "<<"signalProcessRecvBuffer";

		emit signalProcessRecvBuffer();
	}

	
}
void CStockTcpServerActor::writeAck()
{
	QMutexLocker lock(&m_mutex_SocketW);

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
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
		<<" "<<"slot:"<<" "<<"slotDisconnected";

	MYLOG4CPP_INFO<<"client Disconnected"
		<<" "<<"m_nHandle="<<m_nSocketHandle
		<<" "<<"m_strlocalAddress="<<m_strlocalAddress
		<<" "<<"m_nLocalPort="<<m_nLocalPort
		<<" "<<"m_strPeerAddress="<<m_strPeerAddress
		<<" "<<"m_strPeerName="<<m_strPeerName
		<<" "<<"m_nPeerPort="<<m_nPeerPort;

	{
		MYLOG4CPP_DEBUG<<" "
			<<" "<<"class:"<<" "<<"CStockTcpServerActor"
			<<" "<<"fun:"<<" "<<"slotDisconnected"
			<<" "<<"emit:"<<" "<<"signalDeleteMe";

		emit signalDeleteMe();
	}
}

void CStockTcpServerActor::slotProcessRecvBuffer()
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
		<<" "<<"slot:"<<" "<<"slotProcessRecvBuffer";

	QMutexLocker lock(&m_mutex_SocketBuffer);	
	qint32 nBytesInByteArray = 0;
	QDataStream readSocketBuffer(*m_pSocketBuffer);
	qint32 nMessageLength = 0;
	qint32 nReadRawData = 0;
	char* pDataTmp = NULL;
	QByteArray* pMessage = NULL;

	nBytesInByteArray = m_pSocketBuffer->size();
	//check header  4bytes
	if (nBytesInByteArray < sizeof(qint32))
	{
		return;
	}

	//get message length 4bytes
	nMessageLength = 0;
	readSocketBuffer>>nMessageLength;
	
	//check recv one message
	nBytesInByteArray -= sizeof(qint32);
	if (nBytesInByteArray < nMessageLength)
	{
		return;
	}

	pDataTmp = new char[nMessageLength];
	memset(pDataTmp, 0, nMessageLength);
	nReadRawData = readSocketBuffer.readRawData(pDataTmp, nMessageLength);

	if (nReadRawData == nMessageLength)
	{
		pMessage = new QByteArray((const char*)pDataTmp, nMessageLength);
		m_pSocketBuffer->remove(0, nMessageLength + sizeof(qint32));
	}
	else
	{
		MYLOG4CPP_ERROR<<"nReadRawData="<<nReadRawData
			<<" "<<"not nMessageLength="<<nMessageLength;
	}

	if (NULL != pDataTmp)
	{
		delete[] pDataTmp;
		pDataTmp = NULL;
	}

	if (NULL != pMessage)
	{
		MYLOG4CPP_DEBUG<<" "
			<<" "<<"class:"<<" "<<"CStockTcpServerActor"
			<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
			<<" "<<"emit:"<<" "<<"signalProcessMessage"
			<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;
		emit signalProcessMessage(pMessage);
		pMessage = NULL;
	}

	{
		MYLOG4CPP_DEBUG<<" "
			<<" "<<"class:"<<" "<<"CStockTcpServerActor"
			<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
			<<" "<<"emit:"<<" "<<"signalProcessRecvBuffer";

		emit signalProcessRecvBuffer();
	}
}

void CStockTcpServerActor::slotProcessMessage( QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
		<<" "<<"slot:"<<" "<<"slotProcessMessage"
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;

	QDataStream readMessageBuffer(*pMessage);
	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	QString strReqUUID;//37
	QString strACKUUID;//37
	qint32 nDataType = 0;//CTcpComProtocol::EDataType

	QString strUserName;//65
	QString strPassword;//65

	readMessageBuffer>>nMessageType;
	readMessageBuffer>>strReqUUID;
	readMessageBuffer>>strACKUUID;
	readMessageBuffer>>nDataType;

	readMessageBuffer>>strUserName;
	readMessageBuffer>>strPassword;


	if (NULL != pMessage)
	{
		delete pMessage;
		pMessage = NULL;
	}
}



