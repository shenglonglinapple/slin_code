#include "core/CppConfigLib/src/RunParams.h"

#include <boost/algorithm/string.hpp>
#include "core/CppConfigLib/src/ParamItem.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;


NS_BEGIN(TA_Base_Core)





CRunParams* CRunParams::m_pInstance = 0;
boost::mutex CRunParams::m_mutexInstance;

CRunParams& CRunParams::getInstance()
{	
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CRunParams();
	}
	return (*m_pInstance);
}

void CRunParams::removeInstance()
{
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}



CRunParams::CRunParams(void)
{
	BOOST_LOG_FUNCTION();

	{
		_FreeData();
	}

}

CRunParams::~CRunParams(void)
{
	BOOST_LOG_FUNCTION();

	{
		_FreeData();
	}
}


void CRunParams::logInfo()
{
	BOOST_LOG_FUNCTION();

	boost::mutex::scoped_lock lock(m_mutexMapParamKeyParamItem);	

	

	return;
}




//Key=Value
void CRunParams::setParamLine(const std::string& strLine)
{
	BOOST_LOG_FUNCTION();

	std::string strParamKey;
	CParamItem* pParamItem = NULL;

	pParamItem = new CParamItem(strLine);
	strParamKey = pParamItem->getParamKey();

	setParamKeyAndParamItem(strParamKey, pParamItem);

}


void CRunParams::setParamKeyAndValue( const std::string& strParamKey, const std::string& strParamValue )
{
	BOOST_LOG_FUNCTION();

	std::string strParamKeyAndValue;
	CParamItem* pParamItem = NULL;

	strParamKeyAndValue = strParamKey + DEF_VALUE_String_ParamKeyValue_Separator + strParamValue;

	pParamItem = new CParamItem(strParamKeyAndValue);

	setParamKeyAndParamItem(strParamKey, pParamItem);
}

void CRunParams::setParamKeyAndParamItem(const std::string& strParamKey, CParamItem* pParamItem)
{
	boost::mutex::scoped_lock lock(m_mutexMapParamKeyParamItem);	

	BOOST_LOG_FUNCTION();

	MapParamKeyParamItemIterT iterMapFind;
	CParamItem* pParamItemTmp = NULL; 

	iterMapFind = m_MapParamKeyParamItem.find(strParamKey);
	if (iterMapFind != m_MapParamKeyParamItem.end())
	{
		//find Same then delete old one
		pParamItemTmp = (CParamItem*)(iterMapFind->second);
		if (NULL != pParamItemTmp)
		{
			delete pParamItemTmp;
			pParamItemTmp = NULL;
		}

	}

	pParamItemTmp = pParamItem;
	m_MapParamKeyParamItem.insert(MapParamKeyParamItemValueTypeT(strParamKey, pParamItem));

	return;
}




void CRunParams::_FreeData()
{
	boost::mutex::scoped_lock lock(m_mutexMapParamKeyParamItem);	

	BOOST_LOG_FUNCTION();
	MapParamKeyParamItemIterT iterMap;
	CParamItem* pParamItem = NULL;

	iterMap = m_MapParamKeyParamItem.begin();
	while (iterMap != m_MapParamKeyParamItem.end())
	{
		pParamItem = (iterMap->second);

		delete pParamItem;
		pParamItem = NULL;

		iterMap++;
	}

	m_MapParamKeyParamItem.clear();

	return;
}



std::string CRunParams::getStringParamValue( const std::string& strParamKey )
{
	boost::mutex::scoped_lock lock(m_mutexMapParamKeyParamItem);	
	BOOST_LOG_FUNCTION();

	std::string strParamValue;

	MapParamKeyParamItemIterT iterFind;
	CParamItem* pParamItem = NULL;
	std::string strParamKeyUpper = strParamKey;
	boost::algorithm::trim(strParamKeyUpper);
	boost::algorithm::to_upper(strParamKeyUpper);

	iterFind = m_MapParamKeyParamItem.find(strParamKeyUpper);
	if (iterFind != m_MapParamKeyParamItem.end())
	{
		//find ok
		pParamItem = (iterFind->second);

		strParamValue = pParamItem->getStringParamValue();
	}

	return strParamValue;
}

bool CRunParams::isSetParam( const std::string& strParamKey )
{
	boost::mutex::scoped_lock lock(m_mutexMapParamKeyParamItem);	

	BOOST_LOG_FUNCTION();
	bool bIsSetParam = false;
	std::string strParamValue;

	MapParamKeyParamItemIterT iterFind;
	CParamItem* pParamItem = NULL;
	std::string strParamKeyUpper = strParamKey;
	boost::algorithm::trim(strParamKeyUpper);
	boost::algorithm::to_upper(strParamKeyUpper);

	iterFind = m_MapParamKeyParamItem.find(strParamKeyUpper);
	if (iterFind != m_MapParamKeyParamItem.end())
	{
		//find ok
		pParamItem = (iterFind->second);

		strParamValue = pParamItem->getStringParamValue();
		bIsSetParam = true;
	}

	return bIsSetParam;
}



NS_END(TA_Base_Core)
















