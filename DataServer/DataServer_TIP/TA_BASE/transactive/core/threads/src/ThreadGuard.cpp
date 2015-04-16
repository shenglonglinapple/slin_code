#include "core/threads/src/ThreadGuard.h"


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)

//
// Constructor
//
ThreadGuard::ThreadGuard( IThreadLockable& lockable, bool log )
: m_lockable(lockable), m_log (log)
{

	if (m_log)
	{
		LOG_TRACE<<"ThreadGuard: Attempting lock acquire, address 0x"<<(unsigned long)&m_lockable;
	}

	m_lockable.acquire();

	if (m_log)
	{
		LOG_TRACE<<"ThreadGuard: Acquired lock, address 0x"<<(unsigned long)&m_lockable;
	}
}


//
// Destructor
//
ThreadGuard::~ThreadGuard()
{
	if (m_log)
	{
		LOG_TRACE<<"ThreadGuard: Releasing lock, address 0x"<<(unsigned long)&m_lockable;
	}

	m_lockable.release();
}

NS_END(TA_Base_Core)

