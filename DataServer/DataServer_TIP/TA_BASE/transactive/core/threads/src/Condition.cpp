#include "core/threads/src/Condition.h"
#include "core/threads/src/ReEntrantThreadLockable.h"
#include "core/threads/src/ThreadGuard.h"


NS_BEGIN(TA_Base_Core)


//
// Default Constructor
//
Condition::Condition()
{

}


//
// Destructor
//
Condition::~Condition()
{

}


//
// wait
//
void Condition::wait()
{		
	boost::mutex::scoped_lock guard(m_lock);

	m_condition.wait(guard);
}


//
// timedWait
//
int Condition::timedWait(unsigned long milliSeconds)
{
	int nFunRes = 0;
	boost::mutex::scoped_lock guard(m_lock);

	m_condition.timed_wait(guard, boost::get_system_time() + boost::posix_time::millisec(milliSeconds));


	return nFunRes;
}


//
// signal
//
void Condition::signal()
{
	boost::mutex::scoped_lock guard(m_lock);
	m_condition.notify_one();


}


//
// broadcast
//
void Condition::broadcast()
{
	boost::mutex::scoped_lock guard(m_lock);

	m_condition.notify_all();

}



NS_END(TA_Base_Core)

