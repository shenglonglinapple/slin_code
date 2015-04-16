#include "ProjectTestWorker.h"

#include "TestCaseLog4cpp.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;



NS_BEGIN(TA_Base_Test) 




//////////////////////////////////////////////////////////////////////////
CProjectTestWorker::CProjectTestWorker(void)
{	
	BOOST_LOG_FUNCTION();	
	m_toTerminate = false;
	m_nThreadJobState = JobState_Begin;

}

CProjectTestWorker::~CProjectTestWorker(void)
{
	BOOST_LOG_FUNCTION();

}


void CProjectTestWorker::run()
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

void CProjectTestWorker::terminate()
{
	BOOST_LOG_FUNCTION();

	m_toTerminate = true;
}


int CProjectTestWorker::_ProcessUserTerminate()
{
	BOOST_LOG_FUNCTION();

	int nFunRes = 0;
	m_toTerminate = true;
	m_nThreadJobState = JobState_End;
	return nFunRes;
}

bool CProjectTestWorker::isFinishWork()
{
	BOOST_LOG_FUNCTION();

	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CProjectTestWorker::_ThreadJob()
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

void CProjectTestWorker::_DoTest_01()
{
	CTestCaseLog4cpp* pTestCaseLog4cpp = NULL;
	pTestCaseLog4cpp = new CTestCaseLog4cpp();

	TA_Base_Core::CBoostThread::sleep(2000);

	delete pTestCaseLog4cpp;
	pTestCaseLog4cpp = NULL;

}

NS_END(TA_Base_Test) 



