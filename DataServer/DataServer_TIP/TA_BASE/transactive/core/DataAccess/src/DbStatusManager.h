#ifndef __CLASS_DB_STATUS_MANAGER_H__
#define __CLASS_DB_STATUS_MANAGER_H__ 


#include "core/DataAccess/src/DataAccessCommonData.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>


NS_BEGIN(TA_Base_Core)

class CDbStatusItem;
class CDbStatusItemList;

class CConfigXMLParser;

class CDbStatusManager
{

public:
	typedef std::map<EDataTypes, CDbStatusItemList*>                      MapDataTypeDbStautsListItemT;
	typedef std::map<EDataTypes, CDbStatusItemList*>::iterator            MapDataTypeDbStautsListItemIterT;
	typedef std::map<EDataTypes, CDbStatusItemList*>::value_type          MapDataTypeDbStautsListItemTypeT;

public:
	static CDbStatusManager& getInstance();
	static void removeInstance();
public:
	void logInfo();
	void initDbStatusByCfg();
	CDbStatusItem* getDbStatusItem(EDataTypes nDataTypes);
private:
	static CDbStatusManager* m_pInstance;
	static boost::mutex m_mutexInstance;

private:
	CDbStatusManager(void);	
	~CDbStatusManager(void);

private:
	void _FreeData();
	void _ReadDataFromConfigFile();
	void _SetXMLConfigFileFormCfg();
	void _SetXMLConfigFile(const std::string& strXMLConfigFile);

private:
	boost::mutex m_mutexMapDataTypeDbStautsListItem;
	MapDataTypeDbStautsListItemT  m_MapDataTypeDbStautsListItem;

private:
	CConfigXMLParser* m_pConfigXMLParser;
	std::string m_strConfigFile;

};//class


NS_END(TA_Base_Core)


#endif // __CLASS_DB_STATUS_MANAGER_H__



















