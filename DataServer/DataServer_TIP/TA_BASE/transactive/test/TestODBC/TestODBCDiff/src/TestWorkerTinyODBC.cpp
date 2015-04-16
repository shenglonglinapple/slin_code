#include "TestWorkerTinyODBC.h"

#include "tiodbc.h"

#include "ProjectCommonData.h"
#include "BaseLogger.h"
#include "BuildSQLHelper.h"



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
	m_pConnection = NULL;
	m_pBuildSQLHelper = NULL;
	m_pBuildSQLHelper = new CBuildSQLHelper();
	m_pBuildSQLHelper->setDBType(m_nDBType);

}

CTestWorkerTinyODBC::~CTestWorkerTinyODBC( void )
{
	if (NULL != m_pConnection)
	{
		delete m_pConnection;
		m_pConnection = NULL;
	}

	if (NULL != m_pBuildSQLHelper)
	{
		delete m_pBuildSQLHelper;
		m_pBuildSQLHelper = NULL;
	}
}


void CTestWorkerTinyODBC::SetDBType( enDBType nDBType )
{
	m_nDBType = nDBType;
	m_pBuildSQLHelper->setDBType(m_nDBType);

}


int CTestWorkerTinyODBC::do_disconnect_to_db()
{
	int nFunRes = 0;

	if (NULL != m_pConnection)
	{
		m_pConnection->disconnect();
		delete m_pConnection;
		m_pConnection = NULL;
	}

	return nFunRes;
}

int CTestWorkerTinyODBC::do_connect_to_db()
{
	int nFunRes = 0;
	bool bFunRes = false;

	if (NULL != m_pConnection)
	{
		m_pConnection->disconnect();
		delete m_pConnection;
		m_pConnection = NULL;
	}

	if (NULL == m_pConnection)
	{
		m_pConnection = new tiodbc::connection();
		bFunRes = m_pConnection->connect(m_pBuildSQLHelper->m_strDNS, m_pBuildSQLHelper->m_strUSR, m_pBuildSQLHelper->m_strPWD);
	}

	if (false == bFunRes)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"Cannot connect to the Data Source, m_strDNS=%s, m_strUSR=%s,m_strPWD=%s, error:%s", 
			m_pBuildSQLHelper->m_strDNS.c_str(), m_pBuildSQLHelper->m_strUSR.c_str(), m_pBuildSQLHelper->m_strPWD.c_str(),
			m_pConnection->last_error().c_str());

		nFunRes = -1;
	}

	return nFunRes;
}



int CTestWorkerTinyODBC::do_delete_table()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	tiodbc::statement my_statement;

	// Execute a direct query
	strSQL = m_pBuildSQLHelper->build_SQL_DeleteTable();

	bFunRes = my_statement.execute_direct(*m_pConnection, strSQL.c_str());
	if (false == bFunRes)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"Cannot execute strSQL=%s, error:%s", 
			strSQL.c_str(),
			m_pConnection->last_error().c_str());

		nFunRes = -1;
	}

	return nFunRes;
}

int CTestWorkerTinyODBC::do_create_table()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	tiodbc::statement my_statement;

	// Execute a direct query
	strSQL = m_pBuildSQLHelper->build_SQL_CreateTable();

	bFunRes = my_statement.execute_direct(*m_pConnection, strSQL.c_str());
	if (false == bFunRes)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"Cannot execute strSQL=%s, error:%s", 
			strSQL.c_str(),
			m_pConnection->last_error().c_str());

		nFunRes = -1;
	}

	return nFunRes;
}

int CTestWorkerTinyODBC::do_insert_data(int nCount)
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	tiodbc::statement my_statement;
	int nParam_LineID_Value = 1000;
	int nIndex = 0;

	for (nIndex = 0; nIndex < nCount; nIndex++)
	{

		// Execute a direct query
		nParam_LineID_Value = nIndex;
		strSQL = m_pBuildSQLHelper->build_SQL_InsertData(nParam_LineID_Value);

		bFunRes = my_statement.execute_direct(*m_pConnection, strSQL.c_str());
		if (false == bFunRes)
		{
			_BaseLog(BaseLogSourceFLInfo, DebugError, 
				"Cannot execute strSQL=%s, error:%s", 
				strSQL.c_str(),
				m_pConnection->last_error().c_str());

			nFunRes = -1;
		}
		else
		{
			_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_insert_data  nIndex=%d", nIndex);
		}

	}//for
	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_insert_data  Total=%d", nCount);


	return nFunRes;
}

int CTestWorkerTinyODBC::do_select_data()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	tiodbc::statement my_statement;
	int nRowIndex = 0;

	// Execute a direct query
	strSQL = m_pBuildSQLHelper->build_SQL_SelectDataFromTable();

	bFunRes = my_statement.execute_direct(*m_pConnection, strSQL.c_str());
	if (false == bFunRes)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"Cannot execute strSQL=%s, error:%s", 
			strSQL.c_str(),
			m_pConnection->last_error().c_str());

		nFunRes = -1;
		return nFunRes;
	}

	// Get results from statement
	nRowIndex = 0;
	while(my_statement.fetch_next())
	{
		_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_select_data  nRowIndex=%d", nRowIndex);

		// print all fields for each row
		for(int nColumnIndex = 1; nColumnIndex <= my_statement.count_columns(); nColumnIndex++)
		{
			_BaseLog(BaseLogSourceFLInfo, DebugTrace, 
				"nRowIndex=%d get Data nColumnIndex=%d, strColumnValue=%s", 
				nRowIndex, nColumnIndex,
				my_statement.field(nColumnIndex).as_string().c_str());			
		}

		nRowIndex++;
	}
	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_select_data  Total=%d", nRowIndex);


	return nFunRes;
}






