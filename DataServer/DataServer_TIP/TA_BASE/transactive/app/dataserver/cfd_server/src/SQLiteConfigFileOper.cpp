#include "SQLiteConfigFileOper.h"

#include <boost/algorithm/string.hpp>

#include "CFDServerUtilityFun.h"
#include "SQLiteConfigFileOperParam.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

//using namespace TA_Base_App;


////////QT_BEGIN_NAMESPACE


//////////////////////////////////////////////////////////////////////////


static const std::string str_Table_Config = "Table_Config";
static const std::string str_Table_MyLog = "Table_MyLog";

////
static const std::string str_Table_Config_Column_Config_PKE = "Config_PKE";
static const std::string str_Table_Config_Column_Config_LastUpdateTime = "Config_LastUpdateTime";
static const std::string str_Table_Config_Column_NextStartTime = "NextStartTime";

static const std::string str_Table_Config_Column_Config_PKE_Value = ":Config_PKE_Value";
static const std::string str_Table_Config_Column_SetValueTime_Value = ":Config_LastUpdateTime_Value";
static const std::string str_Table_Config_Column_NextStartTime_Value = ":NextStartTime_Value";

////
static const std::string str_Table_MyLog_Column_LOG_PKE = "LOG_PKE";
static const std::string str_Table_MyLog_Column_LOG_TIMESTAMP = "LOG_TIMESTAMP";
static const std::string str_Table_MyLog_Column_LOG_LEVEL = "LOG_LEVEL";
static const std::string str_Table_MyLog_Column_LOG_MSG_FUN = "LOG_MSG_FUN";
static const std::string str_Table_MyLog_Column_LOG_MSG_STR0 = "LOG_MSG_STR0";


static const std::string str_Table_MyLog_Column_LOG_PKE_Value = ":LOG_PKE_Value";
static const std::string str_Table_MyLog_Column_LOG_TIMESTAMP_Value = ":LOG_TIMESTAMP_Value";
static const std::string str_Table_MyLog_Column_LOG_LEVEL_Value = ":LOG_LEVEL_Value";
static const std::string str_Table_MyLog_Column_LOG_MSG_FUN_Value = ":LOG_MSG_FUN_Value";
static const std::string str_Table_MyLog_Column_LOG_MSG_STR0_Value = ":LOG_MSG_STR0_Value";



CSqliteConfigFIleOper::CSqliteConfigFIleOper( const CSQLiteConfigFileOperParam& dbOperParam )
{
	BOOST_LOG_FUNCTION();
	
	m_pUtilityFun = NULL;
	m_pDBOperParam = NULL;
	m_pQSqlDataBaseConfig = NULL;
	m_bStartTransactionTIK = false;

	m_pUtilityFun = new CCFDServerUtilityFun();

	m_pDBOperParam = new CSQLiteConfigFileOperParam();
	*m_pDBOperParam = dbOperParam;


	_InitDataBase();
}

CSqliteConfigFIleOper::~CSqliteConfigFIleOper(void)
{
	BOOST_LOG_FUNCTION();

	_UnInitDataBase();

	if (NULL != m_pDBOperParam)
	{
		delete m_pDBOperParam;
		m_pDBOperParam = NULL;
	}

	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}
	

}

void CSqliteConfigFIleOper::_InitDataBase()
{
	bool bExecRes = false;
	std::string strDBFileName;

	_UnInitDataBase();

	switch (m_pDBOperParam->m_nDataSrcDbType)
	{
	case enumSqliteDb:
		//SQLiteDB_3306.db
		m_pQSqlDataBaseConfig = new QSqlDatabase(QSqlDatabase::addDatabase(m_pDBOperParam->m_strQTDataSrcDbTypeName.c_str(), 
			QLatin1String(m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg.c_str())));
		//d://savedata//SQLiteDB_3306.db
		m_pQSqlDataBaseConfig->setDatabaseName(m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg.c_str());
		LOG_INFO<<m_pDBOperParam->m_strQTDataSrcDbTypeName
			<<" "<<"new Database  m_nDataSrcDbType="<<m_pDBOperParam->m_nDataSrcDbType
			<<" "<<"m_strSQLiteDBFileNameFullPathCfg="<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg;
		
		break;
	default:
		break;
	}

	///////
	bExecRes = m_pQSqlDataBaseConfig->open();
	if (!bExecRes)
	{
		LOG_ERROR<<m_pDBOperParam->m_strQTDataSrcDbTypeName<<" "<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg<<" Fail to open!"
			<<" "<<"error:"<<m_pQSqlDataBaseConfig->lastError().text().toStdString();
	}

	//check
	if (false == m_pQSqlDataBaseConfig->isValid())
	{
		LOG_ERROR<<m_pDBOperParam->m_strQTDataSrcDbTypeName
			<<" "<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg<<" is not Valid";
	}
	else
	{
		LOG_INFO<<m_pDBOperParam->m_strQTDataSrcDbTypeName
			<<" "<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg<<" is Valid";
	}

	if (false == m_pQSqlDataBaseConfig->driver()->hasFeature(QSqlDriver::Transactions)) 
	{
		LOG_INFO<<m_pDBOperParam->m_strQTDataSrcDbTypeName
			<<" "<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg<<" not support Transactions";
	}
	else
	{
		LOG_INFO<<m_pDBOperParam->m_strQTDataSrcDbTypeName
			<<" "<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg<<" support Transactions";
	}
	///////

}

void CSqliteConfigFIleOper::_UnInitDataBase()
{
	if (NULL != m_pQSqlDataBaseConfig)
	{
		LOG_INFO<<m_pDBOperParam->m_strQTDataSrcDbTypeName
			<<" "<<"delete Database  m_nDataSrcDbType="<<m_pDBOperParam->m_nDataSrcDbType
			<<" "<<"m_strSQLiteDBFileNameFullPathCfg="<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg;

		m_pQSqlDataBaseConfig->close();
		delete m_pQSqlDataBaseConfig;
		m_pQSqlDataBaseConfig = NULL;
		//QSqlDatabase::removeDatabase(m_pDBOperParam->m_strSQLiteDBFileName.c_str());
	}

}




int CSqliteConfigFIleOper::_StartTransaction()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	m_bStartTransactionTIK = false;

	if (false == m_pQSqlDataBaseConfig->driver()->hasFeature(QSqlDriver::Transactions)) 
	{
		m_bStartTransactionTIK = false;

		LOG_DEBUG<<m_pDBOperParam->m_strQTDataSrcDbTypeName
			<<" "<<"m_strSQLiteDBFileNameFullPathCfg="<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg
			<<" "<<"not support Transactions";
	}
	else
	{
		if (false == m_pQSqlDataBaseConfig->transaction())
		{
			m_bStartTransactionTIK = false;

			LOG_ERROR<<m_pDBOperParam->m_strQTDataSrcDbTypeName
				<<" "<<"m_strSQLiteDBFileNameFullPathCfg="<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg
				<<" "<<"support Transactions but start transaction error!"
				<<" "<<"error: "<<QSqlDatabase::database().lastError().text().toStdString();
		}
		else
		{
			m_bStartTransactionTIK = true;

			LOG_DEBUG<<m_pDBOperParam->m_strQTDataSrcDbTypeName
				<<" "<<"m_strSQLiteDBFileNameFullPathCfg="<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg
				<<" "<<"start Transaction";
		}
	}

	return nFunRes;
}


int CSqliteConfigFIleOper::_CommitTransaction()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;

	if (m_bStartTransactionTIK)
	{
		if(false == m_pQSqlDataBaseConfig->commit())  
		{  
			LOG_DEBUG<<m_pDBOperParam->m_strQTDataSrcDbTypeName
				<<" "<<"m_strSQLiteDBFileNameFullPathCfg="<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg
				<<" "<<"commit error!"
				<<" "<<"error: "<<QSqlDatabase::database().lastError().text().toStdString();

			if(false == m_pQSqlDataBaseConfig->rollback())  
			{  
				LOG_ERROR<<m_pDBOperParam->m_strQTDataSrcDbTypeName
					<<" "<<"m_strSQLiteDBFileNameFullPathCfg="<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg
					<<" "<<"rollback error!"
					<<" "<<"error: "<<QSqlDatabase::database().lastError().text().toStdString();
			}//if 
		}//if
		else
		{
			LOG_DEBUG<<m_pDBOperParam->m_strQTDataSrcDbTypeName
				<<" "<<"m_strSQLiteDBFileNameFullPathCfg="<<m_pDBOperParam->m_strSQLiteDBFileNameFullPathCfg
				<<" "<<"commit Transaction";
		}
	}//if

	m_bStartTransactionTIK = false;

	return nFunRes;
}



int CSqliteConfigFIleOper::_UseTransactionForBatchMode()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	
	_StartTransaction();

	_CommitTransaction();

	return nFunRes;
}






int CSqliteConfigFIleOper::_CreateDBTableConfig()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	bool bExecRes = true;
	std::string strSQL;

	QSqlQuery* pSqlQuery = NULL;
	pSqlQuery = new QSqlQuery(*m_pQSqlDataBaseConfig);

	strSQL = _BuildSQLForCreateDBTableConfig();

	LOG_DEBUG<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL.c_str());
	if (!bExecRes)
	{
		nFunRes = -1;
		LOG_ERROR<<"Fail to exec sql:"<<strSQL<<" error:"<<pSqlQuery->lastError().text().toStdString();
	}

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}


int CSqliteConfigFIleOper::_CreateDBTableMyLog()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;
	bool bExecRes = true;
	std::string strSQL;

	QSqlQuery* pSqlQuery = NULL;
	pSqlQuery = new QSqlQuery(*m_pQSqlDataBaseConfig);

	strSQL = _BuildSQLForCreateDBTableTableMyLog();

	LOG_DEBUG<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL.c_str());
	if (!bExecRes)
	{
		nFunRes = -1;
		LOG_ERROR<<"Fail to exec sql:"<<strSQL<<" error:"<<pSqlQuery->lastError().text().toStdString();
	}

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}


int CSqliteConfigFIleOper::checkAndInitDBTable()
{
	BOOST_LOG_FUNCTION();
	int nFunRes = 0;

	_CreateDBTableConfig();
	_CreateDBTableMyLog();

	return nFunRes;
}


int CSqliteConfigFIleOper::_CleanDataInTableConfig()
{
	int nFunRes = 0;
	bool bExecRes = false;
	std::ostringstream sreaamTmp;
	std::string strSQL;	
	QSqlQuery* pSqlQuery = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBaseConfig);

	{
		//delete old value
		sreaamTmp.str("");
		sreaamTmp<<"DELETE FROM"
			<<" "<<str_Table_Config
			<<" "<<"Where"
			<<" "<<str_Table_Config_Column_Config_PKE
			<<" "<<">=0";

		strSQL = sreaamTmp.str();
	}

	LOG_DEBUG<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL.c_str());
	if (!bExecRes)
	{
		nFunRes = -1;
		LOG_ERROR<<"Fail to exec sql:"<<strSQL<<" error:"<<pSqlQuery->lastError().text().toStdString();
	}

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}
	
	return nFunRes;
}

int CSqliteConfigFIleOper::updateNextStartTimeToDB(const std::string& strValue)
{
	int nFunRes = 0;
	bool bExecRes = false;
	std::string strDBTableName;
	std::string strCurrentTime;
	std::string strSQL;	
	//QVariantList lstConfigPKE;
	QVariantList lstConfigLastUpdateTime;
	QVariantList lstNextStartTim;
	QSqlQuery* pQSqlQueryForInseert = NULL;

	_CleanDataInTableConfig();

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBaseConfig);

	strDBTableName = str_Table_Config;
	strSQL = _BuildSQLForInsertTableConfig();

	pQSqlQueryForInseert->prepare(strSQL.c_str());


	strCurrentTime = m_pUtilityFun->getCurrentTime();
	
	lstConfigLastUpdateTime<<strCurrentTime.c_str();
	lstNextStartTim<<strValue.c_str();
		
	pQSqlQueryForInseert->addBindValue(lstConfigLastUpdateTime);
	pQSqlQueryForInseert->addBindValue(lstNextStartTim);

	bExecRes = pQSqlQueryForInseert->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		LOG_ERROR<<"execBatch strSQL="<<strSQL
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

int CSqliteConfigFIleOper::addMyLog(const std::string& strLogLevel, 
			 const std::string& strLogFun,
			 const std::string& strLogMsgStr0)
{
	int nFunRes = 0;
	bool bExecRes = false;
	std::string strDBTableName;
	std::string strCurrentTime;
	std::string strSQL;	
	QVariantList lstLogTimestamp;
	QVariantList lstLogLevel;
	QVariantList lstLogMsgFun;
	QVariantList lstLogMsgStr0;
	QSqlQuery* pQSqlQueryForInseert = NULL;

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBaseConfig);

	strDBTableName = str_Table_MyLog;
	strSQL = _BuildSQLForInsertTableMyLog();

	pQSqlQueryForInseert->prepare(strSQL.c_str());

	strCurrentTime = m_pUtilityFun->getCurrentTime();

	lstLogTimestamp<<strCurrentTime.c_str();
	lstLogLevel<<strLogLevel.c_str();
	lstLogMsgFun<<strLogFun.c_str();
	lstLogMsgStr0<<strLogMsgStr0.c_str();
	
	pQSqlQueryForInseert->addBindValue(lstLogTimestamp);
	pQSqlQueryForInseert->addBindValue(lstLogLevel);
	pQSqlQueryForInseert->addBindValue(lstLogMsgFun);
	pQSqlQueryForInseert->addBindValue(lstLogMsgStr0);

	bExecRes = pQSqlQueryForInseert->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		LOG_ERROR<<"execBatch strSQL="<<strSQL
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}


	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

std::string CSqliteConfigFIleOper::getNextStartTimeFormDB()
{
	int nFunRes = 0;
	bool bExecRes = true;
	std::string strSQL;
	int rowNum = 0;
	int columnNum = 0;
	int fieldNo = 0;
	QString qstrNextStartTimeValue;
	std::string strNextStartTimeValue;
	QSqlQuery* pSqlQuery = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBaseConfig);

	strSQL = _BuildSQLForSelectTableConfig();

	LOG_DEBUG<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL.c_str());
	if (!bExecRes)
	{
		nFunRes = -1;
		LOG_ERROR<<"Fail to exec sql:"<<strSQL<<" error:"<<pSqlQuery->lastError().text().toStdString();
	}

	//first record
	if (pSqlQuery->next())
	{
		rowNum = pSqlQuery->at();
		columnNum = pSqlQuery->record().count();
		fieldNo = pSqlQuery->record().indexOf(str_Table_Config_Column_NextStartTime.c_str());
		qstrNextStartTimeValue = pSqlQuery->value(fieldNo).toString();
		strNextStartTimeValue = qstrNextStartTimeValue.toStdString();

		LOG_INFO<<"get next start time form db"
			<<" "<<"strNextStartTimeValue="<<strNextStartTimeValue;

	}
	else
	{
		LOG_INFO<<"get next start time form db, not data";
		strNextStartTimeValue.clear();
	}

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return strNextStartTimeValue;
}


std::string CSqliteConfigFIleOper::_BuildSQLForSelectTableConfig()
{
	BOOST_LOG_FUNCTION();
	std::ostringstream sreaamTmp;
	std::string strSQL;	

	sreaamTmp.str("");
	sreaamTmp<<"SELECT"
		<<" "<<str_Table_Config_Column_NextStartTime
		<<" "<<"FROM"
		<<" "<<str_Table_Config;

	strSQL = sreaamTmp.str();
	return strSQL;	
}


std::string CSqliteConfigFIleOper::_BuildSQLForInsertTableConfig()
{
	BOOST_LOG_FUNCTION();
	std::ostringstream sreaamTmp;
	std::string strSQL;	

	sreaamTmp.str("");
	sreaamTmp<<"INSERT INTO "<<str_Table_Config
		<<" "<<"("
		<<" "<<str_Table_Config_Column_Config_LastUpdateTime<<","
		<<" "<<str_Table_Config_Column_NextStartTime
		<<" "<<")"
		<<" "<<"VALUES"
		<<" "<<"("
		<<" "<<"?"<<","
		<<" "<<"?"
		<<" "<<")";


	strSQL = sreaamTmp.str();
	return strSQL;	
}


std::string CSqliteConfigFIleOper::_BuildSQLForInsertTableMyLog()
{
	BOOST_LOG_FUNCTION();
	std::ostringstream sreaamTmp;
	std::string strSQL;	

	sreaamTmp.str("");
	sreaamTmp<<"INSERT INTO "<<str_Table_MyLog
		<<" "<<"("
		<<" "<<str_Table_MyLog_Column_LOG_TIMESTAMP<<","
		<<" "<<str_Table_MyLog_Column_LOG_LEVEL<<","
		<<" "<<str_Table_MyLog_Column_LOG_MSG_FUN<<","
		<<" "<<str_Table_MyLog_Column_LOG_MSG_STR0
		<<" "<<")"
		<<" "<<"VALUES"
		<<" "<<"("
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"
		<<" "<<")";


	strSQL = sreaamTmp.str();
	return strSQL;	
}

std::string CSqliteConfigFIleOper::_BuildSQLForCreateDBTableConfig()
{
	BOOST_LOG_FUNCTION();
	std::ostringstream sreaamTmp;
	std::string strSQL;

	{
		sreaamTmp.str("");
		sreaamTmp<<"CREATE TABLE IF NOT EXISTS"<<" "<<str_Table_Config
			<<" "<<"("
			<<" "<<str_Table_Config_Column_Config_PKE<<" "<<"INTEGER PRIMARY KEY"<<","
			<<" "<<str_Table_Config_Column_Config_LastUpdateTime<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_Table_Config_Column_NextStartTime<<" "<<"TIMESTAMP NOT NULL"
			<<" "<<")";
	}
	
	strSQL = sreaamTmp.str();
	return strSQL;
}


std::string CSqliteConfigFIleOper::_BuildSQLForCreateDBTableTableMyLog()
{
	BOOST_LOG_FUNCTION();
	std::ostringstream sreaamTmp;
	std::string strSQL;

	{
		sreaamTmp.str("");
		sreaamTmp<<"CREATE TABLE IF NOT EXISTS"<<" "<<str_Table_MyLog
			<<" "<<"("
			<<" "<<str_Table_MyLog_Column_LOG_PKE<<" "<<"INTEGER PRIMARY KEY"<<","
			<<" "<<str_Table_MyLog_Column_LOG_TIMESTAMP<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_Table_MyLog_Column_LOG_LEVEL<<" "<<"VARCHAR"<<","
			<<" "<<str_Table_MyLog_Column_LOG_MSG_FUN<<" "<<"VARCHAR"<<","
			<<" "<<str_Table_MyLog_Column_LOG_MSG_STR0<<" "<<"VARCHAR"
			<<" "<<")";
	}

	strSQL = sreaamTmp.str();
	return strSQL;
}




//////QT_END_NAMESPACE 



