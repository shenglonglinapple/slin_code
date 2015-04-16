#include "TestWorkerOCCI.h"

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
#include "occi.h"


//////////////////////////////////////////////////////////////////////////



CTestWorkerOCCI::CTestWorkerOCCI( void )
{

	m_nDBType = DB_ORACLE;
	m_pENV = NULL;
	m_pConnection = NULL;
	m_pBuildSQLHelper = NULL;
	m_pBuildSQLHelper = new CBuildSQLHelper();
	m_pBuildSQLHelper->setDBType(m_nDBType);


}

CTestWorkerOCCI::~CTestWorkerOCCI( void )
{
	if (NULL != m_pConnection)
	{
		if (NULL != m_pENV)
		{
			m_pENV->terminateConnection(m_pConnection);
		}
		//delete m_pConnection;
		m_pConnection = NULL;
	}

	if (NULL != m_pENV)
	{
		oracle::occi::Environment::terminateEnvironment(m_pENV);
		m_pENV = NULL;
	}

	if (NULL != m_pBuildSQLHelper)
	{
		delete m_pBuildSQLHelper;
		m_pBuildSQLHelper = NULL;
	}
}


void CTestWorkerOCCI::SetDBType( enDBType nDBType )
{
	m_nDBType = nDBType;
	m_pBuildSQLHelper->setDBType(m_nDBType);

}

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CTestWorkerOCCI::fillDataBuffer(oracle::occi::Connection *pconnection, oracle::occi::ResultSet* pQuery, int numColumns, long lMaxRows )
{
	int nFieldNumber = 0;
	int nRecordCount = 0; 
	int nRecordIndex = 0;
	int nOCILIBRes = 0;

	nFieldNumber = numColumns;//pQuery->fieldCount();
	nRecordCount = pQuery->getNumArrayRows();
	
	_BaseLog(BaseLogSourceFLInfo, DebugDebug, "[nRecordCount=%d] [nFieldNumber=%d]", nRecordCount, nFieldNumber);



	// Get results from statement
	try
	{
		//nRecordIndex begin with 1   nFieldIndex begin with 1
		nRecordIndex = 1;
		_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_select_data  nRowIndex=%d", nRecordIndex);

		//while( !pQuery->isEOF() && ( nRecordIndex <= lMaxRows ))

		while(pQuery->next())
		{
			//Row dataRow;
			for ( int nColumnIndex = 0; nColumnIndex < numColumns; ++nColumnIndex )
			{
				std::string strColumnName ;
				//std::string strColumnName = pQuery->getMaxColumnSize();//pQuery->field(nColumnIndex).name();
				std::string strColumnValue = pQuery->getString(nColumnIndex);//begin with 1//->field(nColumnIndex).getString();

				_BaseLog(BaseLogSourceFLInfo, DebugDebug, "[nRecordIndex=%d][nColumnIndex=%d] strColumnName=%s, strColumnValue=%s", 
					nRecordIndex, nColumnIndex+1, strColumnName.c_str(), strColumnValue.c_str());

			}
			//pQuery->next();
			++nRecordIndex;
		}//while

	}
	catch(oracle::occi::SQLException e )
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "OCI_ERROR  [errormsg=%s] [errorcode=%d]", e.getMessage().c_str(), e.getErrorCode());
	}
	catch( ... )
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "fillDataBuffer UNKNOWN ERROR");
	}

	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_select_data  Total=%d", nRecordIndex);

}//CTestClass::fillDataBuffer



void CTestWorkerOCCI::fetchInitial(oracle::occi::Connection *pconnection, oracle::occi::ResultSet* pQuery, int numColumns, long lMaxRows )
{
	try
	{
		fillDataBuffer(pconnection, pQuery, numColumns, lMaxRows);
	}
	catch(...)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "fetchInitial UNKNOWN ERROR");
	}


}//CTestClass::fetchInitial

void CTestWorkerOCCI::exec(oracle::occi::Connection *pconnection, const std::string& strOracleSQL, bool isQuery)
{
	int prefetch = 100;
	std::string strSql = strOracleSQL;
	oracle::occi::Statement* pStatement = NULL;
	oracle::occi::ResultSet* pResultSet = NULL;
	//LOG_GENERIC(SourceInfo, DebugUtil::DebugSQL, "Begin execute the SQL statement: [[%s]]", strSql.c_str());


	try
	{
		
		pStatement = m_pConnection->createStatement();//创Statement对象
		//stmt->setSQL(strSql);//准备SQL语句
		pStatement->setAutoCommit(false);

		if (isQuery) //select *
		{
			//pStatement->setPrefetchRowCount(100);
			pResultSet =  pStatement->executeQuery(strSql);//执行SQL语句，返回结果集.
			_BaseLog(BaseLogSourceFLInfo, DebugDebug, "executeQuery  strSql=%s", strSql.c_str());

		}
		else //like the insert command
		{
			pStatement->executeUpdate(strSql);
			//pStatement->execute(strSql);
			pStatement->getUpdateCount();
			pResultSet = NULL;
			_BaseLog(BaseLogSourceFLInfo, DebugDebug, "executeUpdate  strSql=%s", strSql.c_str());

		}


		m_pConnection->commit();


	}
	catch(oracle::occi::SQLException ex) //异常处理
	{
		m_pConnection->rollback();

		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"exec OCCI_ERROR  [ErrorMessage=%s] [errorcode=%d] strSql=%s", 
			 ex.getMessage().c_str(), ex.getErrorCode(), strSql.c_str());

	}
	catch(...)
	{
		m_pConnection->rollback();

		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"exec OCCI_ERROR  [ErrorMessage=%s] [errorcode=%d]", 
			"UNKNOW", 0);
	}

	//isQuery == true
	//just save the pointer, here
	if ( NULL != pResultSet )
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
		nRecordCount = pResultSet->getNumArrayRows();
		//nRecordCount = pResultSet->recordCount();

		fetchInitial(pconnection, pResultSet, numColumns, nRecordCount);

		pStatement->closeResultSet(pResultSet);
		pResultSet = NULL;

		lstColumns.clear();

	}//if ( NULL != query )

	
	m_pConnection->terminateStatement(pStatement);//终止Statement对象
	pStatement = NULL;



}//CTestClass::exec



//////////////////////////////////////////////////////////////////////////


int CTestWorkerOCCI::do_disconnect_to_db()
{
	int nFunRes = 0;

	try
	{


		if (NULL != m_pConnection)
		{
			if (NULL != m_pENV)
			{
				m_pENV->terminateConnection(m_pConnection);
			}
			//delete m_pConnection;
			m_pConnection = NULL;
		}

		if (NULL != m_pENV)
		{
			oracle::occi::Environment::terminateEnvironment(m_pENV);
			m_pENV = NULL;
		}
	}
	catch(oracle::occi::SQLException ex) //异常处理
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"exec OCCI_ERROR  [ErrorMessage=%s] [errorcode=%d]", 
			ex.getMessage().c_str(), ex.getErrorCode());

		
	}


	return nFunRes;
}

int CTestWorkerOCCI::do_connect_to_db()
{
	int nFunRes = 0;
	bool bFunRes = false;

	do_disconnect_to_db();
	

	try
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug,"begin createEnvironment"); 
		m_pENV = oracle::occi::Environment::createEnvironment(oracle::occi::Environment::DEFAULT);
		_BaseLog(BaseLogSourceFLInfo, DebugDebug,"end createEnvironment m_pENV=0x%0X", m_pENV); 
	}
	catch(oracle::occi::SQLException ex) //异常处理
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"exec OCCI_ERROR  [ErrorMessage=%s] [errorcode=%d]", 
			ex.getMessage().c_str(), ex.getErrorCode());
	}


	try
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug,"begin createConnection"); 

		//std::string connectString = "192.168.123.43/TRANSACT";//
		std::string connectString = "TRANSACT";//
		if (NULL == m_pConnection && NULL != m_pENV)
		{	
			m_pConnection = m_pENV->createConnection(m_pBuildSQLHelper->m_userName,
				m_pBuildSQLHelper->m_password,
				connectString); //创建数据库连接对象
		}
		_BaseLog(BaseLogSourceFLInfo, DebugDebug,"end createConnection m_pConnection=0x%0X", m_pConnection); 

	}
	catch(oracle::occi::SQLException ex) //异常处理
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"exec OCCI_ERROR  [ErrorMessage=%s] [errorcode=%d]", 
			ex.getMessage().c_str(), ex.getErrorCode());
	}


	return nFunRes;
}



int CTestWorkerOCCI::do_delete_table()
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

int CTestWorkerOCCI::do_create_table()
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

int CTestWorkerOCCI::do_insert_data(int nCount)
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

int CTestWorkerOCCI::do_select_data()
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






