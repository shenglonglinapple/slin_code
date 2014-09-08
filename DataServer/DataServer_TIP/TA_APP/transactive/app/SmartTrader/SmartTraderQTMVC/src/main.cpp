//qt app
//#include "vld.h"
#include <QtGui/QApplication>
#include <QtGui/QSplashScreen>
#include <QtGui/QPixmap>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QSharedMemory>
#include <QtCore/QFile>

#include "QTProjectEnvironment.h"
#include "ClientManager.h"

#include "CreateNewOrderDialog.h"
//
//

void setUpSplashScreen()
{
	QSplashScreen* splash = NULL;
	QString strSplashPictureFileName;
	Qt::Alignment topRight;
	qint64 nMilliseconds = 1000;

// 	QTextCodec::setCodecForTr(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
// 	QTextCodec::setCodecForLocale(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
// 	QTextCodec::setCodecForCStrings(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));

	strSplashPictureFileName = QObject::tr(":/images/splash");
	topRight = Qt::AlignRight | Qt::AlignTop;

	splash = new QSplashScreen();
	splash->setPixmap(QPixmap(strSplashPictureFileName));
	splash->move(0, 0);	
	splash->show();

	CQTProjectEnviroment::qtWaitTime(nMilliseconds);	
	//splash->finish(&clientMainWindow);

	if (NULL != splash)
	{
		delete splash;
		splash = NULL;
	}

	return;
}



int main(int argc, char *argv[])
{
	int nFunRes = 0;

	CQTProjectEnviroment::getInstance();


	//创建QApplication对象，管理整个应用程序的资源，通过argc和argv来获取它自己的命令行参数；
	QApplication app(argc, argv);


	//设置编码，一般在Window开发环境里，是GBK编码，在Linux开发环境里，是utf-8编码
	//获取系统编码，否则移植会出现乱码
	QTextCodec *codec = QTextCodec::codecForName("System"); 

	//设置和对本地文件系统读写时候的默认编码格式
	QTextCodec::setCodecForLocale(codec); 

	//设置传给tr函数时的默认字符串编码
	//QTextCodec::setCodecForTr(codec);
	//用在字符常量或者QByteArray构造QString对象时使用的一种编码方式
	//QTextCodec::setCodecForCStrings(codec);  

	//加载Qt中的资源文件，使Qt显示中文（包括QMessageBox、文本框右键菜单等）
	QTranslator translator;  
	translator.load(QString(":/language/qt_zh_CN"));  
	app.installTranslator(&translator);  


	//加载QSS样式表
	QFile qss(":/qss/SmartTraderQTMVC");
	qss.open(QFile::ReadOnly);
	//qApp->setStyleSheet(qss.readAll());//QCoreApplication::instance()
	qss.close();



	//CClientManager objClientWindow;

	//CCreateNewOrderDialog* pCCreateNewOrderDialog = new CCreateNewOrderDialog(NULL);
	//pCCreateNewOrderDialog->show();

	nFunRes = app.exec(); 

	CQTProjectEnviroment::removeInstance();

	return 0;
}


