#include "vld.h"
#include <iostream>

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

#include "core/threads/src/BoostThread.h"
#include "ProjectTestManager.h"

#pragma comment(lib, "Ws2_32.lib")//winsock2
//Ws2_32.lib

int main( int argc, char* argv[] )
{
		
	TA_Base_Core::CBoostLogger::getInstance();

	std::string strLogPath = "ALL_LOG_PATH";
	std::string strLogFileName = "Sample_Log_%Y-%m-%d_%H_%M_%S_%f_%4N.log";
	boost::log::trivial::severity_level nLogLevel = boost::log::trivial::trace;


	TA_Base_Core::CBoostLogger::getInstance().setLogPath(strLogPath);
	TA_Base_Core::CBoostLogger::getInstance().setLogFileName(strLogFileName);
	TA_Base_Core::CBoostLogger::getInstance().setLogLevel(nLogLevel);
	TA_Base_Core::CBoostLogger::getInstance().initBoostLog();
	TA_Base_Core::CBoostLogger::getInstance().testBoostLog();

	TA_Base_Test::CProjectTestManager* pTestManager = new TA_Base_Test::CProjectTestManager();
	
	while (1)
	{
		if (pTestManager->isFinishWork())
		{
			break;
		}
		TA_Base_Core::CBoostThread::sleep(1000);
	}

	if (NULL != pTestManager)
	{
		delete pTestManager;
		pTestManager = NULL;
	}

	TA_Base_Core::CBoostLogger::removeInstance();
	return 0;
}










