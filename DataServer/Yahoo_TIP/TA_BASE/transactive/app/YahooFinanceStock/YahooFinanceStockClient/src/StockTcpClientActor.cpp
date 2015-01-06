#include "StockTcpClientActor.h"

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtSql/QtSql>
#include <QtNetwork/QtNetwork>

#include "BaseException.h"
#include "Log4cppLogger.h"

#include "TcpSocketHelper.h"
#include "MsgManager.h"
#include "SocketInfo.h"

#include "ReqLogin.h"
#include "AckLogin.h"
#include "ReqLogout.h"
#include "AckLogout.h"


CStockTcpClientActor::CStockTcpClientActor(qint32 handle, QObject* parent/*=0*/ )
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

CStockTcpClientActor::~CStockTcpClientActor()
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


void CStockTcpClientActor::slotError(QAbstractSocket::SocketError nSocketError)
{
	QMutexLocker lock(&m_mutex_SocketW);

	QString strSocketError;
	QString strErrorString;
	QString strSocketState;

	strSocketError = CTcpSocketHelper::getStringValue(nSocketError);
	strErrorString = m_pSocketHandle->errorString();
	strSocketState = CTcpSocketHelper::getStringValue(m_pSocketHandle->state());

	if (QAbstractSocket::ConnectionRefusedError == nSocketError)
	{
		MYLOG4CPP_DEBUG<<"m_strID="<<m_pSocketInfo->m_strID
			<<" "<<"strSocketError="<<strSocketError
			<<" "<<"strErrorString="<<strErrorString
			<<" "<<"strSocketState="<<strSocketState;
	}
	else if (QAbstractSocket::SocketTimeoutError == nSocketError)
	{
		//do nothing
	}
	else 
	{
		m_toTerminate = true;
		MYLOG4CPP_DEBUG<<"m_strID="<<m_pSocketInfo->m_strID
			<<" "<<"strSocketError="<<strSocketError
			<<" "<<"strErrorString="<<strErrorString
			<<" "<<"set m_toTerminate="<<m_toTerminate;
	}

}




void CStockTcpClientActor::slotDisconnected()
{
	MYLOG4CPP_DEBUG<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"class:"<<" "<<"CStockTcpServerActor"
		<<" "<<"slot:"<<" "<<"slotDisconnected"
		<<" "<<"set m_toTerminate="<<m_toTerminate;

	m_toTerminate = true;
}


void CStockTcpClientActor::slotWriteMessage(QByteArray* pByteArray)
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

void CStockTcpClientActor::slotReadyRead()
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



void CStockTcpClientActor::run()
{
	{
		QMutexLocker lock(&m_mutex_SocketW);
		m_pSocketHandle = new QTcpSocket();
		m_pSocketInfo = new CSocketInfo();
	}
	//
	QObject::connect(m_pSocketHandle, SIGNAL(connected()), this, SLOT(slotConnected()), Qt::AutoConnection);
	QObject::connect(m_pSocketHandle, SIGNAL(disconnected()), this, SLOT(slotDisconnected()), Qt::AutoConnection);
	//QObject::connect(m_pSocketHandle, SIGNAL(readyRead()), this, SLOT(slotReadyRead()), Qt::BlockingQueuedConnection);//Qt::AutoConnection
	QObject::connect(m_pSocketHandle, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)), Qt::AutoConnection);
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

void CStockTcpClientActor::terminate()
{
	m_toTerminate = true;
	while (WORK_STATE_END != m_WorkerState)
	{
		this->msleep(10);
	}
}


int CStockTcpClientActor::_ProcessUserTerminate()
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

bool CStockTcpClientActor::isFinishWork()
{
	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CStockTcpClientActor::_ThreadJob()
{
	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		m_nThreadJobState = JobState_ConnectToServer;
		break;
	case JobState_ConnectToServer:
		_Do_JobState_ConnectToServer();
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

void CStockTcpClientActor::join()
{
	while (CStockTcpClientActor::JobState_End != m_nThreadJobState)
	{
		this->msleep(10);
	}
}

void CStockTcpClientActor::_Do_JobState_ConnectToServer()
{
	bool bConnected = false;
	//QString strServerIP = "192.168.253.130";//192.168.1.3
	QString strServerIP = "127.0.0.1";
	quint16 nServerPort = 5000;



	{
		QMutexLocker lock(&m_mutex_SocketBuffer);	
		m_pSocketBuffer->clear();
	}

	{

		QMutexLocker lock(&m_mutex_SocketW);
		//Aborts the current connection and resets the socket.
		m_pSocketHandle->abort();

		MYLOG4CPP_INFO<<"begin connect to server"
			<<" "<<"strServerIP="<<strServerIP
			<<" "<<"nServerPort="<<nServerPort;

		m_pSocketHandle->connectToHost(strServerIP, nServerPort);
		//只有使用waitForConnected()后,QTcpSocket才真正尝试连接服务器，并返回是否连接的结果
		//bConnected = m_pSocketHandle->waitForConnected();
		bConnected = m_pSocketHandle->waitForConnected(1000*10);

		MYLOG4CPP_INFO<<"end connect to server"
			<<" "<<"strServerIP="<<strServerIP
			<<" "<<"nServerPort="<<nServerPort
			<<" "<<"bConnected="<<bConnected;
	}


	if (false == bConnected)
	{
		m_nThreadJobState = JobState_ConnectToServer;
	}
	else
	{
		m_pSocketInfo->setValue(m_pSocketHandle);
		m_pSocketInfo->logInfo(__FILE__, __LINE__);
		send_login_req();

		m_nThreadJobState = JobState_TryRecvData;
	}


}

void CStockTcpClientActor::_Do_JobState_TryRecvData()
{
	bool bWaitForReadyRead = false;
	QAbstractSocket::SocketState nSocketStateValue = QAbstractSocket::UnconnectedState;
	nSocketStateValue = m_pSocketHandle->state();
	if (QAbstractSocket::ConnectedState != nSocketStateValue)
	{
		m_nThreadJobState = JobState_ConnectToServer;
		return;
	}
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


void CStockTcpClientActor::_Do_JobState_ProcessRecvData()
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




void CStockTcpClientActor::disConnectToServer()
{
	QMutexLocker lock(&m_mutex_SocketW);

	MYLOG4CPP_INFO<<" "<<"m_strID="<<m_pSocketInfo->m_strID
		<<" "<<"disConnectToServer";


	if (NULL != m_pSocketHandle)
	{
		//m_pSocketHandle->close();
		m_pSocketHandle->disconnectFromHost();
		m_pSocketHandle->waitForDisconnected();
		delete m_pSocketHandle;
		m_pSocketHandle = NULL;
	}

}

void CStockTcpClientActor::send_login_req()
{
	MYLOG4CPP_INFO<<"send_login_req";

	CReqLogin* pReqLogin = NULL;
	pReqLogin = new CReqLogin();

	pReqLogin->m_strReqUUID = CTcpComProtocol::getUUID();
	pReqLogin->m_strUserName = "UserName";
	pReqLogin->m_strPassword = "Password";
	pReqLogin->logInfo(__FILE__, __LINE__);

	slotWriteMessage(pReqLogin->getMessage());

	if (NULL != pReqLogin)
	{
		delete pReqLogin;
		pReqLogin= NULL;
	}
}

void CStockTcpClientActor::slotConnected()
{
	QString strSocketState;
	strSocketState = CTcpSocketHelper::getStringValue(m_pSocketHandle->state());

	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CStockTcpClientActor"
		<<" "<<"slot:"<<" "<<"slotConnected"
		<<" "<<"strSocketState="<<strSocketState;

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


