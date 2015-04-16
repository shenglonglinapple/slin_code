#include "TestDiffWorker.h"

#include "ProjectCommonData.h"
#include "WorkTime.h"

#include "BaseReport.h"
#include "TestWorkerOCCI.h"


static const int DEF_INT_DO_TEST_TOTAL = 10;

static const int DEF_INT_INSERT_TOTAL = 10000;



CTestDiffWorker::CTestDiffWorker( void )
{

	
	m_pWorkTime_OCCI = NULL;
	m_pTestWorker_OCCI = NULL;

	CBaseReport::getInstance();
	std::string strLogFile = DEF_Filename_OUT_BASE_REPORT;
	CBaseReport::getInstance().setlogFile(strLogFile);
// 	_Report(ReportFLInfo, 0, "Test,%d,Test", 1);
// 	_Report(ReportFLInfo, 0, "\n");

}

CTestDiffWorker::~CTestDiffWorker( void )
{
	

	//
	if (NULL != m_pWorkTime_OCCI)
	{
		delete m_pWorkTime_OCCI;
		m_pWorkTime_OCCI = NULL;
	}

	if (NULL != m_pTestWorker_OCCI)
	{
		delete m_pTestWorker_OCCI;
		m_pTestWorker_OCCI = NULL;
	}


}

void CTestDiffWorker::run()
{
	for (int nIndex = 0; nIndex < DEF_INT_DO_TEST_TOTAL; nIndex++)
	{
		//do_test_libODBC();
	}
	
	for (int nIndex = 0; nIndex < DEF_INT_DO_TEST_TOTAL; nIndex++)
	{
		//do_test_OCL();
	}

	for (int nIndex = 0; nIndex < DEF_INT_DO_TEST_TOTAL; nIndex++)
	{
		do_test_OCCI();
	}
	

}

void CTestDiffWorker::do_test_OCCI()
{

	//
	if (NULL != m_pWorkTime_OCCI)
	{
		delete m_pWorkTime_OCCI;
		m_pWorkTime_OCCI = NULL;
	}

	if (NULL != m_pTestWorker_OCCI)
	{
		delete m_pTestWorker_OCCI;
		m_pTestWorker_OCCI = NULL;
	}

	m_pWorkTime_OCCI = NULL;
	m_pWorkTime_OCCI = new CWorkTimeNoLock(0);

	m_pTestWorker_OCCI = NULL;
	m_pTestWorker_OCCI = new CTestWorkerOCCI();


	m_pTestWorker_OCCI->SetDBType(DB_ORACLE);
	m_pTestWorker_OCCI->do_connect_to_db();
	m_pTestWorker_OCCI->do_delete_table();
	m_pTestWorker_OCCI->do_create_table();

	m_pWorkTime_OCCI->workBegin();
	m_pTestWorker_OCCI->do_insert_data(DEF_INT_INSERT_TOTAL);
	m_pWorkTime_OCCI->workEnd();
	_Report(ReportFLInfo, 0, "occi_oracle_insert,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OCCI->getWorkTime());


	m_pWorkTime_OCCI->workBegin();
	//m_pTestWorker_OCCI->do_select_data();
	m_pWorkTime_OCCI->workEnd();
	_Report(ReportFLInfo, 0, "occi_oracle_select,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OCCI->getWorkTime());
	_Report(ReportFLInfo, 0, "\n");

	m_pTestWorker_OCCI->do_disconnect_to_db();

	//
	if (NULL != m_pWorkTime_OCCI)
	{
		delete m_pWorkTime_OCCI;
		m_pWorkTime_OCCI = NULL;
	}

	if (NULL != m_pTestWorker_OCCI)
	{
		delete m_pTestWorker_OCCI;
		m_pTestWorker_OCCI = NULL;
	}


}

