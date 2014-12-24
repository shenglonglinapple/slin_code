#ifndef __CLASS_SERVER_PROCESS_REQUEST_WORKER__HH__
#define __CLASS_SERVER_PROCESS_REQUEST_WORKER__HH__

#include "MyQtThread.h"
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QList>

class CMyTradeClient;
class CReqData;

class CServerProcessRequestWorker : public CMyQtThread
{
	Q_OBJECT
private:
	enum EReqWorkerState
	{
		ReqWokerState_Begin,
		ReqWokerState_CheckProcessReq,

		ReqWokerState_End,
	};

public:
	CServerProcessRequestWorker(void);
	~CServerProcessRequestWorker(void);

public:
	virtual void run();	
	virtual void terminate();
	bool  isFinishWork();
private:
	void _ThreadJob();
	int	 _ProcessUserTerminate();  
private:
	bool	m_toTerminate;
	EReqWorkerState  m_nReqWorkerState;

public:
	void setDataProcessHandle(const CMyTradeClient* pHandle);
	void append_req(CReqData* pReqData);
private:
	void _Free_LstReqData();
	void _DoJob_CheckProcessReq();
	CReqData* _TryGet_ReqData();
	void _ProcessReq_DownLoadStockID();
	void _ProcessReq_SubscribeMarketData();
	void _ProcessReq_UnSubscribeMarketData();
	void _ProcessReq_DownloadHistoryData();
	void _ProcessReq_BuyMarket();
	void _ProcessReq_SellMarket();
private:

	QMutex m_mutex_LstReqData;
	QList<CReqData*> m_LstReqData;

	QMutex m_mutex_CurrentReqData;
	CReqData* m_pCurrentReqData;
};


#endif //__CLASS_SERVER_PROCESS_REQUEST_WORKER__HH__


