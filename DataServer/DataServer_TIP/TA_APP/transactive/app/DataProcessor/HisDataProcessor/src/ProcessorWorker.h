#ifndef __CLASS_PROCESSOR_WORKER_WORKER__HH__
#define __CLASS_PROCESSOR_WORKER_WORKER__HH__


#include "BoostThread.h"


QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE

class CAWorkTime;
class CCFDServerUtilityFun;
class CInstrumentBarInfoRequest;


class CProcessorWorker : public CBoostThread

{
private:
	enum EThreadJobState
	{
		JobState_Begin,

		JobState_CheckUtilityFun,
		JobState_InitRequest,
		JobState_CheckRequest,
		JobState_ProcessRequest,

		JobState_StopWork,
		JobState_End,
	};
public:
	CProcessorWorker(void);
	~CProcessorWorker(void);
public:
	virtual void run();	//CBoostThread
	virtual void terminate();//CBoostThread
	bool  isFinishWork();//CBoostThread
private:
	void _ThreadJob();
	int	 _ProcessUserTerminate();  
private:
	void _Process_CheckUtilityFun();

	void _Process_InitRequest();
	void _Process_CheckRequest();
	void _Process_ProcessRequest();

	void _Process_StopWork();
private:
	bool _CheckContinueProcessRequest();
	void _LogReport();
private:
	bool	m_toTerminate;
	EThreadJobState  m_nThreadJobState;

private:
	CInstrumentBarInfoRequest* m_pRequestBarInfo; 
	BigInt64 m_nProcessRequestCount;
	CCFDServerUtilityFun* m_pUtilityFun;
	CAWorkTime* m_pWorkTimeAuto;
	BigInt64 m_nWorkTimeAutoTimeOut;
private:
	BigInt64 m_nProcessOneRequestTime_ForReport;
};

QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DATA_MAMAGER_WORKER__HH__


