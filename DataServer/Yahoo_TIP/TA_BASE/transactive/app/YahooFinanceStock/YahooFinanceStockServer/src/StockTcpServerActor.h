#ifndef __CLASS_STOCK_TCP_SERVER_ACTOR_H__
#define __CLASS_STOCK_TCP_SERVER_ACTOR_H__

#include "MyQtThread.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <QtNetwork/QTcpSocket>

class CMsgManager;
class CSocketInfo;

class CStockTcpServerActor : public CMyQtThread
{
    Q_OBJECT
public:
	enum EThreadJobState
	{
		JobState_Begin,
		JobState_TryRecvData,
		JobState_ProcessRecvData,
		JobState_End,
	};
public:
    CStockTcpServerActor(qint32 handle, QObject* parent=0);
	~CStockTcpServerActor();
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
	void signalDeleteConnection(CStockTcpServerActor* pActor);
	void signalProcessMessage(QByteArray* pMessage);
private slots:
	void slotError(QAbstractSocket::SocketError nSocketError);
	void slotReadyRead();
	void slotDisconnected();
public slots:
	void slotWriteMessage(QByteArray* pByteArray);
private:
	void _Do_JobState_TryRecvData();
	void _Do_JobState_ProcessRecvData();

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

#endif//__CLASS_STOCK_TCP_SERVER_ACTOR_H__
