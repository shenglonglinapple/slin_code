#ifndef __CLASS_CONFIG_INFO_H__
#define __CLASS_CONFIG_INFO_H__ 


#include "CFDServerCommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>


QT_BEGIN_NAMESPACE

class CCFDServerUtilityFun;

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
	AutoRunType getAutoRunType();
	std::string getAutoRunTime();


	void logInfo();
	void processorCfgValue();

	void setHistoryDataDirectory(const std::string& strValue);
	void setSaveDataDirectoryBAR(const std::string& strValue);
	void setSaveDataDirectoryTIK(const std::string& strValue);
	void setDbType(const std::string& strValue);
	void setStartTime(const std::string& strValue);
	void setAutoRun(const std::string& strValue);
	void setAutoRunTime(const std::string& strValue);
private:
	void _LoadDefaultConfigInfo();
private:
	std::string m_strValue_ConfigFileName;
	std::string m_strValue_HistoryDataDirectory;
	std::string m_strValue_SaveDataDirectoryBAR;
	std::string m_strValue_SaveDataDirectoryTIK;
	std::string m_strValue_DbType;
	std::string m_strValue_StartTime;
	std::string m_strValue_AutoRun;
	std::string m_strValue_AutoRunTime;/*1980-01-28 02:00:01*/
private:
	DbServerType m_nValue_DbType;
	time_t m_nValue_StartTime;
	AutoRunType m_nValue_AutoRun;
	
private:
	CCFDServerUtilityFun* m_pUtilityFun;

};//class


QT_END_NAMESPACE


#endif // __CLASS_CONFIG_INFO_H__



















