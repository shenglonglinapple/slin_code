#include "Log4cppLogger.h"

#include <iostream>  
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "log4cpp/Category.hh"  
#include "log4cpp/PropertyConfigurator.hh"  

#include "log4cpp/OstreamAppender.hh"  
#include "log4cpp/FileAppender.hh" 
#include "log4cpp/RollingFileAppender.hh"  

#include "log4cpp/Win32DebugAppender.hh"  
#include "log4cpp/PatternLayout.hh"  
#include "log4cpp/BasicLayout.hh"  


static const char* DEF_STR_LOG4CPP_CONF = "./log4cpp.conf";
static const char* DEF_STR_CATEGORY_ROOTAPPENDER = "rootAppender";




CLog4cppLogger* CLog4cppLogger::m_pInstance = 0;
QMutex CLog4cppLogger::m_mutexInstance;

CLog4cppLogger& CLog4cppLogger::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CLog4cppLogger();
	}
	return (*m_pInstance);
}

void CLog4cppLogger::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}

	
}


CLog4cppLogger::CLog4cppLogger( void )
{
	m_nLogLevel = log4cpp::Priority::DEBUG;
}

CLog4cppLogger::~CLog4cppLogger( void )
{
	log4cpp::Category::shutdown();  
}




void CLog4cppLogger::setLogLevel( log4cpp::Priority::PriorityLevel nLogLevel )
{
	m_nLogLevel = nLogLevel;
	log4cpp::Category::getInstance(DEF_STR_CATEGORY_ROOTAPPENDER).setPriority(m_nLogLevel);  
}


qint32 CLog4cppLogger::initLog()
{
	qint32 nFunRes = 0;

	try
	{  
		log4cpp::PropertyConfigurator::configure(DEF_STR_LOG4CPP_CONF);  
	}
	catch(log4cpp::ConfigureFailure& f)
	{  
		std::cout<<f.what()<<std::endl;  
		nFunRes = -1;
	}  

	log4cpp::Category& cat = log4cpp::Category::getInstance(DEF_STR_CATEGORY_ROOTAPPENDER);  

	return nFunRes;
}

void CLog4cppLogger::testLog()
{
	MYLOG4CPP_TRACE<<"===================================================================================";

	MYLOG4CPP_TRACE<<"DEF_STR_LOG4CPP_CONF="<<DEF_STR_LOG4CPP_CONF
				   <<" "<<"DEF_STR_CATEGORY_ROOTAPPENDER="<<DEF_STR_CATEGORY_ROOTAPPENDER;

	MYLOG4CPP_TRACE<<"LOG4CPP_TRACE";
	MYLOG4CPP_DEBUG<<"LOG4CPP_DEBUG";
	MYLOG4CPP_INFO<<"LOG4CPP_INFO";
	MYLOG4CPP_WARNING<<"LOG4CPP_WARNING";
	MYLOG4CPP_ERROR<<"LOG4CPP_ERROR";
	MYLOG4CPP_FATAL<<"LOG4CPP_FATAL";
	//MYLOG4CPP_ERROR_Base<<__FILE__<<" "<<__LINE__<<"LOG4CPP_FATAL";

	MYLOG4CPP_TRACE<<"===================================================================================";

	return;
}


#if 0
#include "Log4cppLogger.h"
USING_LOG4CPP_LOG

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
#endif//#if 0

