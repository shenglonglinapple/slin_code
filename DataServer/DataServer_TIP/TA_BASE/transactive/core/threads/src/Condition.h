#ifndef CONDITION_H_INCLUDED
#define CONDITION_H_INCLUDED

#include "core/threads/src/ThreadsCommonData.h"


#include <vector>
#include <boost/utility.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


NS_BEGIN(TA_Base_Core)

class IThreadLockable;

// Forward declared as this class needs pointer to this type (opposed to interface above)
// to use its private backup/restore methods (this class can do so as is declared as friend).
class ReEntrantThreadLockable;


class Condition
{
public:

	/** 
	* Condition
	*
	* Construct a new condition object
	*
	*/
	Condition();


	/** 
	* ~Condition
	* 
	* condition destructor
	*/
	virtual ~Condition();


	/** 
	* wait
	*
	* wait for the condition variable to be signalled, a signal may wake up more
	* than one thread.
	*
	*/
	void wait();


	/** 
	* timedwait
	*
	* Wait for signal for maximum number of milliseconds
	*
	* @param unsigned long milliseconds (number milliseconds to wait for)
	*
	* @return int (1 if successfully signalled | 0 if time expired)
	*/
	int timedWait(unsigned long milliSeconds);


	/** 
	* signal
	*
	* if one or more threads have called wait(), signal wakes up at least
	* one of them, possibly more.
	*
	*/
	void signal();


	/** 
	* signal
	*
	* broadcast is like signal but wakes all threads which have called
	* wait().
	*
	*/
	void broadcast();




private:   

	//
	// Disable the default copy and assignment constructors as shouldn't used.
	//
	Condition( const Condition& );
	Condition& operator=( const Condition& );


	/**
	* The underlying condition implementation
	*/
	boost::condition  m_condition;
	boost::mutex m_lock;
};

NS_END(TA_Base_Core)


#endif // CONDITION_H_INCLUDED

