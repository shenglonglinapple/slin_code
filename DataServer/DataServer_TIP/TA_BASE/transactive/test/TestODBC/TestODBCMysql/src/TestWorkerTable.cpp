#include "TestWorkerTable.h"

#include "ProjectCommonData.h"
#include "BaseLogger.h"




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




CTestWorkerTable::CTestWorkerTable( void )
{
	m_nDBType = DB_ORACLE;
	m_hEnviroment = SQL_NULL_HENV;// = NULL;
	m_hDatabaseConnection = SQL_NULL_HDBC;// = NULL;
	m_hStatement = SQL_NULL_HSTMT;// = NULL;
}

CTestWorkerTable::~CTestWorkerTable( void )
{
	m_hEnviroment = NULL;// = NULL;
	m_hDatabaseConnection = NULL;// = NULL;
	m_hStatement = NULL;// = NULL;
}



void CTestWorkerTable::run()
{
	m_nThreadJobState = JobState_Begin;


	_ThreadJob();


	m_nThreadJobState = JobState_End;
}

void CTestWorkerTable::_ThreadJob()
{
	_TestFun_ODBC_TABLE_TEST_DAITEST();
}

std::string CTestWorkerTable::_BuildSQL_DeleteTable()
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

std::string CTestWorkerTable::_BuildSQL_CreateTable()
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


std::string CTestWorkerTable::_BuildSQL_InsertDataToTable()
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

std::string CTestWorkerTable::_BuildSQL_SelectDataFromTable()
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

int CTestWorkerTable::_ExecModifySQL(const std::string& strSQL)
{
	int nFunRes = 0;
	SQLRETURN retcode = 0;
	SQLINTEGER lGetConAttrRet = SQL_CD_TRUE;
	SQLINTEGER lGetConAttrRetSize = 0;
	SQLSMALLINT nColumnCount = 0;
	SQLLEN nModifyRowCount = 0;



	//下面代码会在数据库重连后产生错误，删除。
	/* values for SQL_ATTR_CONNECTION_DEAD */
	//#define SQL_CD_TRUE                 1L      /* Connection is closed/dead */
	//#define SQL_CD_FALSE                0L      /* Connection is open/available */
	lGetConAttrRet = SQL_CD_TRUE;
	lGetConAttrRetSize = 0;
	//判断连接是否活着，不过断开时一定要等到对数据库有SQL请求后才有可以。
	retcode = SQLGetConnectAttr(m_hDatabaseConnection, SQL_ATTR_CONNECTION_DEAD, (SQLPOINTER)&lGetConAttrRet, SQL_IS_INTEGER, &lGetConAttrRetSize);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLGetConnectAttr(SQL_ATTR_CONNECTION_DEAD)", retcode);
	if (lGetConAttrRet == SQL_CD_FALSE)
	{
		//连接仍然是活动的
	}
	else
	{
		nFunRes = -1;
		return nFunRes;
	}

	if (NULL != m_hStatement)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		m_hStatement = NULL;
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_STMT)", retcode);
	}

	/* Allocate statement handle */
	//因为一个语句句柄只能执行一次sql语句,所有,得先释放才能执行
	//分配SQL语句句柄
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLAllocHandle(SQL_HANDLE_STMT)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}


	//set AUTOCOMMIT OFF
	retcode = SQLSetConnectOption(m_hDatabaseConnection, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetConnectOption(SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}


	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)strSQL.c_str(), SQL_NTS);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLExecDirect(sql)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLEndTran(SQL_HANDLE_DBC, m_hDatabaseConnection, SQL_ROLLBACK);
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLEndTran(SQL_HANDLE_DBC, m_hDatabaseConnection, SQL_ROLLBACK)", retcode);
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}
	else
	{
		retcode = SQLEndTran(SQL_HANDLE_DBC, m_hDatabaseConnection, SQL_COMMIT);
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLEndTran(SQL_HANDLE_DBC, m_hDatabaseConnection, SQL_COMMIT)", retcode);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
		{
			retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			m_hEnviroment = NULL;// = NULL;
			m_hDatabaseConnection = NULL;// = NULL;
			m_hStatement = NULL;// = NULL;
			return nFunRes;
		}
	}

	
	/* get return data Row count insert update delete*/
	nModifyRowCount = 0;
	retcode = ::SQLRowCount(m_hStatement, &nModifyRowCount);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLRowCount()", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = INVALID_HANDLE_VALUE;// = NULL;
		m_hDatabaseConnection = INVALID_HANDLE_VALUE;// = NULL;
		m_hStatement = INVALID_HANDLE_VALUE;// = NULL;
		return nFunRes;
	}




	//set AUTOCOMMIT ON
	retcode = SQLSetConnectOption(m_hDatabaseConnection, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetConnectOption(SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}


	if (NULL != m_hStatement)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		m_hStatement = NULL;
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_STMT)", retcode);
	}

	return nFunRes;
}



int CTestWorkerTable::_ExecSelectSQL(const std::string& strSQL)
{
	int nFunRes = 0;
	SQLRETURN retcode = 0;
	SQLINTEGER lGetConAttrRet = SQL_CD_TRUE;
	SQLINTEGER lGetConAttrRetSize = 0;
	SQLSMALLINT nColumnCount = 0;



	//下面代码会在数据库重连后产生错误，删除。
	/* values for SQL_ATTR_CONNECTION_DEAD */
	//#define SQL_CD_TRUE                 1L      /* Connection is closed/dead */
	//#define SQL_CD_FALSE                0L      /* Connection is open/available */
	lGetConAttrRet = SQL_CD_TRUE;
	lGetConAttrRetSize = 0;
	//判断连接是否活着，不过断开时一定要等到对数据库有SQL请求后才有可以。
	retcode = SQLGetConnectAttr(m_hDatabaseConnection, SQL_ATTR_CONNECTION_DEAD, (SQLPOINTER)&lGetConAttrRet, SQL_IS_INTEGER, &lGetConAttrRetSize);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLGetConnectAttr(SQL_ATTR_CONNECTION_DEAD)", retcode);
	if (lGetConAttrRet == SQL_CD_FALSE)
	{
		//连接仍然是活动的
	}
	else
	{
		nFunRes = -1;
		return nFunRes;
	}

	if (NULL != m_hStatement)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		m_hStatement = NULL;
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_STMT)", retcode);
	}

	/* Allocate statement handle */
	//因为一个语句句柄只能执行一次sql语句,所有,得先释放才能执行
	//分配SQL语句句柄
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLAllocHandle(SQL_HANDLE_STMT)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}


	//set AUTOCOMMIT OFF
	retcode = SQLSetConnectOption(m_hDatabaseConnection, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetConnectOption(SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}


	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)strSQL.c_str(), SQL_NTS);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLExecDirect(sql)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLEndTran(SQL_HANDLE_DBC, m_hDatabaseConnection, SQL_ROLLBACK);
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLEndTran(SQL_HANDLE_DBC, m_hDatabaseConnection, SQL_ROLLBACK)", retcode);
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}
	else
	{
		retcode = SQLEndTran(SQL_HANDLE_DBC, m_hDatabaseConnection, SQL_COMMIT);
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLEndTran(SQL_HANDLE_DBC, m_hDatabaseConnection, SQL_COMMIT)", retcode);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
		{
			retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			m_hEnviroment = NULL;// = NULL;
			m_hDatabaseConnection = NULL;// = NULL;
			m_hStatement = NULL;// = NULL;
			return nFunRes;
		}
	}

	retcode = SQLNumResultCols(m_hStatement, &nColumnCount);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLNumResultCols(nColumnCount)", retcode);


	while (true)
	{
		//fecth data use SQLFetch() return SQL_SUCCESS  then no data
		retcode = SQLFetch(m_hStatement);
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLDescribeCol(pszName)", retcode);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}


		for(SQLSMALLINT nIndex = 1; nIndex < (nColumnCount + 1); nIndex++)
		{
			//依次得到每个列的字段名
			//GetColumnName
			//SQLHSTMT StatementHandle;
			//SQLUSMALLINT ColumnNumber;
			SQLCHAR pszName[256] = "";
			SQLSMALLINT BufferLength = sizeof(SQLCHAR) * 256;
			SQLSMALLINT NameLength = 0;
			SQLSMALLINT DataType = 0;
			SQLULEN ColumnSize = 0;
			SQLSMALLINT DecimalDigits = 0;
			SQLSMALLINT Nullable = 0;
			/* SQL data type codes */
			// #define SQL_UNKNOWN_TYPE    0
			// #define SQL_CHAR            1

			memset(pszName, 0, 256);
			retcode = SQLDescribeCol(m_hStatement, nIndex, (SQLTCHAR*)pszName, BufferLength, &NameLength, &DataType, &ColumnSize, &DecimalDigits, &Nullable);
			_PrintLogCheck(BaseLogSourceFLInfo, "SQLDescribeCol(pszName)", retcode);


			SQLINTEGER sz_needed = 0;
			TCHAR small_buff[256];

			// Try with small buffer
			retcode = SQLGetData(m_hStatement, nIndex, SQL_C_TCHAR, small_buff, sizeof(small_buff), &sz_needed);

			if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode)
			{
				std::string strRes = small_buff;
				_BaseLog(BaseLogSourceFLInfo, DebugTrace, "get row nIndex=%d pszTest=%s nOutLen=%d", nIndex, strRes.c_str(), sz_needed);				
			}
			else if (sz_needed > 0)
			{	// A bigger buffer is needed
				SQLINTEGER sz_buff = sz_needed + 1;
				std::auto_ptr<TCHAR> p_data(new TCHAR[sz_buff]);
				SQLGetData(m_hStatement, nIndex, SQL_C_TCHAR, (SQLTCHAR *)p_data.get(), sz_buff, &sz_needed);
				std::string strRes = p_data.get();
				_BaseLog(BaseLogSourceFLInfo, DebugTrace, "get row nIndex=%d pszTest=%s nOutLen=%d", nIndex, strRes.c_str(), sz_needed);				
			}

		}


	}//while (true)





	//set AUTOCOMMIT ON
	retcode = SQLSetConnectOption(m_hDatabaseConnection, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetConnectOption(SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_ON)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}


	if (NULL != m_hStatement)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		m_hStatement = NULL;
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_STMT)", retcode);
	}

	return nFunRes;
}

int CTestWorkerTable::_TestFun_ODBC_TABLE_TEST_DAITEST()
{
	int nFunRes = 0;
	SQLRETURN retcode = 0;
	SQLSMALLINT nColumnCount = 0;
	SQLINTEGER lGetConAttrRet = SQL_CD_TRUE;
	SQLINTEGER lGetConAttrRetSize = 0;
	std::string strSQL;

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLAllocHandle(SQL_HANDLE_ENV)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}
	

	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetEnvAttr(SQL_ATTR_ODBC_VERSION SQL_OV_ODBC3)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}


	
	/* Allocate connection handle */
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLAllocHandle(SQL_HANDLE_DBC)", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}



	/* Set login timeout to 5 seconds. */
	//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

	/* Connect to data source */
	//Oracle12343DYN
	/*
	error:
	pMessage=[Microsoft][ODBC Driver Manager] Data source name not found and no default driver specified nBufferLenMessage=512 nGetTextLength=91
	*/
	retcode = SQLConnect(m_hDatabaseConnection, 
		(SQLCHAR*) "Oracle12343DYN", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLConnect()", retcode);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;// = NULL;
		m_hDatabaseConnection = NULL;// = NULL;
		m_hStatement = NULL;// = NULL;
		return nFunRes;
	}


	/*
	error:
	HandleType=SQL_HANDLE_STMT Handle=0x612008  pSQLState=42S02 NativeError=942 pMessage=[Oracle][ODBC][Ora]ORA-00942: table or view does not exist
	*/
	strSQL = _BuildSQL_DeleteTable();
	_ExecModifySQL(strSQL);

	strSQL = _BuildSQL_CreateTable();
	_ExecModifySQL(strSQL);

	strSQL = _BuildSQL_InsertDataToTable();
	_ExecModifySQL(strSQL);

	
	strSQL = _BuildSQL_SelectDataFromTable();
	_ExecSelectSQL(strSQL);


	/* Process data */
	if (NULL != m_hStatement)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		m_hStatement = NULL;
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_STMT)", retcode);
	}

	if (NULL != m_hDatabaseConnection)
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLDisconnect()", retcode);

		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		m_hDatabaseConnection = NULL;
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_DBC)", retcode);
	}

	if (NULL != m_hEnviroment)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		m_hEnviroment = NULL;
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_ENV)", retcode);
	}


	m_hEnviroment = NULL;// = NULL;
	m_hDatabaseConnection = NULL;// = NULL;
	m_hStatement = NULL;// = NULL;

	return nFunRes;
}







//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

std::string CTestWorkerTable::_GetHandleTypeStringValue(SQLSMALLINT nHandleType)
{
	std::string strHandleType;

	strHandleType.clear();

	if (SQL_HANDLE_ENV == nHandleType)
	{
		strHandleType = "SQL_HANDLE_ENV";
	}
	else if (SQL_HANDLE_DBC == nHandleType)
	{
		strHandleType = "SQL_HANDLE_DBC";
	}
	else if (SQL_HANDLE_STMT == nHandleType)
	{
		strHandleType = "SQL_HANDLE_STMT";
	}
	else if (SQL_HANDLE_DESC == nHandleType)
	{
		strHandleType = "SQL_HANDLE_DESC";
	}
	else
	{
		strHandleType = "SQL_HANDLE_UNKNOW";
	}

	return strHandleType;	
}

void CTestWorkerTable::_PrintLogCheck(const std::string& strFileName, int nFileLine, const std::string& strLogInfo, SQLRETURN nSQLReturn)
{	
	if (SQL_SUCCESS != nSQLReturn && SQL_SUCCESS_WITH_INFO == nSQLReturn)
	{
		if (NULL != m_hEnviroment)
		{
			_PrintLogEx(strFileName, nFileLine, DebugDatabase, strLogInfo, m_hEnviroment, m_hDatabaseConnection, NULL);
		}
		if (NULL != m_hDatabaseConnection)
		{
			_PrintLog(strFileName, nFileLine, DebugDatabase, strLogInfo, SQL_HANDLE_DBC, m_hDatabaseConnection);
		}
		if (NULL != m_hStatement)
		{
			_PrintLog(strFileName, nFileLine, DebugDatabase, strLogInfo, SQL_HANDLE_STMT, m_hStatement);
		}
	}
	else if (SQL_SUCCESS != nSQLReturn) 
	{
		if (NULL != m_hEnviroment)
		{
			_PrintLogEx(strFileName, nFileLine, DebugError, strLogInfo, m_hEnviroment, m_hDatabaseConnection, NULL);
		}
		if (NULL != m_hDatabaseConnection)
		{
			_PrintLog(strFileName, nFileLine, DebugError, strLogInfo, SQL_HANDLE_DBC, m_hDatabaseConnection);
		}
		if (NULL != m_hStatement)
		{
			_PrintLog(strFileName, nFileLine, DebugError, strLogInfo, SQL_HANDLE_STMT, m_hStatement);
		}
		return;
	}
	_PrintLogInfo(strFileName, nFileLine, DebugTrace, strLogInfo);
}


void CTestWorkerTable::_PrintLogInfo(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo)
{
	_BaseLog(strFileName, nFileLine, level, "m_hEnviroment=0x%0lx m_hDatabaseConnection=0x%0lx m_hStatement=0x%0lx %s", 
		m_hEnviroment, m_hDatabaseConnection, m_hStatement, strLogInfo.c_str());
}

//SQLSMALLINT HandleType    句柄类型标识，它描述期望诊断的句柄的类型。可以是 SQL_HANDLE_STMT 或 SQL_HANDLE_DBC
void CTestWorkerTable::_PrintLog(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo,
							SQLSMALLINT HandleType, SQLHANDLE Handle)
{
	SQLCHAR* pSQLState = NULL;
	SQLCHAR* pMessage = NULL;
	SQLSMALLINT nBufferLenSQLState = 6;//2 + 3 + '/0'
	SQLSMALLINT nBufferLenMessage = SQL_MAX_MESSAGE_LENGTH;
	SQLRETURN nODBCFunRes = SQL_SUCCESS;
	SQLSMALLINT RecNumber = 1;//SQLSMALLINT	RecNumber	输入	指示应用程序从中查找信息的状态记录。状态记录必须是 1。
	SQLINTEGER	NativeError = 0;//SQLINTEGER	NativeErrorPtr	输出	指向一个缓冲区的指针，特定于数据源的本机错误码将在此缓冲区中返回。
	SQLSMALLINT nGetTextLength = 0;
	std::string strHandleType;


	if (SQL_HANDLE_STMT != HandleType && SQL_HANDLE_DBC != HandleType)
	{
		return;
	}

	if (NULL == Handle)
	{
		return;
	}

	pSQLState = new SQLCHAR[nBufferLenSQLState];
	if (NULL == pSQLState)
	{
		return;
	}
	pMessage = new SQLCHAR[nBufferLenMessage];
	if (NULL == pMessage)
	{
		delete pSQLState;
		pSQLState = NULL;
		return;
	}

	memset(pSQLState, 0, nBufferLenSQLState);
	memset(pMessage, 0, nBufferLenMessage);


	nODBCFunRes = SQLGetDiagRec(HandleType, Handle, RecNumber, pSQLState, &NativeError, pMessage, nBufferLenMessage, &nGetTextLength);


	if (nGetTextLength >= nBufferLenMessage - 1)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, "get message 512 length is not enough!");
	}
	strHandleType = _GetHandleTypeStringValue(HandleType);

	_BaseLog(strFileName, nFileLine, level, 
		"HandleType=%s Handle=0x%0lx  pSQLState=%s NativeError=%d pMessage=%s nBufferLenMessage=%d nGetTextLength=%d Fun_SQLGetDiagRec_Res=%d",
		strHandleType.c_str(), Handle, pSQLState, NativeError, pMessage, nBufferLenMessage, nGetTextLength, nODBCFunRes);



	if (NULL != pMessage)
	{
		delete pMessage;
		pMessage = NULL;
		return;
	}

	if (NULL != pSQLState)
	{
		delete pSQLState;
		pSQLState = NULL;
		return;
	}

}//_ReportError





//SQLSMALLINT HandleType    句柄类型标识，它描述期望诊断的句柄的类型。可以是 SQL_HANDLE_STMT 或 SQL_HANDLE_DBC
void CTestWorkerTable::_PrintLogEx(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo, 
							  SQLHENV EnvironmentHandle, SQLHDBC ConnectionHandle, SQLHSTMT StatementHandle)
{
	SQLCHAR* pSQLState = NULL;
	SQLCHAR* pMessage = NULL;
	SQLSMALLINT nBufferLenSQLState = 6;//2 + 3 + '/0'
	SQLSMALLINT nBufferLenMessage = SQL_MAX_MESSAGE_LENGTH;
	SQLRETURN nODBCFunRes = SQL_SUCCESS;
	SQLINTEGER	NativeError = 0;//SQLINTEGER	NativeErrorPtr	输出	指向一个缓冲区的指针，特定于数据源的本机错误码将在此缓冲区中返回。
	SQLSMALLINT nGetTextLength = 0;
	std::string strHandleType;

	if (NULL == EnvironmentHandle && NULL == ConnectionHandle && NULL == StatementHandle)
	{
		return;
	}

	pSQLState = new SQLCHAR[nBufferLenSQLState];
	if (NULL == pSQLState)
	{
		return;
	}
	pMessage = new SQLCHAR[nBufferLenMessage];
	if (NULL == pMessage)
	{
		delete pSQLState;
		pSQLState = NULL;
		return;
	}

	memset(pSQLState, 0, nBufferLenSQLState);
	memset(pMessage, 0, nBufferLenMessage);

	nODBCFunRes = SQLError(EnvironmentHandle, ConnectionHandle, StatementHandle,
		pSQLState, &NativeError, pMessage, nBufferLenMessage, &nGetTextLength);

	if (nGetTextLength >= nBufferLenMessage - 1)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, "get message 512 length is not enough!");
	}

	_BaseLog(strFileName, nFileLine, level, 
		"EnvironmentHandle=0x%0lx, ConnectionHandle=0x%0lx, StatementHandle=0x%0lx,  pSQLState=%s NativeError=%d pMessage=%s nBufferLenMessage=%d nGetTextLength=%d  Fun_SQLError_Res=%d",
		EnvironmentHandle, ConnectionHandle, StatementHandle, pSQLState, NativeError, pMessage, nBufferLenMessage, nGetTextLength, nODBCFunRes);


	if (NULL != pMessage)
	{
		delete pMessage;
		pMessage = NULL;
		return;
	}

	if (NULL != pSQLState)
	{
		delete pSQLState;
		pSQLState = NULL;
		return;
	}

}//_ReportError



