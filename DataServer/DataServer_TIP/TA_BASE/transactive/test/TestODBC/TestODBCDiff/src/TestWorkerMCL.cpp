#include "TestWorkerMCL.h"

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
#include "cppconn/driver.h"
#include "driver/mysql_public_iface.h"




CTestWorkerMCL::CTestWorkerMCL( void )
{
	m_nDBType = DB_ORACLE;
	m_pConnection = NULL;
	m_pBuildSQLHelper = NULL;
	m_pBuildSQLHelper = new CBuildSQLHelper();
	m_pBuildSQLHelper->setDBType(m_nDBType);

	m_pDriver = (sql::Driver*)get_driver_instance();  // for mysql db connection

}

CTestWorkerMCL::~CTestWorkerMCL( void )
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


void CTestWorkerMCL::SetDBType( enDBType nDBType )
{
	m_nDBType = nDBType;
	m_pBuildSQLHelper->setDBType(m_nDBType);

}

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CTestWorkerMCL::fillDataBuffer(sql::Connection *pconnection, sql::ResultSet* pQuery, int numColumns, long lMaxRows )
{
	int nFieldNumber = 0;
	int nRecordCount = 0; 
	int nRecordIndex = 0;
	int nOCILIBRes = 0;

	sql::ResultSetMetaData* pRsMetaData = pQuery->getMetaData() ;
	nFieldNumber = pRsMetaData->getColumnCount();


	// Get results from statement
	try
	{
		//nRecordIndex begin with 1   nFieldIndex begin with 1
		nRecordIndex = 1;
		_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_select_data  nRowIndex=%d", nRecordIndex);

		//while( !pQuery->isEOF() && ( nRecordIndex <= lMaxRows ))
		while( !pQuery->isAfterLast() )
		{
			//Row dataRow;
			for ( int nFieldIndex = 0; nFieldIndex < numColumns; ++nFieldIndex )
			{
				std::string strFieldName = pRsMetaData->getColumnName(nFieldIndex + 1);// 1-based
				std::string strValue = pQuery->getString(nFieldIndex + 1);

				_BaseLog(BaseLogSourceFLInfo, DebugDebug, "[nRecordIndex=%d][nFieldIndex=%d] SQL field name:[%s]; value:[%s]", 
					nRecordIndex, nFieldIndex+1, strFieldName.c_str(), strValue.c_str());

			}
			pQuery->next();
			++nRecordIndex;
		}//while

	}
	catch(  sql::SQLException & e )
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, " sql::SQLException  [errormsg=%s] [errorcode=%d]", e.getSQLStateCStr(), e.getErrorCode());
	}
	catch( ... )
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "fillDataBuffer UNKNOWN ERROR");
	}

	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_select_data  Total=%d", nRecordIndex);

}//CTestClass::fillDataBuffer



void CTestWorkerMCL::fetchInitial(sql::Connection *pconnection, sql::ResultSet* pQuery, int numColumns, long lMaxRows )
{
	try
	{
		if ( pQuery->rowsCount() > 0 )
		{
			pQuery->first();
			fillDataBuffer(pconnection, pQuery, numColumns, lMaxRows);
		}
	}
	catch( sql::SQLException & e )
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "sql::SQLException  [errormsg=%s] [errorcode=%d]", e.getSQLStateCStr(), e.getErrorCode());
	}
	catch(...)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "fetchInitial UNKNOWN ERROR");
	}


}//CTestClass::fetchInitial

void CTestWorkerMCL::exec(sql::Connection *pconnection, const std::string& strOracleSQL, bool isQuery)
{
	int prefetch = 100;
	std::string strSql = strOracleSQL;
	sql::ResultSet* query = NULL;	

	try
	{
		// check the database connection first, if it already closed, open it
		if (m_pConnection->isClosed())
		{
			return;
		}		
		std::auto_ptr< sql::Statement > stmt(m_pConnection->createStatement());
		if (isQuery) //select *
		{
			query = stmt->executeQuery(strSql);
		}
		else //like the insert command
		{
			bool bRetCode = stmt->execute(strSql);
			if (bRetCode)
			{
			}
			if ( NULL != query)
			{
				delete query;
				query = NULL;
			}			
		}
	}
	catch(sql::SQLException & e)
	{

	}
	catch(...)
	{

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
		nRecordCount = 10000000;
		//nRecordCount = query->recordCount();

		fetchInitial(pconnection, query, numColumns, nRecordCount);

		query->close();
		delete query;
		query = NULL;

		lstColumns.clear();

	}//if ( NULL != query )

}//CTestClass::exec



//////////////////////////////////////////////////////////////////////////


int CTestWorkerMCL::do_disconnect_to_db()
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

int CTestWorkerMCL::do_connect_to_db()
{
	int nFunRes = 0;
	bool bFunRes = false;


	try
	{		
		if (NULL != m_pConnection)
		{		
			delete m_pConnection;
			m_pConnection = NULL;
		}	
		if (NULL == m_pConnection)
		{
			sql::ConnectOptionsMap connection_properties;
			connection_properties["hostName"] = m_pBuildSQLHelper->m_hostName;
			connection_properties["userName"] = m_pBuildSQLHelper->m_userName;
			connection_properties["password"] = m_pBuildSQLHelper->m_password;
			connection_properties["metadataUseInfoSchema"] = true;

			m_pConnection = m_pDriver->connect(connection_properties); 

			m_pConnection->setSchema(m_pBuildSQLHelper->m_databaseName);

			// set this session mode with backslash disabled, same with oracle
			std::auto_ptr< sql::Statement > stmt(m_pConnection->createStatement());
			stmt->execute("set session sql_mode=concat(@@sql_mode,',NO_BACKSLASH_ESCAPES')");
		}				

	}
	catch(sql::SQLException & e)
	{

	}		
	catch(...)
	{
	
	}	

	return nFunRes;
}



int CTestWorkerMCL::do_delete_table()
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

int CTestWorkerMCL::do_create_table()
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

int CTestWorkerMCL::do_insert_data(int nCount)
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

		
		_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_insert_data  nIndex=%d", nIndex);
		

	}//for
	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_insert_data  Total=%d", nCount);


	return nFunRes;
}

int CTestWorkerMCL::do_select_data()
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






