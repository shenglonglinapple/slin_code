#ifndef __CLASS_CPP_SOCKET_TEST_WORKDER__HH__
#define __CLASS_CPP_SOCKET_TEST_WORKDER__HH__

#include "core/utilities/src/UtilitiesCommonData.h"
#include "core/threads/src/BoostThread.h"
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>


NS_BEGIN(TA_Base_Core) 



class CCppSocketTestWorker : public TA_Base_Core::CBoostThread
{
private:
	enum EThreadJobState
	{
		JobState_Begin,
		JobState_End,
	};

public:
	CCppSocketTestWorker(void);
	~CCppSocketTestWorker(void);

public:
	virtual void run();	
	virtual void terminate();
	bool  isFinishWork();
private:
	void _ThreadJob();
	int	 _ProcessUserTerminate();  
private:
	bool	m_toTerminate;
	EThreadJobState  m_nThreadJobState;
};

NS_END(TA_Base_Core) 


#endif //__CLASS_CPP_SOCKET_TEST_WORKDER__HH__


