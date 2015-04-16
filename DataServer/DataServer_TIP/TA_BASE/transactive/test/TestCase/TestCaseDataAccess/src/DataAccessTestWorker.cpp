#include "DataAccessTestWorker.h"

#include "core/threads/src/BoostThread.h"
#include "core/CppSQLiteLib/src/CppSQLite3DB.h"
#include "core/DataAccess/src/SQLCode.h"

#include "core/utilities/src/UtilitiesCommonDef.h"
#include "core/utilities/src/UtilitiesCommonData.h"
#include "core/CppConfigLib/src/RunParams.h"


#include "core/DataAccess/src/IDbDataOper.h"
#include "core/DataAccess/src/DatabaseFactory.h"
#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/IQueryAdapter.h"
#include "core/DataAccess/src/DbStatusItem.h"
#include "core/DataAccess/src/DbStatusManager.h"
#include "core/DataAccess/src/ConnectionPoolManager.h"


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

using namespace TA_Base_Core;

NS_BEGIN(TA_Base_Test) 




//////////////////////////////////////////////////////////////////////////
CDataAccesssTestWorker::CDataAccesssTestWorker(void)
{	
	BOOST_LOG_FUNCTION();	
	m_toTerminate = false;
	m_nThreadJobState = JobState_Begin;

}

CDataAccesssTestWorker::~CDataAccesssTestWorker(void)
{
	BOOST_LOG_FUNCTION();

}


void CDataAccesssTestWorker::run()
{
	BOOST_LOG_FUNCTION();

	m_nThreadJobState = JobState_Begin;


	while (false == m_toTerminate)
	{
		_ThreadJob();
		TA_Base_Core::CBoostThread::sleep(1000);
	}

	_ProcessUserTerminate();
}

void CDataAccesssTestWorker::terminate()
{
	BOOST_LOG_FUNCTION();

	m_toTerminate = true;
}


int CDataAccesssTestWorker::_ProcessUserTerminate()
{
	BOOST_LOG_FUNCTION();

	int nFunRes = 0;
	m_toTerminate = true;
	m_nThreadJobState = JobState_End;
	return nFunRes;
}

bool CDataAccesssTestWorker::isFinishWork()
{
	BOOST_LOG_FUNCTION();

	bool bFinishWork = false;
	if (JobState_End == m_nThreadJobState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CDataAccesssTestWorker::_ThreadJob()
{
	BOOST_LOG_FUNCTION();

	switch (m_nThreadJobState)
	{
	case JobState_Begin:
		m_nThreadJobState = JobState_DO_LogTest;
		break;
	case JobState_DO_LogTest:
		_Process_JobState_DO_LogTest();
		m_nThreadJobState = JobState_DO_ThreadTest;
		break;
	case JobState_DO_ThreadTest:
		_Process_JobState_DO_ThreadTest();
		m_nThreadJobState = JobState_DO_SQliteTest;
		break;
	case JobState_DO_SQliteTest:
		_Process_JobState_DO_SQliteTest();
		m_nThreadJobState = JobState_DO_DataAccessTest;
		break;
	case JobState_DO_DataAccessTest:
		//_Process_JobState_DO_DataAccessTest();
		//_Process_JobState_DO_DataAccessTest_ALL();
		//_Process_JobState_DO_DataAccessTest_EnqTest();
		_Process_JobState_DO_DataAccessTest_MemoryTest();
		m_nThreadJobState = JobState_End;
		break;
	case JobState_End:
		break;
	default:
		TA_Base_Core::CBoostThread::sleep(1000);
		break;

	}//switch
}


void CDataAccesssTestWorker::_Process_JobState_DO_LogTest()
{
	BOOST_LOG_FUNCTION();
	TA_Base_Core::CBoostLogger::getInstance().testBoostLog();


}


void CDataAccesssTestWorker::_Process_JobState_DO_ThreadTest()
{
	BOOST_LOG_FUNCTION();
}


void CDataAccesssTestWorker::_Process_JobState_DO_SQliteTest()
{
	BOOST_LOG_FUNCTION();
	std::string strSQLiteDBFile = "SQLiteDBFileTest.db";
	TA_Base_Core::CppSQLite3DB db;
	int nAffectedRows = 0;
	std::string strSQL_Create_Table = "create table emp(empno int, empname char(20))";
	std::string strSQL_Insert_Data = "insert into emp values (7, 'David Beckham')";
	std::string strSQL_Update_Data = "update emp set empname = 'Christiano Ronaldo' where empno = 7";
	std::string strSQL_Delete_Data = "delete from emp where empno = 7";
	



	LOG_DEBUG<<"SQLite Version: "<<db.SQLiteVersion();
	remove(strSQLiteDBFile.c_str());
	db.open(strSQLiteDBFile.c_str());


	LOG_DEBUG<<"Creating emp table";
	db.execDML(strSQL_Create_Table.c_str());
	LOG_DEBUG<<"DML tests";
	nAffectedRows = db.execDML(strSQL_Insert_Data.c_str());
	LOG_DEBUG<<"insert nAffectedRows="<<nAffectedRows;
	nAffectedRows = db.execDML(strSQL_Update_Data.c_str());
	LOG_DEBUG<<"update nAffectedRows="<<nAffectedRows;
	nAffectedRows = db.execDML(strSQL_Delete_Data.c_str());
	LOG_DEBUG<<"delete nAffectedRows="<<nAffectedRows;

	db.close();


}


void CDataAccesssTestWorker::_Process_JobState_DO_DataAccessTest()
{
	BOOST_LOG_FUNCTION();
	TA_Base_Core::CppSQLite3DB db;
	int nAffectedRows = 0;
	std::string strSQLiteDBFile = "SQLiteDBFileTest.db";
	TA_Base_Core::CppSQLite3Query queryGetTime;
	std::string strSysDataNow = "";
	TA_Base_Core::SQLStatement stSqlStatement; 
	TA_Base_Core::SQLCode::getInstance();

	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(
		stSqlStatement, TABLETESTDAITEST_CREATE_6000);

		LOG_DEBUG<<"SQLite Version: "<<db.SQLiteVersion();
	remove(strSQLiteDBFile.c_str());
	db.open(strSQLiteDBFile.c_str());

	

	LOG_DEBUG<<"Creating table  Dai Test ";
	db.execDML(stSqlStatement.m_strSQLiteSQL.c_str());
	LOG_DEBUG<<"DML tests";

	//SELECT STRFTIME('%%Y-%%m-%%d %%H:%%M:%%S', 'now', 'localtime') AS SYSDATENOW
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(
		stSqlStatement, SYS_SYSDATE_NOW_SELECT_1000);
	queryGetTime = db.execQuery(stSqlStatement.m_strSQLiteSQL.c_str());
	strSysDataNow = queryGetTime.getStringField("SYSDATENOW");
	queryGetTime.finalize();
	

	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(
		stSqlStatement, TABLETESTDAITEST_INSERT_2000, strSysDataNow, strSysDataNow);

	nAffectedRows = db.execDML(stSqlStatement.m_strSQLiteSQL.c_str());
	LOG_DEBUG<<"insert nAffectedRows="<<nAffectedRows;

	TA_Base_Core::SQLCode::removeInstance();

}






void CDataAccesssTestWorker::_Process_JobState_DO_DataAccessTest_ALL()
{
	BOOST_LOG_FUNCTION();
	TA_Base_Core::SQLStatement objSqlStatement; 
	std::string strSetParamLine;
	TA_Base_Core::CDbStatusItem* pDbStatusItem = NULL;
	int numRows = 1;
	std::string strColumnName = "SYSDATENOW";
	std::string strSysDataNow = "";
	IDbDataOper* pIDbDataOper = NULL;

	//
	TA_Base_Core::CRunParams::getInstance();

	strSetParamLine = DEF_PARAM_RPARAM_PROJECTCFGFILE + DEF_VALUE_String_ParamKeyValue_Separator + DEF_PARAM_RPARAM_PROJECTCFGFILE_Value;
	TA_Base_Core::CRunParams::getInstance().setParamLine(strSetParamLine);

	//"./cfg/ConnectionString.xml"
	strSetParamLine = DEF_PARAM_RPARAM_DBCONNECTIONFILE + DEF_VALUE_String_ParamKeyValue_Separator + DEF_PARAM_RPARAM_DBCONNECTIONFILE_Value;
	TA_Base_Core::CRunParams::getInstance().setParamLine(strSetParamLine);


	//
	TA_Base_Core::CDatabaseFactory::getInstance();


	//
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, TABLETESTDAITEST_CREATE_6000);
	//
	TA_Base_Core::CDatabaseFactory::getInstance().executeModification(DataTypes_DbSync, objSqlStatement);
	

	//SELECT STRFTIME('%%Y-%%m-%%d %%H:%%M:%%S', 'now', 'localtime') AS SYSDATENOW
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, SYS_SYSDATE_NOW_SELECT_1000);

	pIDbDataOper = TA_Base_Core::CDatabaseFactory::getInstance().executeQuery(DataTypes_DbSync, objSqlStatement, 10);
	strSysDataNow = pIDbDataOper->getStringData(0, strColumnName, "");

	//"2014-07-04 17:32:53"
	//strSysDataNow = "2014-07-04 17:32:53";

	std::string str_p_usr_database_name = "tra_occ";
	std::string str_p_queue_name = "AUDIT_DATA_QUEUE";
	std::string str_p_message_qualifier = "PUBLIC";
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, TABLETESTDAITEST_INSERT_2001, str_p_usr_database_name,str_p_queue_name, strSysDataNow, strSysDataNow);
	//TA_Base_Core::CDatabaseFactory::getInstance().executeModification(DataTypes_DbSync, objSqlStatement);

	TA_Base_Core::CDatabaseFactory::removeInstance();
	TA_Base_Core::CRunParams::removeInstance();
}

void CDataAccesssTestWorker::_Process_JobState_DO_DataAccessTest_EnqTest()
{
	TA_Base_Core::SQLStatement objSqlStatement; 
	std::string strSetParamLine;
	TA_Base_Core::CDbStatusItem* pDbStatusItem = NULL;
	int numRows = 1;
	std::string strColumnName = "SYSDATENOW";
	std::string strSysDataNow = "";
	IDbDataOper* pIDbDataOper = NULL;

	//
	TA_Base_Core::CRunParams::getInstance();

	strSetParamLine = DEF_PARAM_RPARAM_PROJECTCFGFILE + DEF_VALUE_String_ParamKeyValue_Separator + DEF_PARAM_RPARAM_PROJECTCFGFILE_Value;
	TA_Base_Core::CRunParams::getInstance().setParamLine(strSetParamLine);

	//"./cfg/ConnectionString.xml"
	strSetParamLine = DEF_PARAM_RPARAM_DBCONNECTIONFILE + DEF_VALUE_String_ParamKeyValue_Separator + DEF_PARAM_RPARAM_DBCONNECTIONFILE_Value;
	TA_Base_Core::CRunParams::getInstance().setParamLine(strSetParamLine);


	//
	TA_Base_Core::CDatabaseFactory::getInstance();


	//
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, TABLETESTDAITEST_CREATE_6000);
	//
	TA_Base_Core::CDatabaseFactory::getInstance().executeModification(DataTypes_DbSync, objSqlStatement);


	//SELECT STRFTIME('%%Y-%%m-%%d %%H:%%M:%%S', 'now', 'localtime') AS SYSDATENOW
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, SYS_SYSDATE_NOW_SELECT_1000);

	pIDbDataOper = TA_Base_Core::CDatabaseFactory::getInstance().executeQuery(DataTypes_DbSync, objSqlStatement, 10);
	strSysDataNow = pIDbDataOper->getStringData(0, strColumnName, "");
	if (NULL != pIDbDataOper)
	{
		delete pIDbDataOper;
		pIDbDataOper = NULL;
	}

	//"2014-07-04 17:32:53"
	//strSysDataNow = "2014-07-04 17:32:53";
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, TABLETESTDAITEST_INSERT_2000, strSysDataNow, strSysDataNow);
	TA_Base_Core::CDatabaseFactory::getInstance().executeModification(DataTypes_DbSync, objSqlStatement);


	std::string str_p_usr_database_name = "tra_occ";
	std::string str_p_queue_name = "AUDIT_DATA_QUEUE";
	std::string str_p_message_qualifier = "PUBLIC";
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, TABLETESTDAITEST_INSERT_2001, str_p_usr_database_name,str_p_queue_name, strSysDataNow, strSysDataNow);
	TA_Base_Core::CDatabaseFactory::getInstance().executeModification(DataTypes_DbSync, objSqlStatement);

	TA_Base_Core::CDatabaseFactory::removeInstance();
	TA_Base_Core::CRunParams::removeInstance();

}


void CDataAccesssTestWorker::_Process_JobState_DO_DataAccessTest_MemoryTest()
{
	TA_Base_Core::SQLStatement objSqlStatement; 
	std::string strSetParamLine;
	TA_Base_Core::CDbStatusItem* pDbStatusItem = NULL;
	int numRows = 1;
	std::string strColumnName = "SYSDATENOW";
	std::string strSysDataNow = "";
	IDbDataOper* pIDbDataOper = NULL;

	//
	TA_Base_Core::CRunParams::getInstance();

	strSetParamLine = DEF_PARAM_RPARAM_PROJECTCFGFILE + DEF_VALUE_String_ParamKeyValue_Separator + DEF_PARAM_RPARAM_PROJECTCFGFILE_Value;
	TA_Base_Core::CRunParams::getInstance().setParamLine(strSetParamLine);

	//"./cfg/ConnectionString.xml"
	strSetParamLine = DEF_PARAM_RPARAM_DBCONNECTIONFILE + DEF_VALUE_String_ParamKeyValue_Separator + DEF_PARAM_RPARAM_DBCONNECTIONFILE_Value;
	TA_Base_Core::CRunParams::getInstance().setParamLine(strSetParamLine);

	TA_Base_Core::CDatabaseFactory::getInstance();

	
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, TABLETESTDAITEST_CREATE_6000);
	TA_Base_Core::CDatabaseFactory::getInstance().executeModification(DataTypes_DbSync, objSqlStatement);
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, SYS_SYSDATE_NOW_SELECT_1000);
	pIDbDataOper = TA_Base_Core::CDatabaseFactory::getInstance().executeQuery(DataTypes_DbSync, objSqlStatement, 10);
	strSysDataNow = pIDbDataOper->getStringData(0, strColumnName, "");
	if (NULL != pIDbDataOper)
	{
		delete pIDbDataOper;
		pIDbDataOper = NULL;
	}
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, TABLETESTDAITEST_INSERT_2000, strSysDataNow, strSysDataNow);
	TA_Base_Core::CDatabaseFactory::getInstance().executeModification(DataTypes_DbSync, objSqlStatement);
	std::string str_p_usr_database_name = "tra_occ";
	std::string str_p_queue_name = "AUDIT_DATA_QUEUE";
	std::string str_p_message_qualifier = "PUBLIC";
	TA_Base_Core::SQLCode::getInstance().prepareSQLStatement(objSqlStatement, TABLETESTDAITEST_INSERT_2001, str_p_usr_database_name,str_p_queue_name, strSysDataNow, strSysDataNow);
	TA_Base_Core::CDatabaseFactory::getInstance().executeModification(DataTypes_DbSync, objSqlStatement);

	
	TA_Base_Core::CDatabaseFactory::removeInstance();

	TA_Base_Core::CRunParams::removeInstance();

}



NS_END(TA_Base_Test) 



