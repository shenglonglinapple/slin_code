#ifndef __CLASS_PROJECT_TEST_WORKDER__HH__
#define __CLASS_PROJECT_TEST_WORKDER__HH__

#include "core/utilities/src/UtilitiesCommonData.h"
#include "core/threads/src/BoostThread.h"
#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>


NS_BEGIN(TA_Base_Test) 



class CProjectTestWorker : public TA_Base_Core::CBoostThread
{
private:
	enum EThreadJobState
	{
		JobState_Begin,
		JobState_DoTest_01,
		JobState_End,
	};

public:
	CProjectTestWorker(void);
	~CProjectTestWorker(void);

public:
	virtual void run();	
	virtual void terminate();
	bool  isFinishWork();
private:
	void _ThreadJob();
	int	 _ProcessUserTerminate();  
private:
	void _DoTest_01();
private:
	bool	m_toTerminate;
	EThreadJobState  m_nThreadJobState;
};

NS_END(TA_Base_Test) 


#endif //__CLASS_PROJECT_TEST_WORKDER__HH__


