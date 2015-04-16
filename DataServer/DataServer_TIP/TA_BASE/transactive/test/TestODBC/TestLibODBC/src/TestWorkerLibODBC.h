#ifndef __CLASS_TEST_WORKDER_LIB_ODBC__HH__
#define __CLASS_TEST_WORKDER_LIB_ODBC__HH__

#include "ProjectCommonData.h"


#include "odbc++/types.h"

#include "odbc++/drivermanager.h"
#include "odbc++/connection.h"
#include "odbc++/resultset.h"
#include "odbc++/resultsetmetadata.h"
#include "odbc++/callablestatement.h"
#include "odbc++/databasemetadata.h"


#include <sstream>
#include <iostream>
#include <memory>




class CBuildSQLHelper;

class CTestWorkerLibODBC 
{
public:
	CTestWorkerLibODBC(void);
	~CTestWorkerLibODBC(void);

public:
	void SetDBType(enDBType nDBType);
public:
	int do_disconnect_to_db();
	int do_connect_to_db();
	int do_delete_table();
	int do_create_table();
	int do_insert_data(int nCount);
	int do_select_data();
	void dumpWarnings(odbc::Statement* stmt);
private:
	enDBType m_nDBType;
private:
	CBuildSQLHelper* m_pBuildSQLHelper;
private:
	odbc::Connection* m_pConnection;


};



#endif //__CLASS_TEST_WORKDER_LIB_ODBC__HH__


