#ifndef __CLASS_SAMPLE_MY_QT_THREAD__HH__
#define __CLASS_SAMPLE_MY_QT_THREAD__HH__

#include "MyQtThread.h"

class CSampleMyQtThread : public CMyQtThread
{
	Q_OBJECT
private:
	enum EThreadJobState
	{
		JobState_Begin,
		JobState_End,
	};

public:
	CSampleMyQtThread(void);
	~CSampleMyQtThread(void);

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


#endif //__CLASS_SAMPLE_MY_QT_THREAD__HH__


