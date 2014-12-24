#ifndef __CLASS_MY_SERVER_HH__
#define __CLASS_MY_SERVER_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CServerProcessRequestWorker;
class CDataRealTimeWorker;
class CDataProcessOrderWorker;
class CMyTradeClient;
class CReqData;

class CMyServer
{
public:
	static CMyServer& getInstance();
	static void removeInstance();

private:
	static CMyServer* m_pInstance;
	static QMutex m_mutexInstance;
public:
	CMyServer();
	virtual ~CMyServer(void);
public:
	void recv_req(CReqData* pReqData);
	void setHandle(const CMyTradeClient* pHandleRef);

private:
	CServerProcessRequestWorker* m_pServerProcessRequestWorker;
	CDataRealTimeWorker* m_pDataRealTimeWorker;
	CDataProcessOrderWorker* m_pDataProcessOrderWorker;
};



#endif//__CLASS_MY_SERVER_HH__

