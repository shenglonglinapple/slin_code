#include "core/CppConfigLib/src/ParamItem.h"
#include <sstream>
#include <boost/algorithm/string.hpp>

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)



CParamItem::CParamItem( const std::string& strParamLine )
{
	m_strParamLine.clear();
	m_strParam.clear();
	m_strParamValue.clear();

	m_strParamLine = strParamLine;

	_ProcessParamLine();
}

CParamItem::~CParamItem( void )
{
	m_strParamLine.clear();
	m_strParam.clear();
	m_strParamValue.clear();


}
int CParamItem::_ProcessParamLine()
{
	int nFunRes = 0;

	typedef boost::tokenizer<boost::char_separator<char> > tokenizer; 
	boost::char_separator<char> sep("="); //DEF_VALUE_String_ParamKeyValue_Separator
	tokenizer tok(m_strParamLine, sep); 
	for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it) 
	{
		if (m_strParam.empty())
		{
			m_strParam = (*it);
			boost::algorithm::trim(m_strParam);
			boost::algorithm::to_upper(m_strParam);
		}
		else
		{
			m_strParamValue = (*it);
		}
	}

	return nFunRes;
}
std::string CParamItem::getParamKey()
{
	return m_strParam;//upper
}

std::string CParamItem::getStringParamValue()
{
	return m_strParamValue;
}



NS_END(TA_Base_Core)
















