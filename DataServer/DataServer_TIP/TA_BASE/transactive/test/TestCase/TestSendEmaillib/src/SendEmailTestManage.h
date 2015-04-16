#ifndef __CLASS_SEND_EMAIL_TEST_MAMAGER__HH__
#define __CLASS_SEND_EMAIL_TEST_MAMAGER__HH__

#include "core/utilities/src/UtilitiesCommonData.h"

NS_BEGIN(TA_Base_Test) 

class CSendEmailTestWorker;

class CSendEmailTestManager 
{
public:
	CSendEmailTestManager(void);
	~CSendEmailTestManager(void);

public:
	CSendEmailTestWorker* m_pWorker;
};

NS_END(TA_Base_Test) 


#endif //__CLASS_SEND_EMAIL_TEST_MAMAGER__HH__


