#include "SampleMyQtThread.h"


//////////////////////////////////////////////////////////////////////////
CSampleMyQtThread::CSampleMyQtThread(void)
{	
	m_toTerminate = false;
	m_WorkerState = WORK_STATE_BEGIN;
	m_nThreadJobState = JobState_Begin;

}

CSampleMyQtThread::~CSampleMyQtThread(void)
{

}


void CSampleMyQtThread::run()
{
	m_WorkerState = WORK_STATE_BEGIN;
	m_nThreadJobState = JobState_Begin;

	m_WorkerState = WORK_STATE_WORKING;

	while (false == m_toTerminate)
	{
		_ThreadJob();
		this->my_msleep(100);
	}

	_ProcessUserTerminate();
	m_WorkerState = WORK_STATE_END;
}

void CSampleMyQtThread::terminate()
{
	m_toTerminate = true;
	while (WORK_STATE_END != m_WorkerState)
	{
		this->msleep(10);
	}
}


int CSampleMyQtThread::_ProcessUserTerminate()
{
	int nFunRes = 0;
	m_toTerminate = true;
	m_nThreadJobState = JobState_End;
	return nFunRes;
}

bool CSampleMyQtThread::isFinishWork()
{
	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CSampleMyQtThread::_ThreadJob()
{
	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		break;
	case JobState_End:
		break;
	default:
		this->my_msleep(100);
		break;

	}//switch
}

void CSampleMyQtThread::join()
{
	while (CSampleMyQtThread::JobState_End != m_nThreadJobState)
	{
		this->msleep(10);
	}
}

/*

void CTestMyThreadManager::do_test_mythread_2()
{
	CSampleMyQtThread* pMyThreadTest = NULL;
	pMyThreadTest = new CSampleMyQtThread();

	pMyThreadTest->start();

	pMyThreadTest->my_msleep(1000* 10);

	pMyThreadTest->terminateAndWait();

	delete pMyThreadTest;
	pMyThreadTest = NULL;
}
*/

