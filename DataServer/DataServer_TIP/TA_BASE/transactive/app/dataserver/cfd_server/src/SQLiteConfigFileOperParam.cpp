#include "SQLiteConfigFileOperParam.h"

#include <boost/algorithm/string.hpp>
#include "BoostLogger.h"
USING_BOOST_LOG;

////////QT_BEGIN_NAMESPACE




static const std::string DEFVALUE_String_SQLITE_DbFile_Config_HisDataProcessor = ".\\cfg\\Config_HisDataProcessor.db";//Config_HisDataProcessor.db



CSQLiteConfigFileOperParam::CSQLiteConfigFileOperParam(void)
{
	BOOST_LOG_FUNCTION();

	m_strDataSrcDbType.clear();
	m_nDataSrcDbType = enumSqliteDb;
	m_strQTDataSrcDbTypeName = defQTSQLiteDBTypeName;
	m_strSQLiteDBFileNameFullPathCfg.clear();

	//
	m_strDataSrcDbType = defSQLiteDBName;
	m_nDataSrcDbType = enumSqliteDb;
	m_strQTDataSrcDbTypeName = defQTSQLiteDBTypeName;

	m_strSQLiteDBFileNameFullPathCfg = DEFVALUE_String_SQLITE_DbFile_Config_HisDataProcessor;

}

CSQLiteConfigFileOperParam::~CSQLiteConfigFileOperParam(void)
{
	BOOST_LOG_FUNCTION();
}


CSQLiteConfigFileOperParam& CSQLiteConfigFileOperParam::operator=(const CSQLiteConfigFileOperParam& dbOperParam )
{
	BOOST_LOG_FUNCTION();
	//
	m_strDataSrcDbType = dbOperParam.m_strDataSrcDbType;
	m_nDataSrcDbType = dbOperParam.m_nDataSrcDbType;
	m_strQTDataSrcDbTypeName = dbOperParam.m_strQTDataSrcDbTypeName;

	m_strSQLiteDBFileNameFullPathCfg = dbOperParam.m_strSQLiteDBFileNameFullPathCfg;

	return *this;
}

void CSQLiteConfigFileOperParam::logInfo()
{
	BOOST_LOG_FUNCTION();

	LOG_INFO<<" "<<"m_strDataSrcDbType="<<m_strDataSrcDbType;
	LOG_INFO<<" "<<"m_nDataSrcDbType="<<m_nDataSrcDbType;
	LOG_INFO<<" "<<"m_strQTDataSrcDbTypeName="<<m_strQTDataSrcDbTypeName;
	LOG_INFO<<" "<<"m_strSQLiteDBFileNameFullPathCfg="<<m_strSQLiteDBFileNameFullPathCfg;
	return;
}



//////QT_END_NAMESPACE
















