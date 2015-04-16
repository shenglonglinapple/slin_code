#ifndef __CLASS_CPP_SOCKET_TEST_MAMAGER__HH__
#define __CLASS_CPP_SOCKET_TEST_MAMAGER__HH__

#include "core/utilities/src/UtilitiesCommonData.h"

NS_BEGIN(TA_Base_Core) 

class CCppSocketTestWorker;

class CCppSocketTestManager 
{
public:
	CCppSocketTestManager(void);
	~CCppSocketTestManager(void);

public:
	CCppSocketTestWorker* m_pWorker;
};

NS_END(TA_Base_Core) 


#endif //__CLASS_CPP_SOCKET_TEST_MAMAGER__HH__


