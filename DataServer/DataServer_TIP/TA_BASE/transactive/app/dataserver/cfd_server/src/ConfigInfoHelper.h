#ifndef __CLASS_CONFIG_INFO_HELPER_H__
#define __CLASS_CONFIG_INFO_HELPER_H__ 


#include "CFDServerCommonData.h"


#include <boost/filesystem.hpp>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/tokenizer.hpp"

////////QT_BEGIN_NAMESPACE

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


//////QT_END_NAMESPACE


#endif // __CLASS_CONFIG_INFO_HELPER_H__









