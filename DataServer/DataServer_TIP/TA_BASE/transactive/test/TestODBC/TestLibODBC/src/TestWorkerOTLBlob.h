#ifndef __CLASS_TEST_WORKDER_OTL_BLOB__HH__
#define __CLASS_TEST_WORKDER_OTL_BLOB__HH__


#include <string>
#include <iostream>
#include <vector>


#include "ProjectCommonData.h"

#include <otlv4.h> // include the OTL 4 header file

class CBuildSQLHelperBlob;

typedef std::vector<unsigned char> DataClob;
typedef std::vector<DataClob> DataClobArray;


class CTestWorkerOTLBlob 
{
public:
	CTestWorkerOTLBlob(void);
	~CTestWorkerOTLBlob(void);

public:
	void SetDBType(enDBType nDBType);
public:
	int do_disconnect_to_db();
	int do_connect_to_db();
	int do_delete_table();
	int do_create_table();
	int do_insert_data(int nCount);
	int do_select_data();
	int do_update_data();
	int do_update_data_ex();
	int do_update_data_ex_setdata();


private:	
	void fillDataBuffer(otl_connect *pconnection, otl_stream* pQuery, int numColumns, long lMaxRows );
	void fun_testclass_fun_two();
	void fetchInitial(otl_connect *pconnection, otl_stream* pQuery, int numColumns, long lMaxRows );
	void exec(otl_connect *pconnection, const std::string& strOracleSQL, bool isQuery);
private:
	std::string _GetColumnName(otl_stream* pQuery, int nColumnIndex);
	template<class T> std::string t_to_string(const T& t);
	std::string _GetColumnValue(otl_stream* pQuery, int nColumnIndex);
	int _GetColumnCount(otl_stream* pQuery);
private:
	enDBType m_nDBType;
private:
	CBuildSQLHelperBlob* m_pBuildSQLHelperBlob;
private:
	otl_connect* m_pConnection;

};



#endif //__CLASS_TEST_WORKDER_OTL_BLOB__HH__


