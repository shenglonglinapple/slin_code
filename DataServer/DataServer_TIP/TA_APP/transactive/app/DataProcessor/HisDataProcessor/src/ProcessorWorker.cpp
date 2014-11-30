#include "ProcessorWorker.h"

#include "CFDServerCommonData.h"
#include "MarketDataPathManager.h"
#include "WorkTime.h"
#include "ConfigInfo.h"
#include "InstrumentBarInfoRequest.h"
#include "CFDServerUtilityFun.h"


#include "BoostLogger.h"
USING_BOOST_LOG;


QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE



CProcessorWorker::CProcessorWorker(void)
{	
	//BOOST_LOG_FUNCTION();
	m_pRequestBarInfo = NULL;
	m_pRequestBarInfo = new CInstrumentBarInfoRequest();
	m_nProcessRequestCount = 0;
	m_pUtilityFun = NULL;
	m_pUtilityFun = new CCFDServerUtilityFun();
	m_pWorkTimeAuto = NULL;
	m_pWorkTimeAuto = new CWorkTimeNoLock();
	m_pWorkTimeAuto->workBegin();
	m_nWorkTimeAutoTimeOut = TIME_BASE_MS_1DAY;
	m_nProcessOneRequestTime_ForReport = 0;

	m_nThreadJobState = JobState_Begin;
	m_toTerminate = false;	
}

CProcessorWorker::~CProcessorWorker(void)
{	
	//BOOST_LOG_FUNCTION();
	if (NULL != m_pRequestBarInfo)
	{
		delete m_pRequestBarInfo;
		m_pRequestBarInfo = NULL;
	}

	if (NULL != m_pWorkTimeAuto)
	{
		delete m_pWorkTimeAuto;
		m_pWorkTimeAuto = NULL;
	}


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
	case JobState_InitRequest:
		_Process_InitRequest();
		break;
	case JobState_CheckRequest:
		_Process_CheckRequest();
		break;
	case JobState_ProcessRequest:
		_Process_ProcessRequest();
		break;
	case JobState_StopWork:
		_Process_StopWork();
		//TA_App_App::CBoostThread::sleep(1000);
		break;
	case JobState_End:
		//TA_App_App::CBoostThread::sleep(1000);
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
	}
	else
	{
		m_nThreadJobState = JobState_InitRequest;
	}

 }

void CProcessorWorker::_Process_InitRequest()
{
	std::string strLogInfo;
	std::string strCurrentTime;
	std::string strCurrentTimeForReset;
	std::string strAutoRunTime24Clock;



	if (NULL != m_pRequestBarInfo)
	{
		delete m_pRequestBarInfo;
		m_pRequestBarInfo = NULL;
	}

	strLogInfo = "get request from cfg file";

	m_pRequestBarInfo = new CInstrumentBarInfoRequest();
	m_pRequestBarInfo->setValueByCfg();
	m_pRequestBarInfo->logInfo(strLogInfo);

	/*
	first time 
	two type:
	type one:
	strCurrentTime = "2014-01-28 11:00:00"
	AutoRunTime24Clock = "2014-01-28 03:00:00"
	m_nWorkTimeAutoTimeOut = "2014-01-29 03:00:00" - "2014-01-28 11:00:00"

	type one:
	strCurrentTime = "2014-01-28 11:00:00"
	AutoRunTime24Clock = "2014-01-28 13:00:00"
	m_nWorkTimeAutoTimeOut = "2014-01-29 13:00:00" - "2014-01-28 11:00:00"
	*/
	strCurrentTime = m_pWorkTimeAuto->getCurrentTime(NULL);////2014-01-28 11:00:00
	strAutoRunTime24Clock = m_pRequestBarInfo->m_strAutoRunTime24Clock;
	m_nWorkTimeAutoTimeOut = m_pUtilityFun->getAutoTimeOutMilliseconds(strCurrentTime, strAutoRunTime24Clock);

	LOG_INFO<<"set m_nWorkTimeAutoTimeOut="<<m_nWorkTimeAutoTimeOut<<" ms"
		<<" "<<"first cycle less than TIME_BASE_MS_1DAY start";

	m_nThreadJobState = JobState_CheckRequest;

}

void CProcessorWorker::_Process_CheckRequest()
{
	if (NULL == m_pRequestBarInfo)
	{
		m_nThreadJobState = JobState_InitRequest;
		return;
	}

	//check if first time to process request
	if (0 == m_nProcessRequestCount)
	{
		m_nThreadJobState = JobState_ProcessRequest;
		return;
	}

	//other cycle
	if (AutoRunType_NO == m_pRequestBarInfo->m_nAutoRun)
	{
		m_nThreadJobState = JobState_StopWork;
		return;
	}
	else if (AutoRunType_YES == m_pRequestBarInfo->m_nAutoRun)
	{
		if (false == _CheckContinueProcessRequest())
		{
			m_nThreadJobState = JobState_CheckRequest;
			CBoostThread::sleep(TIME_BASE_MS_1MIN);
		}
		else
		{
			m_nThreadJobState = JobState_ProcessRequest;
		}
		return;
	}
	

	m_nThreadJobState = JobState_ProcessRequest;
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

	nFunRes = pMarketDataPathManager->setInstrumentBarInfoRequest(*m_pRequestBarInfo);
	if (0 == nFunRes)
	{
		pMarketDataPathManager->analieAllFiles();
	}

	strLogInfo = "-----Report--- RequestBarInfo Report:";
	m_pRequestBarInfo->logInfo(strLogInfo);

	strLogInfo = "reset request after process one request";
	m_pRequestBarInfo->m_nStartTime = pMarketDataPathManager->getNextStartTime();
	m_pRequestBarInfo->logInfo(strLogInfo);

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
		<<" "<<"m_nProcessRequestCount="<<m_nProcessRequestCount;

	if (NULL != pWorkTime)
	{
		delete pWorkTime;
		pWorkTime = NULL;
	}

	_LogReport();

	m_nThreadJobState = JobState_CheckRequest;
	return;
}



void CProcessorWorker::_Process_StopWork()
{
	
	LOG_DEBUG<<"_Process_StopWork";

	m_nThreadJobState = JobState_End;
}


//////////////////////////////////////////////////////////////////////////


bool CProcessorWorker::_CheckContinueProcessRequest()
{
	bool bContinue = false;
	BigInt64 nWorkTimeAutoMilliSeconds = 0;


	nWorkTimeAutoMilliSeconds = m_pWorkTimeAuto->getNotworkTime();//Milliseconds

	if (nWorkTimeAutoMilliSeconds >= m_nWorkTimeAutoTimeOut)
	{
		bContinue = true;

		LOG_INFO<<"CProcessorWorker::_CheckContinueProcessRequest"
			<<" "<<"nWorkTimeAutoMilliSeconds="<<nWorkTimeAutoMilliSeconds
			<<" "<<">="
			<<" "<<"m_nWorkTimeAutoTimeOut="<<m_nWorkTimeAutoTimeOut<<" ms"
			<<" "<<"set bContinue="<<bContinue;

		m_nWorkTimeAutoTimeOut = TIME_BASE_MS_1DAY;
		m_pWorkTimeAuto->workEnd();
		m_pWorkTimeAuto->workBegin();//cycle start

		LOG_INFO<<"set m_nWorkTimeAutoTimeOut="<<m_nWorkTimeAutoTimeOut<<" ms"
			<<" "<<"cycle TIME_BASE_MS_1DAY start";

	}
	else
	{
		bContinue = false;
	}


	return bContinue;
}


void CProcessorWorker::_LogReport()
{
	LOG_INFO<<"-----Report--- CProcessorWorker Report:"
		<<" "<<"m_nProcessRequestCount="<<m_nProcessRequestCount
		<<" "<<"m_nProcessOneRequestTime_ForReport="<<m_nProcessOneRequestTime_ForReport;
}

QT_END_NAMESPACE


