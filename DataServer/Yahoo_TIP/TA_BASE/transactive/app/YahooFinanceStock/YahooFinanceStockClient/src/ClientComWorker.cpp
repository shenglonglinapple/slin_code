#include "ClientComWorker.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "TcpSocketHelper.h"
#include "SocketInfo.h"



CClientComWorker::CClientComWorker(const QString& strServerIP, quint16 nServerPort, QObject* parent/*=0*/ )
{
	m_strServerIP.clear();
	m_nServerPort = 0;
	m_pSocketInfo = NULL;
	m_pSocketHandle = NULL;
	m_pSocketBuffer = NULL;
	m_nHandle = 0;

	m_WorkerState = WORK_STATE_BEGIN;

	m_strServerIP = strServerIP;
	m_nServerPort = nServerPort;

	{
		QMutexLocker lock(&m_mutex_SocketBuffer);	
		m_pSocketBuffer = new QByteArray();
	}

	QObject::connect(this, SIGNAL(signalProcessRecvData(QByteArray*)), this, SLOT(slotProcessRecvData(QByteArray*)), Qt::AutoConnection);
	QObject::connect(this, SIGNAL(signalSendMessage(qint32, QByteArray*)), this, SLOT(slotSendMessage(qint32, QByteArray*)), Qt::AutoConnection);

}

CClientComWorker::~CClientComWorker()
{	
	//
	{
		QMutexLocker lock(&m_mutex_SocketBuffer);	
		if (NULL != m_pSocketBuffer)
		{
			delete m_pSocketBuffer;
			m_pSocketBuffer = NULL;
		}
	}

	m_nHandle = 0;
}


void CClientComWorker::slotError(QAbstractSocket::SocketError nSocketError)
{
	QString strSocketError;
	QString strErrorString;
	QString strSocketState;


	strSocketError = CTcpSocketHelper::getStringValue(nSocketError);
	strErrorString = m_pSocketHandle->errorString();
	strSocketState = CTcpSocketHelper::getStringValue(m_pSocketHandle->state());


	if (QAbstractSocket::SocketTimeoutError == nSocketError)
	{
		//do nothing
	}
	else if (QAbstractSocket::ConnectionRefusedError == nSocketError
		|| QAbstractSocket::RemoteHostClosedError == nSocketError)
	{
		MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
			<<" "<<"class:"<<" "<<"CClientComWorker"
			<<" "<<"fun:"<<" "<<"slotError"
			<<" "<<"emit signalDisconnected()"
			<<" "<<"param:"<<" "<<"m_nHandle="<<m_nHandle;

		emit signalDisconnected(m_nHandle);
	}
	else 
	{
		MYLOG4CPP_DEBUG<<"m_strID="<<m_pSocketInfo->m_strID
			<<" "<<"strSocketError="<<strSocketError
			<<" "<<"strErrorString="<<strErrorString
			<<" "<<"strSocketState="<<strSocketState;
	}
}




void CClientComWorker::slotDisconnected()
{
	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"class:"<<" "<<"CClientComWorker"
		<<" "<<"slot:"<<" "<<"slotDisconnected";

	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"class:"<<" "<<"CClientComWorker"
		<<" "<<"fun:"<<" "<<"slotDisconnected"
		<<" "<<"emit signalDisconnected()"
		<<" "<<"param:"<<" "<<"m_nHandle="<<m_nHandle;

	emit signalDisconnected(m_nHandle);
}


void CClientComWorker::slotSendMessage(qint32 handle, QByteArray* pByteArray)
{
	if (m_nHandle != handle)
	{
		return;
	}
	quint32 nMessageLenth = 0;
	QByteArray* pMessageLength = NULL;
	pMessageLength = new QByteArray();
	QDataStream writeToMessageLength(pMessageLength, QIODevice::WriteOnly);
	writeToMessageLength.setVersion(QDataStream::Qt_4_0);
	nMessageLenth = pByteArray->size();
	writeToMessageLength<<(quint32)nMessageLenth;

	QMutexLocker lock(&m_mutex_SocketW);
	m_pSocketHandle->write(*pMessageLength);
	m_pSocketHandle->write(*pByteArray);
	//m_pSocketHandle->waitForBytesWritten();


	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"slotSendMessage"
		<<" "<<"m_nHandle="<<m_nHandle
		<<" "<<"pMessageLength->size="<<pMessageLength->size()
		<<" "<<"pByteArray->size="<<pByteArray->size()
		<<" "<<"Total write size="<<pMessageLength->size() + pByteArray->size();


	if (NULL != pMessageLength)
	{
		delete pMessageLength;
		pMessageLength = NULL;
	}
	if (NULL != pByteArray)
	{
		delete pByteArray;
		pByteArray = NULL;
	}


}

void CClientComWorker::slotReadyRead()
{
	qint64 nBytesAvailable = 0;
	QByteArray* pData = NULL;

	nBytesAvailable = m_pSocketHandle->bytesAvailable();
	pData = new QByteArray((qint32)nBytesAvailable, 0);
	*pData = m_pSocketHandle->readAll();

	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"slotReadyRead"
		<<" "<<"m_nHandle="<<m_nHandle
		<<" "<<"pData->size="<<pData->size();


	emit signalProcessRecvData(pData);
}

void CClientComWorker::slotProcessRecvData(QByteArray* pData)
{
	qint32 nBytesInByteArray = 0;
	qint32 nMessageLength = 0;
	qint32 nReadRawData = 0;
	char* pDataTmp = NULL;
	QByteArray* pMessage = NULL;

	if (NULL != pData)
	{
		m_pSocketBuffer->append(*pData);
		MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
			<<" "<<"slotProcessRecvData"
			<<" "<<"m_nHandle="<<m_nHandle
			<<" "<<"pData->size="<<pData->size()
			<<" "<<"m_pSocketBuffer->size="<<m_pSocketBuffer->size();

		delete pData;
		pData = NULL;
	}


	QDataStream readSocketBuffer(*m_pSocketBuffer);
	readSocketBuffer.setVersion(QDataStream::Qt_4_0);
	readSocketBuffer.device()->seek(0);

	nBytesInByteArray = m_pSocketBuffer->size();
	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"slotProcessRecvData"
		<<" "<<"m_nHandle="<<m_nHandle
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
		MYLOG4CPP_ERROR<<" "<<"m_strID="<<m_pSocketInfo->m_strID
			<<" "<<"m_nHandle="<<m_nHandle
			<<" "<<"nReadRawData="<<nReadRawData
			<<" "<<"not nMessageLength="<<nMessageLength;
	}

	if (NULL != pDataTmp)
	{
		delete[] pDataTmp;
		pDataTmp = NULL;
	}

	if (NULL != pMessage)
	{
		MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
			<<" "<<"class:"<<" "<<"CClientComWorker"
			<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
			<<" "<<"emit:"<<" "<<"signalProcessMessage"
			<<" "<<"param:"<<" "<<"m_nHandle="<<m_nHandle
			<<" "<<"param:"<<" "<<"pMessage=0x"<<pMessage;
		emit signalRecvMessage(m_nHandle, pMessage);
		pMessage = NULL;
	}

	emit signalProcessRecvData(NULL);
}


void CClientComWorker::slotConnected()
{
	QString strSocketState;
	strSocketState = CTcpSocketHelper::getStringValue(m_pSocketHandle->state());
	m_pSocketInfo->setValue(m_pSocketHandle);
	m_pSocketInfo->logInfo(__FILE__, __LINE__);
	m_nHandle = m_pSocketInfo->m_nSocketHandle;

	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CClientComWorker"
		<<" "<<"slot:"<<" "<<"slotConnected"
		<<" "<<"m_nHandle="<<m_nHandle
		<<" "<<"strSocketState="<<strSocketState;

	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"class:"<<" "<<"CClientComWorker"
		<<" "<<"fun:"<<" "<<"slotConnected"
		<<" "<<"emit signalConnected()"
		<<" "<<"param:"<<" "<<"m_nHandle="<<m_nHandle;

	emit signalConnected(m_nHandle);
}


void CClientComWorker::slotConnectToServer()
{
	bool bConnected = false;

	{
		QMutexLocker lock(&m_mutex_SocketBuffer);	
		m_pSocketBuffer->clear();
	}

	{

		QMutexLocker lock(&m_mutex_SocketW);
		//Aborts the current connection and resets the socket.
		m_pSocketHandle->abort();

		MYLOG4CPP_INFO<<"begin connect to server"
			<<" "<<"m_strServerIP="<<m_strServerIP
			<<" "<<"m_nServerPort="<<m_nServerPort;

		m_pSocketHandle->connectToHost(m_strServerIP, m_nServerPort);
		//只有使用waitForConnected()后,QTcpSocket才真正尝试连接服务器，并返回是否连接的结果
		//bConnected = m_pSocketHandle->waitForConnected();
		//bConnected = m_pSocketHandle->waitForConnected(1000*10);//not sleep here, why?
		
		MYLOG4CPP_INFO<<"end connect to server"
			<<" "<<"m_strServerIP="<<m_strServerIP
			<<" "<<"m_nServerPort="<<m_nServerPort
			<<" "<<"bConnected="<<bConnected;
	}



}

void CClientComWorker::run()
{
	MYLOG4CPP_DEBUG<<"CClientComWorker::run() begin";

	{
		QMutexLocker lock(&m_mutex_SocketW);
		m_pSocketHandle = new QTcpSocket();
		m_pSocketInfo = new CSocketInfo();
	}
	//
	QObject::connect(m_pSocketHandle, SIGNAL(connected()), this, SLOT(slotConnected()), Qt::AutoConnection);
	QObject::connect(m_pSocketHandle, SIGNAL(disconnected()), this, SLOT(slotDisconnected()), Qt::AutoConnection);
	QObject::connect(m_pSocketHandle, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::AutoConnection);//Qt::AutoConnection Qt::BlockingQueuedConnection
	QObject::connect(m_pSocketHandle, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)), Qt::AutoConnection);


	m_WorkerState = WORK_STATE_BEGIN;
	m_WorkerState = WORK_STATE_WORKING;

	//slotConnectToServer();
	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"class:"<<" "<<"CClientComWorker"
		<<" "<<"fun:"<<" "<<"run"
		<<" "<<"emit signalDisconnected()"
		<<" "<<"param:"<<" "<<"m_nHandle="<<m_nHandle;

	emit signalDisconnected(m_nHandle);

	MYLOG4CPP_DEBUG<<"CClientComWorker::run() exec() begin";

	//QThread::exec() waits until QThread::exit() called
	exec();

	MYLOG4CPP_DEBUG<<"CClientComWorker::run() exec() end";


	{
		QMutexLocker lock(&m_mutex_SocketW);
		if (NULL != m_pSocketHandle)
		{
			//m_pSocketHandle->waitForDisconnected();
			m_pSocketHandle->close();
			delete m_pSocketHandle;
			m_pSocketHandle = NULL;
		}
		if (NULL != m_pSocketInfo)
		{
			delete m_pSocketInfo;
			m_pSocketInfo = NULL;
		}
	}
	m_WorkerState = WORK_STATE_END;
	MYLOG4CPP_DEBUG<<"CClientComWorker::run() end";
}

void CClientComWorker::terminate()
{
	MYLOG4CPP_DEBUG<<" "<<"CClientComWorker::terminate() begin";

	MYLOG4CPP_DEBUG<<" "<<"CClientComWorker::terminate() end";
}

void CClientComWorker::sendMessage( qint32 handle, QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CClientComWorker"
		<<" "<<"fun:"<<" "<<"sendMessage"
		<<" "<<"emit:"<<" "<<"signalSendMessage"
		<<" "<<"param:"<<" "<<"handle="<<handle
		<<" "<<"param:"<<" "<<"pMessage=0x"<<pMessage;

	emit signalSendMessage(handle, pMessage);
}



/*

void CTestMyThreadManager::do_test_mythread_2()
{
	CSampleMyQtThread* pMyThreadTest = NULL;
	pMyThreadTest = new CSampleMyQtThread();

	pMyThreadTest->start();

	pMyThreadTest->join();
	pMyThreadTest->my_msleep(1000* 10);

	pMyThreadTest->terminateAndWait();

	delete pMyThreadTest;
	pMyThreadTest = NULL;
}
*/


