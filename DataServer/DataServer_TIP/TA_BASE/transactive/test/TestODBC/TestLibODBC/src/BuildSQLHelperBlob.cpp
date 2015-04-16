#include "BuildSQLHelperBlob.h"


#include "ProjectCommonData.h"

//////////////////////////////////////////////////////////////////////////
/*
#define        TEST_STRING_BLOB_Table				   "ti_predefined_message_library"
#define        TEST_STRING_BLOB_Field				   "library_file_content"


#define        TEST_STRING_BLOB_INSERT_MYSQL           "insert into ti_predefined_message_library(TIPMLI_ID, VERSION, library_file_content) values(7999999, 7999999, 'TEST')"

#define        TEST_STRING_BLOB_SELECT				   "SELECT library_file_content FROM ti_predefined_message_library WHERE tipmli_id = 7999999"
#define        TEST_STRING_BLOB_DELETE				   "delete  from ti_predefined_message_library where TIPMLI_ID = 7999999"

#define        TEST_STRING_BLOB_WHERE                  "tipmli_id = 7999999"



#define        TEST_STRING_BLOB_Table			   "ti_predefined_message_library"
#define        TEST_STRING_BLOB_Field			   "library_file_content"


#define        TEST_STRING_BLOB_INSERT_ORACLE          "insert into ti_predefined_message_library(TIPMLI_ID, VERSION, LIBRARY_TYPE, LIBRARY_FILE_CONTENT) values(7999999, 7999999, 'TEST', rawtohex('TTTT'))"  //empty_blob()

#define        TEST_STRING_BLOB_SELECT				   "SELECT library_file_content FROM ti_predefined_message_library WHERE tipmli_id = 7999999"
#define        TEST_STRING_BLOB_DELETE				   "delete  from ti_predefined_message_library where TIPMLI_ID = 7999999"

#define        TEST_STRING_BLOB_WHERE                  "tipmli_id = 7999999"


*/


//////////////////////////////////////////////////////////////////////////

CBuildSQLHelperBlob::CBuildSQLHelperBlob( void )
{
	m_nDBType = DB_ORACLE;
	_InitConnectionParam();
	_InitSQL();

}

CBuildSQLHelperBlob::~CBuildSQLHelperBlob( void )
{


}


void CBuildSQLHelperBlob::setDBType( enDBType nDBType )
{
	m_nDBType = nDBType;
	_InitConnectionParam();
	_InitSQL();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CBuildSQLHelperBlob::_InitConnectionParam()
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

void CBuildSQLHelperBlob::_InitSQL()
{
	this->strSql_Oracle_DropTestTable = "DROP TABLE TABLE_TEST_DAITEST";
	this->strSql_Oracle_CreateTestTable = "CREATE TABLE TABLE_TEST_DAITEST(LINE_ID NUMBER, TEST_TYPE VARCHAR2(200), BLOB_COLUMN BLOB, CLOB_COLUMN CLOB)";
	//this->strSql_Oracle_TestTable_INSERT_ok = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (1000, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, sysdate, sysdate)";
	//this->strSql_Oracle_TestTable_INSERT_ok = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, BLOB_COLUMN, CLOB_COLUMN) VALUES (%d, 'Test_Type_BLOB_CLOB', rawtohex('PPPP'), rawtohex('PPPP'))";
	this->strSql_Oracle_TestTable_INSERT_ok = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, BLOB_COLUMN, CLOB_COLUMN) VALUES (%d, 'Test_Type_BLOB_CLOB', 'PPPP', 'PPPP')";
	//"UPDATE TABLE_TEST_DAITEST SET BLOB_COLUMN=rawtohex('BBBBA'), CLOB_COLUMN='BBBBA' WHERE LINE_ID= 1";
	this->strSql_Oracle_TestTable_UPDATE_ok =	"UPDATE TABLE_TEST_DAITEST SET BLOB_COLUMN='BBBB',CLOB_COLUMN='BBBB' WHERE LINE_ID= 1";
	this->strSql_Oracle_TestTable_DELETE_ok =	"DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID= 1";
	this->strSql_Oracle_TestTable_SELECT_ok =	"SELECT LINE_ID, TEST_TYPE, BLOB_COLUMN, CLOB_COLUMN FROM TABLE_TEST_DAITEST";//,empty_blob()

	this->strSql_Mysql_DropTestTable = "DROP TABLE TABLE_TEST_DAITEST";
	this->strSql_Mysql_CreateTestTable = "CREATE TABLE TABLE_TEST_DAITEST(LINE_ID int, TEST_TYPE VARCHAR(200), INT_COLUMN int, STR_COLUMN VARCHAR(200), BOOL_COLUMN int, REAL_COLUMN double, DATE_COLUMN DATETIME, TIMESTAMP_COLUMN TIMESTAMP)";
	//this->strSql_Mysql_TestTable_INSERT_ok = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (1000, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, sysdate(), sysdate())";
	this->strSql_Mysql_TestTable_INSERT_ok = "INSERT INTO TABLE_TEST_DAITEST(LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN) VALUES (%d, 'Test_Type_NormalValue', 1000000, 'str_normal_value', 1, 10000000.10001, sysdate(), sysdate())";
	this->strSql_Mysql_TestTable_UPDATE_ok = "UPDATE TABLE_TEST_DAITEST SET INT_COLUMN=5000,STR_COLUMN='SQL_UPDATE_OK' WHERE LINE_ID= 1000";
	this->strSql_Mysql_TestTable_DELETE_ok =	"DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID= 1000";
	//this->strSql_Mysql_TestTable_SELECT_ok =	"SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST WHERE LINE_ID = 1000";
	this->strSql_Mysql_TestTable_SELECT_ok =	"SELECT LINE_ID, TEST_TYPE, INT_COLUMN, STR_COLUMN, BOOL_COLUMN, REAL_COLUMN, DATE_COLUMN, TIMESTAMP_COLUMN FROM TABLE_TEST_DAITEST";

}

std::string CBuildSQLHelperBlob::build_SQL_DeleteTable()
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

std::string CBuildSQLHelperBlob::build_SQL_CreateTable()
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


std::string CBuildSQLHelperBlob::build_SQL_InsertData(int nParam_LineID_Value)
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

std::string CBuildSQLHelperBlob::build_SQL_SelectDataFromTable()
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
std::string CBuildSQLHelperBlob::build_SQL_DeleteData()
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

std::string CBuildSQLHelperBlob::build_SQL_UpdateData()
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
#if 0
Example 56 (Insert/Update/Select with Oracle 8 CLOB in stream mode)

This example demonstrates INSERT, UPDATE, and SELECT statements with the Oracle 8 CLOB datatype in stream mode.

Source Code

#include <iostream>
using namespace std;

#include <stdio.h>
#define OTL_ORA8 // Compile OTL 4.0/OCI8
#include <otlv4.h> // include the OTL 4.0 header file

otl_connect db; // connect object

void insert()
// insert rows into table
{
	otl_long_string f2(60000); // define long string variable
otl_stream o(1, // buffer size has to be set to 1 for operations with LOBs
			 "insert into test_tab values(:f1<int>,empty_clob()) "
			 "returning f2 into :f2<clob> ",
			 // SQL statement
			 db // connect object
			 );
o.set_commit(0); // setting stream "auto-commit" to "off". It is required
// when LOB stream mode is used.

otl_lob_stream lob; // LOB stream for reading/writing unlimited number
// of bytes regardless of the buffer size.

for(int i=1;i<=20;++i)
{
	for(int j=0;j<50000;++j)
		f2[j]='*';

	f2[50000]='?';
	f2.set_len(50001);

	o<<i;

	o<<lob; // Initialize otl_lob_stream by writing it
	// into otl_stream. Weird, isn't it?

	lob.set_len(50001+23123); // setting the total  size of
	// the CLOB to be written.
	// It is required for compatibility
	// with earlier releases of OCI8: OCI8.0.3, OCI8.0.4.

	lob<<f2; // writing first chunk of the CLOB into lob

	f2[23122]='?';
	f2.set_len(23123); // setting the size of the second chunk

	lob<<f2; // writing the second chunk of the CLOB into lob
	lob.close(); // closing the otl_lob_stream
}

db.commit(); // committing transaction.
}


void update()
// insert rows in table
{ 
	otl_long_string f2(6200); // define long string variable

	otl_stream o(1, // buffer size has to be set to 1 for operations with LOBs
		"update test_tab "
		"   set f2=empty_clob() "
		"where f1=:f1<int> "
		"returning f2 into :f2<clob> ",
		// SQL statement
		db // connect object
		);

	otl_lob_stream lob;

	o.set_commit(0); // setting stream "auto-commit" to "off". 


	for(int j=0;j<6000;++j)
	{
		f2[j]='#';
	}

	f2[6000]='?';
	f2.set_len(6001);

	o<<5;
	o<<lob; // Initialize otl_lob_stream by writing it
	// into otl_stream.

	long rpc=o.get_rpc(); // get the RPC count
	if(rpc==1)
	{
		lob.set_len(6001*4); // setting the total size of of the CLOB to be written
		for(int i=1;i<=4;++i)
			lob<<f2; // writing chunks of the CLOB into the otl_lob_stream

		lob.close(); // closing the otl_lob_stream
	}else if(rpc==0){
		// nothing to do, closing the LOB stream in the "don't throw
		// otl_exception when size doesn't match" mode
		lob.close(true);
	}

	db.commit(); // committing transaction

}

void select()
{ 
	otl_long_string f2(20000); // define long string variable

	otl_stream i(10, // buffer size. To read CLOBs, it can be set to a size greater than 1
		"select * from test_tab where f1>=:f<int> and f1<=:f*2",
		// SELECT statement
		db // connect object
		); 
	// create select stream

	float f1;
	otl_lob_stream lob; // Stream for reading CLOB

	i<<4; // assigning :f = 4
	// SELECT automatically executes when all input variables are
	// assigned. First portion of output rows is fetched to the buffer

	while(!i.eof()){ // while not end-of-data
		i>>f1;
		cout<<"f1="<<f1<<endl;
		i>>lob; // initializing CLOB stream by reading the CLOB reference 
		// into the otl_lob_stream from the otl_stream.
		if(f1==4 || f1==8)
			lob.setInitialReadOffset(30000);
		int n=0;
		while(!lob.eof()){ // read while not "end-of-file" -- end of CLOB
			++n;
			lob>>f2; // reading a chunk of CLOB
			cout<<"   chunk #"<<n;
			cout<<", f2="<<f2[0]<<f2[f2.len()-1]<<", len="<<f2.len()<<endl;
		}
		lob.close(); // closing the otl_lob_stream. This step may be skipped.

	}

}

int main()
{
	otl_connect::otl_initialize(); // initialize OCI environment
	try{

		db.rlogon("scott/tiger"); // connect to Oracle

		otl_cursor::direct_exec
			(
			db,
			"drop table test_tab",
			otl_exception::disabled // disable OTL exceptions
			); // drop table

		otl_cursor::direct_exec
			(
			db,
			"create table test_tab(f1 number, f2 clob)"
			);  // create table

		insert(); // insert records into table
		update(); // update records in table
		select(); // select records from table

	}

	catch(otl_exception& p){ // intercept OTL exceptions
		cerr<<p.msg<<endl; // print out error message
		cerr<<p.stm_text<<endl; // print out SQL that caused the error
		cerr<<p.var_info<<endl; // print out the variable that caused the error
	}

	db.logoff(); // disconnect from Oracle

	return 0;

}
Output

f1=4
chunk #1, f2=**, len=20000
chunk #2, f2=?*, len=20000
chunk #3, f2=*?, len=3124
f1=5
chunk #1, f2=##, len=20000
chunk #2, f2=#?, len=4004
f1=6
chunk #1, f2=**, len=20000
chunk #2, f2=**, len=20000
chunk #3, f2=**, len=20000
chunk #4, f2=*?, len=13124
f1=7
chunk #1, f2=**, len=20000
chunk #2, f2=**, len=20000
chunk #3, f2=**, len=20000
chunk #4, f2=*?, len=13124
f1=8
chunk #1, f2=**, len=20000
chunk #2, f2=?*, len=20000
chunk #3, f2=*?, len=3124
#endif