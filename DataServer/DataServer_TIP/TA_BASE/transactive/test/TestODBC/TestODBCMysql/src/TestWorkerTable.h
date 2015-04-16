#ifndef __CLASS_TEST_WORKDER_TABLE__HH__
#define __CLASS_TEST_WORKDER_TABLE__HH__


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

class CTestWorkerTable 
{
public:
	enum enDBType
	{
		DB_ORACLE,
		DB_MYSQL
	};
private:
	enum EThreadJobState
	{
		JobState_Begin,
		JobState_End,
	};

public:
	CTestWorkerTable(void);
	~CTestWorkerTable(void);

public:
	void run();	
private:
	void _ThreadJob();
	int _TestFun_ODBC_TABLE_TEST_DAITEST();

private:
	std::string _GetHandleTypeStringValue(SQLSMALLINT nHandleType);
	void _PrintLog(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo, SQLSMALLINT HandleType, SQLHANDLE Handle);
	void _PrintLogEx(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo, SQLHENV EnvironmentHandle, SQLHDBC ConnectionHandle, SQLHSTMT StatementHandle);
	void _PrintLogInfo(const std::string& strFileName, int nFileLine, EDebugLevel level, const std::string& strLogInfo);
	void _PrintLogCheck(const std::string& strFileName, int nFileLine, const std::string& strLogInfo, SQLRETURN nSQLReturn);
private:
	std::string _BuildSQL_DeleteTable();
	std::string _BuildSQL_CreateTable();
	std::string _BuildSQL_InsertDataToTable();
	std::string _BuildSQL_SelectDataFromTable();
private:
	int _ExecModifySQL(const std::string& strSQL);
	int _ExecSelectSQL(const std::string& strSQL);
private:
	EThreadJobState  m_nThreadJobState;

private:
	SQLHENV m_hEnviroment;// = NULL; INVALID_HANDLE_VALUE
	SQLHDBC m_hDatabaseConnection;// = NULL;
	SQLHSTMT m_hStatement;// = NULL;
	SQLHDESC m_hSQLHDesc;
	enDBType m_nDBType;
};



#endif //__CLASS_TEST_WORKDER_TABLE__HH__


