#ifndef __CLASS_TEST_DIFF_WORKER__HH__
#define __CLASS_TEST_DIFF_WORKER__HH__

#include "ProjectCommonData.h"


class CWorkTimeNoLock;
class CTestWorkerLibODBC;
class CTestWorkerOCL;
class CTestWorkerOTL;
class CTestWorkerOTLBlob;
class CTestWorkerOTLODBC;

class CTestDiffWorker
{
public:
	CTestDiffWorker(void);
	~CTestDiffWorker(void);
public:
	void run();
	void do_test_libODBC();
	void do_test_OCL();
	void do_test_OTL();
	void do_test_OTL_Blob();
	void do_test_OTL_ODBC();
private:
	CWorkTimeNoLock* m_pWorkTime_LibODBC;
	CTestWorkerLibODBC* m_pTestWorker_LibODBC;
private:
	CWorkTimeNoLock* m_pWorkTime_OCL;
	CTestWorkerOCL* m_pTestWorker_OCL;
private:
	CWorkTimeNoLock* m_pWorkTime_OTL;
	CTestWorkerOTL* m_pTestWorker_OTL;
private:
	CWorkTimeNoLock* m_pWorkTime_OTLBlob;
	CTestWorkerOTLBlob* m_pTestWorker_OTLBlob;
private:
	CWorkTimeNoLock* m_pWorkTime_OTLODBC;
	CTestWorkerOTLODBC* m_pTestWorker_OTLODBC;
	
	
};



#endif //__CLASS_TEST_DIFF_WORKER__HH__


