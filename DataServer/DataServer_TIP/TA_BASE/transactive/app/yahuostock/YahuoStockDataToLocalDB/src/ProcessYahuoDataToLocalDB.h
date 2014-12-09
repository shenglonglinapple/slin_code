#ifndef __CLASS_PROCESS_YAHUO_DATA_TO_LOCAL_DB_H__
#define __CLASS_PROCESS_YAHUO_DATA_TO_LOCAL_DB_H__


#include <string>


class CProcessYahuoDataToLocalDB
{
public:
	CProcessYahuoDataToLocalDB();
	virtual ~CProcessYahuoDataToLocalDB();
public:
	void processStock(const std::string& strSymbolUse);
private:
	void _SaveDataToLocalDB(const std::string& strSymbolUse, const std::string& strData);


};


#endif //__CLASS_PROCESS_YAHUO_DATA_TO_LOCAL_DB_H__
