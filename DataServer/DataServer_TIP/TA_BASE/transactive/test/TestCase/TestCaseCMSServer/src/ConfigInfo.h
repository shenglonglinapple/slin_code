#ifndef __CLASS_CONFIG_INFO_H__
#define __CLASS_CONFIG_INFO_H__ 


#include "UtilityFun.h"
#include "CommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>


NS_BEGIN(TA_Base_Test)

class CUtilityFun;

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
	RunType getRunType();
	int getClientCount();
	int getDoTestTimeMicroSeconds();
	std::string getServerAddress();

	void logInfo();
private:
	void _LoadDefaultConfigInfo();
	
private:
	std::string m_strValue_CFGFile;
	std::string m_strValue_RunType;
	std::string m_strValue_ServerAddress;
	std::string m_strValue_ClientCount;
	std::string m_strValue_DoTestHours;

private:
	RunType m_nValue_RunType;
	int m_nValue_ClientCount;
	int m_nValue_DoTestMicroSeconds;

private:
	CUtilityFun* m_pUtilityFun;

};//class


NS_END(TA_Base_Test)


#endif // __CLASS_CONFIG_INFO_H__



















