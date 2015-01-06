#ifndef __CLASS_STOCK_TCP_CLIENT_ACTOR_H__
#define __CLASS_STOCK_TCP_CLIENT_ACTOR_H__

#include "MyQtThread.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtNetwork/QTcpSocket>

class CMsgManager;
class CSocketInfo;

class CStockTcpClientActor : public CMyQtThread
{
    Q_OBJECT
public:
	enum EThreadTcpJobState
	{
		TcpJobState_Begin,
		TcpJobState_ConnectToServer,
		TcpJobState_WaitConnectedToServer,
		TcpJobState_TryRecvData,
		TcpJobState_ProcessRecvData,
		TcpJobState_End,
	};
	enum EThreadJobState
	{
		JobState_Begin,
		JobState_ConnectToServer,
		JobState_TryRecvData,
		JobState_ProcessRecvData,
		JobState_End,
	};
public:
    CStockTcpClientActor(qint32 handle, QObject* parent=0);
	~CStockTcpClientActor();
public:
	virtual void run();	
	virtual void terminate();
	virtual void join();
	bool  isFinishWork();
private:
	void _ThreadJob();
	int	 _ProcessUserTerminate();  
private:
	bool	m_toTerminate;
	EThreadJobState  m_nThreadJobState;
//////////////////////////////////////////////////////////////////////////
signals:
	void signalDeleteConnection(CStockTcpClientActor* pActor);
	void signalProcessMessage(QByteArray* pMessage);
private slots:
	void slotError(QAbstractSocket::SocketError nSocketError);
	void slotReadyRead();
	void slotDisconnected();
public slots:
	void slotWriteMessage(QByteArray* pByteArray);
	void slotConnected();

private:
	void _Do_JobState_ConnectToServer();
	void _Do_JobState_TryRecvData();
	void _Do_JobState_ProcessRecvData();
	void send_login_req();
	void disConnectToServer();
private:
	QMutex m_mutex_SocketW;
    qint32 m_nSocketHandle;
	CSocketInfo* m_pSocketInfo;
	QTcpSocket* m_pSocketHandle;

	QMutex m_mutex_SocketBuffer;
	QByteArray* m_pSocketBuffer;
private:
	CMsgManager* m_pMsgManager;
};

#endif//__CLASS_STOCK_TCP_CLIENT_ACTOR_H__
