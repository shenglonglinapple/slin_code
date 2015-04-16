#include "TestCase.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>


#include "CommonData.h"
#include "SysTypes.h"
#include "ServerManage.h"
#include "ClientsManagerWorker.h"
#include "ConfigInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

namespace boost 
{
	class thread;
	class thread_group;
}


// extern boost::condition_variable g_conditionMainRun;

NS_BEGIN(TA_Base_Test) 



//////////////////////////////////////////////////////////////////////////

CTestCase::CTestCase(void)
{
	m_pClientsManagerWorker = NULL;
}

CTestCase::~CTestCase(void)
{
	if (NULL != m_pClientsManagerWorker)
	{
		m_pClientsManagerWorker->terminateAndWait();
		delete m_pClientsManagerWorker;
		m_pClientsManagerWorker = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void CTestCase::_RunTestCase_Client()
{
	BOOST_LOG_FUNCTION();
	m_pClientsManagerWorker = new CClientsManagerWorker();
	m_pClientsManagerWorker->start();
}


void CTestCase::_RunTestCase_Server()
{
	BOOST_LOG_FUNCTION();
	CServerManager::getInstance();

}

void CTestCase::runTestCase()
{
	RunType nRunType;
	nRunType = CConfigInfo::getInstance().getRunType();
	switch (nRunType)
	{
	case RunType_SERVER:
		_RunTestCase_Server();
		break;
	case RunType_CLIENT:
		_RunTestCase_Client();
		break;
	default:
		break;
	}
}


NS_END(TA_Base_Test) 



