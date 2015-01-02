#ifndef __CLASS_PROJECT_ENVIRONMENT_HH__
#define __CLASS_PROJECT_ENVIRONMENT_HH__

#include <Qtcore/QGlobalStatic>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CProjectEnviroment
{
public:
	static CProjectEnviroment& getInstance();
	static void removeInstance();

private:
	static CProjectEnviroment* m_pInstance;
	static QMutex m_mutexInstance;

private:
	CProjectEnviroment(void);	
	~CProjectEnviroment(void);
public:
	static void qtWaitTime(qint64 milliseconds);
public:
	/*
	//qglobal.h  qglobal.cpp
	//enum QtMsgType { QtDebugMsg, QtWarningMsg, QtCriticalMsg, QtFatalMsg, QtSystemMsg = QtCriticalMsg };
	//Log4Qt http://log4qt.sourceforge.net/
	//set qDebug() info to Project log
	*/
	static void logMsgHandlerToProjectLog(QtMsgType type, const char *msg);
	static void logMsgHandlerToUsrFile(QtMsgType type, const char *msg);
	
private:
	void _ReSetQTLog();
	void _TestQTLog();
	void _CheckSupportDBType();
	void _SetFont();
	void _InitLog();
	void _UnInitLog();
};//class


//QT_END_NAMESPACE

#endif // __CLASS_PROJECT_ENVIRONMENT_HH__









