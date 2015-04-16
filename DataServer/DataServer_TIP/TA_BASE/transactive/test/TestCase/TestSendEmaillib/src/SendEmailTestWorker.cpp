#include "SendEmailTestWorker.h"
#include "MyCppSendMailTest.h"


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;



NS_BEGIN(TA_Base_Test) 




//////////////////////////////////////////////////////////////////////////
CSendEmailTestWorker::CSendEmailTestWorker(void)
{	
	BOOST_LOG_FUNCTION();	
	m_toTerminate = false;
	m_nThreadJobState = JobState_Begin;

}

CSendEmailTestWorker::~CSendEmailTestWorker(void)
{
	BOOST_LOG_FUNCTION();

}


void CSendEmailTestWorker::run()
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

void CSendEmailTestWorker::terminate()
{
	BOOST_LOG_FUNCTION();

	m_toTerminate = true;
}


int CSendEmailTestWorker::_ProcessUserTerminate()
{
	BOOST_LOG_FUNCTION();

	int nFunRes = 0;
	m_toTerminate = true;
	m_nThreadJobState = JobState_End;
	return nFunRes;
}

bool CSendEmailTestWorker::isFinishWork()
{
	BOOST_LOG_FUNCTION();

	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CSendEmailTestWorker::_ThreadJob()
{
	BOOST_LOG_FUNCTION();

	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		m_nThreadJobState = JobState_DoTest_01;
		break;
	case  JobState_DoTest_01:
		_DoTest_01();
		m_nThreadJobState = JobState_End;
		break;
	case JobState_End:
		break;
		TA_Base_Core::CBoostThread::sleep(1000);
	default:
		TA_Base_Core::CBoostThread::sleep(1000);
		break;

	}//switch
}

void CSendEmailTestWorker::_DoTest_01()
{
	CMyCppSendMailTest TestObj;
	TestObj.test_SendOneEmail();

}

NS_END(TA_Base_Test) 



