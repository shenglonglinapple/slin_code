
#ifndef __I_THREAD_GUARD__HH__
#define __I_THREAD_GUARD__HH__

#include "core/threads/src/ThreadsCommonData.h"

NS_BEGIN(TA_Base_Core)

class IThreadLockable
{

public:

	IThreadLockable();
	
	/** 
	* Destructor
	*/
	virtual ~IThreadLockable();

	/** 
	* acquire
	*
	* Acquire the lock.
	*
	*/
	virtual void acquire() = 0;


	/** 
	* acquireRead
	*
	* Acquire the read lock.
	*
	* This function will be overridden by those 
	* drived classes that support read locks
	*/
	virtual void acquireRead();


	/** 
	* release
	*
	* Release the lock.
	*
	* PreCondition: This IThreadLockable is currently acquired. 
	*/
	virtual void release() = 0;


	/** 
	* release
	*
	* Release the lock.
	*
	* PreCondition: This IThreadLockable is currently acquired. 
	*/
	virtual void releaseRead();


};
NS_END(TA_Base_Core)


#endif // !defined(__I_THREAD_GUARD__HH__)



