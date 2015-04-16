#ifndef __CLASS_TESTCASE_HH__
#define __CLASS_TESTCASE_HH__

#include "UtilityFun.h"



NS_BEGIN(TA_Base_Test) 

class CClientsManagerWorker;
class CTestCase
{
public:
	CTestCase(void);
	~CTestCase(void);

public:
	void runTestCase();
public:
	void _RunTestCase_Server();
	void _RunTestCase_Client();

private:
	CClientsManagerWorker* m_pClientsManagerWorker;


};

NS_END(TA_Base_Test) 


#endif //__CLASS_TESTCASE_CLIENT_SERVER__HH__


