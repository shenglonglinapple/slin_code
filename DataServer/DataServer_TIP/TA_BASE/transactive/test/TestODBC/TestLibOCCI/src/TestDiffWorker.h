#ifndef __CLASS_TEST_DIFF_WORKER__HH__
#define __CLASS_TEST_DIFF_WORKER__HH__

#include "ProjectCommonData.h"


class CWorkTimeNoLock;
class CTestWorkerOCCI;


class CTestDiffWorker
{
public:
	CTestDiffWorker(void);
	~CTestDiffWorker(void);
public:
	void run();

	void do_test_OCCI();
private:
	CWorkTimeNoLock* m_pWorkTime_OCCI;
	CTestWorkerOCCI* m_pTestWorker_OCCI;
};



#endif //__CLASS_TEST_DIFF_WORKER__HH__


