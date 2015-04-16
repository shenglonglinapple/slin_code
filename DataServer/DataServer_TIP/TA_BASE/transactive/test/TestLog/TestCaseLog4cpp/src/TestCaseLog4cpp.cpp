#include "TestCaseLog4cpp.h"


#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>


#include <iostream>  
#include "log4cpp/Category.hh"  
#include "log4cpp/PropertyConfigurator.hh"  

#include "log4cpp/OstreamAppender.hh"  
#include "log4cpp/FileAppender.hh" 
#include "log4cpp/RollingFileAppender.hh"  

#include "log4cpp/Win32DebugAppender.hh"  
#include "log4cpp/PatternLayout.hh"  
#include "log4cpp/BasicLayout.hh"  

#include "core/utilities/src/Log4cppLogger.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;



NS_BEGIN(TA_Base_Test) 


//////////////////////////////////////////////////////////////////////////
CTestCaseLog4cpp::CTestCaseLog4cpp(void)
{	

	_TestLog4Cpp_ByManualOperation();
	_TestLog4Cpp_ByManualOperation2();
	//_TestLog4Cpp_ByCfgFile();
	_TestLog4Cpp_ByCfgFile2();
}

CTestCaseLog4cpp::~CTestCaseLog4cpp(void)
{


}

void CTestCaseLog4cpp::_TestLog4Cpp_ByManualOperation(void)
{
	//NOTSET < DEBUG < INFO < NOTICE < WARN < ERROR < CRIT < ALERT < FATAL = EMERG
	// 1实例化一个layout 对象
	log4cpp::Layout* layout = new log4cpp::BasicLayout();

	// 2. 初始化一个appender 对象
	log4cpp::Appender* appender = new log4cpp::FileAppender("FileAppender",	"./LOGT/TestLog4cppByManual.log");

	// 3. 把layout对象附着在appender对象上
	appender->setLayout(layout);

	// 4. 实例化一个category对象
	log4cpp::Category& warn_log = log4cpp::Category::getInstance("mywarn");

	// 5. 设置additivity为false，替换已有的appender
	warn_log.setAdditivity(false);

	// 5. 把appender对象附到category上
	warn_log.setAppender(appender);

	// 6. 设置category的优先级，低于此优先级的日志不被记录
	warn_log.setPriority(log4cpp::Priority::DEBUG);

	// 记录一些日志
	warn_log.info("Program info which cannot be wirten");
	warn_log.debug("This debug message will fail to write");
	warn_log.alert("Alert info");
	// 其他记录日志方式
	warn_log.log(log4cpp::Priority::WARN, "This will be a logged warning");
	log4cpp::Priority::PriorityLevel priority;
	bool this_is_critical = true;
	if(this_is_critical)
		priority = log4cpp::Priority::CRIT;
	else
		priority = log4cpp::Priority::DEBUG;
	warn_log.log(priority,"Importance depends on context");

	warn_log.critStream() << "This will show up << as "<< 1 << " critical message";

	warn_log.infoStream() << "infoStream newline";
	warn_log.debugStream() << "debugStream newline";
	warn_log.errorStream() << "errorStream newline";
	warn_log.warnStream() << "errorStream newline";
	warn_log.noticeStream() << "errorStream newline";
	warn_log.fatalStream() << "errorStream newline";
	// clean up and flush all appenders
	log4cpp::Category::shutdown();

}

void CTestCaseLog4cpp::_TestLog4Cpp_ByCfgFile( void )
{
	try
	{  
		log4cpp::PropertyConfigurator::configure("./log4cpp.conf");  
	}
	catch(log4cpp::ConfigureFailure& f)
	{  
		std::cout<<f.what()<<std::endl;  
	}  

	log4cpp::Category &cat=log4cpp::Category::getInstance("rootAppender");  

	cat.info("system is running");  
	cat.warn("system has a warning");  
	cat.error("system has a error, can't find a file");  
	cat.fatal("system has a fatal error,must be shutdown");  
	cat.info("system shutdown,you can find some information in system log");  
	cat.critStream() << "This will show up << as "<< 1 << " critical message";

	log4cpp::Category::shutdown();  


}

void CTestCaseLog4cpp::_TestLog4Cpp_ByManualOperation2( void )
{
	/*
	%m log message 内容, 即 用户写 log 的具体信息
	%n 回车换行
	%c category 名字
	%d 时间戳
	%p 优先级
	%r 距离上一次写 log 的间隔, 单位毫秒
	%R 距离上一次写 log 的间隔, 单位秒
	%t 线程名
	%u 处理器时间
	%x NDC ?
	*/

	log4cpp::Appender *osa;  
	//osa=new OstreamAppender("osa",&cout);  
	//osa=new Win32DebugAppender("osa");  
	osa=new log4cpp::RollingFileAppender("osa", "./LOGT/TestLog4cppByManual2.log" ,10*1024*1024, 100); //"./LOGT/TestLog4cppByManual.log" 
	log4cpp::PatternLayout *layout=new log4cpp::PatternLayout();  
	//layout->setConversionPattern("%d: %p %c %x: %m%n");  
	layout->setConversionPattern("%d{%Y-%m-%d %H:%M:%S:%l}: %p %c %x: %t %m%n");  
	//%d{%Y-%m-%d %H:%M:%S:%l}: %p %c %x: %m%n
	osa->setLayout(layout);  

	//log4cpp::Category &cat=log4cpp::Category::getInstance("rootAppender");  
	log4cpp::Category::getInstance("rootAppender").addAppender(osa);  
	log4cpp::Category::getInstance("rootAppender").setPriority(log4cpp::Priority::DEBUG);  

	for(int i=0;i<100;++i)
	{  
		log4cpp::Category::getInstance("rootAppender").info("system is running");  
		log4cpp::Category::getInstance("rootAppender").warn("system has a warning");  
		log4cpp::Category::getInstance("rootAppender").error("system has a error, can't find a file");  
		log4cpp::Category::getInstance("rootAppender").fatal("system has a fatal error,must be shutdown");  
		log4cpp::Category::getInstance("rootAppender").info("system shutdown,you can find some information in system log");  
	}  
	log4cpp::Category::getInstance("rootAppender").debugStream() << " debugStream This will show up << as "<< 1 << " critical message";

	log4cpp::Category::shutdown();  
}

void CTestCaseLog4cpp::_TestLog4Cpp_ByCfgFile2( void )
{
	TA_Base_Core::CLog4cppLogger::getInstance();
	TA_Base_Core::CLog4cppLogger::getInstance().initLog();
	TA_Base_Core::CLog4cppLogger::getInstance().testLog();
	TA_Base_Core::CLog4cppLogger::removeInstance();
}



NS_END(TA_Base_Test) 



