#include "StockTcpServerActor.h"

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtSql/QtSql>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "TcpSocketHelper.h"
#include "MsgManager.h"
#include "SocketInfo.h"

CStockTcpServerActor::CStockTcpServerActor(qint32 handle, QObject* parent/*=0*/ )
{
	m_nSocketHandle = 0;
	m_pSocketInfo = NULL;
	m_pSocketHandle = NULL;
	m_pSocketBuffer = NULL;
	m_pMsgManager = NULL;

	m_toTerminate = false;
	m_WorkerState = WORK_STATE_BEGIN;
	m_nThreadJobState = JobState_Begin;

	m_nSocketHandle = handle;

	{
		QMutexLocker lock(&m_mutex_SocketBuffer);	
		m_pSocketBuffer = new QByteArray();
	}
}

CStockTcpServerActor::~CStockTcpServerActor()
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


void CStockTcpServerActor::slotError(QAbstractSocket::SocketError nSocketError)
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"slot:"<<" "<<"slotError";

	QMutexLocker lock(&m_mutex_SocketW);

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
		m_toTerminate = true;
		MYLOG4CPP_DEBUG<<"m_strID="<<m_pSocketInfo->m_strID
			<<" "<<"strSocketError="<<strSocketError
			<<" "<<"strErrorString="<<strErrorString
			<<" "<<"strSocketState="<<strSocketState
			<<" "<<"set m_toTerminate="<<m_toTerminate;
	}
}




void CStockTcpServerActor::slotDisconnected()
{
	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"slot:"<<" "<<"slotDisconnected"
		<<" "<<"set m_toTerminate="<<m_toTerminate;

	m_toTerminate = true;
}


void CStockTcpServerActor::slotWriteMessage(QByteArray* pByteArray)
{
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
		<<" "<<"slotWriteMessage"
		<<" "<<"pMessageLength->size="<<pMessageLength->size()
		<<" "<<"pByteArray->size="<<pByteArray->size();


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

void CStockTcpServerActor::slotReadyRead()
{
	QMutexLocker lock(&m_mutex_SocketBuffer);	

	qint64 nBytesAvailable = 0;
	QByteArray blockTmp;

	nBytesAvailable = m_pSocketHandle->bytesAvailable();
	blockTmp = m_pSocketHandle->readAll();
	m_pSocketBuffer->append(blockTmp);

	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"slotReadyRead"
		<<" "<<"nBytesAvailable="<<nBytesAvailable
		<<" "<<"blockTmp.size="<<blockTmp.size()
		<<" "<<"m_pSocketBuffer.size="<<m_pSocketBuffer->size();	
}


void CStockTcpServerActor::run()
{
	{
		QMutexLocker lock(&m_mutex_SocketW);
		m_pSocketHandle = new QTcpSocket();
		m_pSocketInfo = new CSocketInfo();
	}
	//
	QObject::connect(m_pSocketHandle, SIGNAL(disconnected()), this, SLOT(slotDisconnected()), Qt::AutoConnection);
	//QObject::connect(m_pSocketHandle, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::BlockingQueuedConnection);//Qt::AutoConnection
	QObject::connect(m_pSocketHandle, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)), Qt::AutoConnection);
	//
	if (false == m_pSocketHandle->setSocketDescriptor(m_nSocketHandle))
	{
		throw CBaseException(__FILE__, __LINE__, m_pSocketHandle->errorString());
	}
	m_pSocketInfo->setValue(m_pSocketHandle);
	m_pSocketInfo->logInfo(__FILE__, __LINE__);
	//
	m_pMsgManager = new CMsgManager(this);
	QObject::connect(this, SIGNAL(signalProcessMessage(QByteArray*)), m_pMsgManager, SLOT(slotProcessMessage(QByteArray*)), Qt::AutoConnection);
	QObject::connect(m_pMsgManager, SIGNAL(signalWriteMessage(QByteArray*)), this, SLOT(slotWriteMessage(QByteArray*)), Qt::AutoConnection);



	m_WorkerState = WORK_STATE_BEGIN;
	m_nThreadJobState = JobState_Begin;

	m_WorkerState = WORK_STATE_WORKING;

	while (false == m_toTerminate)
	{
		_ThreadJob();
		//this->msleep(100);
	}

	_ProcessUserTerminate();
	m_WorkerState = WORK_STATE_END;

	//QThread::exec() waits until QThread::exit() called
	//exec();

	emit signalDeleteConnection(this);
}

void CStockTcpServerActor::terminate()
{
	m_toTerminate = true;
	while (WORK_STATE_END != m_WorkerState)
	{
		this->msleep(10);
	}
}


int CStockTcpServerActor::_ProcessUserTerminate()
{
	int nFunRes = 0;
	m_toTerminate = true;
	m_nThreadJobState = JobState_End;

	//
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

	if (NULL != m_pSocketInfo)
	{
		delete m_pSocketInfo;
		m_pSocketInfo = NULL;
	}
	if (NULL != m_pMsgManager)
	{
		delete m_pMsgManager;
		m_pMsgManager = NULL;
	}
	return nFunRes;
}

bool CStockTcpServerActor::isFinishWork()
{
	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CStockTcpServerActor::_ThreadJob()
{
	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		m_nThreadJobState = JobState_TryRecvData;
		break;
	case JobState_TryRecvData:
		_Do_JobState_TryRecvData();
		break;
	case JobState_ProcessRecvData:
		_Do_JobState_ProcessRecvData();
		break;
	case JobState_End:
		break;
	default:
		this->msleep(100);
		break;

	}//switch
}

void CStockTcpServerActor::join()
{
	while (CStockTcpServerActor::JobState_End != m_nThreadJobState)
	{
		this->msleep(10);
	}
}

void CStockTcpServerActor::_Do_JobState_TryRecvData()
{
	bool bWaitForReadyRead = false;
	
	bWaitForReadyRead = m_pSocketHandle->waitForReadyRead();//sleep here

	if (bWaitForReadyRead)
	{
		slotReadyRead();
		m_nThreadJobState = JobState_ProcessRecvData;
	}
	else
	{
		m_nThreadJobState = JobState_TryRecvData;
	}
	
}


void CStockTcpServerActor::_Do_JobState_ProcessRecvData()
{
	QMutexLocker lock(&m_mutex_SocketBuffer);	

	qint32 nBytesInByteArray = 0;
	QDataStream readSocketBuffer(*m_pSocketBuffer);
	readSocketBuffer.setVersion(QDataStream::Qt_4_0);

	qint32 nMessageLength = 0;
	qint32 nReadRawData = 0;
	char* pDataTmp = NULL;
	QByteArray* pMessage = NULL;

	readSocketBuffer.device()->seek(0);

	nBytesInByteArray = m_pSocketBuffer->size();
	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"_ProcessRecvBuffer"
		<<" "<<"nBytesInByteArray="<<nBytesInByteArray;

	//check header  4bytes
	if (nBytesInByteArray < sizeof(qint32))
	{
		m_nThreadJobState = JobState_TryRecvData;
		return;
	}

	//get message length 4bytes
	nMessageLength = 0;
	readSocketBuffer>>nMessageLength;

	//check recv one message
	nBytesInByteArray -= sizeof(qint32);
	if (nBytesInByteArray < nMessageLength)
	{
		m_nThreadJobState = JobState_TryRecvData;
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
			<<" "<<"class:"<<" "<<"CStockTcpServerActor"
			<<" "<<"fun:"<<" "<<"slotProcessRecvBuffer"
			<<" "<<"emit:"<<" "<<"signalProcessMessage"
			<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;
		emit signalProcessMessage(pMessage);
		pMessage = NULL;
	}

	m_nThreadJobState = JobState_ProcessRecvData;
	//_Do_JobState_ProcessRecvData();
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


