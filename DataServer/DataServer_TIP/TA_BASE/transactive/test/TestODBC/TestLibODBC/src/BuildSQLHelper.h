#ifndef __CLASS_BUILD_SQL_HELPER__HH__
#define __CLASS_BUILD_SQL_HELPER__HH__


#include <string>
#include <iostream>


#include "ProjectCommonData.h"


class CBuildSQLHelper 
{
public:
	CBuildSQLHelper(void);
	~CBuildSQLHelper(void);

public:
	void setDBType(enDBType nDBType);

public:
	std::string build_SQL_DeleteTable();
	std::string build_SQL_CreateTable();
	std::string build_SQL_InsertData(int nParam_LineID_Value);
	std::string build_SQL_SelectDataFromTable();
	std::string build_SQL_UpdateData();
	std::string build_SQL_DeleteData();

private:
	void _InitConnectionParam();
	void _InitSQL();


private:
	enDBType m_nDBType;
public:
	std::string m_strDNS;// = "Oracle12343DYN";
	std::string m_strUSR;// = "IT271350_5";
	std::string m_strPWD;// = "IT271350_5";

public:
	std::string m_connectionStr;// = "Oracle,TRANSACT,IT271350_5,IT271350_5,192.168.123.43";
	std::string m_databaseName;// = "TRANSACT";
	std::string m_userName;// = "IT271350_5";
	std::string m_password;// = "IT271350_5";
	std::string m_hostName;// = "192.168.123.43";

private:
	std::string strSql_Oracle_DropTestTable;// = "drop table table_test_daitest";
	std::string strSql_Oracle_CreateTestTable;// = "CREATE TABLE table_test_daitest(line_id NUMBER, test_type VARCHAR2(200), int_column NUMBER, str_column VARCHAR2(200), bool_column NUMBER, real_column NUMBER(38,8), date_column DATE, timestamp_column TIMESTAMP)";
	std::string strSql_Oracle_TestTable_INSERT_ok;// =	"insert into table_test_daitest(line_id, test_type, int_column, str_column, bool_column, real_column, date_column, timestamp_column) values(1000, 'Test_Type_NormalValue',1000000, 'str_normal_value', 1, 10000000.10001, sysdate, sysdate)";
	std::string strSql_Oracle_TestTable_UPDATE_ok;// =	"UPDATE table_test_daitest set int_column=5000,str_column='SQL_UPDATE_OK' where line_id= 1000";
	std::string strSql_Oracle_TestTable_DELETE_ok;// =	"DELETE from table_test_daitest where line_id= 1000";
	std::string strSql_Oracle_TestTable_SELECT_ok;// =	"SELECT str_column from table_test_daitest where line_id= 1000";


	std::string strSql_Mysql_DropTestTable;// = "drop table table_test_daitest";
	std::string strSql_Mysql_CreateTestTable;// ="CREATE TABLE table_test_daitest(line_id int, test_type VARCHAR(200), int_column int, str_column VARCHAR(200), bool_column int, real_column double, date_column datetime, timestamp_column TIMESTAMP)";
	std::string strSql_Mysql_TestTable_INSERT_ok;// =	"insert into table_test_daitest(line_id, test_type, int_column, str_column, bool_column, real_column, date_column, timestamp_column) values(1000, 'Test_Type_NormalValue',1000000, 'str_normal_value', 1, 10000000.10001, sysdate(), sysdate())";
	std::string strSql_Mysql_TestTable_UPDATE_ok;// = "UPDATE table_test_daitest set int_column=5000,str_column='SQL_UPDATE_OK' where line_id= 1000";
	std::string strSql_Mysql_TestTable_DELETE_ok;// =	"DELETE from table_test_daitest where line_id= 1000";
	std::string strSql_Mysql_TestTable_SELECT_ok;// =	"SELECT str_column table_test_daitest where line_id= 1000";


};



#endif //__CLASS_TEST_WORKDER_TABLE__HH__


