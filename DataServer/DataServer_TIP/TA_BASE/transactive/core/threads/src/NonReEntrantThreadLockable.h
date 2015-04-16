#ifndef NONREENTRANTTHREADLOCKABLE_H_INCLUDED
#define NONREENTRANTTHREADLOCKABLE_H_INCLUDED


#include "core/threads/src/ThreadsCommonData.h"

#include "core/threads/src/IThreadLockable.h"
#include "core/threads/src/ThreadLockableHolderVerifier.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>


NS_BEGIN(TA_Base_Core)


// Forward declared struct so as not to bring in any dependencies here that are
// needed to identify the current thread on various platforms.
class ThreadIdWrapper;



class NonReEntrantThreadLockable : public IThreadLockable
{
public:

	/** 
	* Constructor
	*
	*/
	NonReEntrantThreadLockable();


	/** 
	* Destructor
	*
	*/
	virtual ~NonReEntrantThreadLockable();


	/** 
	* acquire
	*
	* Acquire the lock.
	*
	* PreCondition: The lock is not already acquired by the current thread.
	*/
	virtual void acquire();


	/** 
	* release
	*
	* Release the lock.
	*
	* PreCondition: The lock is currently acquired.  
	*/
	virtual void release();

private:

	//
	// Disable the default copy and assignment constructors as shouldn't used.
	//
	NonReEntrantThreadLockable( const NonReEntrantThreadLockable& );
	NonReEntrantThreadLockable& operator=( const NonReEntrantThreadLockable& );

private:
	// The underlying omni_mutex this class is wrapping.
	//omni_mutex* m_lock;
	boost::mutex* m_lock;/* Log Lock */


	// Struct used to store the identifier of the thread that has currently aquired
	// the lock and inform client code whether its thread is a match.
	ThreadIdWrapper* m_threadLockableHolderVerifier;

	// Indicates when some thread has currently aquired this lock.
	volatile bool m_isLockCurrentlyAcquired;


};

NS_END(TA_Base_Core)


#endif // NONREENTRANTTHREADLOCKABLE_H_INCLUDED

