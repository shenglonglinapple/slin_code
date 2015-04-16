#ifndef __CLASS_TEST_MAMAGER__HH__
#define __CLASS_TEST_MAMAGER__HH__



class CTestWorker;
class CTestWorkerTable;
class CTestWorkerTinyODBC;

class CTestManager 
{
public:
	CTestManager(void);
	~CTestManager(void);

public:
	CTestWorker* m_pWorker;
	CTestWorkerTable* m_pTestWorkerTable;
	CTestWorkerTinyODBC* m_pTestWorkerTinyODBC;
};



#endif //__CLASS_DATA_ACCESS_TEST_MAMAGER__HH__


