#include "TestWorkerLibODBC.h"


#include "ProjectCommonData.h"
#include "BaseLogger.h"
#include "BuildSQLHelper.h"

#include "odbc++/drivermanager.h"
#include "odbc++/connection.h"
#include "odbc++/resultset.h"
#include "odbc++/resultsetmetadata.h"
#include "odbc++/callablestatement.h"
#include "odbc++/databasemetadata.h"


#include <sstream>
#include <iostream>
#include <memory>



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





CTestWorkerLibODBC::CTestWorkerLibODBC( void )
{
	m_nDBType = DB_ORACLE;
	m_pConnection = NULL;
	m_pBuildSQLHelper = NULL;
	m_pBuildSQLHelper = new CBuildSQLHelper();
	m_pBuildSQLHelper->setDBType(m_nDBType);

}

CTestWorkerLibODBC::~CTestWorkerLibODBC( void )
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
	odbc::DriverManager::shutdown();
}

void CTestWorkerLibODBC::dumpWarnings(odbc::Statement* stmt)
{
	std::auto_ptr<odbc::WarningList> warnings	= std::auto_ptr<odbc::WarningList>(stmt->getWarnings());

	for (odbc::WarningList::iterator iterLst=warnings->begin(); iterLst != warnings->end(); iterLst++) 
	{
		_BaseLog(BaseLogSourceFLInfo, DebugWarn, "Warning:", (*iterLst)->getMessage().c_str());
	}
}

void CTestWorkerLibODBC::SetDBType( enDBType nDBType )
{
	m_nDBType = nDBType;
	m_pBuildSQLHelper->setDBType(m_nDBType);

}


int CTestWorkerLibODBC::do_disconnect_to_db()
{
	int nFunRes = 0;

	if (NULL != m_pConnection)
	{
		delete m_pConnection;
		m_pConnection = NULL;
	}

	return nFunRes;
}

int CTestWorkerLibODBC::do_connect_to_db()
{
	int nFunRes = 0;
	bool bFunRes = false;

	if (NULL != m_pConnection)
	{
		delete m_pConnection;
		m_pConnection = NULL;
	}



	try
	{
		if (NULL == m_pConnection)
		{
			m_pConnection = odbc::DriverManager::getConnection(m_pBuildSQLHelper->m_strDNS, m_pBuildSQLHelper->m_strUSR, m_pBuildSQLHelper->m_strPWD);
			m_pConnection->setAutoCommit(false);
		}
	} 
	catch(odbc::SQLException& e) 
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"Cannot connect to the Data Source, m_strDNS=%s, m_strUSR=%s,m_strPWD=%s, error:%s", 
			m_pBuildSQLHelper->m_strDNS.c_str(), m_pBuildSQLHelper->m_strUSR.c_str(), m_pBuildSQLHelper->m_strPWD.c_str(),
			e.getMessage().c_str());

		nFunRes = -1;
	}
	
	return nFunRes;
}



int CTestWorkerLibODBC::do_delete_table()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	std::auto_ptr<odbc::Statement> stmt=std::auto_ptr<odbc::Statement>(m_pConnection->createStatement());


	// Execute a direct query
	strSQL = m_pBuildSQLHelper->build_SQL_DeleteTable();
	try 
	{
		m_pConnection->setAutoCommit(false);
		stmt->executeUpdate(strSQL.c_str());
		dumpWarnings(stmt.get());
		m_pConnection->commit();
	} 
	catch(odbc::SQLException& e) 
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"Cannot execute strSQL=%s, error:%s", 
			strSQL.c_str(),
			e.getMessage().c_str());
		nFunRes = -1;
		m_pConnection->rollback();
	}


	return nFunRes;
}

int CTestWorkerLibODBC::do_create_table()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	std::auto_ptr<odbc::Statement> stmt=std::auto_ptr<odbc::Statement>(m_pConnection->createStatement());


	// Execute a direct query
	strSQL = m_pBuildSQLHelper->build_SQL_CreateTable();
	try 
	{
		m_pConnection->setAutoCommit(false);
		stmt->executeUpdate(strSQL.c_str());
		dumpWarnings(stmt.get());
		m_pConnection->commit();
	} 
	catch(odbc::SQLException& e) 
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"Cannot execute strSQL=%s, error:%s", 
			strSQL.c_str(),
			e.getMessage().c_str());
		nFunRes = -1;
		m_pConnection->rollback();
	}


	return nFunRes;
}

int CTestWorkerLibODBC::do_insert_data(int nCount)
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	int nParam_LineID_Value = 1000;
	int nIndex = 0;

	for (nIndex = 0; nIndex < nCount; nIndex++)
	{

		// Execute a direct query
		nParam_LineID_Value = nIndex;
		strSQL = m_pBuildSQLHelper->build_SQL_InsertData(nParam_LineID_Value);

		try 
		{
			m_pConnection->setAutoCommit(false);

			std::auto_ptr<odbc::Statement> stmt=std::auto_ptr<odbc::Statement>(m_pConnection->createStatement());

			stmt->executeUpdate(strSQL.c_str());
			dumpWarnings(stmt.get());
			m_pConnection->commit();

		} 
		catch(odbc::SQLException& e) 
		{
			_BaseLog(BaseLogSourceFLInfo, DebugError, 
				"Cannot execute strSQL=%s, error:%s", 
				strSQL.c_str(),
				e.getMessage().c_str());
			nFunRes = -1;
			m_pConnection->rollback();
		}


		{
			_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_insert_data  nIndex=%d", nIndex);
		}

	}//for
	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_insert_data  Total=%d", nCount);


	return nFunRes;
}

int CTestWorkerLibODBC::do_select_data()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	int nRowIndex = 0;
	// populate our table using a ResultSet
// 	std::auto_ptr<odbc::Statement> stmt=std::auto_ptr<odbc::Statement>(
// 		m_pConnection->createStatement(odbc::ResultSet::TYPE_SCROLL_SENSITIVE, 
// 		odbc::ResultSet::CONCUR_UPDATABLE));


	std::auto_ptr<odbc::Statement> stmt=std::auto_ptr<odbc::Statement>(
		m_pConnection->createStatement(odbc::ResultSet::TYPE_FORWARD_ONLY, 
		odbc::ResultSet::CONCUR_READ_ONLY));

	// set fetch size to something useful
	stmt->setFetchSize(100);

	//
	//SQLSetStmtAttr(hstmt_,SQL_ATTR_ROW_ARRAY_SIZE,(SQLPOINTER)100,SQL_IS_UINTEGER);
	//(SQL_ATTR_ROW_ARRAY_SIZE,SQL_ROWSET_SIZE),		currentFetchSize_);

	// Execute a direct query
	strSQL = m_pBuildSQLHelper->build_SQL_SelectDataFromTable();

	try
	{
		m_pConnection->setAutoCommit(false);
		std::auto_ptr<odbc::ResultSet> rs = std::auto_ptr<odbc::ResultSet>(stmt->executeQuery(strSQL.c_str()));
		m_pConnection->commit();

		odbc::ResultSetMetaData* pResultSetMetaData = rs->getMetaData();
		int nGetMaxRows = 0;
		int nGetMaxFieldSize = 0;
		int nGetColumnCount = 0;
		nGetMaxRows = stmt->getMaxRows();
		nGetMaxFieldSize = stmt->getMaxFieldSize();
		nGetColumnCount = pResultSetMetaData->getColumnCount();
		_BaseLog(BaseLogSourceFLInfo, DebugInfo, "nGetMaxRows=%d nGetMaxFieldSize=%d nGetColumnCount=%d", nGetMaxRows, nGetMaxFieldSize, nGetColumnCount);

		nRowIndex = 0;
		while (rs->next()) 
		{
			_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_select_data  nRowIndex=%d", nRowIndex);
			// print all fields for each row
			for(int nColumnIndex = 1; nColumnIndex <= nGetColumnCount; nColumnIndex++)
			{
				std::string strColumnName = pResultSetMetaData->getColumnName(nColumnIndex);
				std::string strColumnValue = rs->getString(nColumnIndex);

				_BaseLog(BaseLogSourceFLInfo, DebugTrace, 
					"nRowIndex=%d get Data nColumnIndex=%d, strColumnName=%s, strColumnValue=%s", 
					nRowIndex, nColumnIndex,
					strColumnName.c_str(),
					strColumnValue.c_str());			
			}

			nRowIndex++;


		}//while


	}
	catch (...)
	{
		m_pConnection->rollback();

	}
	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_select_data  Total=%d", nRowIndex);



	return nFunRes;
}






