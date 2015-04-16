#include "CommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>

#include "ConfigInfo.h"
#include "TestCase.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

boost::mutex g_mutexMainRun;
boost::condition_variable g_conditionMainRun;


using namespace TA_Base_Test;

void logInit()
{
	TA_Base_App::CBoostLogger::getInstance();

	std::string strLogPath = "ALL_TestCMS_LOG";
	std::string strLogFileName = "TestCMS_Log_%Y-%m-%d_%H_%M_%S_%f_%4N.log";
	boost::log::trivial::severity_level nLogLevel = boost::log::trivial::trace;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::info;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::debug;


	TA_Base_App::CBoostLogger::getInstance().setLogPath(strLogPath);
	TA_Base_App::CBoostLogger::getInstance().setLogFileName(strLogFileName);
	TA_Base_App::CBoostLogger::getInstance().setLogLevel(nLogLevel);
	TA_Base_App::CBoostLogger::getInstance().logInit();
	TA_Base_App::CBoostLogger::getInstance().testBoostLog();
}

void logUnInit()
{
	TA_Base_App::CBoostLogger::removeInstance();
}


int main( int argc, char* argv[] )
{
	logInit();

	CConfigInfo::getInstance();
	CConfigInfo::getInstance().logInfo();
	

	TA_Base_Test::CTestCase* pTestCase = new TA_Base_Test::CTestCase();

	pTestCase->runTestCase();
	//

	//sleep
	{	
		boost::mutex::scoped_lock lock(g_mutexMainRun);
		g_conditionMainRun.wait(lock);
	}

	delete pTestCase;
	pTestCase = NULL;


	CConfigInfo::removeInstance();

	logUnInit();

	return 0;
}










