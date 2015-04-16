#ifndef __CLASS_CONFIG_INFO_HELPER_H__
#define __CLASS_CONFIG_INFO_HELPER_H__ 


#include "UtilityFun.h"




NS_BEGIN(TA_Base_Test)

class CFileSystemItem;
class CParamItem;


class CConfigInfoHelper
{
private:
	typedef std::map<std::string, CParamItem*>                      MapParamKeyParamItemT;
	typedef std::map<std::string, CParamItem*>::iterator            MapParamKeyParamItemIterT;
	typedef std::map<std::string, CParamItem*>::value_type          MapParamKeyParamItemValueTypeT;
public:
	CConfigInfoHelper(const std::string& strConfigFileName);	
	~CConfigInfoHelper(void);

public:
	void logInfo();
	std::string getStringParamValue(const std::string& strParamKey);
private:
	void _FreeData(MapParamKeyParamItemT& mapParamKeyParamItemT);
	void _GetConifgFileInfo();
private:
	std::string m_strConfigFileName;
	CFileSystemItem* m_pConfigFileInfo;
	MapParamKeyParamItemT  m_MapParamKeyParamItem;

};


NS_END(TA_Base_Test)


#endif // __CLASS_CONFIG_INFO_HELPER_H__









