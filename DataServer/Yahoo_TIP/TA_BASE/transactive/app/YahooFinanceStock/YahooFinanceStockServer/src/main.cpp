#include <iostream>
//#include <QtCore/QtCore>
#include <QtGui/QApplication>


////////////////
//_WINDOWS;UNICODE;WIN32;QT_DLL;QT_HAVE_MMX;QT_HAVE_3DNOW;QT_HAVE_SSE;QT_HAVE_MMXEXT;QT_HAVE_SSE2;QT_GUI_LIB;QT_CORE_LIB;QT_THREAD_SUPPORT

////////////////
//sys
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"wldap32.lib")
#pragma comment(lib,"ws2_32.lib")//winsock2

//qt
#pragma comment(lib,"qtmaind.lib")
#pragma comment(lib,"QtCored4.lib")
#pragma comment(lib,"QtGuid4.lib")
#pragma comment(lib,"QtSqld4.lib")
#pragma comment(lib,"QtNetworkd4.lib")

//user
#pragma comment(lib,"log4cppD.lib")
////////////////



#include "ServerManager.h"

#include "BaseException.h"
#include "ProjectEnvironment.h"



int main(int argc, char *argv[])
{
	qint32 nFunRes = 0;
    QApplication app(argc, argv);
	CProjectEnviroment::getInstance();

	CServerManager::getInstance();
	CServerManager::getInstance().createServer(5000);

    nFunRes = app.exec();

	CServerManager::getInstance().destoryServer(5000);
	CServerManager::removeInstance();

	CProjectEnviroment::removeInstance();

	return 0;
}




