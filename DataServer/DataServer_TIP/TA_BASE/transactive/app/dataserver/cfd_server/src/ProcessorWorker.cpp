#include "ProcessorWorker.h"

#include "CFDServerCommonData.h"
#include "MarketDataPathManager.h"
#include "WorkTime.h"
#include "ConfigInfo.h"
#include "InstrumentBarInfoRequest.h"
#include "CFDServerUtilityFun.h"


#include "BoostLogger.h"
USING_BOOST_LOG;


//////QT_BEGIN_NAMESPACE
//////QT_END_NAMESPACE



CProcessorWorker::CProcessorWorker(void)
{	
	//BOOST_LOG_FUNCTION();
	m_nProcessRequestCount = 0;
	m_pUtilityFun = NULL;
	m_pUtilityFun = new CCFDServerUtilityFun();
	m_nWorkTimeAutoTimeOut = TIME_BASE_MS_1DAY;
	m_nProcessOneRequestTime_ForReport = 0;

	m_nThreadJobState = JobState_Begin;
	m_toTerminate = false;	
}

CProcessorWorker::~CProcessorWorker(void)
{	
	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}
	
	
}

void CProcessorWorker::run()
{
	m_nThreadJobState = JobState_Begin;

	while (false == m_toTerminate)
	{
		_ThreadJob();
		CBoostThread::sleep(100);
	}
	_ProcessUserTerminate();
}

void CProcessorWorker::terminate()
{
	//BOOST_LOG_FUNCTION();

	m_toTerminate = true;
}


int CProcessorWorker::_ProcessUserTerminate()
{
	//BOOST_LOG_FUNCTION();

	int nFunRes = 0;
	m_nThreadJobState = JobState_End;
	return nFunRes;
}

bool CProcessorWorker::isFinishWork()
{
	//BOOST_LOG_FUNCTION();

	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CProcessorWorker::_ThreadJob()
{
	//BOOST_LOG_FUNCTION();


	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		m_nThreadJobState = JobState_CheckUtilityFun;
		break;
	case JobState_CheckUtilityFun:
		_Process_CheckUtilityFun();
		break;
	case JobState_ProcessRequest:
		_Process_ProcessRequest();
		break;
	case JobState_StopWork:
		_Process_StopWork();
		//TA_App_App::CBoostThread::sleep(1000);
		break;
	case JobState_End:
		//CBoostThread::sleep(1000);
		break;
	default:
		break;

	}//switch
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
 void CProcessorWorker::_Process_CheckUtilityFun()
 {
	 int nFunRes = 0;

	nFunRes = m_pUtilityFun->checkUtilityFun();
	if (0 != nFunRes)
	{
		LOG_ERROR<<" m_pUtilityFun->checkUtilityFun <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
		m_nThreadJobState = JobState_StopWork;

	}
	else
	{
		m_nThreadJobState = JobState_ProcessRequest;
	}

 }

void CProcessorWorker::_Process_ProcessRequest()
{
	int nFunRes = 0;
	CAWorkTime* pWorkTime = NULL;
	CMarketDataPathManager* pMarketDataPathManager = NULL;
	std::string strLogInfo;

	pWorkTime = new CWorkTimeNoLock();
	pMarketDataPathManager = new CMarketDataPathManager();

	pWorkTime->workBegin();

	//begin analie All files
	pMarketDataPathManager->analieAllFilesOneByOne();
	
	//end analie All files

	if (NULL != pMarketDataPathManager)
	{
		delete pMarketDataPathManager;
		pMarketDataPathManager = NULL;
	}

	pWorkTime->workEnd();

	m_nProcessRequestCount++;

	m_nProcessOneRequestTime_ForReport = pWorkTime->getWorkTime();

	LOG_INFO<<"Process one Request"
		<<" "<<"WorkTime="<<pWorkTime->getWorkTime()
		<<" "<<"ms"
		<<" "<<"m_nProcessRequestCount="<<m_nProcessRequestCount
		<<" "<<"and next start time="<<CConfigInfo::getInstance().getStartTime()
		<<" "<<"string next start time="<<m_pUtilityFun->dataTimeToStr(CConfigInfo::getInstance().getStartTime());

	if (NULL != pWorkTime)
	{
		delete pWorkTime;
		pWorkTime = NULL;
	}

	_LogReport();

	m_nThreadJobState = JobState_StopWork;
	return;
}



void CProcessorWorker::_Process_StopWork()
{
	
	LOG_DEBUG<<"_Process_StopWork";

	m_nThreadJobState = JobState_End;
}


//////////////////////////////////////////////////////////////////////////


void CProcessorWorker::_LogReport()
{
	LOG_INFO<<"-----Report--- CProcessorWorker Report:"
		<<" "<<"m_nProcessRequestCount="<<m_nProcessRequestCount
		<<" "<<"m_nProcessOneRequestTime_ForReport="<<m_nProcessOneRequestTime_ForReport;
}

////QT_END_NAMESPACE


