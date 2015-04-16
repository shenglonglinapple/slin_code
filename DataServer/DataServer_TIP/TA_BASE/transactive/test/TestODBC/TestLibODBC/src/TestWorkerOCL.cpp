#include "TestWorkerOCL.h"

#include <iostream>
#include <sstream>
#include <time.h>
#include <vector>	
#include <list>  
#include <time.h>
#include <sys/timeb.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ProjectCommonData.h"
#include "BaseLogger.h"
#include "BuildSQLHelper.h"



//TestClass
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ocl.h"


//////////////////////////////////////////////////////////////////////////
using namespace ocl;



CTestWorkerOCL::CTestWorkerOCL( void )
{
	m_nDBType = DB_ORACLE;
	m_pConnection = NULL;
	m_pBuildSQLHelper = NULL;
	m_pBuildSQLHelper = new CBuildSQLHelper();
	m_pBuildSQLHelper->setDBType(m_nDBType);

}

CTestWorkerOCL::~CTestWorkerOCL( void )
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


void CTestWorkerOCL::SetDBType( enDBType nDBType )
{
	m_nDBType = nDBType;
	m_pBuildSQLHelper->setDBType(m_nDBType);

}

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CTestWorkerOCL::fillDataBuffer(ocl::OraConnection *pconnection, ocl::OraQuery* pQuery, int numColumns, long lMaxRows )
{
	int nFieldNumber = 0;
	int nRecordCount = 0; 
	int nRecordIndex = 0;
	int nOCILIBRes = 0;

	nFieldNumber = pQuery->fieldCount();
	nRecordCount = pQuery->recordCount();
	
	_BaseLog(BaseLogSourceFLInfo, DebugDebug, "[nRecordCount=%d] [nFieldNumber=%d]", nRecordCount, nFieldNumber);



	// Get results from statement
	try
	{
		//nRecordIndex begin with 1   nFieldIndex begin with 1
		nRecordIndex = 1;
		_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_select_data  nRowIndex=%d", nRecordIndex);

		//while( !pQuery->isEOF() && ( nRecordIndex <= lMaxRows ))
		while( !pQuery->isEOF() )
		{
			//Row dataRow;
			for ( int nColumnIndex = 0; nColumnIndex < numColumns; ++nColumnIndex )
			{
				ocl::CRString strColumnName = pQuery->field(nColumnIndex).name();
				std::string strColumnValue = pQuery->field(nColumnIndex).getString();

				_BaseLog(BaseLogSourceFLInfo, DebugDebug, "[nRecordIndex=%d][nColumnIndex=%d] strColumnName=%s, strColumnValue=%s", 
					nRecordIndex, nColumnIndex+1, strColumnName.c_str(), strColumnValue.c_str());

			}
			pQuery->next();
			++nRecordIndex;
		}//while

	}
	catch( ocl::OraException & e )
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "OCI_ERROR  [errormsg=%s] [errorcode=%d]", e.message().c_str(), e.errorCode());
	}
	catch( ... )
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "fillDataBuffer UNKNOWN ERROR");
	}

	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_select_data  Total=%d", nRecordIndex);

}//CTestClass::fillDataBuffer



void CTestWorkerOCL::fetchInitial(ocl::OraConnection *pconnection, ocl::OraQuery* pQuery, int numColumns, long lMaxRows )
{
	try
	{
		if ( pQuery->isRowsReturn() )
		{
			pQuery->moveTo(1);
			fillDataBuffer(pconnection, pQuery, numColumns, lMaxRows);
		}
	}
	catch( ocl::OraException & e )
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "OCI_ERROR  [errormsg=%s] [errorcode=%d]", e.message().c_str(), e.errorCode());
	}
	catch(...)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "fetchInitial UNKNOWN ERROR");
	}


}//CTestClass::fetchInitial

void CTestWorkerOCL::exec(ocl::OraConnection *pconnection, const std::string& strOracleSQL, bool isQuery)
{
	int prefetch = 100;
	std::string strSql = strOracleSQL;
	OraQuery* query = NULL;

	//LOG_GENERIC(SourceInfo, DebugUtil::DebugSQL, "Begin execute the SQL statement: [[%s]]", strSql.c_str());


	try
	{
		query = new OraQuery(); // Wrap it to OCIQueryAdapter
		query->setConnection(*pconnection);
		if (isQuery) //select *
		{
			query->setCached(false);  // noncached mode
			query->setFetchRows(prefetch);
			query->setSQL(strSql);
			query->prepare(); 
			query->open();   // query result rows
		}
		else //like the insert command
		{
			//LOG ( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, "The SQL modification to execute is: %s", strSql.c_str());
			query->setCommandType(ocl::ctSQL);
			query->setCommandText(strSql);
			pconnection->startTransaction();  //  start the transaction must after seting the command text.
			query->execute(); 
			query->close();
			if (pconnection->inTransaction()) // returns true 
			{
				pconnection->commit();          // ends current transaction 
			}
			else
			{
				//LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugError, "[ocl-error], transaction is broken" );
			}

			delete query;
			query = NULL;
		}
	}
	catch(ocl::OraException & e)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "exec OCI_ERROR  [errormsg=%s] [errorcode=%d]", e.message().c_str(), e.errorCode());
		delete query; 
		query = NULL;  //it will cause cursor leak if don't delete it.
	}
	catch(ocl::CRException &e)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "exec OCI_ERROR  [errormsg=%s] ", e.message().c_str());

		delete query; 
		query = NULL;  //it will cause cursor leak if don't delete it.

	}
	catch(...)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "exec UNKNOWN ERROR");
	}	

	//isQuery == true
	//just save the pointer, here
	if ( NULL != query )
	{
		std::string strColumnName;
		int numColumns = 0;
		int nRecordCount = 0;
		std::list<std::string> lstColumns;

		strColumnName = "LINE_ID";
		lstColumns.push_back(strColumnName);

		strColumnName = "TEST_TYPE";
		lstColumns.push_back(strColumnName);

		strColumnName = "INT_COLUMN";
		lstColumns.push_back(strColumnName);

		strColumnName = "STR_COLUMN";
		lstColumns.push_back(strColumnName);

		strColumnName = "BOOL_COLUMN";
		lstColumns.push_back(strColumnName);

		strColumnName = "REAL_COLUMN";
		lstColumns.push_back(strColumnName);

		strColumnName = "DATE_COLUMN";
		lstColumns.push_back(strColumnName);

		strColumnName = "TIMESTAMP_COLUMN";
		lstColumns.push_back(strColumnName);


		numColumns = (int)lstColumns.size();
		nRecordCount = query->recordCount();

		fetchInitial(pconnection, query, numColumns, nRecordCount);

		query->close();
		query->unprepare();
		delete query;
		query = NULL;

		lstColumns.clear();

	}//if ( NULL != query )

}//CTestClass::exec



//////////////////////////////////////////////////////////////////////////


int CTestWorkerOCL::do_disconnect_to_db()
{
	int nFunRes = 0;

	if (NULL != m_pConnection)
	{
		m_pConnection->close();
		delete m_pConnection;
		m_pConnection = NULL;
	}

	return nFunRes;
}

int CTestWorkerOCL::do_connect_to_db()
{
	int nFunRes = 0;
	bool bFunRes = false;

	if (NULL != m_pConnection)
	{
		m_pConnection->close();
		delete m_pConnection;
		m_pConnection = NULL;
	}

	OraEnvironment::setInitMode(OraEnvironment::imObject);
	OraEnvironment::setInitMode(OraEnvironment::imThreaded);
	OraEnvironment::setThreaded(true);


	if (NULL == m_pConnection)
	{	
		m_pConnection = new ocl::OraConnection();
		m_pConnection->setConnectMode(cmNormal);
		m_pConnection->setUsername(m_pBuildSQLHelper->m_userName); 
		m_pConnection->setPassword(m_pBuildSQLHelper->m_password); 
		m_pConnection->setServer(m_pBuildSQLHelper->m_databaseName); 
		m_pConnection->open();
	}

	return nFunRes;
}



int CTestWorkerOCL::do_delete_table()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	bool isQuery = false;

	// Execute a direct query
	strSQL = m_pBuildSQLHelper->build_SQL_DeleteTable();

	isQuery = false;
	exec(m_pConnection, strSQL, isQuery);
	return nFunRes;
}

int CTestWorkerOCL::do_create_table()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	bool isQuery = false;


	// Execute a direct query
	strSQL = m_pBuildSQLHelper->build_SQL_CreateTable();
	isQuery = false;
	exec(m_pConnection, strSQL, isQuery);

	return nFunRes;
}

int CTestWorkerOCL::do_insert_data(int nCount)
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	int nParam_LineID_Value = 1000;
	int nIndex = 0;
	bool isQuery = false;


	for (nIndex = 0; nIndex < nCount; nIndex++)
	{

		// Execute a direct query
		nParam_LineID_Value = nIndex;
		strSQL = m_pBuildSQLHelper->build_SQL_InsertData(nParam_LineID_Value);

		isQuery = false;
		exec(m_pConnection, strSQL, isQuery);

		{
			_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_insert_data  nIndex=%d", nIndex);
		}

	}//for
	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_insert_data  Total=%d", nCount);


	return nFunRes;
}

int CTestWorkerOCL::do_select_data()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	int nRowIndex = 0;
	bool isQuery = true;

	// Execute a direct query
	strSQL = m_pBuildSQLHelper->build_SQL_SelectDataFromTable();
	isQuery = true;
	exec(m_pConnection, strSQL, isQuery);

	return nFunRes;
}






