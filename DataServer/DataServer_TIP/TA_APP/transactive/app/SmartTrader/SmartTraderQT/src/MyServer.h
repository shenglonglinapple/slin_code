#ifndef __CLASS_MY_SERVER_HH__
#define __CLASS_MY_SERVER_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CDataWorker;
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
	void send_req(CReqData* pReqData);
	void setHandle(const CMyTradeClient* pHandleRef);

private:
	CDataWorker* m_pDataWorker;
	CDataRealTimeWorker* m_pDataRealTimeWorker;
	CDataProcessOrderWorker* m_pDataProcessOrderWorker;
};



#endif//__CLASS_MY_SERVER_HH__

