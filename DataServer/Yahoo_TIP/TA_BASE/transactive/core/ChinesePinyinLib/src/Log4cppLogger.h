#ifndef __CLASS_LOG4CPP_LOGGER__HH__
#define __CLASS_LOG4CPP_LOGGER__HH__

//#include <iostream>  

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "log4cpp/Category.hh"  
 



//////////////////////////////////////////////////////////////////////////
#define LOG4CPPFLInfo			__FILE__, __LINE__
#define LOG4CPPSourceFLInfo    " "<<"["<<__FILE__<<":"<<__LINE__<<"]"<<" "

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
	void setLogLevel(log4cpp::Priority::PriorityLevel nLogLevel);

	qint32 initLog();
	void testLog();
private:
	log4cpp::Priority::PriorityLevel m_nLogLevel;


};//class


#endif // __CLASS_LOG4CPP_LOGGER__HH__









