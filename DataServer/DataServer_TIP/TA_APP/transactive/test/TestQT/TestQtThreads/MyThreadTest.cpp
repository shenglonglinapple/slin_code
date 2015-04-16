#include "MyThreadTest.h"

#include "Log4cppLogger.h"


//CMyThreadTest::CMyThreadTest( QObject *parent /*= 0*/ ) : QObject(parent)
CMyThreadTest::CMyThreadTest( QObject *parent /*= 0*/ ) : QThread(parent)
{	
	MYLOG4CPP_DEBUG<<"CMyThreadTest::CMyThreadTest"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId();
	
	m_toTerminate = false;
	m_nThreadJobState = JobState_Begin;

	m_pThread = NULL;
	m_pThread = new QThread(parent);	
	this->moveToThread(m_pThread);
	QObject::connect(m_pThread, SIGNAL(started()), this, SLOT(slot_my_thread_run()));
}

CMyThreadTest::~CMyThreadTest()
{
	MYLOG4CPP_DEBUG<<"CMyThreadTest::~CMyThreadTest"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId();

	if (false == m_toTerminate)
	{
		my_terminateAndWait();
	}
	if (NULL != m_pThread)
	{
		delete m_pThread;
		m_pThread = NULL;
	}
}

void CMyThreadTest::my_start()
{
	MYLOG4CPP_DEBUG<<"CMyThreadTest::do_start"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"begin";

	if (false == m_pThread->isRunning())
	{
		m_toTerminate = false;
		m_nThreadJobState = JobState_Begin;
		m_pThread->start();
	}

	MYLOG4CPP_DEBUG<<"CMyThreadTest::do_start"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"end";
}
void CMyThreadTest::my_terminateAndWait()
{
	MYLOG4CPP_DEBUG<<"CMyThreadTest::do_terminateAndWait"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"begin";

	m_toTerminate = true;
	m_pThread->quit();
	while (false == m_pThread->isFinished())
	{
		this->msleep(100);
	}

	MYLOG4CPP_DEBUG<<"CMyThreadTest::do_terminateAndWait"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"end";
}
void CMyThreadTest::slot_my_thread_run()
{
	MYLOG4CPP_DEBUG<<"CMyThreadTest do_run"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"begin";

	while (false == m_toTerminate)
	{
		MYLOG4CPP_DEBUG<<"CMyThreadTest do_run _ThreadJob"
			<<" "<<"currentThreadId=0x"<<QThread::currentThreadId();
		_ThreadJob();
		this->msleep(100);		
	}

	_ProcessUserTerminate();

	MYLOG4CPP_DEBUG<<"CMyThreadTest do_run"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"end";
}

void CMyThreadTest::my_msleep( int mseconds )
{
	MYLOG4CPP_DEBUG<<"CMyThreadTest do_sleep mseconds="<<mseconds
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"begin";

	this->msleep(mseconds);

	MYLOG4CPP_DEBUG<<"CMyThreadTest do_sleep mseconds="<<mseconds
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"end";
}

bool CMyThreadTest::my_isFinishWork()
{
	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;
}

void CMyThreadTest::_ThreadJob()
{
	MYLOG4CPP_DEBUG<<"CMyThreadTest _ThreadJob"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId();

	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		break;
	case JobState_End:
		break;
	default:
		this->msleep(100);
		break;

	}//switch
	
}

void CMyThreadTest::_ProcessUserTerminate()
{
	MYLOG4CPP_DEBUG<<"CMyThreadTest _ProcessUserTerminate"
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId();

}

