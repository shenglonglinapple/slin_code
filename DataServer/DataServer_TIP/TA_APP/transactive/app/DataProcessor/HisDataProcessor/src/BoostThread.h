#ifndef __CLASS_BOOST_THREAD__HH__
#define __CLASS_BOOST_THREAD__HH__

#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "CFDServerCommonData.h"

//NS_BEGIN(TA_Base_Core) 
QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE



class CBoostThread
{


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
	EThreadState getCurrentState() const;

public:
	void  runThread(void * args);   

private: 
	boost::thread*  m_thread; 

public:
	EThreadState    m_ThreadState;
	int             m_nThreadID;
};


//NS_END(TA_Base_Core) 
QT_END_NAMESPACE

#endif  // __CLASS_BOOST_THREAD__HH__



