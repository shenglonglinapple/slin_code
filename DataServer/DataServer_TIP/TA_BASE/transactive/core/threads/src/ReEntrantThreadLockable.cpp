#include "core/threads/src/ReEntrantThreadLockable.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)


//
// Default Constructor
//
ReEntrantThreadLockable::ReEntrantThreadLockable() 
{
	m_lock = new boost::mutex();

	m_numTimesThreadAcquiredLock = 0;

	m_threadLockableHolderVerifier = NULL;
	m_threadLockableHolderVerifier = new ThreadIdWrapper();

	m_previousNumTimesThreadAcquiredLock = 0;

	m_previousThreadLockableHolderVerifier = NULL;
	m_previousThreadLockableHolderVerifier = new ThreadIdWrapper();


}




//
// Destructor
//
ReEntrantThreadLockable::~ReEntrantThreadLockable()
{
	int nFunRes = 0;

	if (NULL != m_lock)
	{
		delete m_lock;
		m_lock = NULL;
	}

	if (NULL != m_threadLockableHolderVerifier)
	{
		delete m_threadLockableHolderVerifier;
		m_threadLockableHolderVerifier = NULL;
	}

	if (NULL != m_previousThreadLockableHolderVerifier)
	{
		delete m_previousThreadLockableHolderVerifier;
		m_previousThreadLockableHolderVerifier = NULL;
	}
}


//
// acquire
//
void ReEntrantThreadLockable::acquire()
{
	int nFunRes = 0;

	// (ReEntrant) If the thread has currently acquired this lock already, increment the count and 
	// return without passing call onto the mutex.
	if ( ( 0 < m_numTimesThreadAcquiredLock ) && ( m_threadLockableHolderVerifier->isCurrentThreadId() ) )
	{
		m_numTimesThreadAcquiredLock++;
		return;
	}
	m_lock->lock();

	// Thread has acquired lock so set as current lock holder and set count to 1.
	m_threadLockableHolderVerifier->setCurrentThreadId();
	m_numTimesThreadAcquiredLock = 1;
}


//
// release
//
void ReEntrantThreadLockable::release()
{
	int nFunRes = 0;
	//TA_ASSERT( ( 0 != m_numTimesThreadAcquiredLock ), "Call made to release while lock not currently acquired." );

	if (0 == m_numTimesThreadAcquiredLock)
	{
		LOG_ERROR<<"Call made to release while lock not currently acquired.";
	}

	// Decrement the count.
	m_numTimesThreadAcquiredLock--;

	// If the count is now back to 0, release the mutex.
	if ( 0 == m_numTimesThreadAcquiredLock )
	{
		m_lock->unlock();
	}
}


//
// backupReEntrantAcquisitionState
//
void ReEntrantThreadLockable::backupReEntrantAcquisitionState()
{
	*m_previousThreadLockableHolderVerifier = *m_threadLockableHolderVerifier;
	m_previousNumTimesThreadAcquiredLock = m_numTimesThreadAcquiredLock;
}


//
// restoreReEntrantAcquisitionState
//
void ReEntrantThreadLockable::restoreReEntrantAcquisitionState()
{
	// !! The order is important here - should always set identity of lockholder
	// before indicating it is indeed acquired by setting count !!
	*m_threadLockableHolderVerifier = *m_previousThreadLockableHolderVerifier;
	m_numTimesThreadAcquiredLock = m_previousNumTimesThreadAcquiredLock;
}


NS_END(TA_Base_Core)












