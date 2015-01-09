#ifndef __CLASS_TCP_SERVER_WORKER_H__
#define __CLASS_TCP_SERVER_WORKER_H__

#include "MyQtThread.h"

class CStockTcpServer;
class CServerDistributeTaskWorker;

class CTcpServerWorker : public CMyQtThread
{
    Q_OBJECT
public:
    CTcpServerWorker(quint16 nListenPort, QObject* parent=0);
	~CTcpServerWorker();
public:
	virtual void run();	
	virtual void terminate();
signals:

private slots:

private:
	quint16 m_nListenPort;
	CStockTcpServer* m_pStockTcpServer;
	CServerDistributeTaskWorker* m_pServerDistributeTaskWorker;

};

#endif//__CLASS_TCP_SERVER_WORKER_H__
