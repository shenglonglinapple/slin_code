#include "DbStatusManager.h"

#include <boost/algorithm/string.hpp>
#include "core/DataAccess/src/DbStatusItem.h"
#include "core/DataAccess/src/DbStatusItemList.h"

#include "core/DataAccess/src/ConfigXMLParser.h"
#include "core/CppConfigLib/src/RunParams.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)


CDbStatusManager* CDbStatusManager::m_pInstance = 0;
boost::mutex CDbStatusManager::m_mutexInstance;

CDbStatusManager& CDbStatusManager::getInstance()
{	
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDbStatusManager();
	}
	return (*m_pInstance);
}

void CDbStatusManager::removeInstance()
{
	boost::mutex::scoped_lock lock(m_mutexInstance);	


	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}

}



CDbStatusManager::CDbStatusManager(void)
{
	BOOST_LOG_FUNCTION();

	{
		_FreeData();
	}

	m_strConfigFile = "./cfg/ConnectionString.xml";
	m_pConfigXMLParser = new CConfigXMLParser();



}

CDbStatusManager::~CDbStatusManager(void)
{
	BOOST_LOG_FUNCTION();

	{
		_FreeData();
	}

	if (NULL != m_pConfigXMLParser)
	{
		delete m_pConfigXMLParser;
		m_pConfigXMLParser = NULL;
	}
}


void CDbStatusManager::_SetXMLConfigFile( const std::string& strXMLConfigFile )
{
	m_strConfigFile = strXMLConfigFile;
}



void CDbStatusManager::_SetXMLConfigFileFormCfg()
{
	std::string strConfigFileTmp;
	strConfigFileTmp = TA_Base_Core::CRunParams::getInstance().getStringParamValue(DEF_PARAM_RPARAM_DBCONNECTIONFILE);
	m_strConfigFile = strConfigFileTmp;
}



void CDbStatusManager::logInfo()
{
	BOOST_LOG_FUNCTION();

	boost::mutex::scoped_lock lock(m_mutexMapDataTypeDbStautsListItem);	

	

	return;
}


void CDbStatusManager::initDbStatusByCfg()
{
	_SetXMLConfigFileFormCfg();
	_ReadDataFromConfigFile();
}


void CDbStatusManager::_ReadDataFromConfigFile()
{
	int nParserRes = 0;
	boost::mutex::scoped_lock lock(m_mutexMapDataTypeDbStautsListItem);	

	nParserRes = m_pConfigXMLParser->parserConfigFile(m_strConfigFile, m_MapDataTypeDbStautsListItem);
	if (0 != nParserRes)
	{
		LOG_ERROR<<"_ReadDataFromConfigFile error!";
	}
}

void CDbStatusManager::_FreeData()
{
	boost::mutex::scoped_lock lock(m_mutexMapDataTypeDbStautsListItem);	

	BOOST_LOG_FUNCTION();
	MapDataTypeDbStautsListItemIterT iterMap;
	CDbStatusItemList* pItem = NULL;

	iterMap = m_MapDataTypeDbStautsListItem.begin();
	while (iterMap != m_MapDataTypeDbStautsListItem.end())
	{
		pItem = (iterMap->second);

		delete pItem;
		pItem = NULL;

		iterMap++;
	}

	m_MapDataTypeDbStautsListItem.clear();

	return;
}

CDbStatusItem* CDbStatusManager::getDbStatusItem(EDataTypes nDataTypes)
{
	boost::mutex::scoped_lock lock(m_mutexMapDataTypeDbStautsListItem);	

	BOOST_LOG_FUNCTION();
	MapDataTypeDbStautsListItemIterT iterMap;
	CDbStatusItemList* pDbStatusItemList = NULL;
	CDbStatusItem* pDbStatusItem = NULL;

	iterMap = m_MapDataTypeDbStautsListItem.find(nDataTypes);
	if (iterMap != m_MapDataTypeDbStautsListItem.end())
	{
		//find ok
		pDbStatusItemList = (iterMap->second);

		pDbStatusItem = pDbStatusItemList->getItem();

		iterMap++;
	}


	return pDbStatusItem;
}


NS_END(TA_Base_Core)
















