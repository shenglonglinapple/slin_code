#include "TestWorker.h"

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



CTestWorker::CTestWorker( void )
{
	m_hEnviroment = NULL;// = NULL;
	m_hDatabaseConnection = NULL;// = NULL;
	m_hStatement = NULL;// = NULL;
}

CTestWorker::~CTestWorker( void )
{


	m_hEnviroment = NULL;// = NULL;
	m_hDatabaseConnection = NULL;// = NULL;
	m_hStatement = NULL;// = NULL;
}



void CTestWorker::run()
{
	m_nThreadJobState = JobState_Begin;


	_ThreadJob();


	m_nThreadJobState = JobState_End;
}

void CTestWorker::_ThreadJob()
{
	//_TestFun_ODBC_API_return_info();

	_TestFun_ODBC_API_Sample();
}




int CTestWorker::_TestFun_ODBC_API_Sample()
{
	int nFunRes = 0;
	SQLRETURN retcode = 0;
	SQLSMALLINT nColumnCount = 0;



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




	//下面代码会在数据库重连后产生错误，删除。
	/* values for SQL_ATTR_CONNECTION_DEAD */
	//#define SQL_CD_TRUE                 1L      /* Connection is closed/dead */
	//#define SQL_CD_FALSE                0L      /* Connection is open/available */
	SQLINTEGER lGetConAttrRet = SQL_CD_TRUE;
	SQLINTEGER lGetConAttrRetSize = 0;


	//判断连接是否活着，不过断开时一定要等到对数据库有SQL请求后才有可以。
	retcode = SQLGetConnectAttr(m_hDatabaseConnection, SQL_ATTR_CONNECTION_DEAD, (SQLPOINTER)&lGetConAttrRet, SQL_IS_INTEGER, &lGetConAttrRetSize);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLGetConnectAttr(SQL_ATTR_CONNECTION_DEAD)", retcode);
	if (lGetConAttrRet == SQL_CD_FALSE)
	{
		//连接仍然是活动的
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

	/*
	error:
	HandleType=SQL_HANDLE_STMT Handle=0x612008  pSQLState=42S02 NativeError=942 pMessage=[Oracle][ODBC][Ora]ORA-00942: table or view does not exist
	*/
	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
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

			if (SQL_DOUBLE == DataType)
			{
				SQLINTEGER l_siID = 0;
				SQLINTEGER l_siIDLength = 0;
				retcode = SQLGetData(m_hStatement, nIndex, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
				_BaseLog(BaseLogSourceFLInfo, DebugTrace, "get row nIndex=%d l_siID=%d l_siIDLength=%d", nIndex, l_siID, l_siIDLength);

			}
			else
			{
				char pszTest[256];
				SQLINTEGER nOutLen = 0;
				memset((char*)pszTest, 0, sizeof(pszTest));
				retcode = SQLGetData(m_hStatement, nIndex, SQL_C_DEFAULT, pszTest, sizeof(pszTest), &nOutLen);
				_PrintLogCheck(BaseLogSourceFLInfo, "SQLGetData(SQL_C_DEFAULT)", retcode);
				_BaseLog(BaseLogSourceFLInfo, DebugTrace, "get row nIndex=%d pszTest=%s nOutLen=%d", nIndex, pszTest, nOutLen);

			}

		}


	}//while (true)


	//set AUTOCOMMIT OFF
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

	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	m_hStatement = NULL;
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_STMT)", retcode);

	retcode = SQLDisconnect(m_hDatabaseConnection);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLDisconnect()", retcode);

	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	m_hDatabaseConnection = NULL;
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_DBC)", retcode);

	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
	m_hEnviroment = NULL;
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_ENV)", retcode);

	m_hEnviroment = NULL;// = NULL;
	m_hDatabaseConnection = NULL;// = NULL;
	m_hStatement = NULL;// = NULL;

	return nFunRes;
}







int CTestWorker::_TestFun_ODBC_API_Sample_Table()
{
	int nFunRes = 0;
	SQLRETURN retcode = 0;
	SQLSMALLINT nColumnCount = 0;



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




	//下面代码会在数据库重连后产生错误，删除。
	/* values for SQL_ATTR_CONNECTION_DEAD */
	//#define SQL_CD_TRUE                 1L      /* Connection is closed/dead */
	//#define SQL_CD_FALSE                0L      /* Connection is open/available */
	SQLINTEGER lGetConAttrRet = SQL_CD_TRUE;
	SQLINTEGER lGetConAttrRetSize = 0;


	//判断连接是否活着，不过断开时一定要等到对数据库有SQL请求后才有可以。
	retcode = SQLGetConnectAttr(m_hDatabaseConnection, SQL_ATTR_CONNECTION_DEAD, (SQLPOINTER)&lGetConAttrRet, SQL_IS_INTEGER, &lGetConAttrRetSize);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLGetConnectAttr(SQL_ATTR_CONNECTION_DEAD)", retcode);
	if (lGetConAttrRet == SQL_CD_FALSE)
	{
		//连接仍然是活动的
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

	/*
	error:
	HandleType=SQL_HANDLE_STMT Handle=0x612008  pSQLState=42S02 NativeError=942 pMessage=[Oracle][ODBC][Ora]ORA-00942: table or view does not exist
	*/
	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
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

			if (SQL_DOUBLE == DataType)
			{
				SQLINTEGER l_siID = 0;
				SQLINTEGER l_siIDLength = 0;
				retcode = SQLGetData(m_hStatement, nIndex, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
				_BaseLog(BaseLogSourceFLInfo, DebugTrace, "get row nIndex=%d l_siID=%d l_siIDLength=%d", nIndex, l_siID, l_siIDLength);

			}
			else
			{
				char pszTest[256];
				SQLINTEGER nOutLen = 0;
				memset((char*)pszTest, 0, sizeof(pszTest));
				retcode = SQLGetData(m_hStatement, nIndex, SQL_C_DEFAULT, pszTest, sizeof(pszTest), &nOutLen);
				_PrintLogCheck(BaseLogSourceFLInfo, "SQLGetData(SQL_C_DEFAULT)", retcode);
				_BaseLog(BaseLogSourceFLInfo, DebugTrace, "get row nIndex=%d pszTest=%s nOutLen=%d", nIndex, pszTest, nOutLen);

			}

		}


	}//while (true)


	//set AUTOCOMMIT OFF
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

	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	m_hStatement = NULL;
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_STMT)", retcode);

	retcode = SQLDisconnect(m_hDatabaseConnection);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLDisconnect()", retcode);

	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	m_hDatabaseConnection = NULL;
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_DBC)", retcode);

	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
	m_hEnviroment = NULL;
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_ENV)", retcode);

	m_hEnviroment = NULL;// = NULL;
	m_hDatabaseConnection = NULL;// = NULL;
	m_hStatement = NULL;// = NULL;

	return nFunRes;
}


int CTestWorker::_TestFun_ODBC_API_return_info()
{
	int nFunRes = 0;
	SQLRETURN retcode = 0;
	SQLINTEGER l_siIdCount = 0;
	unsigned int nLoginTimeOut = 5;//s
	unsigned int nConnectTimeOut = 5;//s
	unsigned int nQueryTimeOut = 5;//s



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

// 	retcode = SQLSetConnectAttr(m_hDatabaseConnection, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)&nLoginTimeOut, SQL_IS_INTEGER);
// 	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetConnectAttr(SQL_ATTR_LOGIN_TIMEOUT)", retcode);
// 
// 	retcode = SQLSetConnectAttr(m_hDatabaseConnection, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)&nConnectTimeOut, SQL_IS_INTEGER);
// 	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetConnectAttr(SQL_ATTR_CONNECTION_TIMEOUT)", retcode);




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




	//下面代码会在数据库重连后产生错误，删除。
	/* values for SQL_ATTR_CONNECTION_DEAD */
	//#define SQL_CD_TRUE                 1L      /* Connection is closed/dead */
	//#define SQL_CD_FALSE                0L      /* Connection is open/available */
	SQLINTEGER lGetConAttrRet = SQL_CD_TRUE;
	SQLINTEGER lGetConAttrRetSize = 0;


	//判断连接是否活着，不过断开时一定要等到对数据库有SQL请求后才有可以。
	retcode = SQLGetConnectAttr(m_hDatabaseConnection, SQL_ATTR_CONNECTION_DEAD, (SQLPOINTER)&lGetConAttrRet, SQL_IS_INTEGER, &lGetConAttrRetSize);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLGetConnectAttr(SQL_ATTR_CONNECTION_DEAD)", retcode);
	if (lGetConAttrRet == SQL_CD_FALSE)
	{
		//连接仍然是活动的
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

	//指定要使用的游标并发级别
	retcode = SQLSetStmtAttr(m_hStatement, SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_ROWVER, 0);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetStmtAttr(SQL_ATTR_CONCURRENCY, SQL_CONCUR_ROWVER)", retcode);

	//设置光标类型为键集光标,
	//键集光标能够检测到行的删除和修改，但是无法检测到检测到行的添加和结果集顺序变化。
	//因为在光标创建时就创建了整个结果集，结果集合中记录和顺序已经被固定，
	//这一点和静态光标一样。所以键集光标可以说是一种介于静态光标和动态光标之间的光标类型。
	retcode = SQLSetStmtAttr(m_hStatement, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_DYNAMIC , 0);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetStmtAttr(SQL_ATTR_CURSOR_TYPE, SQL_CURSOR_DYNAMIC)", retcode);

	retcode = SQLSetStmtAttr(m_hStatement, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)nQueryTimeOut, SQL_IS_UINTEGER);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLSetStmtAttr(SQL_ATTR_QUERY_TIMEOUT, nQueryTimeOut)", retcode);


	/*
	error:
	HandleType=SQL_HANDLE_STMT Handle=0x612008  pSQLState=42S02 NativeError=942 pMessage=[Oracle][ODBC][Ora]ORA-00942: table or view does not exist
	*/
	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
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

	SQLSMALLINT nColumnCount = 0;

	//执行查询语句完毕，开始取数据
	//FetchFirst
	retcode = SQLFetchScroll(m_hStatement, SQL_FETCH_FIRST, 0);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFetchScroll(SQL_FETCH_FIRST,0)", retcode);

	retcode = SQLNumResultCols(m_hStatement, &nColumnCount);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLNumResultCols(nColumnCount)", retcode);

	do 
	{

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
			// #define SQL_NUMERIC         2
			// #define SQL_DECIMAL         3
			// #define SQL_INTEGER         4
			// #define SQL_SMALLINT        5
			// #define SQL_FLOAT           6
			// #define SQL_REAL            7
			// #define SQL_DOUBLE          8
			// #if (ODBCVER >= 0x0300)
			// #define SQL_DATETIME        9
			// #endif
			// #define SQL_VARCHAR        12


			memset(pszName, 0, 256);
			retcode = SQLDescribeCol(m_hStatement, nIndex, (SQLTCHAR*)pszName, BufferLength, &NameLength, &DataType, &ColumnSize, &DecimalDigits, &Nullable);
			_PrintLogCheck(BaseLogSourceFLInfo, "SQLDescribeCol(pszName)", retcode);

			if (SQL_DOUBLE == DataType)
			{
				SQLINTEGER l_siID = 0;
				SQLINTEGER l_siIDLength = 0;
				retcode = SQLGetData(m_hStatement, nIndex, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
				_BaseLog(BaseLogSourceFLInfo, DebugTrace, "get row nIndex=%d l_siID=%d l_siIDLength=%d", nIndex, l_siID, l_siIDLength);

			}
			else
			{
				char pszTest[256];
				SQLINTEGER nOutLen = 0;
				memset((char*)pszTest, 0, sizeof(pszTest));
				retcode = SQLGetData(m_hStatement, nIndex, SQL_C_DEFAULT, pszTest, sizeof(pszTest), &nOutLen);
				_PrintLogCheck(BaseLogSourceFLInfo, "SQLGetData(SQL_C_DEFAULT)", retcode);
				_BaseLog(BaseLogSourceFLInfo, DebugTrace, "get row nIndex=%d pszTest=%s nOutLen=%d", nIndex, pszTest, nOutLen);

			}

		}
		//下一个记录
		retcode = SQLFetch(m_hStatement);
		_PrintLogCheck(BaseLogSourceFLInfo, "SQLFetch(m_hStatement)", retcode);

	} while (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode);




#if 0
	/* get return data Row count insert update delete*/
	retcode = SQLRowCount(m_hStatement, &l_siIdCount);
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

	SQLINTEGER l_siID = 0;
	SQLINTEGER l_siIDLength = 0;

	while (true)
	{
		l_siID = 0;
		l_siIDLength = 0;

		//fecth data use SQLFetch() return SQL_SUCCESS  then no data
		retcode = SQLFetch(m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}


		retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}

		_BaseLog(BaseLogSourceFLInfo, DebugTrace, "get row l_siID=%d l_siIDLength=%d", l_siID, l_siIDLength);
	}//while (true)
#endif

	//set AUTOCOMMIT OFF
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

	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	m_hStatement = NULL;
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_STMT)", retcode);

	retcode = SQLDisconnect(m_hDatabaseConnection);
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLDisconnect()", retcode);

	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	m_hDatabaseConnection = NULL;
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_DBC)", retcode);

	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
	m_hEnviroment = NULL;
	_PrintLogCheck(BaseLogSourceFLInfo, "SQLFreeHandle(SQL_HANDLE_ENV)", retcode);

	m_hEnviroment = NULL;// = NULL;
	m_hDatabaseConnection = NULL;// = NULL;
	m_hStatement = NULL;// = NULL;

	return nFunRes;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

std::string CTestWorker::_GetHandleTypeStringValue(SQLSMALLINT nHandleType)
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

void CTestWorker::_PrintLogCheck(const std::string& strFileName, int nFileLine, const std::string& strLogInfo, SQLRETURN nSQLReturn)
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


void CTestWorker::_PrintLogInfo(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo)
{
	_BaseLog(strFileName, nFileLine, level, "m_hEnviroment=0x%0lx m_hDatabaseConnection=0x%0lx m_hStatement=0x%0lx %s", 
		m_hEnviroment, m_hDatabaseConnection, m_hStatement, strLogInfo.c_str());
}

//SQLSMALLINT HandleType    句柄类型标识，它描述期望诊断的句柄的类型。可以是 SQL_HANDLE_STMT 或 SQL_HANDLE_DBC
void CTestWorker::_PrintLog(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo,
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
void CTestWorker::_PrintLogEx(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo, 
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



