#ifndef __CLASS_PROJECT_MAMAGER__HH__
#define __CLASS_PROJECT_MAMAGER__HH__

#include "core/utilities/src/UtilitiesCommonData.h"

NS_BEGIN(TA_Base_Test) 

class CProjectTestWorker;

class CProjectTestManager 
{
public:
	CProjectTestManager(void);
	~CProjectTestManager(void);
public:
	bool  isFinishWork();
public:
	CProjectTestWorker* m_pWorker;
};

NS_END(TA_Base_Test) 


#endif //__CLASS_PROJECT_MAMAGER__HH__


