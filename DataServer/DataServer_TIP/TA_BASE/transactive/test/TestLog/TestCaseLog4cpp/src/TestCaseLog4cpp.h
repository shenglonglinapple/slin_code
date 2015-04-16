#ifndef __CLASS_TESTCASE_LOG4CPP__HH__
#define __CLASS_TESTCASE_LOG4CPP__HH__

#include "core/utilities/src/UtilitiesCommonData.h"

NS_BEGIN(TA_Base_Test) 


class CTestCaseLog4cpp 
{
public:
	CTestCaseLog4cpp(void);
	~CTestCaseLog4cpp(void);
private:
	void _TestLog4Cpp_ByManualOperation(void);
	void _TestLog4Cpp_ByManualOperation2(void);
	void _TestLog4Cpp_ByCfgFile(void);
	void _TestLog4Cpp_ByCfgFile2(void);
};

NS_END(TA_Base_Test) 


#endif //__CLASS_TESTCASE_LOG4CPP__HH__


