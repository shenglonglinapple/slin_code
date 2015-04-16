#ifndef __CLASS_TEST_WORKDER_OCL__HH__
#define __CLASS_TEST_WORKDER_OCL__HH__


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

#include "ocl.h"

class CBuildSQLHelper;

class CTestWorkerOCL 
{
public:
	CTestWorkerOCL(void);
	~CTestWorkerOCL(void);

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
	void fillDataBuffer(ocl::OraConnection *pconnection, ocl::OraQuery* pQuery, int numColumns, long lMaxRows );
	void fun_testclass_fun_two();
	void fetchInitial(ocl::OraConnection *pconnection, ocl::OraQuery* pQuery, int numColumns, long lMaxRows );
	void exec(ocl::OraConnection *pconnection, const std::string& strOracleSQL, bool isQuery);

private:
	enDBType m_nDBType;
private:
	CBuildSQLHelper* m_pBuildSQLHelper;
private:
	ocl::OraConnection* m_pConnection;


};



#endif //__CLASS_TEST_WORKDER_OCL__HH__


