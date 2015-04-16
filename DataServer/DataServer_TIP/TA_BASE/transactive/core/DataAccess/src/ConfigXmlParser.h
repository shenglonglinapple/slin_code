#ifndef __CLASS_CONFIG_XML_PARSER_HH__
#define __CLASS_CONFIG_XML_PARSER_HH__



#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/DbStatusManager.h"

NS_BEGIN(TA_Base_Core)

class CConfigXMLParser
{
public:
	CConfigXMLParser(); 
	~CConfigXMLParser();
public:
	int parserConfigFile(const std::string& strFileName, CDbStatusManager::MapDataTypeDbStautsListItemT& mapDataTypeDbStautsList);
	EDataTypes getDataTypesByString(const std::string& strDataTypes);
	EDbServerPriority getDbServerPriorityByInt(int nPriority);
	EDbServerType getDbServerTypeByString(const std::string& strDbServerType);
};

NS_END(TA_Base_Core)

#endif//__CLASS_CONFIG_XML_PARSER_HH__