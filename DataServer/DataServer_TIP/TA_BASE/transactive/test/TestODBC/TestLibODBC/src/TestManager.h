#ifndef __CLASS_TEST_MAMAGER__HH__
#define __CLASS_TEST_MAMAGER__HH__




class CTestDiffWorker;

class CTestManager 
{
public:
	CTestManager(void);
	~CTestManager(void);

public:
	CTestDiffWorker* m_pTestDiffWorker;
};



#endif //__CLASS_DATA_ACCESS_TEST_MAMAGER__HH__


