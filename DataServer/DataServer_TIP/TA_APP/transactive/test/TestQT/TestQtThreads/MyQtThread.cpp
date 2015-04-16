#include "MyQtThread.h"

#include "Log4cppLogger.h"


CMyQtThread::CMyQtThread()
{
	m_ThreadState = THREAD_STATE_UNKNOWN;
	m_thread = NULL;	
	m_nThreadID = 0;
}

CMyQtThread::~CMyQtThread()
{

}


void CMyQtThread::runThread()
{
	this->m_ThreadState = THREAD_STATE_RUNNING;
	this->m_nThreadID = getCurrentThreadId();

	MYLOG4CPP_DEBUG<<"runThread(): [Thrd: "<<this->m_nThreadID<<"] begin  call run()";

	try
	{
		this->run();
	}
	catch (std::exception& e)
	{
		std::string msg( "runThread(): " );
		msg.append( e.what() );
		MYLOG4CPP_ERROR<<"runThread(): std::exception  msg="<<msg;
		return;
	}
	catch (...)
	{
		MYLOG4CPP_ERROR<<"runThread(): Unknown exception";		
		return;
	}

	MYLOG4CPP_DEBUG<<"runThread(): [Thrd: "<<this->m_nThreadID<<"] end  call run()";

	this->m_ThreadState = THREAD_STATE_FINISH; 
	return;
}


void CMyQtThread::start()
{
	if (THREAD_STATE_RUNNING ==	m_ThreadState
		|| THREAD_STATE_FINISH == m_ThreadState)
	{
		MYLOG4CPP_WARNING<<"start(): [Thrd: "<<this->m_nThreadID<<"] is already running";
		return;
	}
	
	MYLOG4CPP_DEBUG<<"CMyQtThread::start()"
		<<" "<<"CurrentThread="<<getCurrentThreadId()
		<<" "<<"begin create a new thread";

	m_thread = new QThread(this);	
	this->moveToThread(m_thread);
	QObject::connect(m_thread, SIGNAL(started()), this, SLOT(runThread()));

	m_ThreadState = THREAD_STATE_NEW;

	m_thread->start();

	MYLOG4CPP_DEBUG<<"CMyQtThread::start()"
		<<" "<<"CurrentThread="<<getCurrentThreadId()
		<<" "<<"end create a new thread";

}


void CMyQtThread::terminateAndWait()
{
	if (NULL != m_thread)
	{
		MYLOG4CPP_DEBUG<<"CMyQtThread::terminateAndWait()"
			<<" "<<"CurrentThread="<<getCurrentThreadId()
			<<" "<<"begin delete a exit thread"
			<<" "<<"m_nThreadID="<<m_nThreadID
			<<" "<<"begin call terminate()";

		terminate();

		MYLOG4CPP_DEBUG<<"CMyQtThread::terminateAndWait()"
			<<" "<<"CurrentThread="<<getCurrentThreadId()
			<<" "<<"begin delete a exit thread"
			<<" "<<"m_nThreadID="<<m_nThreadID
			<<" "<<"end call terminate()";


		MYLOG4CPP_DEBUG<<"CMyQtThread::terminateAndWait()"
			<<" "<<"CurrentThread="<<getCurrentThreadId()
			<<" "<<"begin delete a exit thread"
			<<" "<<"m_nThreadID="<<m_nThreadID
			<<" "<<"begin join";

		m_thread->quit();
		while (false == m_thread->isFinished())
		{
			this->msleep(100);
		}



		m_ThreadState = THREAD_STATE_TERMINATED;
		m_ThreadState = THREAD_STATE_FINISH;
		delete m_thread;
		m_thread = NULL;

		MYLOG4CPP_DEBUG<<"CMyQtThread::terminateAndWait()"
			<<" "<<"CurrentThread="<<getCurrentThreadId()
			<<" "<<"begin delete a exit thread"
			<<" "<<"m_nThreadID="<<m_nThreadID
			<<" "<<"end join";
	}
}


void CMyQtThread::my_msleep(unsigned int milliSeconds)
{  
	this->msleep(milliSeconds);
/*
	MYLOG4CPP_DEBUG<<"CMyThreadTest my_msleep milliSeconds="<<milliSeconds
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"begin";

	this->msleep(milliSeconds);

	MYLOG4CPP_DEBUG<<"CMyThreadTest my_msleep milliSeconds="<<milliSeconds
		<<" "<<"currentThreadId=0x"<<QThread::currentThreadId()
		<<" "<<"end";
*/
}


unsigned int CMyQtThread::getId() const
{
	return (m_thread != NULL) ? m_nThreadID : static_cast< unsigned int >( -1 );
}

unsigned int CMyQtThread::getCurrentThreadId()
{
	/*
	// printf("&i = %p\n", &i)	// printf Thread address
	#elif defined(Q_WS_WIN)
	typedef void *HANDLE;
	*/
	void* pThreadIDValue = 0;
	char szThreadIDValue[64];
	unsigned int threadNumber = 0;

	memset(szThreadIDValue, 0, 64);

	pThreadIDValue = QThread::currentThreadId();
	//MYLOG4CPP_DEBUG<<"getCurrentThreadId pThreadIDValue="<<pThreadIDValue;

	sprintf(szThreadIDValue, "%p", pThreadIDValue);
	//MYLOG4CPP_DEBUG<<"getCurrentThreadId szThreadIDValue="<<szThreadIDValue;

	sscanf(szThreadIDValue, "%lx", &threadNumber);
	//MYLOG4CPP_DEBUG<<"getCurrentThreadId threadNumber2="<<threadNumber;

	return threadNumber;
}
CMyQtThread::EThreadStates CMyQtThread::getCurrentState() const
{
	return m_ThreadState;
}


