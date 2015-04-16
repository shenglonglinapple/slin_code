#ifndef __CLASS_SQLITE_CONFIG_FILE_OPER__HH__
#define __CLASS_SQLITE_CONFIG_FILE_OPER__HH__

#include "CFDServerCommonData.h"

#include <QtSql/QtSql>
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>

#include "SQLiteConfigFileOperParam.h"

////////QT_BEGIN_NAMESPACE 

class CCFDServerUtilityFun;

class CSqliteConfigFIleOper
{
public:
	CSqliteConfigFIleOper(const CSQLiteConfigFileOperParam&  dbOperParam);
	~CSqliteConfigFIleOper(void);
public:
	int checkAndInitDBTable();
	std::string getNextStartTimeFormDB();
	int updateNextStartTimeToDB(const std::string& strValue);//2014-01-02 10:00:02

	int addMyLog(const std::string& strLogLevel, 
		const std::string& strLogFun,
		const std::string& strLogMsgStr0);


private:
	void _InitDataBase();
	void _UnInitDataBase();
	int _StartTransaction();
	int _CommitTransaction();

	int _UseTransactionForBatchMode();
private:
	int _CreateDBTableConfig();
	std::string _BuildSQLForCreateDBTableConfig();
	std::string _BuildSQLForInsertTableConfig();
	std::string _BuildSQLForSelectTableConfig();

private:
	int _CreateDBTableMyLog();
	std::string _BuildSQLForCreateDBTableTableMyLog();
	std::string _BuildSQLForInsertTableMyLog();
	int _CleanDataInTableConfig();
private:
	QSqlDatabase*		m_pQSqlDataBaseConfig;
	bool                m_bStartTransactionTIK;


private:
	CSQLiteConfigFileOperParam*  m_pDBOperParam;
	CCFDServerUtilityFun*  m_pUtilityFun;
};

//////QT_END_NAMESPACE 


#endif //__CLASS_SQLITE_DB_OPER__HH__


