#ifndef THREADLOCKABLEHOLDERVERIFIER_H_INCLUDED
#define THREADLOCKABLEHOLDERVERIFIER_H_INCLUDED

#include "core/threads/src/ThreadsCommonData.h"

#include "core/threads/src/BoostThread.h"  

NS_BEGIN(TA_Base_Core)


class ThreadIdWrapper
{
public: 
	ThreadIdWrapper() 
	{
		m_threadId = TA_Base_Core::CBoostThread::getCurrentThreadId();
	}

	/** 
	* setCurrentThreadId
	*
	* Set the id to the current thread id.
	*
	*/
	void setCurrentThreadId()
	{

		m_threadId = TA_Base_Core::CBoostThread::getCurrentThreadId();

		return;
	}


	/** 
	* isCurrentThreadId
	*
	* returns true if the id is the same as the current thread's id.
	*
	*
	* @return bool
	*/
	bool isCurrentThreadId()
	{
		unsigned int nCurrentThreadID = 0;

		nCurrentThreadID = TA_Base_Core::CBoostThread::getCurrentThreadId();

		if (m_threadId == nCurrentThreadID)
		{
			return true;
		}
		return false;
	}


	unsigned int getCurrentThreadId()
	{
		return TA_Base_Core::CBoostThread::getCurrentThreadId();
	}

private:
	unsigned int m_threadId;  //use


};
NS_END(TA_Base_Core)


#endif // THREADLOCKABLEHOLDERVERIFIER_H_INCLUDED
