#ifndef REENTRANTTHREADLOCKABLE_H_INCLUDED
#define REENTRANTTHREADLOCKABLE_H_INCLUDED


#include "core/threads/src/ThreadsCommonData.h"
#include "core/threads/src/IThreadLockable.h"
#include "core/threads/src/ThreadLockableHolderVerifier.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>

NS_BEGIN(TA_Base_Core)



class ReEntrantThreadLockable : public IThreadLockable
{
public:	

	/** 
	* Default Constructor
	*/
	ReEntrantThreadLockable();


	/** 
	* Destructor
	*/
	virtual ~ReEntrantThreadLockable();


	/** 
	* acquire
	*
	* Acquire the lock. Consecutive acquisitions from the same thread is
	* allowed, but the lock will not be subsequently released until an
	* equivalent number of calls to release are made.
	*
	*/
	virtual void acquire();


	/** 
	* release
	*
	* Release the lock. If a thread has made multiple acquisitions, the lock
	* will not be released until an equivalent number of calls to this method
	* are made.
	*
	* PreCondition: The lock is currently acquired.  
	*/
	virtual void release();

private:

	//
	// Disable the default copy and assignment constructors as shouldn't used.
	//
	ReEntrantThreadLockable( const ReEntrantThreadLockable& );
	ReEntrantThreadLockable& operator=( const ReEntrantThreadLockable& );


	// Indicates when some thread has currently aquired this lock and the number
	// of times it has re-entered.
	volatile unsigned int m_numTimesThreadAcquiredLock;

	// The underlying omni_mutex this class is wrapping.
	boost::mutex* m_lock;/* Log Lock */


	// Struct used to store the identifier of the thread that has currently aquired
	// the lock and inform client code whether its thread is a match.
	ThreadIdWrapper* m_threadLockableHolderVerifier;

	// Member used to backup the number of times the current lockholding thread
	// has acquired the lock.
	volatile unsigned int m_previousNumTimesThreadAcquiredLock;

	// Member used to backup the identifier of the thread that has currently aquired
	// the lock.
	ThreadIdWrapper* m_previousThreadLockableHolderVerifier;

public:	

	/** 
	* backupReEntrantAcquisitionState
	*
	* Private method so as to allow friend class Condition to backup 
	* re-entrant acquisition state before intrinsically releasing its
	* linked mutex prior to entering wait.
	*/
	void backupReEntrantAcquisitionState();


	/** 
	* restoreReEntrantAcquisitionState
	*
	* Private method so as to allow friend class Condition to restore the previous
	* re-entrant acquisition state after intrinsically re-acquiring its
	* linked mutex after completing wait.
	*/
	void restoreReEntrantAcquisitionState();



};


NS_END(TA_Base_Core)


#endif // REENTRANTTHREADLOCKABLE_H_INCLUDED

