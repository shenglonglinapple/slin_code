#ifndef __CLASS_PROCESS_YAHUO_DATA_TO_LOCAL_DB_H__
#define __CLASS_PROCESS_YAHUO_DATA_TO_LOCAL_DB_H__


#include <QtCore/QString>

class CProcessYahuoDataToLocalDB
{
public:
	CProcessYahuoDataToLocalDB();
	virtual ~CProcessYahuoDataToLocalDB();
public:
	void processStock(const QString & strSymbolUse);
private:
	void _SaveDataToLocalDB(const QString & strSymbolUse, const QString & strData);


};


#endif //__CLASS_PROCESS_YAHUO_DATA_TO_LOCAL_DB_H__
