#include "ConfigInfo.h"

#include "ConfigInfoHelper.h"
#include "UtilityFun.h"

#include <boost/algorithm/string.hpp>

#include "BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Test)


static const std::string DEF_PARAM_Value_ConfigFileName = "./cfg/testcms.cfg";

static const std::string DEF_PARAM_Value_RunType_default = "SERVER";
static const std::string DEF_PARAM_Value_RunType_server = "SERVER";
static const std::string DEF_PARAM_Value_RunType_client = "CLIENT";

static const std::string DEF_PARAM_Value_ServerAddress_default = "tcp://127.0.0.1:5555";

static const std::string DEF_PARAM_Value_ClientCount_default = "1";

static const std::string DEF_PARAM_Value_DoTestHours_default = "1";

/////
static const std::string DEF_PARAM_KEY_ConfigFileName = "CFGFile";//cfgfile=./cfg/testcms.cfg
static const std::string DEF_PARAM_KEY_RunType = "RunType";//RunType=SERVER CLIENT
static const std::string DEF_PARAM_KEY_ServerAddress = "ServerAddress";//ServerAddress=tcp://127.0.0.1:5555
static const std::string DEF_PARAM_KEY_ClientCount = "ClientCount";//ClientCount=1
static const std::string DEF_PARAM_KEY_DoTestHours = "DoTestHours";//DoTestHours=1



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
	m_strValue_CFGFile.clear();
	m_strValue_RunType.clear();
	m_strValue_ServerAddress.clear();
	m_strValue_ClientCount.clear();
	m_strValue_DoTestHours.clear();


	m_strValue_CFGFile = DEF_PARAM_Value_ConfigFileName;
	m_strValue_RunType = DEF_PARAM_Value_RunType_default;
	m_strValue_ServerAddress = DEF_PARAM_Value_ServerAddress_default;
	m_strValue_ClientCount = DEF_PARAM_Value_ClientCount_default;
	m_strValue_DoTestHours = DEF_PARAM_Value_DoTestHours_default;

	m_pUtilityFun = new CUtilityFun();

	_LoadDefaultConfigInfo();
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
	pConfigInfoHelper = new CConfigInfoHelper(m_strValue_CFGFile);


	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_RunType);
	if (!strParamValue.empty())
	{
		m_strValue_RunType = strParamValue;
	}


	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_ServerAddress);
	if (!strParamValue.empty())
	{
		m_strValue_ServerAddress = strParamValue;
	}


	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_KEY_ClientCount);
	if (!strParamValue.empty())
	{
		m_strValue_ClientCount = strParamValue;
	}


	strParamValue = pConfigInfoHelper->getStringParamValue(DEF_PARAM_Value_DoTestHours_default);
	if (!strParamValue.empty())
	{
		m_strValue_DoTestHours = strParamValue;
	}

	

	if (NULL != pConfigInfoHelper)
	{
		delete pConfigInfoHelper;
		pConfigInfoHelper = NULL;
	}
}


RunType CConfigInfo::getRunType()
{
	boost::algorithm::trim(m_strValue_RunType);
	boost::algorithm::to_upper(m_strValue_RunType);

	if (DEF_PARAM_Value_RunType_client == m_strValue_RunType)
	{
		m_nValue_RunType = RunType_CLIENT;
	}
	else
	{
		m_nValue_RunType = RunType_SERVER;
	}
	return m_nValue_RunType;
}

int CConfigInfo::getClientCount()
{
	m_nValue_ClientCount = m_pUtilityFun->mysys_boost_strToint(m_strValue_ClientCount);
	return m_nValue_ClientCount;
}

int CConfigInfo::getDoTestTimeMicroSeconds()
{
	int nHours = 0;
	nHours = m_pUtilityFun->mysys_boost_strToint(m_strValue_DoTestHours);
	m_nValue_DoTestMicroSeconds = nHours * TIME_BASE_HOUR;
	return m_nValue_DoTestMicroSeconds;
}

std::string CConfigInfo::getServerAddress()
{
	return m_strValue_ServerAddress;
}



void CConfigInfo::logInfo()
{
	BOOST_LOG_FUNCTION();

	LOG_DEBUG<<"CConfigInfo::logInfo "
		<<" "<<"m_strValue_CFGFile="<<m_strValue_CFGFile
		<<" "<<"m_strValue_RunType="<<m_strValue_RunType
		<<" "<<"m_strValue_ServerAddress="<<m_strValue_ServerAddress
		<<" "<<"m_strValue_ClientCount="<<m_strValue_ClientCount
		<<" "<<"m_strValue_DoTestHours="<<m_strValue_DoTestHours;

	return;
}


NS_END(TA_Base_Test)
















