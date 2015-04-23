#include <iostream>
#include <QtGui/QApplication>
#include <QtCore/QDebug>

////////////////
//_WINDOWS;UNICODE;WIN32;QT_DLL;QT_HAVE_MMX;QT_HAVE_3DNOW;QT_HAVE_SSE;QT_HAVE_MMXEXT;QT_HAVE_SSE2;QT_GUI_LIB;QT_CORE_LIB;QT_THREAD_SUPPORT

////////////////
//sys
//#pragma comment(lib,"winmm.lib")
//#pragma comment(lib,"wldap32.lib")
//#pragma comment(lib,"ws2_32.lib")//winsock2

//qt
#pragma comment(lib,"qtmaind.lib")
#pragma comment(lib,"QtCored4.lib")
#pragma comment(lib,"QtGuid4.lib")
//#pragma comment(lib,"QtSqld4.lib")
//#pragma comment(lib,"QtNetworkd4.lib")
//#pragma comment(lib,"QtXmld4.lib")

//user
//#pragma comment(lib,"log4cppD.lib")
////////////////


#include "share/QtCppLogger.h"
#include <QtCore/QDebug>

#include "share/UiImageBorderWidget.h"
#include "share/UiCanResizeMoveWidget.h"


#include "share/UiCanMoveWidget.h"
#include "share/UiCanResizeWidget.h"
#include "UiTitleWidget.h"
#include "ClientLoginWindow.h"


int main(int argc, char *argv[])
{
	int ret = 0;
	QApplication app(argc, argv);

	//===============
#if QT_VERSION > 0x050000
	qInstallMessageHandler(Utils::Logger::messageHandler);
	QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#else
	qInstallMsgHandler(QtCppLogger::messageHandler);
#endif
	//===============
	QApplication::setApplicationName(QObject::tr("WizNote"));
	QApplication::setOrganizationName(QObject::tr("cn.wiz.wiznoteformac"));
	qDebug()<<"Test Log ret="<<ret;


	//CUiRect9GirdWidget objTest_CUiRect9GirdWidget;
	//objTest_CUiRect9GirdWidget.resize(200, 400);
	//objTest_CUiRect9GirdWidget.show();

	//CUiImageBorderWidget objTest_UiImageBorderWidget;
	//objTest_UiImageBorderWidget.resize(200, 400);
	//objTest_UiImageBorderWidget.show();

	//CUiCanMoveWindow objTest_CUiCanMoveWindow;
	//objTest_CUiCanMoveWindow.resize(200, 400);
	//objTest_CUiCanMoveWindow.show();

	//CUiCanResizeWindow objTest_CUiCanResizeWindow;
	//objTest_CUiCanResizeWindow.resize(200, 400);
	//objTest_CUiCanResizeWindow.show();

	//CUiCanMoveResizeWidget objTest_CUiCanMoveResizeWindow;
	//objTest_CUiCanMoveResizeWindow.resize(300, 500);
	//objTest_CUiCanMoveResizeWindow.show();

	//CUiCanResizeMoveWidget objTest_CUiCanResizeMoveWidget;
	//objTest_CUiCanResizeMoveWidget.resize(300, 500);
	//objTest_CUiCanResizeMoveWidget.show();

	//CUiTitleWidget objTest_CUiTitleWidget;
	//objTest_CUiTitleWidget.resize(300, 50);
	//objTest_CUiTitleWidget.show();

	CClientLoginWindow objTest_CClientLoginWindow;
	objTest_CClientLoginWindow.resize(300, 500);
	objTest_CClientLoginWindow.show();

	ret = app.exec();
	return ret;
}

