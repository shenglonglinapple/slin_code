//#include "vld.h"
#include <signal.h>
#include "CommonData.h"

#include <QtGui/QApplication>
//#include "QTProjectEnvironment.h"

#include "IndicatorEditorMainWindow.h"

//#include "BoostLogger.h"
//USING_BOOST_LOG;




// boost::mutex g_mutexMainRun;
// boost::condition_variable g_conditionMainRun;
bool g_bProgramContinueRun = true;


void usr_signal(int SigNo)
{
	if (SigNo == SIGINT)
	{
		g_bProgramContinueRun = false;
		//g_conditionMainRun.notify_one();
	}
	
#ifndef WIN32
	if (SigNo == SIGHUP)
	{
	}
#endif
}



void BoostLogInit()
{
	//CBoostLogger::getInstance();

	std::string strLogPath = "ALL_IndicatorEditor_LOG_PATH";
	std::string strLogFileName = "IndicatorEditor_Log_%Y-%m-%d_%H_%M_%S.log";
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::trace;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::info;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::debug;


// 	CBoostLogger::getInstance().setLogPath(strLogPath);
// 	CBoostLogger::getInstance().setLogFileName(strLogFileName);
// 	CBoostLogger::getInstance().setLogLevel(nLogLevel);
// 	CBoostLogger::getInstance().initBoostLog();
// 	CBoostLogger::getInstance().testBoostLog();
}

void BoostLogUnInit()
{
/*	CBoostLogger::removeInstance();*/
}


void QTProjectInit()
{
	BoostLogInit();
	//CQTProjectEnvironment::getInstance();
	//

}



void QTProjectUnInit()
{
	//
	//CQTProjectEnvironment::removeInstance();
	BoostLogUnInit();
}



int main( int argc, char* argv[])
{ 	   
	int nFunRes = 0;
	Q_INIT_RESOURCE(IndicatorEditor);

	g_bProgramContinueRun = true;

	signal(SIGINT, usr_signal);
#ifndef WIN32
	signal(SIGHUP, usr_signal);	//close putty
#endif


	QApplication app(argc, argv);
	QTProjectInit();

	//app.setFont(CQTProjectEnvironment::getInstance().getQTProjectEnvFont());


	CIndicatorEditorMainWindow IndicatorEditorMainWindow;
	IndicatorEditorMainWindow.show();

	nFunRes = app.exec();


	
	QTProjectUnInit();

	return 0;
}





void setVision()
{	

	std::string strVision = "1.00.400";
	std::string strDate = "2014-05-22";
	std::string strRemark = "Drag RectItem and Text Item";
	
	/*
	std::string strVision = "1.00.301";
	std::string strDate = "2014-05-21";
	std::string strRemark = "Drag RectItem";
	*/

	/*
	std::string strVision = "1.00.200";
	std::string strDate = "2014-05-12";
	std::string strRemark = "Text font and colour set show";
	*/
}



