
#ifndef __CLASS_QT_PROJECT_ENVIRONMENT_HH__
#define __CLASS_QT_PROJECT_ENVIRONMENT_HH__


#include <Qtcore/QGlobalStatic>
#include <QtCore/QtDebug>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDateTime>
#include <QtCore/QTextCodec>
#include <QtGui/QFont>


#include <boost/chrono.hpp>
#include <boost/thread.hpp>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CQTProjectEnvironment
{
public:
	static CQTProjectEnvironment& getInstance();
	static void removeInstance();

private:
	static CQTProjectEnvironment* m_pInstance;
	static boost::mutex m_mutexInstance;

private:
	CQTProjectEnvironment(void);	
	~CQTProjectEnvironment(void);
public:
	static void qtWaitTime(qint64 milliseconds);
public:
	QFont getQTProjectEnvFont();

public:
	/*
	//qglobal.h  qglobal.cpp
	//enum QtMsgType { QtDebugMsg, QtWarningMsg, QtCriticalMsg, QtFatalMsg, QtSystemMsg = QtCriticalMsg };
	//Log4Qt http://log4qt.sourceforge.net/
	//set qDebug() info to boost log
	*/
	static void logMsgHandlerToBoostLog(QtMsgType type, const char *msg);

	static void logMsgHandlerToUsrFile(QtMsgType type, const char *msg);

	
private:
	int _SetQTLogToBoostLog();
	int _QTLogTest();
	void _LogQTProjectEnvSupportDBType();
	void _SetQTProjectEnvFont();
	
private:
	QFont m_QTProjectEnvFont;
};//class


//QT_END_NAMESPACE

#endif // __CLASS_QT_PROJECT_ENVIRONMENT_HH__









