#ifndef _CLASS_DB_STATUS_ITEM_H__
#define _CLASS_DB_STATUS_ITEM_H__

#include <iostream>
#include "core/DataAccess/src/DataAccessCommonData.h"

NS_BEGIN(TA_Base_Core)

class CDbStatusItem
{
public:
	CDbStatusItem();
	~CDbStatusItem();
public:
	CDbStatusItem& operator=(const CDbStatusItem& objectCopy);
public:
	EDataTypes m_nDataTypes;
	EDbServerPriority m_nDbServerPriority;
	EDbServerType m_nDbServerType;
	EDbServerState m_nDbServerState;
	std::string m_strDBConnectionStringLine;
	
	std::string m_strDbType;
	std::string m_strSchema;
	std::string m_strUser;
	std::string m_strPassword;
	std::string m_strIP;
	

public:
	void clear();
	void logInfo(const std::string& strLogInfo);
	std::string getConnectionString();
	bool isValid();
};//class SQLStatement

NS_END(TA_Base_Core)

#endif //_CLASS_DB_STATUS_ITEM_H__



