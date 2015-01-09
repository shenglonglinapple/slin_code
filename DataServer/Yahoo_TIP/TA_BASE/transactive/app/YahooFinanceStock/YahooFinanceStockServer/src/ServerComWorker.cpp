#include "ServerComWorker.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "TcpSocketHelper.h"
#include "SocketInfo.h"

CServerComWorker::CServerComWorker(qint32 handle, QObject* parent/*=0*/ )
{
	m_nSocketHandle = 0;
	m_pSocketInfo = NULL;
	m_pSocketHandle = NULL;
	m_pSocketBuffer = NULL;

	m_WorkerState = WORK_STATE_BEGIN;

	m_nSocketHandle = handle;

	{
		QMutexLocker lock(&m_mutex_SocketBuffer);	
		m_pSocketBuffer = new QByteArray();
	}

	QObject::connect(this, SIGNAL(signalProcessRecvData(QByteArray*)), this, SLOT(slotProcessRecvData(QByteArray*)), Qt::AutoConnection);
	QObject::connect(this, SIGNAL(signalSendMessage(qint32, QByteArray*)), this, SLOT(slotSendMessage(qint32, QByteArray*)), Qt::AutoConnection);

}

CServerComWorker::~CServerComWorker()
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

}


void CServerComWorker::slotError(QAbstractSocket::SocketError nSocketError)
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
	else 
	{
		MYLOG4CPP_DEBUG<<"m_strID="<<m_pSocketInfo->m_strID
			<<" "<<"strSocketError="<<strSocketError
			<<" "<<"strErrorString="<<strErrorString
			<<" "<<"strSocketState="<<strSocketState;
	}
}




void CServerComWorker::slotDisconnected()
{
	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"class:"<<" "<<"CServerComWorker"
		<<" "<<"slot:"<<" "<<"slotDisconnected";

	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"class:"<<" "<<"CServerComWorker"
		<<" "<<"fun:"<<" "<<"slotDisconnected"
		<<" "<<"emit:"<<" "<<"signalDisconnected"
		<<" "<<"param:"<<"m_nSocketHandle="<<m_nSocketHandle;

	emit signalDisconnected(m_nSocketHandle);
}


void CServerComWorker::slotSendMessage(qint32 handle, QByteArray* pMessage)
{
	if (m_nSocketHandle != handle)
	{
		return;
	}
	quint32 nMessageLenth = 0;
	QByteArray* pMessageLength = NULL;
	pMessageLength = new QByteArray();
	QDataStream writeToMessageLength(pMessageLength, QIODevice::WriteOnly);
	writeToMessageLength.setVersion(QDataStream::Qt_4_0);
	nMessageLenth = pMessage->size();
	writeToMessageLength<<(quint32)nMessageLenth;

	QMutexLocker lock(&m_mutex_SocketW);
	m_pSocketHandle->write(*pMessageLength);
	m_pSocketHandle->write(*pMessage);
	//m_pSocketHandle->waitForBytesWritten();


	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"slotSendMessage"
		<<" "<<"pMessageLength->size="<<pMessageLength->size()
		<<" "<<"pMessage->size="<<pMessage->size()
		<<" "<<"Total write size="<<pMessageLength->size() + pMessage->size();


	if (NULL != pMessageLength)
	{
		delete pMessageLength;
		pMessageLength = NULL;
	}
	if (NULL != pMessage)
	{
		delete pMessage;
		pMessage = NULL;
	}


}

void CServerComWorker::slotReadyRead()
{
	qint64 nBytesAvailable = 0;
	QByteArray* pData = NULL;

	nBytesAvailable = m_pSocketHandle->bytesAvailable();
	pData = new QByteArray((qint32)nBytesAvailable, 0);
	*pData = m_pSocketHandle->readAll();

	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"slotReadyRead"
		<<" "<<"pData->size="<<pData->size();


	emit signalProcessRecvData(pData);
}

void CServerComWorker::slotProcessRecvData(QByteArray* pData)
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
			<<" "<<"class:"<<" "<<"CServerComWorker"
			<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
			<<" "<<"emit:"<<" "<<"signalRecvMessage"
			<<" "<<"param:"<<" "<<"handle="<<m_nSocketHandle
			<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;
		emit signalRecvMessage(m_nSocketHandle, pMessage);
		pMessage = NULL;
	}

	emit signalProcessRecvData(NULL);
}




void CServerComWorker::run()
{
	MYLOG4CPP_DEBUG<<"CServerComWorker::run()";

	{
		QMutexLocker lock(&m_mutex_SocketW);
		m_pSocketHandle = new QTcpSocket();
		m_pSocketInfo = new CSocketInfo();
	}
	//
	QObject::connect(m_pSocketHandle, SIGNAL(disconnected()), this, SLOT(slotDisconnected()), Qt::AutoConnection);
	QObject::connect(m_pSocketHandle, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::AutoConnection);//Qt::AutoConnection Qt::BlockingQueuedConnection
	QObject::connect(m_pSocketHandle, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)), Qt::AutoConnection);
	//
	if (false == m_pSocketHandle->setSocketDescriptor(m_nSocketHandle))
	{
		throw CBaseException(__FILE__, __LINE__, m_pSocketHandle->errorString());
	}
	m_pSocketInfo->setValue(m_pSocketHandle);
	m_pSocketInfo->logInfo(__FILE__, __LINE__);


	m_WorkerState = WORK_STATE_BEGIN;
	m_WorkerState = WORK_STATE_WORKING;

	//QThread::exec() waits until QThread::exit() called
	exec();


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

}

void CServerComWorker::terminate()
{
	return;
}

void CServerComWorker::sendMessage( qint32 handle, QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CServerComWorker"
		<<" "<<"fun:"<<" "<<"sendMessage"
		<<" "<<"emit:"<<" "<<"signalSendMessage"
		<<" "<<"param:"<<" "<<"handle="<<handle
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;

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


