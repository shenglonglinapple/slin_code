#include "MyThreadWithTimerTest.h"

#include "Log4cppLogger.h"


CMyThreadWithTimerTest::CMyThreadWithTimerTest( QObject *parent /*= 0*/ ) : QObject(parent)
{
	MYLOG4CPP_DEBUG<<"CMyThreadWithTimerTest::CMyThreadWithTimerTest"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId();
	m_pThread = NULL;
	m_pThread = new QThread(parent);
	m_Timer.setInterval(1000);

	m_Timer.moveToThread(m_pThread);
	this->moveToThread(m_pThread);

	QObject::connect(m_pThread, SIGNAL(started()), &m_Timer, SLOT(start()));
	QObject::connect(this, SIGNAL(signalDoSomething()), this, SLOT(slotDoSomething()));
	QObject::connect(&m_Timer, SIGNAL(timeout()), this, SLOT(trigger()));

	m_pThread->start();
}

CMyThreadWithTimerTest::~CMyThreadWithTimerTest()
{
	MYLOG4CPP_DEBUG<<"CMyThreadWithTimerTest::~CMyThreadWithTimerTest"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId();

	m_Timer.stop();

	m_pThread->quit();

	delete m_pThread;
	m_pThread = NULL;
}

void CMyThreadWithTimerTest::trigger()
{
	MYLOG4CPP_DEBUG<<"CMyThreadWithTimerTest emit signalDoSomething"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId();
	emit signalDoSomething();
}

void CMyThreadWithTimerTest::slotDoSomething()
{
	MYLOG4CPP_DEBUG<<"CMyThreadWithTimerTest slotDoSomething"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId();

}

