#include "TestManager.h"

#include "TestWorker.h"
#include "TestWorkerTable.h"
#include "TestWorkerTinyODBC.h"

#include "ProjectCommonData.h"

CTestManager::CTestManager( void )
{
// 	m_pWorker = NULL;
// 	m_pWorker = new CTestWorker();
// 	m_pWorker->run();

	m_pTestWorkerTable = NULL;
	m_pTestWorkerTable = new CTestWorkerTable();
	m_pTestWorkerTable->run();

// 	m_pTestWorkerTinyODBC = NULL;
// 	m_pTestWorkerTinyODBC = new CTestWorkerTinyODBC();
// 	m_pTestWorkerTinyODBC->run();
	
}

CTestManager::~CTestManager( void )
{
// 	if (NULL != m_pWorker)
// 	{
// 		delete m_pWorker;
// 		m_pWorker = NULL;
// 	}


	if (NULL != m_pTestWorkerTable)
	{
		delete m_pTestWorkerTable;
		m_pTestWorkerTable = NULL;
	}


// 	if (NULL != m_pTestWorkerTinyODBC)
// 	{
// 		delete m_pTestWorkerTinyODBC;
// 		m_pTestWorkerTinyODBC = NULL;
// 	}

}
