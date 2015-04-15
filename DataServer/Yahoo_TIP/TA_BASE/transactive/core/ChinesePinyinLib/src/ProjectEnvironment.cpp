#include "ProjectEnvironment.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>
#include <QtCore/QTextCodec>

#include <Qtcore/QGlobalStatic>
#include <QtCore/QtDebug>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDateTime>

//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>

//qt db
#include <QtSql/QtSql>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


CProjectEnvironment* CProjectEnvironment::m_pInstance = 0;
QMutex CProjectEnvironment::m_mutexInstance;

CProjectEnvironment& CProjectEnvironment::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CProjectEnvironment();
	}
	return (*m_pInstance);
}

void CProjectEnvironment::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}


CProjectEnvironment::CProjectEnvironment( void )
{
	_InitLog();
	_ReSetQTLog();
	_TestQTLog();
	_CheckSupportDBType();
}

CProjectEnvironment::~CProjectEnvironment( void )
{
	_UnInitLog();
}

void CProjectEnvironment::_ReSetQTLog()
{
	//QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	/**< install qDebug function handler.*/
	qInstallMsgHandler(logMsgHandlerToProjectLog);
}

void CProjectEnvironment::_TestQTLog()
{
	qDebug()<<"QTLogTest qDebug";
	qWarning()<<"QTLogTest qWarning";
	qCritical()<<"QTLogTest qCritical";
	//qFatal<<"QTLogTest qFatal";//will crash exe
}




/**
//typedef void (*QtMsgHandler)(QtMsgType, const char *);
//Q_CORE_EXPORT QtMsgHandler qInstallMsgHandler(QtMsgHandler);
* @brief  custom message handler
* @param type [QtMsgType]
* @param msg [const char *]
* @return void
*/
void CProjectEnvironment::logMsgHandlerToProjectLog( QtMsgType type, const char *msg )
{
	QString strLog;

	strLog = "---QTLOG---";

	switch (type) 
	{
	case QtDebugMsg:
		strLog += QObject::tr(msg);
		MYLOG4CPP_DEBUG<<strLog.toStdString();
		break;
	case QtWarningMsg:
		strLog += QObject::tr(msg);
		MYLOG4CPP_WARNING<<strLog.toStdString();
		break;
	case QtCriticalMsg:
		strLog += QObject::tr(msg);
		MYLOG4CPP_ERROR<<strLog.toStdString();
		break;
	case QtFatalMsg:
		strLog += QObject::tr(msg);
		MYLOG4CPP_FATAL<<strLog.toStdString();
		//abort();
	default:
		break;
	}//switch
}




/**
//typedef void (*QtMsgHandler)(QtMsgType, const char *);
//Q_CORE_EXPORT QtMsgHandler qInstallMsgHandler(QtMsgHandler);
* @brief  custom message handler
* @param type [QtMsgType]
* @param msg [const char *]
* @return void
*/
void CProjectEnvironment::logMsgHandlerToUsrFile( QtMsgType type, const char *msg )
{
	QString strLog;

	strLog = "---QTLOG---";

	switch (type) 
	{
	case QtDebugMsg:
		//program msg
		strLog += QString(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss ")+"[Debug] %1").arg(QObject::tr(msg));
		break;
	case QtWarningMsg:
		//program warning
		strLog += QString(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss ")+"[Warn] %1").arg(QObject::tr(msg));
		break;
	case QtCriticalMsg:
		//program error
		strLog += QString(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss ")+"[Critical] %1").arg(QObject::tr(msg));
		break;
	case QtFatalMsg:
		//program  crash error
		strLog = QString(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss ")+"[Fatal] %1").arg(QObject::tr(msg));
		//abort();
	default:
		break;
	}//switch

	QFile outFile("QT_LOG_FILE.log");
	outFile.open(QIODevice::WriteOnly | QIODevice::Append);
	// 	/**< the max size of log.txt.*/
	if(outFile.size()/1000>10000000)
	{
		outFile.close();
		outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Truncate);
		outFile.close();
		outFile.open(QIODevice::WriteOnly | QIODevice::Append);
	}
	QTextStream ts(&outFile);
	ts << strLog << endl;
}



void CProjectEnvironment::_CheckSupportDBType()
{
	qDebug() << "Available drivers:";
	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
	{
		qDebug() << "\t" << driver;
	}
}


void CProjectEnvironment::_SetFont()
{
	//set Font
	QTextCodec* tc = NULL;
	//tc=QTextCodec::codecForName("utf-8");
	//tc = QTextCodec::codecForLocale();
	tc = QTextCodec::codecForName("gb2312");
	QTextCodec::setCodecForTr(tc);

	//QFont font("Times", 10, QFont::Normal, FALSE);
	//app.setFont(font);
	//qt designer qtconfig font = Bitstream Charter


	//QFont m_QTProjectEnvFont = font;

	//为QObject::tr设置字符编码
	//QTextCodec::setCodecForTr( QTextCodec::codecForName( "GB18030" ));
	//如果在linux上，设置local为gb18030可能会导致读取//或输出的unicode中文字符不能正确显示
	//QTextCodec::setCodecForLocale( QTextCodec::codecForName( "GB18030" ));  
	//为QString设置字符编码，默认情况下为Latin1
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName( "GB18030" ) );  
	//QString testStr = QObject::tr("测试");
}




void CProjectEnvironment::qtWaitTime(qint64 milliseconds)
{
	//QThread::exec() waits until QThread::exit() called
	QElapsedTimer timeElapsedTimer;
	timeElapsedTimer.start();
	while(timeElapsedTimer.elapsed() < milliseconds)
	{
		QCoreApplication::processEvents();
	}
}

void CProjectEnvironment::_InitLog()
{
	CLog4cppLogger::getInstance();
	CLog4cppLogger::getInstance().initLog();
	CLog4cppLogger::getInstance().testLog();
}

void CProjectEnvironment::_UnInitLog()
{
	CLog4cppLogger::removeInstance();
}

//QT_END_NAMESPACE












