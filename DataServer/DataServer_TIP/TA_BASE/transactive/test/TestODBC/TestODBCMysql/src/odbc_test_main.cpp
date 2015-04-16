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




int test_fun_odbc_api_Oracle__getdata();
int test_fun_odbc_api_Oracle__dynDNS();
int test_fun_odbc_api_Oracle__dynDNS_Error();
int test_fun_odbc_api_Oracle__DBPOOL_DYN();
int test_fun_odbc_api_Oracle__DBPOOL();

//
//////////////////////////////////////////////////////////////////////////
int test_fun_odbc_api_Mysql__getdata();
int test_fun_odbc_api_Mysql__dynDNS();
int test_fun_odbc_api_Mysql__dynDNS_Error();
int test_fun_odbc_api_Mysql__DBPOOL_DYN();
int test_fun_odbc_api_Mysql__DBPOOL();


//////////////////////////////////////////////////////////////////////////


int test_fun_odbc_api_Oracle_exec_return_info();



//////////////////////////////////////////////////////////////////////////



int main()
{
	int nFunRes = 0;

	test_fun_odbc_api_Oracle_exec_return_info();

	return nFunRes;
}







//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


int test_fun_odbc_api_Oracle__DBPOOL()
{

	SQLHENV   henv;
	SQLHDBC   hdbc;
	int       nIndex=0;
	SQLRETURN retcode;

	try
	{

		/*Enable connection pooling ..  this must be done before any ADO calls  are made.  Only needs to occur one time per process*/
		retcode = SQLSetEnvAttr(0, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER) SQL_CP_ONE_PER_DRIVER, SQL_IS_INTEGER);
		if (!SQL_SUCCEEDED(retcode))  
		{
			printf("SQLSetEnvAttr/SQL_ATTR_CONNECTION_POOLING error\n");
			return retcode;
		}
	}
	catch (std::exception& e)
	{
		int a = 0;
	}
	catch (...)
	{
		int a = 0;
	}


	retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);
	if (!SQL_SUCCEEDED(retcode))  
	{
		printf("SQLAllocHandle error\n");
		return retcode;
	}

	// Set the ODBC behavior version. 
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER) SQL_OV_ODBC2, SQL_IS_INTEGER);
	if (!SQL_SUCCEEDED(retcode))  
	{
		printf("SQLSetEnvAttr/SQL_ATTR_ODBC_VERSION error\n");
		return retcode;
	}

	// Set the matching condition for using an existing 
	// connection in the pool 
	retcode = SQLSetEnvAttr(henv,SQL_ATTR_CP_MATCH,(SQLPOINTER)SQL_CP_RELAXED_MATCH, SQL_IS_INTEGER);
	if (!SQL_SUCCEEDED(retcode))  
	{
		printf("SQLSetEnvAttr/SQL_ATTR_CP_MATCH error\n");
		return retcode;
	}



	while (nIndex < 10) 
	{
		if (!SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC,
			henv, &hdbc)))
			printf("SQLAllocHandle error\n");


		if (!SQL_SUCCEEDED(SQLConnect(hdbc,
			(unsigned char*)"Oracle12343DYN\0", SQL_NTS,
			(unsigned char*)"IT271350_5\0", SQL_NTS,
			(unsigned char*)"IT271350_5\0", SQL_NTS)))
			printf("SQLConnect error\n");
		else
			printf("Connect successfully %d times\n", nIndex);
		//When the ODBC application calls SQLDisconnect the first time, the connection is saved to the pool. 
		//Any subsequent SQLConnect/SQLDisconnect that matches the required condition will reuse the first connection.
		
		
		
		//the first time, the application calls SQLDisconenct, it will return
		//the connection to the //pool
		SQLDisconnect(hdbc);

		if (!SQL_SUCCEEDED(SQLFreeHandle(SQL_HANDLE_DBC, hdbc)))
			printf("SQLFreeHandle error\n");
		nIndex++;
	}
	SQLFreeHandle(SQL_HANDLE_ENV, henv);

	return 0;
}

int test_fun_odbc_api_Oracle__DBPOOL_DYN()
{
	int nFunRes = 0;

	// Drop and re-create a Msorcl10.dll (version 1.0) data source.
	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"Microsoft ODBC for Oracle", "DSN=Oracle12343DYN\0");

	nFunRes = SQLConfigDataSource( NULL,
		ODBC_ADD_DSN,
		"Microsoft ODBC for Oracle",
		"Description=My Description Text\0"
		"Server=TRANSACT\0"
		"DSN=Oracle12343DYN\0"
		"PWD=IT271350_5\0"
		"UID=IT271350_5\0"
		);



	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	////http://support.microsoft.com/kb/164221/en-us

	////http://www.informixchina.net/club/thread-5924-1-1.html

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}
	// set the ODBC behavior version.
	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	if (!SQL_SUCCEEDED(retcode))  
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	// make process level cursor pooling
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_CONNECTION_POOLING,	(SQLPOINTER)SQL_CP_ONE_PER_DRIVER, SQL_IS_UINTEGER);
	if (!SQL_SUCCEEDED(retcode)) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}




	//set the matching condition for using an existing connection in the pool
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_CP_MATCH, (SQLPOINTER)SQL_CP_RELAXED_MATCH, 0);//SQL_IS_INTEGER
	if (!SQL_SUCCEEDED(retcode))  
	{
		printf("SQLSetEnvAttr/SQL_ATTR_CP_MATCH error\n");
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	int nIndex = 0;
	while (nIndex < 10) 
	{
		/* Allocate connection handle */
		retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
		if (!SQL_SUCCEEDED(retcode))  
		{
			printf("SQLAllocHandle error\n");
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}



		/* Set login timeout to 5 seconds. */
		//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

		/* Connect to data source */
		retcode = SQLConnect(m_hDatabaseConnection, 
			(SQLCHAR*) "Oracle12343DYN", SQL_NTS,
			(SQLCHAR*) "IT271350_5", SQL_NTS,
			(SQLCHAR*) "IT271350_5", SQL_NTS);
		if (!SQL_SUCCEEDED(retcode))  
		{
			printf("SQLConnect error\n");
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}
		else
		{
			printf("Connect successfully %d times\n", nIndex);
		}


		//////////////////////////////////////////////////////////////////////////
		
		/* Allocate statement handle */
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
		{
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}

		retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}


		/* get return data Row count */
		SQLINTEGER l_siIdCount = 0;
		retcode = SQLRowCount(m_hStatement, &l_siIdCount);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}

		while (true)
		{
			//fecth data use SQLFetch() return SQL_SUCCESS  then no data
			retcode = SQLFetch(m_hStatement);
			if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
			{
				break;
			}

			SQLINTEGER l_siID;
			SQLINTEGER l_siIDLength = 0;

			retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
			if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
			{
				break;
			}
		}//while (true)


		//the first time, the application calls SQLDisconenct, it will return
		//the connection to the //pool
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);

		//////////////////////////////////////////////////////////////////////////

		nIndex++;
	}//while (nIndex < 10) 
	
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);


	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"Microsoft ODBC for Oracle", "DSN=Oracle12343DYN\0");

	return nFunRes;
}



//error test_fun_odbc_api_Oracle__dynDNS_Error
int test_fun_odbc_api_Oracle__dynDNS_Error()
{
	int nFunRes = 0;

	// Drop and re-create a Msorcl10.dll (version 1.0) data source.
	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"Oracle in OraHome90", "DSN=Oracle12343DYN\0");

	nFunRes = SQLConfigDataSource( NULL,
		ODBC_ADD_DSN,
		"Oracle in OraHome90",
		"Description=My Description Text\0"
		"Server=TRANSACT\0"
		"DSN=Oracle12343DYN\0"
		"PWD=IT271350_5\0"
		"UID=IT271350_5\0"
		);


	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}

	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	/* Allocate connection handle */
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Set login timeout to 5 seconds. */
	//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

	/* Connect to data source */
	retcode = SQLConnect(m_hDatabaseConnection, 
		(SQLCHAR*) "Oracle12343DYN", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Allocate statement handle */
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* get return data Row count */
	SQLINTEGER l_siIdCount = 0;
	retcode = SQLRowCount(m_hStatement, &l_siIdCount);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	while (true)
	{
		//fecth data use SQLFetch() return SQL_SUCCESS  then no data
		retcode = SQLFetch(m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}

		SQLINTEGER l_siID;
		SQLINTEGER l_siIDLength = 0;

		retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}
	}//while (true)


	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	retcode = SQLDisconnect(m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);



	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"Microsoft ODBC for Oracle", "DSN=Oracle12343DYN\0");

	return nFunRes;
}

int test_fun_odbc_api_Oracle__dynDNS()
{
	int nFunRes = 0;

	// Drop and re-create a Msorcl10.dll (version 1.0) data source.
	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"Microsoft ODBC for Oracle", "DSN=Oracle12343DYN\0");

	nFunRes = SQLConfigDataSource( NULL,
		ODBC_ADD_DSN,
		"Microsoft ODBC for Oracle",
		"Description=My Description Text\0"
		"Server=TRANSACT\0"
		"DSN=Oracle12343DYN\0"
		"PWD=IT271350_5\0"
		"UID=IT271350_5\0"
		);


	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}

	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	/* Allocate connection handle */
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Set login timeout to 5 seconds. */
	//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

	/* Connect to data source */
	retcode = SQLConnect(m_hDatabaseConnection, 
		(SQLCHAR*) "Oracle12343DYN", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Allocate statement handle */
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* get return data Row count */
	SQLINTEGER l_siIdCount = 0;
	retcode = SQLRowCount(m_hStatement, &l_siIdCount);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	while (true)
	{
		//fecth data use SQLFetch() return SQL_SUCCESS  then no data
		retcode = SQLFetch(m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}

		SQLINTEGER l_siID;
		SQLINTEGER l_siIDLength = 0;

		retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}
	}//while (true)


	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	retcode = SQLDisconnect(m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);



	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"Microsoft ODBC for Oracle", "DSN=Oracle12343DYN\0");

	return nFunRes;
}



int test_fun_odbc_api_Oracle__getdata()
{
	int nFunRes = 0;

	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}

	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	/* Allocate connection handle */
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Set login timeout to 5 seconds. */
	//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

	/* Connect to data source */
	//Oracle12343DYN
	retcode = SQLConnect(m_hDatabaseConnection, 
		(SQLCHAR*) "Oracle12343DYN", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Allocate statement handle */
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* get return data Row count */
	SQLINTEGER l_siIdCount = 0;
	retcode = SQLRowCount(m_hStatement, &l_siIdCount);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	while (true)
	{
		//fecth data use SQLFetch() return SQL_SUCCESS  then no data
		retcode = SQLFetch(m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}

		SQLINTEGER l_siID;
		SQLINTEGER l_siIDLength = 0;

		retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}
	}//while (true)


	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	retcode = SQLDisconnect(m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);

	return nFunRes;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////












//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



int test_fun_odbc_api_Mysql__DBPOOL()
{
	SQLHENV   henv;
	SQLHDBC   hdbc;
	int       nIndex=0;
	SQLRETURN retcode;

	try
	{

		/*Enable connection pooling ..  this must be done before any ADO calls  are made.  Only needs to occur one time per process*/
		retcode = SQLSetEnvAttr(0, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER) SQL_CP_ONE_PER_DRIVER, SQL_IS_INTEGER);
		if (!SQL_SUCCEEDED(retcode))  
		{
			printf("SQLSetEnvAttr/SQL_ATTR_CONNECTION_POOLING error\n");
			return retcode;
		}
	}
	catch (std::exception& e)
	{
		int a = 0;
	}
	catch (...)
	{
		int a = 0;
	}


	retcode = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);
	if (!SQL_SUCCEEDED(retcode))  
	{
		printf("SQLAllocHandle error\n");
		return retcode;
	}

	// Set the ODBC behavior version. 
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER) SQL_OV_ODBC2, SQL_IS_INTEGER);
	if (!SQL_SUCCEEDED(retcode))  
	{
		printf("SQLSetEnvAttr/SQL_ATTR_ODBC_VERSION error\n");
		return retcode;
	}

	// Set the matching condition for using an existing 
	// connection in the pool 
	retcode = SQLSetEnvAttr(henv,SQL_ATTR_CP_MATCH,(SQLPOINTER)SQL_CP_RELAXED_MATCH, SQL_IS_INTEGER);
	if (!SQL_SUCCEEDED(retcode))  
	{
		printf("SQLSetEnvAttr/SQL_ATTR_CP_MATCH error\n");
		return retcode;
	}



	while (nIndex < 10) 
	{
		if (!SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC,
			henv, &hdbc)))
			printf("SQLAllocHandle error\n");


		if (!SQL_SUCCEEDED(SQLConnect(hdbc,
			(unsigned char*)"Mysql12343\0", SQL_NTS,
			(unsigned char*)"IT271350_5\0", SQL_NTS,
			(unsigned char*)"IT271350_5\0", SQL_NTS)))
			printf("SQLConnect error\n");
		else
			printf("Connect successfully %d times\n", nIndex);
		//When the ODBC application calls SQLDisconnect the first time, the connection is saved to the pool. 
		//Any subsequent SQLConnect/SQLDisconnect that matches the required condition will reuse the first connection.



		//the first time, the application calls SQLDisconenct, it will return
		//the connection to the //pool
		SQLDisconnect(hdbc);

		if (!SQL_SUCCEEDED(SQLFreeHandle(SQL_HANDLE_DBC, hdbc)))
			printf("SQLFreeHandle error\n");
		nIndex++;
	}
	SQLFreeHandle(SQL_HANDLE_ENV, henv);

	return 0;
}

int test_fun_odbc_api_Mysql__DBPOOL_DYN()
{
	int nFunRes = 0;

	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"MySQL ODBC 5.2 Unicode Driver", "DSN=Mysql12343DYN\0");

	// Drop and re-create a Msorcl10.dll (version 1.0) data source.
	SQLConfigDataSource(NULL, ODBC_ADD_DSN, "MySQL ODBC 5.2 Unicode Driver",
		"DSN=Mysql12343DYN;UID=IT271350_5;PWD=IT271350_5;SERVER=192.168.123.43;DATABASE=tra_occ");


	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	////http://support.microsoft.com/kb/164221/en-us

	////http://www.informixchina.net/club/thread-5924-1-1.html

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}
	// set the ODBC behavior version.
	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	if (!SQL_SUCCEEDED(retcode))  
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	// make process level cursor pooling
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_CONNECTION_POOLING,	(SQLPOINTER)SQL_CP_ONE_PER_DRIVER, SQL_IS_UINTEGER);
	if (!SQL_SUCCEEDED(retcode)) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}




	//set the matching condition for using an existing connection in the pool
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_CP_MATCH, (SQLPOINTER)SQL_CP_RELAXED_MATCH, 0);//SQL_IS_INTEGER
	if (!SQL_SUCCEEDED(retcode))  
	{
		printf("SQLSetEnvAttr/SQL_ATTR_CP_MATCH error\n");
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	int nIndex = 0;
	while (nIndex < 10) 
	{
		/* Allocate connection handle */
		retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
		if (!SQL_SUCCEEDED(retcode))  
		{
			printf("SQLAllocHandle error\n");
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}



		/* Set login timeout to 5 seconds. */
		//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

		/* Connect to data source */
		retcode = SQLConnect(m_hDatabaseConnection, 
			(SQLCHAR*) "Mysql12343DYN", SQL_NTS,
			(SQLCHAR*) "IT271350_5", SQL_NTS,
			(SQLCHAR*) "IT271350_5", SQL_NTS);
		if (!SQL_SUCCEEDED(retcode))  
		{
			printf("SQLConnect error\n");
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}
		else
		{
			printf("Connect successfully %d times\n", nIndex);
		}


		//////////////////////////////////////////////////////////////////////////

		/* Allocate statement handle */
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
		{
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}

		retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}


		/* get return data Row count */
		SQLINTEGER l_siIdCount = 0;
		retcode = SQLRowCount(m_hStatement, &l_siIdCount);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
			retcode = SQLDisconnect(m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
			retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
			return nFunRes;
		}

		while (true)
		{
			//fecth data use SQLFetch() return SQL_SUCCESS  then no data
			retcode = SQLFetch(m_hStatement);
			if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
			{
				break;
			}

			SQLINTEGER l_siID;
			SQLINTEGER l_siIDLength = 0;

			retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
			if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
			{
				break;
			}
		}//while (true)


		//the first time, the application calls SQLDisconenct, it will return
		//the connection to the //pool
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);

		//////////////////////////////////////////////////////////////////////////

		nIndex++;
	}//while (nIndex < 10) 

	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);


	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"MySQL ODBC 5.2 Unicode Driver", "DSN=Mysql12343DYN\0");

	return nFunRes;
}



//error test_fun_odbc_api_Oracle__dynDNS_Error
int test_fun_odbc_api_Mysql__dynDNS_Error()
{
	int nFunRes = 0;

	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"MySQL ODBC 5.2 Unicode Driver", "DSN=Mysql12343DYN\0");

	// Drop and re-create a Msorcl10.dll (version 1.0) data source.
	SQLConfigDataSource(NULL, ODBC_ADD_DSN, "MySQL ODBC 5.2 Unicode Driver",
		"DSN=Mysql12343DYN;UID=IT271350_5;PWD=IT271350_5;SERVER=192.168.123.43;DATABASE=tra_occ");


	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}

	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	/* Allocate connection handle */
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Set login timeout to 5 seconds. */
	//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

	/* Connect to data source */
	retcode = SQLConnect(m_hDatabaseConnection, 
		(SQLCHAR*) "Mysql12343DYN", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Allocate statement handle */
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* get return data Row count */
	SQLINTEGER l_siIdCount = 0;
	retcode = SQLRowCount(m_hStatement, &l_siIdCount);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	while (true)
	{
		//fecth data use SQLFetch() return SQL_SUCCESS  then no data
		retcode = SQLFetch(m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}

		SQLINTEGER l_siID;
		SQLINTEGER l_siIDLength = 0;

		retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}
	}//while (true)


	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	retcode = SQLDisconnect(m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);



	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"MySQL ODBC 5.2 Unicode Driver", "DSN=Mysql12343DYN\0");

	return nFunRes;
}

int test_fun_odbc_api_Mysql__dynDNS()
{
	int nFunRes = 0;

	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"MySQL ODBC 5.2 Unicode Driver", "DSN=Mysql12343DYN\0");

	// Drop and re-create a Msorcl10.dll (version 1.0) data source.
	SQLConfigDataSource(NULL, ODBC_ADD_DSN, "MySQL ODBC 5.2 Unicode Driver",
		"DSN=Mysql12343DYN;UID=IT271350_5;PWD=IT271350_5;SERVER=192.168.123.43;DATABASE=tra_occ");



	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}

	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	/* Allocate connection handle */
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Set login timeout to 5 seconds. */
	//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);
	//	nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"MySQL ODBC 5.2 Unicode Driver", "DSN=Mysql12343DYN\0");

	/* Connect to data source */
	retcode = SQLConnect(m_hDatabaseConnection, 
		(SQLCHAR*) "Mysql12343DYN", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Allocate statement handle */
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* get return data Row count */
	SQLINTEGER l_siIdCount = 0;
	retcode = SQLRowCount(m_hStatement, &l_siIdCount);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	while (true)
	{
		//fecth data use SQLFetch() return SQL_SUCCESS  then no data
		retcode = SQLFetch(m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}

		SQLINTEGER l_siID;
		SQLINTEGER l_siIDLength = 0;

		retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}
	}//while (true)


	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	retcode = SQLDisconnect(m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);



nFunRes = SQLConfigDataSource( NULL, ODBC_REMOVE_DSN,	"MySQL ODBC 5.2 Unicode Driver", "DSN=Mysql12343DYN\0");
	return nFunRes;
}



int test_fun_odbc_api_Mysql__getdata()
{
	int nFunRes = 0;

	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}

	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	/* Allocate connection handle */
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Set login timeout to 5 seconds. */
	//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

	/* Connect to data source */
	retcode = SQLConnect(m_hDatabaseConnection, 
		(SQLCHAR*) "Mysql12343", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Allocate statement handle */
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* get return data Row count */
	SQLINTEGER l_siIdCount = 0;
	retcode = SQLRowCount(m_hStatement, &l_siIdCount);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	while (true)
	{
		//fecth data use SQLFetch() return SQL_SUCCESS  then no data
		retcode = SQLFetch(m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}

		SQLINTEGER l_siID;
		SQLINTEGER l_siIDLength = 0;

		retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}
	}//while (true)


	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	retcode = SQLDisconnect(m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);

	return nFunRes;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////






int test_fun_odbc_api_Oracle_exec_return_info()
{
	int nFunRes = 0;

	SQLHENV m_hEnviroment;
	SQLHDBC m_hDatabaseConnection;
	SQLHSTMT m_hStatement;
	SQLRETURN retcode;

	/*Allocate environment handle */
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnviroment);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		return nFunRes;
	}

	/* Set the ODBC version environment attribute */
	retcode = SQLSetEnvAttr(m_hEnviroment, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	/* Allocate connection handle */
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnviroment, &m_hDatabaseConnection);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Set login timeout to 5 seconds. */
	//SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, 5, 0);

	/* Connect to data source */
	//Oracle12343DYN
	retcode = SQLConnect(m_hDatabaseConnection, 
		(SQLCHAR*) "Oracle12343DYN", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS,
		(SQLCHAR*) "IT271350_5", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* Allocate statement handle */
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hDatabaseConnection, &m_hStatement);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) 
	{
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	retcode = SQLExecDirect(m_hStatement,(SQLCHAR*)"select pkey from recipient_info", SQL_NTS);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}


	/* get return data Row count */
	SQLINTEGER l_siIdCount = 0;
	retcode = SQLRowCount(m_hStatement, &l_siIdCount);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		retcode = SQLDisconnect(m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
		retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);
		return nFunRes;
	}

	while (true)
	{
		//fecth data use SQLFetch() return SQL_SUCCESS  then no data
		retcode = SQLFetch(m_hStatement);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}

		SQLINTEGER l_siID;
		SQLINTEGER l_siIDLength = 0;

		retcode = SQLGetData(m_hStatement, 1, SQL_C_ULONG, &l_siID, 0, &l_siIDLength);
		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}
	}//while (true)


	/* Process data */
	retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
	retcode = SQLDisconnect(m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_DBC, m_hDatabaseConnection);
	retcode = SQLFreeHandle(SQL_HANDLE_ENV, m_hEnviroment);

	return nFunRes;
}




































