#include "TestCaseLog4qt.h"

#include <QtCore/QFileInfo>

#include <QtCore/QDateTime>
#include <QtCore/QString>
#include <QtCore/QDir>

#include "log4qt/logger.h"
#include "log4qt/fileappender.h"
#include "log4qt/ttcclayout.h"
#include "log4qt/patternlayout.h"
#include "log4qt/logmanager.h"


using namespace std;
using namespace Log4Qt;

//////////////////////////////////////////////////////////////////////////
CTestCaseLog4qt::CTestCaseLog4qt(void)
{	
	_Test_CFG_1();
}

CTestCaseLog4qt::~CTestCaseLog4qt(void)
{


}

void CTestCaseLog4qt::_Test_CFG_1()
{
	//声明日志器，保存并跟踪对象日志信息变更的实体
	Logger* logger = Log4Qt::Logger::rootLogger();
	logger->removeAllAppenders();
	//创建日志文件
	Log4Qt::FileAppender *fileappender=new Log4Qt::FileAppender();
	fileappender->setName("MyLogger");
	//设置日志名
	QFileInfo fileinfo(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".log");
	fileappender->setFile(fileinfo.filePath());
	//设置日志格式
	//Log4Qt::TTCCLayout *filelayout = new Log4Qt::TTCCLayout(Log4Qt::TTCCLayout::ISO8601);
	Log4Qt::PatternLayout *filelayout= new Log4Qt::PatternLayout("%d %p-%m %n");
	fileappender->setLayout(filelayout);
	fileappender->activateOptions();
	logger->addAppender(fileappender);

	// Request a logger and output "Hello World!"
	Log4Qt::Logger::logger(QLatin1String("MyLogger"))->info("Hello World!");
}

void CTestCaseLog4qt::_Test_CFG_2()
{
	
}

/*
layout有三种类型，可以是：
PatternLayout（可以灵活地指定布局模式）， 
SimpleLayout（包含日志信息的级别和信息字符串）， 
TTCCLayout（包含日志产生的时间、线程、类别等等信息） 
具体讲解可参照第三部分定义配置文件中的Layout。 
如果使用pattern布局就要指定的打印信息的具体格式ConversionPattern，打印参数如下： 
　　%m 输出代码中指定的消息 
  　%p 输出优先级，即DEBUG，INFO，WARN，ERROR，FATAL 
	%r 输出自应用启动到输出该log信息耗费的毫秒数 
	%c 输出所属的类目，通常就是所在类的全名 
	%t 输出产生该日志事件的线程名 
	%n 输出一个回车换行符，Windows平台为“n”，Unix平台为“rn（不确定）” 
	%d 输出日志时间点的日期或时间，默认格式为ISO8601，也可以在其后指定格式，比如：%d{yyyy MMM dd HH:mm:ss,SSS}，输出类似：2002年10月18日 22：10：28，921 
	%l 输出日志事件的发生位置，包括类目名、发生的线程，以及在代码中的行数。 
*/



