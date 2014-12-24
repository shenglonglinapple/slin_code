#ifndef __CLASS_DATA_PROCESS_ORDER_WORKER__HH__
#define __CLASS_DATA_PROCESS_ORDER_WORKER__HH__

#include "MyQtThread.h"
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QList>

class CReqData;


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
};


#endif //__CLASS_DATA_PROCESS_ORDER_WORKER__HH__


