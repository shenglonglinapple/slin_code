#include "Log4cppLogger.h"


static const std::string DEF_STR_LOG4CPP_CONF = "./log4cpp.conf";
static const std::string DEF_STR_CATEGORY_ROOTAPPENDER = "rootAppender";

static const std::string DEF_STR_LOG_PATH = "./";
static const std::string DEF_STR_LOG_FILENAME = "Sample_log.log";

int g_CLog4Logger_handle = 1;


CLog4cppLogger* CLog4cppLogger::m_pInstance = 0;
boost::mutex CLog4cppLogger::m_mutexInstance;

CLog4cppLogger& CLog4cppLogger::getInstance()
{	
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CLog4cppLogger();
	}
	return (*m_pInstance);
}

void CLog4cppLogger::removeInstance()
{
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;
	
}


CLog4cppLogger::CLog4cppLogger( void )
{
	m_strLogPath = DEF_STR_LOG_PATH;
	m_strLogFileName = DEF_STR_LOG_FILENAME;
	m_nLogLevel = log4cpp::Priority::DEBUG;
}

CLog4cppLogger::~CLog4cppLogger( void )
{
	log4cpp::Category::shutdown();  
}


void CLog4cppLogger::setLogPath(const std::string& strLogPath)
{
	m_strLogPath = strLogPath;
}
void CLog4cppLogger::setLogFileName(const std::string& strLogFileName)
{
	m_strLogFileName = strLogFileName;
}


void CLog4cppLogger::setLogLevel( log4cpp::Priority::PriorityLevel nLogLevel )
{
	m_nLogLevel = nLogLevel;
	log4cpp::Category::getInstance(DEF_STR_CATEGORY_ROOTAPPENDER).setPriority(m_nLogLevel);  
}


int CLog4cppLogger::initLog()
{
	int nFunRes = 0;
	std::string strLogPath = m_strLogPath;
	std::string strLogFileName = m_strLogFileName;

	try
	{  
		log4cpp::PropertyConfigurator::configure(DEF_STR_LOG4CPP_CONF);  
	}
	catch(log4cpp::ConfigureFailure& f)
	{  
		std::cout<<f.what()<<std::endl;  
		nFunRes = -1;
	}  

	log4cpp::Category &cat=log4cpp::Category::getInstance(DEF_STR_CATEGORY_ROOTAPPENDER);  

	return nFunRes;
}

int CLog4cppLogger::testLog()
{
	MYLOG4CPP_TRACE<<"===================================================================================";
	MYLOG4CPP_TRACE<<"DEF_STR_LOG4CPP_CONF="<<DEF_STR_LOG4CPP_CONF
		<<" "<<"DEF_STR_CATEGORY_ROOTAPPENDER="<<DEF_STR_CATEGORY_ROOTAPPENDER
		<<" "<<"DEF_STR_LOG_PATH="<<DEF_STR_LOG_PATH		
		<<" "<<"DEF_STR_LOG_FILENAME="<<DEF_STR_LOG_FILENAME;
	MYLOG4CPP_TRACE<<"===================================================================================";


	MYLOG4CPP_TRACE<<"LOG4CPP_TRACE";
	MYLOG4CPP_DEBUG<<"LOG4CPP_DEBUG";
	MYLOG4CPP_INFO<<"LOG4CPP_INFO";
	MYLOG4CPP_WARNING<<"LOG4CPP_WARNING";
	MYLOG4CPP_ERROR<<"LOG4CPP_ERROR";
	MYLOG4CPP_FATAL<<"LOG4CPP_FATAL";
	MYLOG4CPP_ERROR_Base<<__FILE__<<" "<<__LINE__<<"LOG4CPP_FATAL";

	return 0;
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

void BoostLogUnInit()
{
	CLog4cppLogger::removeInstance();
}
#endif//#if 0

















