#include "TestDiffWorker.h"

#include "ProjectCommonData.h"
#include "WorkTime.h"

#include "BaseReport.h"
#include "TestWorkerLibODBC.h"
#include "TestWorkerOCL.h"
#include "TestWorkerOTL.h"

#include "TestWorkerOTLBlob.h"
#include "TestWorkerOTLODBC.h"


static const int DEF_INT_DO_TEST_TOTAL = 1;

static const int DEF_INT_INSERT_TOTAL = 1000;



CTestDiffWorker::CTestDiffWorker( void )
{

	m_pWorkTime_LibODBC = NULL;
	m_pTestWorker_LibODBC = NULL;

	m_pWorkTime_OCL = NULL;
	m_pTestWorker_OCL = NULL;

	m_pWorkTime_OTL = NULL;
	m_pTestWorker_OTL = NULL;

	m_pWorkTime_OTLBlob = NULL;
	m_pTestWorker_OTLBlob = NULL;

	m_pWorkTime_OTLODBC = NULL;
	m_pTestWorker_OTLODBC = NULL;


	CBaseReport::getInstance();
	std::string strLogFile = DEF_Filename_OUT_BASE_REPORT;
	CBaseReport::getInstance().setlogFile(strLogFile);
// 	_Report(ReportFLInfo, 0, "Test,%d,Test", 1);
// 	_Report(ReportFLInfo, 0, "\n");

}

CTestDiffWorker::~CTestDiffWorker( void )
{
	//
	if (NULL != m_pWorkTime_LibODBC)
	{
		delete m_pWorkTime_LibODBC;
		m_pWorkTime_LibODBC = NULL;
	}

	if (NULL != m_pTestWorker_LibODBC)
	{
		delete m_pTestWorker_LibODBC;
		m_pTestWorker_LibODBC = NULL;
	}

	//
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
	if (NULL != m_pWorkTime_OTL)
	{
		delete m_pWorkTime_OTL;
		m_pWorkTime_OTL = NULL;
	}

	if (NULL != m_pTestWorker_OTL)
	{
		delete m_pTestWorker_OTL;
		m_pTestWorker_OTL = NULL;
	}
	
	//
	if (NULL != m_pWorkTime_OTLBlob)
	{
		delete m_pWorkTime_OTLBlob;
		m_pWorkTime_OTLBlob = NULL;
	}

	if (NULL != m_pTestWorker_OTLBlob)
	{
		delete m_pTestWorker_OTLBlob;
		m_pTestWorker_OTLBlob = NULL;
	}

	//
	if (NULL != m_pWorkTime_OTLODBC)
	{
		delete m_pWorkTime_OTLODBC;
		m_pWorkTime_OTLODBC = NULL;
	}

	if (NULL != m_pTestWorker_OTLODBC)
	{
		delete m_pTestWorker_OTLODBC;
		m_pTestWorker_OTLODBC = NULL;
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
		//do_test_OTL();
	}
	
	for (int nIndex = 0; nIndex < DEF_INT_DO_TEST_TOTAL; nIndex++)
	{
		//do_test_OTL_Blob();
	}

	for (int nIndex = 0; nIndex < DEF_INT_DO_TEST_TOTAL; nIndex++)
	{
		do_test_OTL_ODBC();
	}
	
}

void CTestDiffWorker::do_test_libODBC()
{

	//
	if (NULL != m_pWorkTime_LibODBC)
	{
		delete m_pWorkTime_LibODBC;
		m_pWorkTime_LibODBC = NULL;
	}

	if (NULL != m_pTestWorker_LibODBC)
	{
		delete m_pTestWorker_LibODBC;
		m_pTestWorker_LibODBC = NULL;
	}

	m_pWorkTime_LibODBC = NULL;
	m_pWorkTime_LibODBC = new CWorkTimeNoLock(0);

	m_pTestWorker_LibODBC = NULL;
	m_pTestWorker_LibODBC = new CTestWorkerLibODBC();


	m_pTestWorker_LibODBC->SetDBType(DB_ORACLE);
	m_pTestWorker_LibODBC->do_connect_to_db();
	m_pTestWorker_LibODBC->do_delete_table();
	m_pTestWorker_LibODBC->do_create_table();

	m_pWorkTime_LibODBC->workBegin();
	m_pTestWorker_LibODBC->do_insert_data(DEF_INT_INSERT_TOTAL);
	m_pWorkTime_LibODBC->workEnd();
	_Report(ReportFLInfo, 0, "libodbc_oracle_insert,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_LibODBC->getWorkTime());


	m_pWorkTime_LibODBC->workBegin();
	m_pTestWorker_LibODBC->do_select_data();
	m_pWorkTime_LibODBC->workEnd();
	_Report(ReportFLInfo, 0, "libodbc_oracle_select,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_LibODBC->getWorkTime());
	_Report(ReportFLInfo, 0, "\n");

	m_pTestWorker_LibODBC->do_disconnect_to_db();

	//
	if (NULL != m_pWorkTime_LibODBC)
	{
		delete m_pWorkTime_LibODBC;
		m_pWorkTime_LibODBC = NULL;
	}

	if (NULL != m_pTestWorker_LibODBC)
	{
		delete m_pTestWorker_LibODBC;
		m_pTestWorker_LibODBC = NULL;
	}


}



void CTestDiffWorker::do_test_OCL()
{

	//
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

	//
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

void CTestDiffWorker::do_test_OTL()
{

	//
	if (NULL != m_pWorkTime_OTL)
	{
		delete m_pWorkTime_OTL;
		m_pWorkTime_OTL = NULL;
	}

	if (NULL != m_pTestWorker_OTL)
	{
		delete m_pTestWorker_OTL;
		m_pTestWorker_OTL = NULL;
	}

	m_pWorkTime_OTL = NULL;
	m_pWorkTime_OTL = new CWorkTimeNoLock(0);

	m_pTestWorker_OTL = NULL;
	m_pTestWorker_OTL = new CTestWorkerOTL();


	m_pTestWorker_OTL->SetDBType(DB_ORACLE);
	m_pTestWorker_OTL->do_connect_to_db();
	m_pTestWorker_OTL->do_delete_table();
	m_pTestWorker_OTL->do_create_table();

	m_pWorkTime_OTL->workBegin();
	m_pTestWorker_OTL->do_insert_data(DEF_INT_INSERT_TOTAL);
	m_pWorkTime_OTL->workEnd();
	_Report(ReportFLInfo, 0, "OTL_oracle_insert,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OTL->getWorkTime());


	m_pWorkTime_OTL->workBegin();
	m_pTestWorker_OTL->do_select_data();
	m_pWorkTime_OTL->workEnd();
	_Report(ReportFLInfo, 0, "OTL_oracle_select,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OTL->getWorkTime());
	_Report(ReportFLInfo, 0, "\n");

	m_pTestWorker_OTL->do_disconnect_to_db();

	//
	if (NULL != m_pWorkTime_OTL)
	{
		delete m_pWorkTime_OTL;
		m_pWorkTime_OTL = NULL;
	}

	if (NULL != m_pTestWorker_OTL)
	{
		delete m_pTestWorker_OTL;
		m_pTestWorker_OTL = NULL;
	}


}

void CTestDiffWorker::do_test_OTL_Blob()
{

	//
	if (NULL != m_pWorkTime_OTLBlob)
	{
		delete m_pWorkTime_OTLBlob;
		m_pWorkTime_OTLBlob = NULL;
	}

	if (NULL != m_pTestWorker_OTLBlob)
	{
		delete m_pTestWorker_OTLBlob;
		m_pTestWorker_OTLBlob = NULL;
	}

	m_pWorkTime_OTLBlob = NULL;
	m_pWorkTime_OTLBlob = new CWorkTimeNoLock(0);

	m_pTestWorker_OTLBlob = NULL;
	m_pTestWorker_OTLBlob = new CTestWorkerOTLBlob();


	m_pTestWorker_OTLBlob->SetDBType(DB_ORACLE);
	m_pTestWorker_OTLBlob->do_connect_to_db();
	m_pTestWorker_OTLBlob->do_delete_table();
	m_pTestWorker_OTLBlob->do_create_table();

	m_pWorkTime_OTLBlob->workBegin();
	m_pTestWorker_OTLBlob->do_insert_data(DEF_INT_INSERT_TOTAL);
	m_pWorkTime_OTLBlob->workEnd();
	_Report(ReportFLInfo, 0, "OTL_oracle_insert,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OTLBlob->getWorkTime());

	m_pTestWorker_OTLBlob->do_update_data_ex_setdata();


	m_pWorkTime_OTLBlob->workBegin();
	m_pTestWorker_OTLBlob->do_select_data();
	m_pWorkTime_OTLBlob->workEnd();
	_Report(ReportFLInfo, 0, "OTL_oracle_select,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OTLBlob->getWorkTime());
	_Report(ReportFLInfo, 0, "\n");

	m_pTestWorker_OTLBlob->do_disconnect_to_db();

	//
	if (NULL != m_pWorkTime_OTLBlob)
	{
		delete m_pWorkTime_OTLBlob;
		m_pWorkTime_OTLBlob = NULL;
	}

	if (NULL != m_pTestWorker_OTLBlob)
	{
		delete m_pTestWorker_OTLBlob;
		m_pTestWorker_OTLBlob = NULL;
	}


}




void CTestDiffWorker::do_test_OTL_ODBC()
{

	//
	if (NULL != m_pWorkTime_OTLODBC)
	{
		delete m_pWorkTime_OTLODBC;
		m_pWorkTime_OTLODBC = NULL;
	}

	if (NULL != m_pTestWorker_OTLODBC)
	{
		delete m_pTestWorker_OTLODBC;
		m_pTestWorker_OTLODBC = NULL;
	}

	m_pWorkTime_OTLODBC = NULL;
	m_pWorkTime_OTLODBC = new CWorkTimeNoLock(0);

	m_pTestWorker_OTLODBC = NULL;
	m_pTestWorker_OTLODBC = new CTestWorkerOTLODBC();


	m_pTestWorker_OTLODBC->SetDBType(DB_ORACLE);
	m_pTestWorker_OTLODBC->do_connect_to_db();
	m_pTestWorker_OTLODBC->do_delete_table();
	m_pTestWorker_OTLODBC->do_create_table();

	m_pWorkTime_OTLODBC->workBegin();
	m_pTestWorker_OTLODBC->do_insert_data(DEF_INT_INSERT_TOTAL);
	m_pWorkTime_OTLODBC->workEnd();
	_Report(ReportFLInfo, 0, "OTL_oracle_insert,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OTLODBC->getWorkTime());



	m_pWorkTime_OTLODBC->workBegin();
	m_pTestWorker_OTLODBC->do_select_data();
	m_pWorkTime_OTLODBC->workEnd();
	_Report(ReportFLInfo, 0, "OTL_oracle_select,%d,", DEF_INT_INSERT_TOTAL);
	_Report(ReportFLInfo, 0, "%llu,ms,", m_pWorkTime_OTLODBC->getWorkTime());
	_Report(ReportFLInfo, 0, "\n");

	m_pTestWorker_OTLODBC->do_disconnect_to_db();

	//
	if (NULL != m_pWorkTime_OTLODBC)
	{
		delete m_pWorkTime_OTLODBC;
		m_pWorkTime_OTLODBC = NULL;
	}

	if (NULL != m_pTestWorker_OTLODBC)
	{
		delete m_pTestWorker_OTLODBC;
		m_pTestWorker_OTLODBC = NULL;
	}


}