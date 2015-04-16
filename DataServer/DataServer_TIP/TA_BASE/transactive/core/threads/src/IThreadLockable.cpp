
#include "core/threads/src/IThreadLockable.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;


NS_BEGIN(TA_Base_Core)


IThreadLockable::IThreadLockable()
{
	return;
}


IThreadLockable::~IThreadLockable()
{
	return;
}

void IThreadLockable::acquireRead()
{
	LOG_ERROR<<"Read locks not supported";
}

void IThreadLockable::releaseRead()
{
	LOG_ERROR<<"Read locks not supported";
}



NS_END(TA_Base_Core)
