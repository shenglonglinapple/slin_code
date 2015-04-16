#ifndef __CLASS_TEST_WORKDER_MCL__HH__
#define __CLASS_TEST_WORKDER_MCL__HH__


#include <string>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined (WIN32)
# include <windows.h>
# include <io.h>
#else
# include <unistd.h>
#endif

#include "ProjectCommonData.h"

#include "cppconn/driver.h"
#include "driver/mysql_public_iface.h"



class CBuildSQLHelper;

class CTestWorkerMCL 
{
public:
	CTestWorkerMCL(void);
	~CTestWorkerMCL(void);

public:
	void SetDBType(enDBType nDBType);
public:
	int do_disconnect_to_db();
	int do_connect_to_db();
	int do_delete_table();
	int do_create_table();
	int do_insert_data(int nCount);
	int do_select_data();
private:	
	void fillDataBuffer(sql::Connection *pconnection, sql::ResultSet* pQuery, int numColumns, long lMaxRows );
	void fun_testclass_fun_two();
	void fetchInitial(sql::Connection *pconnection, sql::ResultSet* pQuery, int numColumns, long lMaxRows );
	void exec(sql::Connection *pconnection, const std::string& strOracleSQL, bool isQuery);

private:
	enDBType m_nDBType;
private:
	CBuildSQLHelper* m_pBuildSQLHelper;
private:
	sql::Driver* m_pDriver;
	sql::Connection* m_pConnection;


};



#endif //__CLASS_TEST_WORKDER_MCL__HH__


