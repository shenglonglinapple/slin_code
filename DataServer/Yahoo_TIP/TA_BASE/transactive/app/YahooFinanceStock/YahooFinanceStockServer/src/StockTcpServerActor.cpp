#include "StockTcpServerActor.h"

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtSql/QtSql>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "TcpSocketHelper.h"
#include "MsgManager.h"

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
	m_pMsgManager = NULL;


	{
		QMutexLocker lock(&m_mutex_SocketW);
		m_nSocketHandle = handle;
		m_pSocketHandle = new QTcpSocket();
	}

	{
		QMutexLocker lock(&m_mutex_SocketBuffer);	
		m_pSocketBuffer = new QByteArray();
	}

	m_pMsgManager = new CMsgManager(this);

	//
	QObject::connect(m_pSocketHandle, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
	QObject::connect(m_pSocketHandle, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
	QObject::connect(m_pSocketHandle, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
	//
	QObject::connect(this, SIGNAL(signalDeleteMe()), this, SLOT(deleteLater()));
	//
	QObject::connect(this, SIGNAL(signalProcessMessage(QByteArray*)), m_pMsgManager, SLOT(slotProcessMessage(QByteArray*)));
	QObject::connect(m_pMsgManager, SIGNAL(signalWriteMessage(QByteArray*)), this, SLOT(slotWriteMessage(QByteArray*)));



	//
	if (false == m_pSocketHandle->setSocketDescriptor(m_nSocketHandle))
	{
		throw CBaseException(__FILE__, __LINE__, m_pSocketHandle->errorString());
	}
	_GetSocketInfo();
}

CStockTcpServerActor::~CStockTcpServerActor()
{

	if (NULL != m_pMsgManager)
	{
		delete m_pMsgManager;
		m_pMsgManager = NULL;
	}
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
			//m_pSocketHandle->waitForDisconnected();
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
		<<" "<<"m_nSocketHandle="<<m_nSocketHandle
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
		<<" "<<"slot:"<<" "<<"slotError";

	QMutexLocker lock(&m_mutex_SocketW);

	QString strSocketError;
	QString strErrorString;
	CTcpSocketHelper tcpSocketHelper;

	strSocketError = tcpSocketHelper.getSocketError(nSocketError);
	strErrorString = m_pSocketHandle->errorString();

	MYLOG4CPP_DEBUG<<"strSocketError="<<strSocketError
		<<" "<<"strErrorString="<<strErrorString;
}


void CStockTcpServerActor::slotReadyRead()
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"slot:"<<" "<<"slotReadyRead";

	QMutexLocker lock(&m_mutex_SocketBuffer);	

	qint64 nBytesAvailable = 0;
	QByteArray blockTmp;

	nBytesAvailable = m_pSocketHandle->bytesAvailable();
	blockTmp = m_pSocketHandle->readAll();
	MYLOG4CPP_DEBUG<<"CStockTcpServerActor::slotReadyRead"
		<<" "<<"nBytesAvailable="<<nBytesAvailable;

	if (nBytesAvailable > 0)
	{
		m_pSocketBuffer->append(blockTmp);
		MYLOG4CPP_DEBUG<<"CStockTcpServerActor::slotReadyRead"
			<<" "<<"m_pSocketBuffer->size="<<m_pSocketBuffer->size();

	}

	_ProcessRecvBuffer();
	
}

void CStockTcpServerActor::slotWriteMessage(QByteArray* pByteArray)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"slot:"<<" "<<"slotWriteMessage";

	quint32 nMessageLenth = 0;
	QByteArray* pMessage = NULL;
	pMessage = new QByteArray();
	QDataStream writeToMessage(pMessage, QIODevice::WriteOnly);
	writeToMessage.setVersion(QDataStream::Qt_4_0);

	nMessageLenth = pByteArray->size();
	writeToMessage<<(quint32)nMessageLenth;
	pMessage->append(*pByteArray);

	if (NULL != pByteArray)
	{
		delete pByteArray;
		pByteArray = NULL;
	}


	QMutexLocker lock(&m_mutex_SocketW);

	m_pSocketHandle->write(*pMessage);
	m_pSocketHandle->waitForBytesWritten();
	if (NULL != pMessage)
	{
		delete pMessage;
		pMessage = NULL;
	}


}


void CStockTcpServerActor::slotDisconnected()
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"slot:"<<" "<<"slotDisconnected";

	MYLOG4CPP_INFO<<"client Disconnected"
		<<" "<<"m_nSocketHandle="<<m_nSocketHandle
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

void CStockTcpServerActor::_ProcessRecvBuffer()
{
	qint32 nBytesInByteArray = 0;
	QDataStream readSocketBuffer(*m_pSocketBuffer);
	readSocketBuffer.setVersion(QDataStream::Qt_4_0);

	qint32 nMessageLength = 0;
	qint32 nReadRawData = 0;
	char* pDataTmp = NULL;
	QByteArray* pMessage = NULL;

	readSocketBuffer.device()->seek(0);

	nBytesInByteArray = m_pSocketBuffer->size();
	MYLOG4CPP_DEBUG<<"CStockTcpServerActor::_ProcessRecvBuffer"
		<<" "<<"nBytesInByteArray="<<nBytesInByteArray;

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

	_ProcessRecvBuffer();
}




