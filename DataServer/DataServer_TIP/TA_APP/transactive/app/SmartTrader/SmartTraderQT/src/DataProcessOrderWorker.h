#ifndef __CLASS_DATA_PROCESS_ORDER_WORKER__HH__
#define __CLASS_DATA_PROCESS_ORDER_WORKER__HH__

#include "MyQtThread.h"
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QList>

class CQtTimeHelper;
class COrderData;

class CDataProcessOrderWorker : public CMyQtThread
{
	Q_OBJECT
public:
	enum EDataWorkerState
	{
		DataWorkerState_Begin,
		
		DataWorkerState_ProcessOrder,

		DataWorkerState_End,
	};

public:
	CDataProcessOrderWorker(void);
	~CDataProcessOrderWorker(void);

public:
	virtual void run();	
	virtual void terminate();
	bool  isFinishWork();
private:
	void _ThreadJob();
	int	 _ProcessUserTerminate();  
private:
	bool	m_toTerminate;
	EDataWorkerState m_nDataWorkerState;
private:
	void _DoJob_ProcessOrder();
private:
	void _FreeData_ListOrderData(std::list<COrderData*>& lstMyOrderData);
	void _ProcessOrder(COrderData* pData);
private:
	void _ProcessOrder_MARKET_BUY(COrderData* pData);
	void _ProcessOrder_MARKET_SELL(COrderData* pData);
	void _ProcessOrder_MARKET(COrderData* pData);
private:
	CQtTimeHelper* m_pQtTimeHelper;
};


#endif //__CLASS_DATA_PROCESS_ORDER_WORKER__HH__


