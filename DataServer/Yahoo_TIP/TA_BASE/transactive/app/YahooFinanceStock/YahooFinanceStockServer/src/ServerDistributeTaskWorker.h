#ifndef __CLASS_SERVER_DISTRIBUTE_TASK_WORKER_H__
#define __CLASS_SERVER_DISTRIBUTE_TASK_WORKER_H__

#include "MyQtThread.h"

class CStockTcpServer;
class CServerComManager;
class CMessageManager;

class CServerDistributeTaskWorker : public CMyQtThread
{
    Q_OBJECT
public:
    CServerDistributeTaskWorker(QObject* parent=0);
	~CServerDistributeTaskWorker();
public:
	virtual void run();	
	virtual void terminate();
signals:

public slots:
	void slotIncomingConnection( qint32 handle );

private:
	CServerComManager* m_pServerComManager;
	CMessageManager* m_pMessageManager;

};

#endif//__CLASS_SERVER_DISTRIBUTE_TASK_WORKER_H__
