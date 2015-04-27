//#include "vld.h"
#include <signal.h>
#include "CommonData.h"

#include <QtGui/QApplication>
//#include "QTProjectEnvironment.h"
#include "IndicatorEditorWindow.h"

//#include "BoostLogger.h"
//USING_BOOST_LOG;






void usr_signal(int SigNo)
{
	if (SigNo == SIGINT)
	{
	}
	
#ifndef WIN32
	if (SigNo == SIGHUP)
	{
	}
#endif
}



void BoostLogInit()
{

}

void BoostLogUnInit()
{
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
    //Q_INIT_RESOURCE(RectCollidingTest);


	signal(SIGINT, usr_signal);
#ifndef WIN32
	signal(SIGHUP, usr_signal);	//close putty
#endif


	QApplication app(argc, argv);
	QTProjectInit();

    //app.setFont(CQTProjectEnvironment::getInstance().getQTProjectEnvFont());

    CIndicatorEditorWindow IndicatorEditorWindowTmp;
	IndicatorEditorWindowTmp.show();

	nFunRes = app.exec();


	
	QTProjectUnInit();

	return 0;
}








