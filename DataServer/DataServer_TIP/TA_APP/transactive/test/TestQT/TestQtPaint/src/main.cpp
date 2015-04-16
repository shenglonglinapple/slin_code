#include "CommonData.h"

#include "MyRect.h"

#include <iostream>	
#include <string>
#include <sstream>
#include <fstream>
#include "core/utilities/src/BoostLogger.h"

using namespace TA_Base_Core;

void BoostLogInit()
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

void BoostLogUnInit()
{
	CBoostLogger::removeInstance();
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	BoostLogInit();

	CMyRect w;
	w.show();

	app.exec();

	BoostLogUnInit();
	return 0;
}


