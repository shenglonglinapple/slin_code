#ifndef __CLASS_TEST_DIFF_WORKER__HH__
#define __CLASS_TEST_DIFF_WORKER__HH__

#include "ProjectCommonData.h"


class CWorkTimeNoLock;
class CTestWorkerTinyODBC;
class CTestWorkerOCL;
class CTestWorkerMCL;

class CTestDiffWorker
{
public:
	CTestDiffWorker(void);
	~CTestDiffWorker(void);
public:
	void run();
	void do_test_TinyODBC();
	void do_test_OCL();
private:
	CTestWorkerTinyODBC* m_pTestWorker_TinyODBC;
	CWorkTimeNoLock* m_pWorkTime_TinyODBC;
private:	
	CTestWorkerOCL* m_pTestWorker_OCL;
	CWorkTimeNoLock* m_pWorkTime_OCL;
private:
	CTestWorkerMCL* m_pTestWorker_MCL;
	CWorkTimeNoLock* m_pWorkTime_MCL;
	
};



#endif //__CLASS_TEST_DIFF_WORKER__HH__


