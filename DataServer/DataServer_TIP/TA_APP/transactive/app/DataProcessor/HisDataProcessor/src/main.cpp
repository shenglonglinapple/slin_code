//#include "vld.h"
#include <signal.h>
#include <iostream>

#include <QtGui/QApplication>

#include "CFDServerCommonData.h"
#include "QTProjectEnvironment.h"
#include "BoostThread.h"
#include "ServerSettingDialog.h"
#include "ConfigInfo.h"

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

	std::string strLogPath = "ALL_QTHisDataProcessor_LOG_PATH";
	std::string strLogFileName = "QTHisDataProcessor_Log_%Y-%m-%d_%H_%M_%S_%f_%4N.log";
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


void QTProjectInit()
{
	BoostLogInit();
	CQTProjectEnvironment::getInstance();
	//

}



void QTProjectUnInit()
{
	//
	CQTProjectEnvironment::removeInstance();
	BoostLogUnInit();
}



int main( int argc, char* argv[])
{ 	   
	int nFunRes = 0;
	CServerSettingDialog* pServerDialog = NULL;

	signal(SIGINT, usr_signal);
#ifndef WIN32
	signal(SIGHUP, usr_signal);	//close putty
#endif


	QApplication app(argc, argv);
	QTProjectInit();

	app.setFont(CQTProjectEnvironment::getInstance().getQTProjectEnvFont());


	CConfigInfo::getInstance();
	pServerDialog = new CServerSettingDialog(NULL);

	pServerDialog->show();

	nFunRes = app.exec();

	if (NULL != pServerDialog)
	{
		delete pServerDialog;
		pServerDialog = NULL;
	}

	CConfigInfo::removeInstance();
	QTProjectUnInit();

	return 0;
}









//////////////////////////////////////////////////////////////////////////
#if 0


int main( int argc, char* argv[])
{ 	   
	int nFunRes = 0;
	QApplication app(argc, argv);


	signal(SIGINT, usr_signal);
#ifndef WIN32
	signal(SIGHUP, usr_signal);	//close putty
#endif

	QTProjectInit();
	CConfigInfo::getInstance();


	nFunRes = app.exec();



	CProcessorWorker* pProcessWorker = new CProcessorWorker();
	pProcessWorker->start();

	//sleep
	// 	{	
	// 		boost::mutex::scoped_lock lock(g_mutexMainRun);
	// 		g_conditionMainRun.wait(lock);
	// 	}

	while (1)
	{
		if (pProcessWorker->isFinishWork())
		{
			break;
		}
		CBoostThread::sleep(TIME_BASE_MS_1MIN);
	}

	if (NULL != pProcessWorker)
	{
		pProcessWorker->terminateAndWait();
		delete pProcessWorker;
		pProcessWorker = NULL;
	}

	CConfigInfo::removeInstance();
	QTProjectUnInit();

	return 0;
}

void Test_CInstrumentBarInfoRequest()
{
	int nFunRes = 0;
	std::string strLogInfo;

	CConfigInfo::getInstance();
	CConfigInfo::getInstance().logInfo();

	CAWorkTime* pWorkTime = NULL;
	CMarketDataPathManager* pMarketDataPathManager = NULL;

	strLogInfo = "get request from cfg file";
	CInstrumentBarInfoRequest requestBarInfo; 
	requestBarInfo.setValueByCfg();
	requestBarInfo.logInfo(strLogInfo);

	pWorkTime = new CWorkTimeNoLock();
	pWorkTime->workBegin();

	pMarketDataPathManager = new CMarketDataPathManager();
	nFunRes = pMarketDataPathManager->setInstrumentBarInfoRequest(requestBarInfo);
	if (0 == nFunRes)
	{
		pMarketDataPathManager->analieAllFiles();
	}

	if (NULL != pMarketDataPathManager)
	{
		delete pMarketDataPathManager;
		pMarketDataPathManager = NULL;
	}

	pWorkTime->workEnd();

	LOG_INFO<<"Test_CInstrumentBarInfoRequest work time = "<<pWorkTime->getWorkTime();

	if (NULL != pWorkTime)
	{
		delete pWorkTime;
		pWorkTime = NULL;
	}

	CConfigInfo::removeInstance();

}

#endif

//////////////////////////////////////////////////////////////////////////




