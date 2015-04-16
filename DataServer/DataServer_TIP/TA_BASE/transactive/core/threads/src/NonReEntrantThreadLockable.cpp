#include "core/threads/src/NonReEntrantThreadLockable.h"
#include "core/threads/src/ThreadLockableHolderVerifier.h"


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;


NS_BEGIN(TA_Base_Core)

//
// Constructor
//
NonReEntrantThreadLockable::NonReEntrantThreadLockable() 
{
	m_lock = new boost::mutex();

	m_isLockCurrentlyAcquired = false;
	m_threadLockableHolderVerifier = new ThreadIdWrapper();
}


//
// Destructor
//
NonReEntrantThreadLockable::~NonReEntrantThreadLockable()
{

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


}


//
// acquire
//
void NonReEntrantThreadLockable::acquire()
{
	if (true == ( m_isLockCurrentlyAcquired && m_threadLockableHolderVerifier->isCurrentThreadId() ))
	{
		LOG_ERROR<<"Thread attempted to acquire NonReEntrantThreadLockable on consecutive occasions without first releasing.";
	}

	m_lock->lock();

	// Thread has acquired lock so set as current lock holder and set flag indicating lock is acquired.
	m_threadLockableHolderVerifier->setCurrentThreadId();
	m_isLockCurrentlyAcquired = true;
}


//
// release
//
void NonReEntrantThreadLockable::release()
{
	if (false == m_isLockCurrentlyAcquired)
	{
		LOG_ERROR<< "Call made to release while lock not currently acquired.";
	}

	// Reset flag indicating lock is acquired.
	m_isLockCurrentlyAcquired = false;
	m_lock->unlock();

}
NS_END(TA_Base_Core)

