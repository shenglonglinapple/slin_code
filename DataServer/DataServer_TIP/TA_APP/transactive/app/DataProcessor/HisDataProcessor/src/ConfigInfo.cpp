#include "ConfigInfo.h"

#include "ConfigInfoHelper.h"
#include "CFDServerUtilityFun.h"
#include <boost/algorithm/string.hpp>

#include "BoostLogger.h"
USING_BOOST_LOG;

QT_BEGIN_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static const std::string DEF_PARAM_VALUE_ConfigFileName_default = ".\\cfg\\Config_HisDataProcessor.cfg";
static const std::string DEF_PARAM_VALUE_HisDataDirectory_default = "D:\\HistData";
static const std::string DEF_PARAM_VALUE_SaveDataDirectoryBAR_default = "D:\\sllin_code\\DataServer\\SaveDataBAR";
static const std::string DEF_PARAM_VALUE_SaveDataDirectoryTIK_default = "D:\\sllin_code\\DataServer\\SaveDataTIK";

static const std::string DEF_PARAM_VALUE_DbType_default = "SQLITE";//MYSQL
static const std::string DEF_PARAM_VALUE_DbType_SQLITE = "SQLITE";//MYSQL
static const std::string DEF_PARAM_VALUE_DbType_MYSQL = "MYSQL";//MYSQL

static const std::string DEF_PARAM_VALUE_StartTime_default = "1980-01-01 09:00:01";//file time 1980-01-01 09:00:00

static const std::string DEF_PARAM_VALUE_AutoRun_default = "YES";//AutoRun=NO
static const std::string DEF_PARAM_VALUE_AutoRun_YES = "YES";//
static const std::string DEF_PARAM_VALUE_AutoRun_NO = "NO";//

static const std::string DEF_PARAM_VALUE_AutoRunTime_default = "2014-04-09 02::00:01";//2014-04-09 02::00:00 


//////////////////////////////////////////////////////////////////////////
static const std::string DEF_PARAM_KEY_ConfigFileName = "CFGFile";//CFGFile=./cfg/cfdServerConfigfile.cfg
//hisdata=C://TestData//HisData
static const std::string DEF_PARAM_KEY_HisDataDirectory = "hisdata";
//savedatabar=C://TestData//SaveDataBar
static const std::string DEF_PARAM_KEY_SaveDataDirectoryBAR = "savedatabar";
//savedatatik=C://TestData//SaveDataTIK
static const std::string DEF_PARAM_KEY_SaveDataDirectoryTIK = "savedatatik";
//defMysqlDBName  "MYSQL"  defSQLiteDBName "SQLITE"
static const std::string DEF_PARAM_KEY_DbType = "dbtype";//dbtype=SQLITE
//YYYY-MM-DD HH:MM:SS  2013-01-01 10:00:00
//file time is 2013-01-01 09:00:00 so must set bigger than 09:00:00
static const std::string DEF_PARAM_KEY_StartTime = "starttime";//dbtype=SQLITE

static const std::string DEF_PARAM_KEY_AutoRun = "AutoRun";//AutoRun=YES

static const std::string DEF_PARAM_KEY_AutoRunTime = "AutoRunTime";//02
//////////////////////////////////////////////////////////////////////////


CConfigInfo* CConfigInfo::m_pInstance = 0;
boost::mutex CConfigInfo::m_mutexInstance;

CConfigInfo& CConfigInfo::getInstance()
{	
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CConfigInfo();
	}
	return (*m_pInstance);
}

void CConfigInfo::removeInstance()
{
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}



CConfigInfo::CConfigInfo(void)
{
	BOOST_LOG_FUNCTION();

	m_pUtilityFun = NULL;
	m_pUtilityFun = new CCFDServerUtilityFun();


	m_strValue_ConfigFileName.clear();
	m_strValue_HistoryDataDirectory.clear();
	m_strValue_SaveDataDirectoryBAR.clear();
	m_strValue_SaveDataDirectoryTIK.clear();
	m_strValue_StartTime.clear();

	m_strValue_ConfigFileName = DEF_PARAM_VALUE_ConfigFileName_default;
	m_strValue_HistoryDataDirectory = DEF_PARAM_VALUE_HisDataDirectory_default;
	m_strValue_SaveDataDirectoryBAR = DEF_PARAM_VALUE_SaveDataDirectoryBAR_default;
	m_strValue_SaveDataDirectoryTIK = DEF_PARAM_VALUE_SaveDataDirectoryTIK_default;
	m_strValue_DbType = DEF_PARAM_VALUE_DbType_default;
	m_strValue_StartTime = DEF_PARAM_VALUE_StartTime_default;
	m_strValue_AutoRun = DEF_PARAM_VALUE_AutoRun_default;
	m_strValue_AutoRunTime = DEF_PARAM_VALUE_AutoRunTime_default;

	_LoadDefaultConfigInfo();
	processorCfgValue();

}

CConfigInfo::~CConfigInfo(void)
{
	BOOST_LOG_FUNCTION();

	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}
}

void CConfigInfo::_LoadDefaultConfigInfo()
{
	BOOST_LOG_FUNCTION();
	std::string strParamValue;

	CConfigInfoHelper* pConfigInfoHelper = NULL;
	pConfigInfoHelper = new CConfigInfoHelper(m_strValue_ConfigFileName);


	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_HisDataDirectory);
	if (!strParamValue.empty())
	{
		m_strValue_HistoryDataDirectory = strParamValue;
	}

	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_SaveDataDirectoryBAR);
	if (!strParamValue.empty())
	{
		m_strValue_SaveDataDirectoryBAR = strParamValue;
	}	

	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_SaveDataDirectoryTIK);
	if (!strParamValue.empty())
	{
		m_strValue_SaveDataDirectoryTIK = strParamValue;
	}	

	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_DbType);
	if (!strParamValue.empty())
	{
		m_strValue_DbType = strParamValue;
		boost::algorithm::trim(m_strValue_DbType);
		boost::algorithm::to_upper(m_strValue_DbType);
	}	

	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_StartTime);
	if (!strParamValue.empty())
	{
		m_strValue_StartTime = strParamValue;
		boost::algorithm::trim(m_strValue_StartTime);
		boost::algorithm::to_upper(m_strValue_StartTime);
	}

	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_AutoRun);
	if (!strParamValue.empty())
	{
		m_strValue_AutoRun = strParamValue;
		boost::algorithm::trim(m_strValue_AutoRun);
		boost::algorithm::to_upper(m_strValue_AutoRun);
	}	

	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_AutoRunTime);
	if (!strParamValue.empty())
	{
		m_strValue_AutoRunTime = strParamValue;
		boost::algorithm::trim(m_strValue_AutoRunTime);
		boost::algorithm::to_upper(m_strValue_AutoRunTime);
	}	


	if (NULL != pConfigInfoHelper)
	{
		delete pConfigInfoHelper;
		pConfigInfoHelper = NULL;
	}


}

void CConfigInfo::processorCfgValue()
{
	getHistoryDataDirectory();
	getSaveDataDirectoryBAR();
	getSaveDataDirectoryTIK();
	getDbType();
	getStartTime();
	getAutoRunType();
	getAutoRunTime();

	//logInfo();


}

std::string CConfigInfo::getHistoryDataDirectory()
{
	return m_strValue_HistoryDataDirectory;
}

std::string CConfigInfo::getSaveDataDirectoryBAR()
{
	return m_strValue_SaveDataDirectoryBAR;
}
std::string CConfigInfo::getSaveDataDirectoryTIK()
{
	return m_strValue_SaveDataDirectoryTIK;
}

DbServerType CConfigInfo::getDbType()
{
	if (m_strValue_DbType == DEF_PARAM_VALUE_DbType_MYSQL)
	{
		m_nValue_DbType = enumMysqlDb;
	}
	else if (m_strValue_DbType == DEF_PARAM_VALUE_DbType_SQLITE)
	{
		m_nValue_DbType = enumSqliteDb;
	}

	return m_nValue_DbType;
}

time_t CConfigInfo::getStartTime()
{
	m_nValue_StartTime = m_pUtilityFun->strToDateTime(m_strValue_StartTime);

	return m_nValue_StartTime;
}

AutoRunType CConfigInfo::getAutoRunType()
{
	if (m_strValue_AutoRun == DEF_PARAM_VALUE_AutoRun_NO)
	{
		m_nValue_AutoRun = AutoRunType_NO;
	}
	else if (m_strValue_AutoRun == DEF_PARAM_VALUE_AutoRun_YES)
	{
		m_nValue_AutoRun = AutoRunType_YES;
	}

	return m_nValue_AutoRun;
}

std::string CConfigInfo::getAutoRunTime()
{
	return m_strValue_AutoRunTime;
}

void CConfigInfo::logInfo()
{
	BOOST_LOG_FUNCTION();

	LOG_INFO<<"CConfigInfo::logInfo"
		<<" "<<"m_strValue_ConfigFileName="<<m_strValue_ConfigFileName
		<<" "<<"m_strValue_HistoryDataDirectory="<<m_strValue_HistoryDataDirectory
		<<" "<<"m_strValue_SaveDataDirectoryBAR="<<m_strValue_SaveDataDirectoryBAR
		<<" "<<"m_strValue_SaveDataDirectoryTIK="<<m_strValue_SaveDataDirectoryTIK
		<<" "<<"m_strValue_DbType="<<m_strValue_DbType
		<<" "<<"m_strValue_StartTime="<<m_strValue_StartTime
		<<" "<<"m_strValue_AutoRun="<<m_strValue_AutoRun
		<<" "<<"m_strValue_AutoRunTime="<<m_strValue_AutoRunTime;

	LOG_INFO<<"CConfigInfo::logInfo"
		<<" "<<"m_nValue_DbType="<<m_nValue_DbType
		<<" "<<"m_nValue_StartTime="<<m_nValue_StartTime
		<<" "<<"m_nValue_AutoRun="<<m_nValue_AutoRun;

	return;
}




void CConfigInfo::setHistoryDataDirectory(const std::string& strValue)
{
	m_strValue_HistoryDataDirectory = strValue;
}
void CConfigInfo::setSaveDataDirectoryBAR(const std::string& strValue)
{
	m_strValue_SaveDataDirectoryBAR = strValue;
}
void CConfigInfo::setSaveDataDirectoryTIK(const std::string& strValue)
{
	m_strValue_SaveDataDirectoryTIK = strValue;
}
void CConfigInfo::setDbType(const std::string& strValue)
{
	m_strValue_DbType = strValue;
}
void CConfigInfo::setStartTime(const std::string& strValue)
{
	m_strValue_StartTime = strValue;
}
void CConfigInfo::setAutoRun(const std::string& strValue)
{
	m_strValue_AutoRun = strValue;
}
void CConfigInfo::setAutoRunTime(const std::string& strValue)
{
	m_strValue_AutoRunTime = strValue;
}

QT_END_NAMESPACE
















