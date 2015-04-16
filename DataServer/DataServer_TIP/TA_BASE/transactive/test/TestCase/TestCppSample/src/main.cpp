#include <iostream>
#include "CppSampleTestManager.h"


#include "core/threads/src/BoostThread.h"



#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG

using namespace TA_Base_Core;

void g_BoostLogInit();
void g_BoostLogUnInit();


void g_BoostLogInit()
{
	CBoostLogger::getInstance();

	std::string strLogPath = "ALL_LOG_PATH";
	//std::string strLogFileName = "Test_Log_%Y-%m-%d_%H_%M_%S_%f_%4N.log";
	std::string strLogFileName = "Test_Log_%Y-%m-%d_%H_%M_%S.log";
	boost::log::trivial::severity_level nLogLevel = boost::log::trivial::trace;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::info;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::debug;


	CBoostLogger::getInstance().setLogPath(strLogPath);
	CBoostLogger::getInstance().setLogFileName(strLogFileName);
	CBoostLogger::getInstance().setLogLevel(nLogLevel);
	CBoostLogger::getInstance().initBoostLog();
	CBoostLogger::getInstance().testBoostLog();
}

void g_BoostLogUnInit()
{
	CBoostLogger::removeInstance();
}

int main( int argc, char* argv[] )
{
		
	g_BoostLogInit();



	TA_Base_Core::CCppSocketTestManager* pTestManager = new TA_Base_Core::CCppSocketTestManager();
	

	TA_Base_Core::CBoostThread::sleep(TA_Base_Core::TIME_BASE_S_1HOUR);

	if (NULL != pTestManager)
	{
		delete pTestManager;
		pTestManager = NULL;
	}



	g_BoostLogUnInit();

	return 0;
}










