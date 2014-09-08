#ifndef __CLASS_BOOST_THREAD__HH__
#define __CLASS_BOOST_THREAD__HH__



#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



class CBoostThread
{
public:
	typedef enum enThreadStates
	{
		THREAD_STATE_NEW,

		THREAD_STATE_RUNNING,
		THREAD_STATE_TERMINATED,

		THREAD_STATE_FINISH,
		THREAD_STATE_UNKNOWN                                     
	}EThreadStates;
public:
	CBoostThread(); 
	virtual ~CBoostThread();
	virtual void run() = 0;	
	virtual void terminate() = 0;

public:
	void start();
	void terminateAndWait();

public:	
	unsigned int getId() const;
	static void sleep(unsigned int milliseconds);
	static unsigned int getCurrentThreadId();
public:	
	EThreadStates getCurrentState() const;

public:
	void  runThread(void * args);   

private: 
	boost::thread*  m_thread; 

public:
	EThreadStates    m_ThreadState;
	int             m_nThreadID;
};

//QT_END_NAMESPACE

#endif  // __CLASS_BOOST_THREAD__HH__



