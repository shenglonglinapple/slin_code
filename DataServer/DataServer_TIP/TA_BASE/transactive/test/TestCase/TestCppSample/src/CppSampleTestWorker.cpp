#include "CppSampleTestWorker.h"



#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;



NS_BEGIN(TA_Base_Core) 




//////////////////////////////////////////////////////////////////////////
CCppSocketTestWorker::CCppSocketTestWorker(void)
{	
	BOOST_LOG_FUNCTION();	
	m_toTerminate = false;
	m_nThreadJobState = JobState_Begin;

}

CCppSocketTestWorker::~CCppSocketTestWorker(void)
{
	BOOST_LOG_FUNCTION();

}


void CCppSocketTestWorker::run()
{
	BOOST_LOG_FUNCTION();

	m_nThreadJobState = JobState_Begin;


	while (false == m_toTerminate)
	{
		_ThreadJob();
		TA_Base_Core::CBoostThread::sleep(1000);
	}

	_ProcessUserTerminate();
}

void CCppSocketTestWorker::terminate()
{
	BOOST_LOG_FUNCTION();

	m_toTerminate = true;
}


int CCppSocketTestWorker::_ProcessUserTerminate()
{
	BOOST_LOG_FUNCTION();

	int nFunRes = 0;
	m_toTerminate = true;
	m_nThreadJobState = JobState_End;
	return nFunRes;
}

bool CCppSocketTestWorker::isFinishWork()
{
	BOOST_LOG_FUNCTION();

	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CCppSocketTestWorker::_ThreadJob()
{
	BOOST_LOG_FUNCTION();

	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		break;
	case JobState_End:
		break;
	default:
		TA_Base_Core::CBoostThread::sleep(1000);
		break;

	}//switch
}

NS_END(TA_Base_Core) 



