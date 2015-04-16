#include "BuildSQLHelper.h"


#include "ProjectCommonData.h"



CBuildSQLHelper::CBuildSQLHelper( void )
{
	m_nDBType = DB_ORACLE;
	_InitConnectionParam();
	_InitSQL();

}

CBuildSQLHelper::~CBuildSQLHelper( void )
{


}


void CBuildSQLHelper::setDBType( enDBType nDBType )
{
	m_nDBType = nDBType;
	_InitConnectionParam();
	_InitSQL();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CBuildSQLHelper::_InitConnectionParam()
{
	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			m_strDNS = "Oracle225";//"Oracle12343DYN";
			m_strUSR = "IT271350_5";
			m_strPWD = "IT271350_5";

			m_connectionStr = "Oracle,DEV_C225,IT271350_5,IT271350_5,192.168.253.225";//"Oracle,TRANSACT,IT271350_5,IT271350_5,192.168.123.43";
			m_databaseName = "DEV_C225";//DEV_C225 "TRANSACT"
			m_userName = "IT271350_5";
			m_password = "IT271350_5";
			m_hostName = "192.168.253.225";//"192.168.123.43";
		}
		break;
	case DB_MYSQL:
		{
			m_strDNS = "Oracle225";//"Oracle12343DYN";
			m_strUSR = "IT271350_5";
			m_strPWD = "IT271350_5";

			m_connectionStr = "Mysql,TRA_OCC,IT271350_5,IT271350_5,192.168.123.43";
			m_databaseName = "TRA_OCC";
			m_userName = "IT271350_5";
			m_password = "IT271350_5";
			m_hostName = "192.168.123.43";
		}
		break;
	default:
		break;
	}//switch


}

void CBuildSQLHelper::_InitSQL()
{
	this->strSql_Oracle_DropTestTable = "DROP TABLE TABLE_TEST_DAITEST";
	this->strSql_Oracle_CreateTestTable = "CREATE TABLE TABLE_TEST_DAITEST(LINE_ID NUMBER, TEST_TYPE VARCHAR2(200), INT_COLUMN NUMBER, STR_COLUMN VARCHAR2(200), BOOL_COLUMN NUMBER, REAL_COLUMN NUMBER(20,8), DATE_COLUMN DATE, TIMESTAMP_COLUMN TIMESTAMP)";
	//this->strSql_Oracle_TestTable_INSERT_ok = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (1000, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, sysdate, sysdate)";
	this->strSql_Oracle_TestTable_INSERT_ok = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (%d, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, sysdate, sysdate)";
	this->strSql_Oracle_TestTable_UPDATE_ok =	"UPDATE TABLE_TEST_DAITEST SET INT_COLUMN=5000,STR_COLUMN='SQL_UPDATE_OK' WHERE LINE_ID= 1000";
	this->strSql_Oracle_TestTable_DELETE_ok =	"DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID= 1000";
	//this->strSql_Oracle_TestTable_SELECT_ok =	"SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST WHERE LINE_ID = 1000";
	//this->strSql_Oracle_TestTable_SELECT_ok =	"SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST";
	this->strSql_Oracle_TestTable_SELECT_ok =	"SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TO_CHAR(TIMESTAMP_COLUMN,'MM/DD/YYYY HH24:MI:SS.FF')  FROM TABLE_TEST_DAITEST";

	this->strSql_Mysql_DropTestTable = "DROP TABLE TABLE_TEST_DAITEST";
	this->strSql_Mysql_CreateTestTable = "CREATE TABLE TABLE_TEST_DAITEST(LINE_ID int, TEST_TYPE VARCHAR(200), INT_COLUMN int, STR_COLUMN VARCHAR(200), BOOL_COLUMN int, REAL_COLUMN double, DATE_COLUMN DATETIME, TIMESTAMP_COLUMN TIMESTAMP)";
	//this->strSql_Mysql_TestTable_INSERT_ok = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (1000, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, sysdate(), sysdate())";
	this->strSql_Mysql_TestTable_INSERT_ok = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (%d, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, sysdate(), sysdate())";
	this->strSql_Mysql_TestTable_UPDATE_ok = "UPDATE TABLE_TEST_DAITEST SET INT_COLUMN=5000,STR_COLUMN='SQL_UPDATE_OK' WHERE LINE_ID= 1000";
	this->strSql_Mysql_TestTable_DELETE_ok =	"DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID= 1000";
	//this->strSql_Mysql_TestTable_SELECT_ok =	"SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST WHERE LINE_ID = 1000";
	this->strSql_Mysql_TestTable_SELECT_ok =	"SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST";

}

std::string CBuildSQLHelper::build_SQL_DeleteTable()
{
	std::string strSQL;

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			strSQL = strSql_Oracle_DropTestTable;
		}
		break;
	case DB_MYSQL:
		{
			strSQL = strSql_Mysql_DropTestTable;//"DROP TABLE TABLE_TEST_DAITEST";
		}
		break;
	default:
		break;
	}//switch

	return strSQL;
}

std::string CBuildSQLHelper::build_SQL_CreateTable()
{
	std::string strSQL;

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			strSQL = strSql_Oracle_CreateTestTable;//"CREATE TABLE TABLE_TEST_DAITEST(LINE_ID NUMBER, TEST_TYPE VARCHAR2(200), INT_COLUMN NUMBER, STR_COLUMN VARCHAR2(200), BOOL_COLUMN NUMBER, REAL_COLUMN NUMBER(20,8), DATE_COLUMN DATE, TIMESTAMP_COLUMN TIMESTAMP)";
		}
		break;
	case DB_MYSQL:
		{
			strSQL = strSql_Mysql_CreateTestTable;//"CREATE TABLE TABLE_TEST_DAITEST(LINE_ID int, TEST_TYPE VARCHAR(200), INT_COLUMN int, STR_COLUMN VARCHAR(200), BOOL_COLUMN int, REAL_COLUMN double, DATE_COLUMN DATETIME, TIMESTAMP_COLUMN TIMESTAMP)";
		}
		break;
	default:
		break;
	}//switch

	return strSQL;
}


std::string CBuildSQLHelper::build_SQL_InsertData(int nParam_LineID_Value)
{
	std::string strSQL;
	char* pBuffer = NULL;
	int nBufferSize = 1024;

	pBuffer = new char[nBufferSize];
	memset(pBuffer, 0, nBufferSize * sizeof(char));

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			//strSQL = strSql_Oracle_TestTable_INSERT_ok;//"INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (1000, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, TO_DATE('09/09/2014 09:57:20','dd/mm/yyyy hh24:mi:ss'), TO_DATE('09/09/2014 09:57:20','dd/mm/yyyy hh24:mi:ss'))";
			sprintf(pBuffer, strSql_Oracle_TestTable_INSERT_ok.c_str(), nParam_LineID_Value);
		}
		break;
	case DB_MYSQL:
		{
			//strSQL = strSql_Mysql_TestTable_INSERT_ok;//"INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (1000, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, '09/09/2014 09:57:20', '09/09/2014 09:57:20')";
			sprintf(pBuffer, strSql_Mysql_TestTable_INSERT_ok.c_str(), nParam_LineID_Value);
		}
		break;
	default:
		break;
	}//switch

	strSQL = pBuffer;

	if (NULL != pBuffer)
	{
		delete[] pBuffer;
		pBuffer = NULL;
	}

	return strSQL;
}

std::string CBuildSQLHelper::build_SQL_SelectDataFromTable()
{
	std::string strSQL;

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			strSQL = strSql_Oracle_TestTable_SELECT_ok;//"SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST WHERE LINE_ID = 1000";
		}
		break;
	case DB_MYSQL:
		{
			strSQL = strSql_Mysql_TestTable_SELECT_ok;//"SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST WHERE LINE_ID = 1000";
		}
		break;
	default:
		break;
	}//switch

	return strSQL;
}
std::string CBuildSQLHelper::build_SQL_DeleteData()
{
	std::string strSQL;

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			strSQL = strSql_Oracle_TestTable_DELETE_ok;
		}
		break;
	case DB_MYSQL:
		{
			strSQL = strSql_Mysql_TestTable_DELETE_ok;
		}
		break;
	default:
		break;
	}//switch

	return strSQL;
}

std::string CBuildSQLHelper::build_SQL_UpdateData()
{
	std::string strSQL;

	switch(m_nDBType)
	{
	case DB_ORACLE:
		{
			strSQL = strSql_Oracle_TestTable_UPDATE_ok;
		}
		break;
	case DB_MYSQL:
		{
			strSQL = strSql_Mysql_TestTable_UPDATE_ok;
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






//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
