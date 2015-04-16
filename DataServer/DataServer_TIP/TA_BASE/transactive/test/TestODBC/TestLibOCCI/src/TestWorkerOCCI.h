#ifndef __CLASS_TEST_WORKDER_OCCI__HH__
#define __CLASS_TEST_WORKDER_OCCI__HH__


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

#include "occi.h"

class CBuildSQLHelper;

class CTestWorkerOCCI 
{
public:
	CTestWorkerOCCI(void);
	~CTestWorkerOCCI(void);

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
	void fillDataBuffer(oracle::occi::Connection *pconnection, oracle::occi::ResultSet* pQuery, int numColumns, long lMaxRows );
	void fun_testclass_fun_two();
	void fetchInitial(oracle::occi::Connection *pconnection, oracle::occi::ResultSet* pQuery, int numColumns, long lMaxRows );
	void exec(oracle::occi::Connection *pconnection, const std::string& strOracleSQL, bool isQuery);

private:
	enDBType m_nDBType;
private:
	CBuildSQLHelper* m_pBuildSQLHelper;
private:
	oracle::occi::Environment* m_pENV;
	oracle::occi::Connection* m_pConnection;


};



#endif //__CLASS_TEST_WORKDER_OCCI__HH__


