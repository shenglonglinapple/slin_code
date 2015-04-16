#include "ConfigInfo.h"

#include "ConfigInfoHelper.h"

#include <boost/algorithm/string.hpp>

#include "BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)


static const std::string DEF_VALUE_strConfigFileName = "./cfg/cfdServerConfigfile.cfg";
static const std::string DEF_VALUE_DbType = "SQLITE";//MYSQL

//defMysqlDBName  "MYSQL"  defSQLiteDBName "SQLITE"
static const std::string DEF_VALUE_PARAM_DbType = "dbtype";//dbtype=SQLITE


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
	m_strConfigFileName.clear();

	m_strConfigFileName = DEF_VALUE_strConfigFileName;
	m_strDbType = DEF_VALUE_DbType;
	_LoadDefaultConfigInfo();
}

CConfigInfo::~CConfigInfo(void)
{
	BOOST_LOG_FUNCTION();
}

void CConfigInfo::_LoadDefaultConfigInfo()
{
	BOOST_LOG_FUNCTION();
	std::string strParamValue;

	CConfigInfoHelper* pConfigInfoHelper = NULL;
	pConfigInfoHelper = new CConfigInfoHelper(m_strConfigFileName);

	strParamValue =pConfigInfoHelper->getStringParamValue(DEF_VALUE_PARAM_DbType);
	if (!strParamValue.empty())
	{
		m_strDbType = strParamValue;
		boost::algorithm::trim(m_strDbType);
		boost::algorithm::to_upper(m_strDbType);
	}	

	if (NULL != pConfigInfoHelper)
	{
		delete pConfigInfoHelper;
		pConfigInfoHelper = NULL;
	}
}


std::string CConfigInfo::getDbType()
{
	return m_strDbType;
}



void CConfigInfo::logInfo()
{
	BOOST_LOG_FUNCTION();

	return;
}


NS_END(TA_Base_Core)
















