#ifndef __CLASS_DATA_WORKER__HH__
#define __CLASS_DATA_WORKER__HH__

#include "MyQtThread.h"
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QList>

class CMyTradeClient;
class CReqData;


class CDataWorker : public CMyQtThread
{
	Q_OBJECT
private:
	enum EReqWorkerState
	{
		ReqWokerState_Begin,
		ReqWokerState_CheckProcessReq,

		ReqWokerState_End,
	};

	enum EDataWorkerState
	{
		DataWorkerState_Begin,
		
		DataWorkerState_UpdateStockRealTimeInfo,

		DataWorkerState_End,
	};

public:
	CDataWorker(void);
	~CDataWorker(void);

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
	EDataWorkerState m_nDataWorkerState;


public:
	void setDataProcessHandle(CMyTradeClient* pHandle);
	void append_req(CReqData* pReqData);
private:
	void _Free_LstReqData();
	void _DoJob_CheckProcessReq();
	void _DoJob_UpdateStockRealTimeInfo();
	CReqData* _TryGet_ReqData();
	void _ProcessReq_DownLoadStockID();
	void _ProcessReq_SubscribeMarketData();
	void _ProcessReq_UnSubscribeMarketData();
	void _ProcessReq_DownloadHistoryData();
private:
	CMyTradeClient* m_pMyTradeClientRef;

	QMutex m_mutex_LstReqData;
	QList<CReqData*> m_LstReqData;

	QMutex m_mutex_CurrentReqData;
	CReqData* m_pCurrentReqData;
};


#endif //__CLASS_DATA_WORKER__HH__


