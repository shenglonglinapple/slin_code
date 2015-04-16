#include "ProjectTestManager.h"


#include <boost/chrono.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "ProjectTestWorker.h"



#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;



NS_BEGIN(TA_Base_Test) 


//////////////////////////////////////////////////////////////////////////
CProjectTestManager::CProjectTestManager(void)
{	
	BOOST_LOG_FUNCTION();	
	m_pWorker = NULL;
	m_pWorker = new CProjectTestWorker();
	m_pWorker->start();
	
}

CProjectTestManager::~CProjectTestManager(void)
{
	BOOST_LOG_FUNCTION();

	if (NULL != m_pWorker)
	{
		m_pWorker->terminateAndWait();
		delete m_pWorker;
		m_pWorker = NULL;
	}


}

bool CProjectTestManager::isFinishWork()
{
	bool bFunRes = false;

	if (NULL != m_pWorker)
	{
		bFunRes = m_pWorker->isFinishWork();

	}

	return bFunRes;
}



NS_END(TA_Base_Test) 



