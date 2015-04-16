#include "TestManager.h"

#include "ProjectCommonData.h"
#include "TestDiffWorker.h"


CTestManager::CTestManager( void )
{
	m_pTestDiffWorker = NULL;
	m_pTestDiffWorker = new CTestDiffWorker();
	m_pTestDiffWorker->run();
	
}

CTestManager::~CTestManager( void )
{

	if (NULL != m_pTestDiffWorker)
	{
		delete m_pTestDiffWorker;
		m_pTestDiffWorker = NULL;
	}

}
