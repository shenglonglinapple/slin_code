#include "TestWorkerTinyODBC.h"

#include "ProjectCommonData.h"
#include "BaseLogger.h"
#include "tiodbc.h"



//#include "vld.h"
//#include <odbcinst.h>
//SqlConfigDataSource odbcinst.h  odbccp32.lib ODBCCP32.DLL
//#import "C:\LSL\SVNWork\MT\3001_TIP_NEW\bin\win32_nd\MSADO15.DLL" no_namespace rename("EOF","adoEOF")
//SQLConfigDataSource(NULL,ODBC_ADD_DSN,"MySQL ODBC 5.2 Unicode Driver","DSN=odbctest\0 UID=root\0 PWD=\0 SERVER=localhost\0 DATABASE=odbc\0\0");

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined (WIN32)
# include <windows.h>
# include <io.h>
#else
# include <unistd.h>
#endif

#include <stdio.h>
#include <iostream>

#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

#include <odbcinst.h>
#include <conio.h>

#pragma comment(lib,"odbc32.lib")
#pragma comment(lib,"odbccp32.lib")




CTestWorkerTinyODBC::CTestWorkerTinyODBC( void )
{
	m_nDBType = DB_ORACLE;
}

CTestWorkerTinyODBC::~CTestWorkerTinyODBC( void )
{

}



void CTestWorkerTinyODBC::run()
{
	m_nThreadJobState = JobState_Begin;


	_ThreadJob();


	m_nThreadJobState = JobState_End;
}

void CTestWorkerTinyODBC::_ThreadJob()
{
	_TestFun_SampleTable();
}

std::string CTestWorkerTinyODBC::_BuildSQL_DeleteTable()
{
	std::string strSQL;

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			strSQL = "DROP TABLE TABLE_TEST_DAITEST";
		}
		break;
	case DB_MYSQL:
		{
			strSQL = "DROP TABLE TABLE_TEST_DAITEST";
		}
		break;
	default:
		break;
	}//switch

	return strSQL;
}

std::string CTestWorkerTinyODBC::_BuildSQL_CreateTable()
{
	std::string strSQL;

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			strSQL = "CREATE TABLE TABLE_TEST_DAITEST(LINE_ID NUMBER, TEST_TYPE VARCHAR2(200), INT_COLUMN NUMBER, STR_COLUMN VARCHAR2(200), BOOL_COLUMN NUMBER, REAL_COLUMN NUMBER(20,8), DATE_COLUMN DATE, TIMESTAMP_COLUMN TIMESTAMP)";
		}
		break;
	case DB_MYSQL:
		{
			strSQL = "CREATE TABLE TABLE_TEST_DAITEST(LINE_ID int, TEST_TYPE VARCHAR(200), INT_COLUMN int, STR_COLUMN VARCHAR(200), BOOL_COLUMN int, REAL_COLUMN double, DATE_COLUMN DATETIME, TIMESTAMP_COLUMN TIMESTAMP)";
		}
		break;
	default:
		break;
	}//switch

	return strSQL;
}


std::string CTestWorkerTinyODBC::_BuildSQL_InsertDataToTable()
{
	std::string strSQL;

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			strSQL = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (1000, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, TO_DATE('09/09/2014 09:57:20','dd/mm/yyyy hh24:mi:ss'), TO_DATE('09/09/2014 09:57:20','dd/mm/yyyy hh24:mi:ss'))";
		}
		break;
	case DB_MYSQL:
		{
			strSQL = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (1000, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, '09/09/2014 09:57:20', '09/09/2014 09:57:20')";
		}
		break;
	default:
		break;
	}//switch

	return strSQL;
}

std::string CTestWorkerTinyODBC::_BuildSQL_SelectDataFromTable()
{
	std::string strSQL;

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			strSQL = "SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST WHERE LINE_ID = 1000";
		}
		break;
	case DB_MYSQL:
		{
			strSQL = "SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST WHERE LINE_ID = 1000";
		}
		break;
	default:
		break;
	}//switch

	return strSQL;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////




int CTestWorkerTinyODBC::_TestFun_SampleTable()
{
	int nFunRes = 0;
	std::string strSQL;

	tiodbc::connection my_connection;
	tiodbc::statement my_statement;

	// Create a connection with an ODBC Data Source
	if (!my_connection.connect("Oracle12343DYN", "IT271350_5", "IT271350_5"))
	{
		std::cout<<"Cannot connect to the Data Source"<<"\t"<< my_connection.last_error();
		return nFunRes;
	}

	// Execute a direct query
	strSQL = _BuildSQL_DeleteTable();
	if (!my_statement.execute_direct(my_connection, strSQL.c_str()))
	{
		std::cout<<"Cannot execute query!"<<"\t"<< my_connection.last_error();
		return nFunRes;
	}

	strSQL = _BuildSQL_CreateTable();
	if (!my_statement.execute_direct(my_connection, strSQL.c_str()))
	{
		std::cout<<"Cannot execute query!"<<"\t"<< my_connection.last_error();
		return nFunRes;
	}

	strSQL = _BuildSQL_InsertDataToTable();
	if (!my_statement.execute_direct(my_connection, strSQL.c_str()))
	{
		std::cout<<"Cannot execute query!"<<"\t"<< my_connection.last_error();
		return nFunRes;
	}

	strSQL = _BuildSQL_SelectDataFromTable();
	if (!my_statement.execute_direct(my_connection, strSQL.c_str()))
	{
		std::cout<<"Cannot execute query!"<<"\t"<< my_connection.last_error();
		return nFunRes;
	}

	// Get results from statement
	while(my_statement.fetch_next())
	{
		// print all fields for each row
		for(int i = 1;i <= my_statement.count_columns(); i ++)
		{
			std::cout<<my_statement.field(i).as_string()<<"\t";
		}
		std::cout <<std::endl;
	}


	return nFunRes;
}








//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
