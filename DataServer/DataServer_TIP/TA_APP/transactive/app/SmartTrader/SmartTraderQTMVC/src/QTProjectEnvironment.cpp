#include "QTProjectEnvironment.h"


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

//#include <boost/foreach.hpp>

#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


CQTProjectEnviroment* CQTProjectEnviroment::m_pInstance = 0;
boost::mutex CQTProjectEnviroment::m_mutexInstance;

CQTProjectEnviroment& CQTProjectEnviroment::getInstance()
{	
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CQTProjectEnviroment();
	}
	return (*m_pInstance);
}

void CQTProjectEnviroment::removeInstance()
{
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}


CQTProjectEnviroment::CQTProjectEnviroment( void )
{
	_InitBoostLog();
	_RedirectQTLogToBoostLog();
	_TestQTLog();
	_PrintSupportDBType();
	//_SetQTProjectEnvFont();
}

CQTProjectEnviroment::~CQTProjectEnviroment( void )
{
	_UnInitBoostLog();
}


void CQTProjectEnviroment::_InitBoostLog()
{
	//init CBoostLogger
	CBoostLogger::getInstance();

	std::string strLogPath = "ALL_LOG_PATH";
	//std::string strLogFileName = "Test_Log_%Y-%m-%d_%H_%M_%S_%f_%4N.log";
	std::string strLogFileName = "SmartTrader_Log_%Y-%m-%d_%H_%M_%S.log";
	boost::log::trivial::severity_level nLogLevel = boost::log::trivial::trace;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::info;
	//boost::log::trivial::severity_level nLogLevel = boost::log::trivial::debug;
	CBoostLogger::getInstance().setLogPath(strLogPath);
	CBoostLogger::getInstance().setLogFileName(strLogFileName);
	CBoostLogger::getInstance().setLogLevel(nLogLevel);
	CBoostLogger::getInstance().initBoostLog();
	CBoostLogger::getInstance().testBoostLog();
}
void CQTProjectEnviroment::_UnInitBoostLog()
{
	CBoostLogger::removeInstance();
}

int CQTProjectEnviroment::_RedirectQTLogToBoostLog()
{
	//QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

	/**< install qDebug function handler.*/
	qInstallMsgHandler(logMsgHandlerToBoostLog);

	return 0;
}

int CQTProjectEnviroment::_TestQTLog()
{
	qDebug()<<"QTLogTest qDebug";
	qWarning()<<"QTLogTest qWarning";
	qCritical()<<"QTLogTest qCritical";

	//qFatal<<"QTLogTest qFatal";//will crash exe
	return 0;
}




/**
//typedef void (*QtMsgHandler)(QtMsgType, const char *);
//Q_CORE_EXPORT QtMsgHandler qInstallMsgHandler(QtMsgHandler);
* @brief  custom message handler
* @param type [QtMsgType]
* @param msg [const char *]
* @return void
*/
void CQTProjectEnviroment::logMsgHandlerToBoostLog( QtMsgType type, const char *msg )
{
	QString strLog;

	strLog = "---QTLOG---";

	switch (type) 
	{
	case QtDebugMsg:
		strLog += QObject::tr(msg);
		LOG_DEBUG<<strLog.toStdString();
		break;
	case QtWarningMsg:
		strLog += QObject::tr(msg);
		LOG_WARNING<<strLog.toStdString();
		break;
	case QtCriticalMsg:
		strLog += QObject::tr(msg);
		LOG_ERROR<<strLog.toStdString();
		break;
	case QtFatalMsg:
		strLog += QObject::tr(msg);
		LOG_FATAL<<strLog.toStdString();
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
void CQTProjectEnviroment::logMsgHandlerToUsrFile( QtMsgType type, const char *msg )
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



void CQTProjectEnviroment::_PrintSupportDBType()
{
	qDebug() << "Available drivers:";
	QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
	{
		qDebug() << "\t" << driver;
	}
}


void CQTProjectEnviroment::_SetFont()
{
	//set Font
	QTextCodec* tc = NULL;
	//tc=QTextCodec::codecForName("utf-8");
	//tc = QTextCodec::codecForLocale();
	tc = QTextCodec::codecForName("gb2312");
	QTextCodec::setCodecForTr(tc);

	QFont font("Times", 10, QFont::Normal, FALSE);
	//app.setFont(font);
	//qt designer qtconfig font = Bitstream Charter


	QFont m_QTProjectEnvFont = font;
}




void CQTProjectEnviroment::qtWaitTime(qint64 milliseconds)
{
	QElapsedTimer timeElapsedTimer;
	timeElapsedTimer.start();
	while(timeElapsedTimer.elapsed() < milliseconds)
	{
		QCoreApplication::processEvents();
	}
}

//QT_END_NAMESPACE












