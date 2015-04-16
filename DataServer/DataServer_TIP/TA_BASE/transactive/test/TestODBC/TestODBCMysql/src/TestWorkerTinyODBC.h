#ifndef __CLASS_TEST_WORKDER_TINY_ODBC__HH__
#define __CLASS_TEST_WORKDER_TINY_ODBC__HH__


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

class CTestWorkerTinyODBC 
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
	CTestWorkerTinyODBC(void);
	~CTestWorkerTinyODBC(void);

public:
	void run();	
private:
	void _ThreadJob();

private:
	std::string _BuildSQL_DeleteTable();
	std::string _BuildSQL_CreateTable();
	std::string _BuildSQL_InsertDataToTable();
	std::string _BuildSQL_SelectDataFromTable();
private:
	int _TestFun_SampleTable();
private:
	EThreadJobState  m_nThreadJobState;

private:
	enDBType m_nDBType;
};



#endif //__CLASS_TEST_WORKDER_TABLE__HH__


