#ifndef __CLASS_CONFIG_INFO_H__
#define __CLASS_CONFIG_INFO_H__ 


#include "CFDServerCommonData.h"
#include "SqliteConfigFIleOper.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>


////////QT_BEGIN_NAMESPACE

class CCFDServerUtilityFun;
class CSQLiteConfigFileOperParam;


class CConfigInfo
{
public:
	static CConfigInfo& getInstance();
	static void removeInstance();

private:
	static CConfigInfo* m_pInstance;
	static boost::mutex m_mutexInstance;

private:
	CConfigInfo(void);	
	~CConfigInfo(void);

public:
	std::string getHistoryDataDirectory();
	std::string getSaveDataDirectoryBAR();
	std::string getSaveDataDirectoryTIK();

	DbServerType getDbType();
	time_t getStartTime();
	int getLoadMaxFilesSize();
	AutoRunType getAutoRunType();
	std::string getAutoRunTime();


	void logInfo();
	void logToDB(const std::string& strLogLevel, 
		const std::string& strLogFun,
		const std::string& strLogMsgStr0);
	void processorCfgValue();

	void setHistoryDataDirectory(const std::string& strValue);
	void setSaveDataDirectoryBAR(const std::string& strValue);
	void setSaveDataDirectoryTIK(const std::string& strValue);
	void setDbType(const std::string& strValue);
	void setStartTime(const std::string& strValue);
	void setAutoRun(const std::string& strValue);
	void setAutoRunTime(const std::string& strValue);
private:
	void _LoadConfigDBData();//fist read data from ".\\cfg\\Config_HisDataProcessor.db"
	void _LoadConfigFileData();//second read data from ".\\cfg\\Config_HisDataProcessor.cfg"

private:
	std::string m_strValue_ConfigFileName;
	std::string m_strValue_HistoryDataDirectory;
	std::string m_strValue_SaveDataDirectoryBAR;
	std::string m_strValue_SaveDataDirectoryTIK;
	std::string m_strValue_DbType;
	std::string m_strValue_StartTime_InFile;
	std::string m_strValue_LoadMaxFilesSize;
	std::string m_strValue_AutoRun;
	std::string m_strValue_AutoRunTime;/*1980-01-28 02:00:01*/

	std::string m_strValue_StartTime_InDB;

private:
	time_t m_nValue_StartTime_InFile;
	time_t m_nValue_StartTime_InDB;

private:
	DbServerType m_nValue_DbType;
	time_t m_nValue_StartTime;
	AutoRunType m_nValue_AutoRun;
	int m_nValue_LoadMaxFilesSize;
private:
	CCFDServerUtilityFun* m_pUtilityFun;
	CSQLiteConfigFileOperParam* m_pSQLiteConfigFileOperParam;
	CSqliteConfigFIleOper* m_pSqliteConfigFIleOper;
};//class


//////QT_END_NAMESPACE


#endif // __CLASS_CONFIG_INFO_H__



















