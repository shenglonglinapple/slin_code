#ifndef __CLASS_SQLITE_CONFIGFILE_OPER_PARAM_H__
#define __CLASS_SQLITE_CONFIGFILE_OPER_PARAM_H__


#include "CFDServerCommonData.h"

////////QT_BEGIN_NAMESPACE


class CSQLiteConfigFileOperParam
{
public:
	CSQLiteConfigFileOperParam(void);	
	~CSQLiteConfigFileOperParam(void);

public:
	CSQLiteConfigFileOperParam& operator=(const CSQLiteConfigFileOperParam& dbOperParam);

public:
	void logInfo();

public:
	std::string m_strDataSrcDbType;//"MYSQL"  "SQLITE"
	DbServerType m_nDataSrcDbType;//enumSqliteDb
	std::string m_strQTDataSrcDbTypeName;//"QSQLITE"

public:
	std::string m_strSQLiteDBFileNameFullPathCfg;//.\\Config_HisDataProcessor.db


};


//////QT_END_NAMESPACE


#endif // __CLASS_SQLITE_CONFIGFILE_OPER_PARAM_H__









