//#include "vld.h"
#include <signal.h>
#include <iostream>


#include "CFDServerCommonData.h"
#include "BoostThread.h"
#include "ConfigInfo.h"
#include "ProcessorWorker.h"
#include "QTProjectEnvironment.h"


#include "BoostLogger.h"
USING_BOOST_LOG;

//using namespace TA_Base_App;


boost::mutex g_mutexMainRun;
boost::condition_variable g_conditionMainRun;


void usr_signal(int SigNo)
{
	if (SigNo == SIGINT)
	{
		g_conditionMainRun.notify_one();
	}
	
#ifndef WIN32
	if (SigNo == SIGHUP)
	{
	}
#endif
}



void BoostLogInit()
{
	CBoostLogger::getInstance();

	std::string strLogPath = "ALL_HisDataProcessor_LOG_PATH";
	std::string strLogFileName = "HisDataProcessor_Log_%Y-%m-%d_%H_%M_%S_%f_%4N.log";
	boost::log::trivial::severity_level nLogLevel = boost::log::trivial::trace;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::info;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::debug;


	CBoostLogger::getInstance().setLogPath(strLogPath);
	CBoostLogger::getInstance().setLogFileName(strLogFileName);
	CBoostLogger::getInstance().setLogLevel(nLogLevel);
	CBoostLogger::getInstance().logInit();
	CBoostLogger::getInstance().testBoostLog();
}

void BoostLogUnInit()
{
	CBoostLogger::removeInstance();
}






int main( int argc, char* argv[])
{ 	   
	int nFunRes = 0;

	signal(SIGINT, usr_signal);
#ifndef WIN32
	signal(SIGHUP, usr_signal);	//close putty
#endif

	BoostLogInit();
	CQTProjectEnvironment::getInstance();
	CConfigInfo::getInstance();

	CProcessorWorker* pProcessorWorker = NULL;

	pProcessorWorker = new CProcessorWorker();

	pProcessorWorker->start();

	while (1)
	{
		CBoostThread::sleep(1000);
		if (pProcessorWorker->isFinishWork())
		{
			break;
		}
	}

	if (NULL != pProcessorWorker)
	{
		pProcessorWorker->terminateAndWait();
		delete pProcessorWorker;
		pProcessorWorker = NULL;
	}

	CConfigInfo::removeInstance();
	CQTProjectEnvironment::removeInstance();
	BoostLogUnInit();
	return 0;
}












