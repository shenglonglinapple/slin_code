#ifndef THREADGUARD_H_INCLUDED
#define THREADGUARD_H_INCLUDED

#include "core/threads/src/ThreadsCommonData.h"

#include "core/threads/src/IThreadLockable.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>

NS_BEGIN(TA_Base_Core)

class ThreadGuard
{
public:

	/** 
	* Constructor
	*
	* Constructs ThreadGuard object, automatically acquiring the 
	* IThreadLockable object passed to it.
	*
	* @param &IThreadLockable - The IThreadLockable this ThreadGuard
	*                           is to acquire/release    
	*/
	ThreadGuard( IThreadLockable& lockable, bool log = false );


	/** 
	* Destructor
	*
	* Automatically releases the IThreadLockable this ThreadGuard was
	* constructed with.
	*
	*/
	virtual ~ThreadGuard();


	/** 
	* acquire
	*
	* Acquire the lock.
	*
	*/
	inline void acquire()
	{
		m_lockable.acquire();
	}

	/** 
	* release
	*
	* Release the lock.
	* 
	*/
	inline void release()
	{
		m_lockable.release();
	}

private:

	//
	// Disable the default copy and assignment constructors as shouldn't used.
	//
	ThreadGuard( const ThreadGuard& );
	ThreadGuard& operator=( const ThreadGuard& );


	IThreadLockable& m_lockable;    // Reference to IThreadLockable this object 
	bool m_log;
};
NS_END(TA_Base_Core)


#endif // THREADGUARD_H_INCLUDED

