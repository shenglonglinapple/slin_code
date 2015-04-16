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

#include "ProjectCommonData.h"
#include "tiodbc.h"


class CBuildSQLHelper;

class CTestWorkerTinyODBC 
{
public:
	CTestWorkerTinyODBC(void);
	~CTestWorkerTinyODBC(void);

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
	enDBType m_nDBType;
private:
	CBuildSQLHelper* m_pBuildSQLHelper;
private:
	tiodbc::connection* m_pConnection;


};



#endif //__CLASS_TEST_WORKDER_TABLE__HH__


