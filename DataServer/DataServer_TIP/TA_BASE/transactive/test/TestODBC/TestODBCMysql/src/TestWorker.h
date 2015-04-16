#ifndef __CLASS_TEST_WORKDER__HH__
#define __CLASS_TEST_WORKDER__HH__


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

#include <stdio.h>
#include <iostream>

#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

#include <odbcinst.h>
#include <conio.h>

#include "BaseLogger.h"

class CTestWorker 
{
private:
	enum EThreadJobState
	{
		JobState_Begin,
		JobState_End,
	};

public:
	CTestWorker(void);
	~CTestWorker(void);

public:
	void run();	
private:
	void _ThreadJob();
	int _TestFun_ODBC_API_return_info();
	int _TestFun_ODBC_API_Sample();
	int _TestFun_ODBC_API_Sample_Table();


private:
	std::string _GetHandleTypeStringValue(SQLSMALLINT nHandleType);
	void _PrintLog(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo, SQLSMALLINT HandleType, SQLHANDLE Handle);
	void _PrintLogEx(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo, SQLHENV EnvironmentHandle, SQLHDBC ConnectionHandle, SQLHSTMT StatementHandle);
	void _PrintLogInfo(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo);
	void _PrintLogCheck(const std::string& strFileName, int nFileLine, const std::string& strLogInfo, SQLRETURN nSQLReturn);
private:
	EThreadJobState  m_nThreadJobState;

private:
	SQLHENV m_hEnviroment;// = NULL; INVALID_HANDLE_VALUE
	SQLHDBC m_hDatabaseConnection;// = NULL;
	SQLHSTMT m_hStatement;// = NULL;
	SQLHDESC m_hSQLHDesc;
};



#endif //__CLASS_TEST_WORKDER__HH__


