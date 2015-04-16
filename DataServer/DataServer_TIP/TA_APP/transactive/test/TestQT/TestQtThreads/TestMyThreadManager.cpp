#include "TestMyThreadManager.h"
#include "MyThreadTest.h"
#include "SampleMyQtThread.h"

#include "Log4cppLogger.h"



CTestMyThreadManager::CTestMyThreadManager()
{
	_InitLog();
}

CTestMyThreadManager::~CTestMyThreadManager()
{
	_UnInitLog();
}

void CTestMyThreadManager::_InitLog()
{
	CLog4cppLogger::getInstance();
	CLog4cppLogger::getInstance().initLog();
	CLog4cppLogger::getInstance().testLog();
}

void CTestMyThreadManager::_UnInitLog()
{
	CLog4cppLogger::removeInstance();
}
void CTestMyThreadManager::do_test_mythread_1()
{
	CMyThreadTest* pMyThreadTest = NULL;
	pMyThreadTest = new CMyThreadTest(NULL);

	pMyThreadTest->my_start();

	pMyThreadTest->my_msleep(1000* 10);

	pMyThreadTest->my_terminateAndWait();

	delete pMyThreadTest;
	pMyThreadTest = NULL;
}

void CTestMyThreadManager::do_test_mythread_2()
{
	CSampleMyQtThread* pMyThreadTest = NULL;
	pMyThreadTest = new CSampleMyQtThread();

	pMyThreadTest->start();

	pMyThreadTest->my_msleep(1000* 10);

	pMyThreadTest->terminateAndWait();

	delete pMyThreadTest;
	pMyThreadTest = NULL;
}

