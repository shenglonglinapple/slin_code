#include <QtGui/QApplication>


#include "QTProjectEnvironment.h"
#include "ClientUIManager.h"


//////////////////////////////////////////////////////////////////////////
//#define CURL_STATICLIB
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"wldap32.lib")
#pragma comment(lib,"libcurld.lib")
#pragma comment(lib,"log4cppD.lib")
#pragma comment(lib,"ws2_32.lib")//winsock2

//qcustomplotd.lib StrategyEngine.lib log4cppD.lib
#pragma comment(lib,"qtmaind.lib")
#pragma comment(lib,"QtCored4.lib")
#pragma comment(lib,"QtGuid4.lib")
#pragma comment(lib,"QtSqld4.lib")


#pragma comment(lib,"StrategyEngine.lib")
//////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	int nFunRes = 0;

    QApplication app(argc, argv);
	CQTProjectEnviroment::getInstance();

    CClientUIManager clientUIManager;
    clientUIManager.showClientLoginWindow(true);

    nFunRes = app.exec();

	CQTProjectEnviroment::removeInstance();
	return 0;
}
