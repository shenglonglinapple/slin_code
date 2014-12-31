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


/*
typedef signed char qint8;  
typedef unsigned char quint8;
typedef short qint16;        
typedef unsigned short quint16;
typedef int qint32;            
typedef unsigned int quint32;  
typedef __int64 qint64;        
typedef unsigned __int64 quint64;
typedef qint64 qlonglong;
typedef quint64 qulonglong;
*/

#include "StockTcpServer.h"

#include "BaseException.h"
#include "Log4cppLogger.h"

void LogInit()
{
	CLog4cppLogger::getInstance();
	CLog4cppLogger::getInstance().initLog();
	CLog4cppLogger::getInstance().testLog();
}

void LogUnInit()
{
	CLog4cppLogger::removeInstance();
}

int main(int argc, char *argv[])
{
	qint32 nFunRes = 0;
    QApplication app(argc, argv);
	LogInit();
	CStockTcpServer* pServer;

	try
	{
		pServer->startListen();
	}
	catch (CBaseException& e)
	{
		e.logInfo(__FILE__, __LINE__);
	}

    nFunRes = app.exec();

	if (NULL != pServer)
	{
		pServer->stopListen();
		delete pServer;
		pServer = NULL;
	}
	LogUnInit();
	return 0;
}




