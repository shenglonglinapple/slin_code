#include "DataProcessOrderWorker.h"
#include "ServerComManager.h"
#include "DataOrderManager.h"

#include "Log4cppLogger.h"


CDataProcessOrderWorker::CDataProcessOrderWorker(void)
{	
	m_toTerminate = false;
	m_WorkerState = WORK_STATE_BEGIN;
	m_nDataWorkerState = DataWorkerState_Begin;

}

CDataProcessOrderWorker::~CDataProcessOrderWorker(void)
{
}


void CDataProcessOrderWorker::run()
{
	m_WorkerState = WORK_STATE_BEGIN;
	m_nDataWorkerState = DataWorkerState_Begin;
	
	m_WorkerState = WORK_STATE_WORKING;
	while (false == m_toTerminate)
	{
		_ThreadJob();
		this->my_msleep(5000);
	}

	_ProcessUserTerminate();
	m_WorkerState = WORK_STATE_END;

}

void CDataProcessOrderWorker::terminate()
{
	m_toTerminate = true;

	while (WORK_STATE_END != m_WorkerState)
	{
		this->msleep(10);
	}
}


int CDataProcessOrderWorker::_ProcessUserTerminate()
{
	int nFunRes = 0;
	m_toTerminate = true;
	m_nDataWorkerState = DataWorkerState_End;
	return nFunRes;
}

bool CDataProcessOrderWorker::isFinishWork()
{
	bool bFinishWork = false;
	if (DataWorkerState_End == m_nDataWorkerState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CDataProcessOrderWorker::_ThreadJob()
{
	switch (m_nDataWorkerState)
	{
	case DataWorkerState_Begin:
		m_nDataWorkerState = DataWorkerState_ProcessOrder;
		break;
	case DataWorkerState_ProcessOrder:
		_DoJob_ProcessOrder();
		break;
	case DataWorkerState_End:
		this->my_msleep(100);
		break;
	default:
		this->my_msleep(100);
		break;
	}//switch (m_nDataWorkerState)

}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void CDataProcessOrderWorker::_DoJob_ProcessOrder()
{
	
	m_nDataWorkerState = DataWorkerState_ProcessOrder;
}
