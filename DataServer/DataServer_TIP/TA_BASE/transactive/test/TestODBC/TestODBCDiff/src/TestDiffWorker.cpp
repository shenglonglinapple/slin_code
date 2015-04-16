#include "TestDiffWorker.h"

#include "ProjectCommonData.h"
#include "WorkTime.h"

#include "BaseReport.h"
#include "TestWorkerTinyODBC.h"
#include "TestWorkerOCL.h"
#include "TestWorkerMCL.h"


static const int DEF_INT_DO_TEST_TOTAL = 10;

static const int DEF_INT_INSERT_TOTAL = 10000;


CTestDiffWorker::CTestDiffWorker( void )
{
	m_pWorkTime_TinyODBC = NULL;
	//m_pWorkTime_TinyODBC = new CWorkTimeNoLock(0);

	m_pTestWorker_TinyODBC = NULL;
	//m_pTestWorker_TinyODBC = new CTestWorkerTinyODBC();

	m_pWorkTime_OCL = NULL;
	//m_pWorkTime_OCL = new CWorkTimeNoLock(0);

	m_pTestWorker_OCL = NULL;
	//m_pTestWorker_OCL = new CTestWorkerOCL();


	m_pWorkTime_MCL = NULL;
	//m_pWorkTime_MCL = new CWorkTimeNoLock(0);

	m_pTestWorker_MCL = NULL;
	//m_pTestWorker_MCL = new CTestWorkerMCL();


	CBaseReport::getInstance();
	std::string strLogFile = DEF_Filename_OUT_BASE_REPORT;
	CBaseReport::getInstance().setlogFile(strLogFile);
	//_Report(ReportFLInfo, 0, "Test,%d,Test", 1);
	//_Report(ReportFLInfo, 0, "\n");

}

CTestDiffWorker::~CTestDiffWorker( void )
{
	if (NULL != m_pWorkTime_TinyODBC)
	{
		delete m_pWorkTime_TinyODBC;
		m_pWorkTime_TinyODBC = NULL;
	}

	if (NULL != m_pTestWorker_TinyODBC)
	{
		delete m_pTestWorker_TinyODBC;
		m_pTestWorker_TinyODBC = NULL;
	}


	if (NULL != m_pWorkTime_OCL)
	{
		delete m_pWorkTime_OCL;
		m_pWorkTime_OCL = NULL;
	}

	if (NULL != m_pTestWorker_OCL)
	{
		delete m_pTestWorker_OCL;
		m_pTestWorker_OCL = NULL;
	}

	//
	if (NULL != m_pWorkTime_MCL)
	{
		delete m_pWorkTime_MCL;
		m_pWorkTime_MCL = NULL;
	}

	if (NULL != m_pTestWorker_MCL)
	{
		delete m_pTestWorker_MCL;
		m_pTestWorker_MCL = NULL;
	}

}

void CTestDiffWorker::run()
{
	for (int nIndex = 0; nIndex < DEF_INT_DO_TEST_TOTAL; nIndex++)
	{
		//do_test_TinyODBC();
		do_test_OCL();
	}



}

void CTestDiffWorker::do_test_TinyODBC()
{
	if (NULL != m_pWorkTime_TinyODBC)
	{
		delete m_pWorkTime_TinyODBC;
		m_pWorkTime_TinyODBC = NULL;
	}

	if (NULL != m_pTestWorker_TinyODBC)
	{
		delete m_pTestWorker_TinyODBC;
		m_pTestWorker_TinyODBC = NULL;
	}

	m_pWorkTime_TinyODBC = NULL;
	m_pWorkTime_TinyODBC = new CWorkTimeNoLock(0);

	m_pTestWorker_TinyODBC = NULL;
	m_pTestWorker_TinyODBC = new CTestWorkerTinyODBC();

	m_pTestWorker_TinyODBC->SetDBType(DB_ORACLE);
	m_pTestWorker_TinyODBC->do_connect_to_db();
	m_pTestWorker_TinyODBC->do_delete_table();
	m_pTestWorker_TinyODBC->do_create_table();

	m_pWorkTime_TinyODBC->workBegin();
	m_pTestWorker_TinyODBC->do_insert_data(DEF_INT_INSERT_TOTAL);
	m_pWorkTime_TinyODBC->workEnd();
	_Report(ReportFLInfo, 0, "odbc_oracle_insert,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_TinyODBC->getWorkTime());


	m_pWorkTime_TinyODBC->workBegin();
	m_pTestWorker_TinyODBC->do_select_data();
	m_pWorkTime_TinyODBC->workEnd();
	_Report(ReportFLInfo, 0, "odbc_oracle_select,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_TinyODBC->getWorkTime());
	_Report(ReportFLInfo, 0, "\n");

	m_pTestWorker_TinyODBC->do_disconnect_to_db();

	if (NULL != m_pWorkTime_TinyODBC)
	{
		delete m_pWorkTime_TinyODBC;
		m_pWorkTime_TinyODBC = NULL;
	}

	if (NULL != m_pTestWorker_TinyODBC)
	{
		delete m_pTestWorker_TinyODBC;
		m_pTestWorker_TinyODBC = NULL;
	}

}



void CTestDiffWorker::do_test_OCL()
{

	if (NULL != m_pWorkTime_OCL)
	{
		delete m_pWorkTime_OCL;
		m_pWorkTime_OCL = NULL;
	}

	if (NULL != m_pTestWorker_OCL)
	{
		delete m_pTestWorker_OCL;
		m_pTestWorker_OCL = NULL;
	}

	m_pWorkTime_OCL = NULL;
	m_pWorkTime_OCL = new CWorkTimeNoLock(0);

	m_pTestWorker_OCL = NULL;
	m_pTestWorker_OCL = new CTestWorkerOCL();


	m_pTestWorker_OCL->SetDBType(DB_ORACLE);
	m_pTestWorker_OCL->do_connect_to_db();
	m_pTestWorker_OCL->do_delete_table();
	m_pTestWorker_OCL->do_create_table();

	m_pWorkTime_OCL->workBegin();
	m_pTestWorker_OCL->do_insert_data(DEF_INT_INSERT_TOTAL);
	m_pWorkTime_OCL->workEnd();
	_Report(ReportFLInfo, 0, "ocl_oracle_insert,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OCL->getWorkTime());


	m_pWorkTime_OCL->workBegin();
	m_pTestWorker_OCL->do_select_data();
	m_pWorkTime_OCL->workEnd();
	_Report(ReportFLInfo, 0, "ocl_oracle_select,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OCL->getWorkTime());
	_Report(ReportFLInfo, 0, "\n");

	m_pTestWorker_OCL->do_disconnect_to_db();

	if (NULL != m_pWorkTime_OCL)
	{
		delete m_pWorkTime_OCL;
		m_pWorkTime_OCL = NULL;
	}

	if (NULL != m_pTestWorker_OCL)
	{
		delete m_pTestWorker_OCL;
		m_pTestWorker_OCL = NULL;
	}

}
