#ifndef __CLASS_LOG4CPP_LOGGER__HH__
#define __CLASS_LOG4CPP_LOGGER__HH__

#include <iostream>  
#include "log4cpp/Category.hh"  
#include "log4cpp/PropertyConfigurator.hh"  

#include "log4cpp/OstreamAppender.hh"  
#include "log4cpp/FileAppender.hh" 
#include "log4cpp/RollingFileAppender.hh"  

#include "log4cpp/Win32DebugAppender.hh"  
#include "log4cpp/PatternLayout.hh"  
#include "log4cpp/BasicLayout.hh"  

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>


//////////////////////////////////////////////////////////////////////////
#define USING_LOG4CPP_LOG      extern int g_CLog4Logger_handle;
#define LOG4CPPFLInfo			__FILE__, __LINE__

#define LOG4CPPSourceFLInfo    " ["<<__FILE__<<":"<<__LINE__<<"] "

#define  MYLOG4CPP_TRACE      log4cpp::Category::getInstance("rootAppender").debugStream()<<LOG4CPPSourceFLInfo
#define  MYLOG4CPP_DEBUG      log4cpp::Category::getInstance("rootAppender").debugStream()<<LOG4CPPSourceFLInfo
#define  MYLOG4CPP_INFO       log4cpp::Category::getInstance("rootAppender").infoStream()<<LOG4CPPSourceFLInfo
#define  MYLOG4CPP_WARNING    log4cpp::Category::getInstance("rootAppender").warnStream()<<LOG4CPPSourceFLInfo
#define  MYLOG4CPP_ERROR      log4cpp::Category::getInstance("rootAppender").errorStream()<<LOG4CPPSourceFLInfo
#define  MYLOG4CPP_FATAL      log4cpp::Category::getInstance("rootAppender").fatalStream()<<LOG4CPPSourceFLInfo

#define  MYLOG4CPP_ERROR_Base      log4cpp::Category::getInstance("rootAppender").errorStream()<<""
#define  MYLOG4CPP_DEBUG_Base      log4cpp::Category::getInstance("rootAppender").debugStream()<<""

//////////////////////////////////////////////////////////////////////////



#if 0
//NOTSET < DEBUG < INFO < NOTICE < WARN < ERROR < CRIT < ALERT < FATAL = EMERG
#endif


class CLog4cppLogger
{
public:
	static CLog4cppLogger& getInstance();
	static void removeInstance();

private:
	static CLog4cppLogger* m_pInstance;
	static QMutex m_mutexInstance;

private:
	CLog4cppLogger(void);	
	~CLog4cppLogger(void);

public:
	void setLogPath(const std::string& strLogPath);
	void setLogFileName(const std::string& strLogFileName);
	void setLogLevel(log4cpp::Priority::PriorityLevel nLogLevel);

	int initLog();
	int testLog();

private:
	std::string m_strLogPath;// = "./";
	std::string m_strLogFileName;// = "Sample_Log.log";
	log4cpp::Priority::PriorityLevel m_nLogLevel;


};//class


#endif // __CLASS_LOG4CPP_LOGGER__HH__









