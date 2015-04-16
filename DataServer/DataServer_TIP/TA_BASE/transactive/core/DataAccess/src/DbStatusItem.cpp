#include "DbStatusItem.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)


CDbStatusItem::CDbStatusItem()
{
	clear();
}

CDbStatusItem::~CDbStatusItem()
{
	clear();
}

CDbStatusItem& CDbStatusItem::operator=( const CDbStatusItem& objectCopy )
{
	m_nDataTypes = objectCopy.m_nDataTypes;
	m_nDbServerPriority = objectCopy.m_nDbServerPriority;
	m_nDbServerType = objectCopy.m_nDbServerType;
	m_nDbServerState = objectCopy.m_nDbServerState;
	m_strDBConnectionStringLine = objectCopy.m_strDBConnectionStringLine;
	m_strDbType = objectCopy.m_strDbType;
	m_strSchema = objectCopy.m_strSchema;
	m_strUser = objectCopy.m_strUser;
	m_strPassword = objectCopy.m_strPassword;
	m_strIP = objectCopy.m_strIP;

	return *this;
}

void CDbStatusItem::clear()
{
	m_nDataTypes = DataTypes_DbSync;
	m_nDbServerPriority = DbServerPriority_0;
	m_nDbServerType = DbServerType_OracleDb;
	m_nDbServerState = DbServerState_Online;
	m_strDBConnectionStringLine.clear();
	m_strDbType.clear();
	m_strSchema.clear();
	m_strUser.clear();
	m_strPassword.clear();
	m_strIP.clear();

}


void  CDbStatusItem::logInfo(const std::string& strLogInfo)
{
	LOG_DEBUG<<"CDbStatusItem Info:"
		<<" "<<"strLogInfo="<<strLogInfo
		<<" "<<"m_nDataTypes="<<m_nDataTypes
		<<" "<<"m_nDbServerPriority="<<m_nDbServerPriority
		<<" "<<"m_nDbServerType="<<m_nDbServerType
		<<" "<<"m_nDbServerState="<<m_nDbServerState
		<<" "<<"m_strDBConnectionStringLine="<<m_strDBConnectionStringLine
		<<" "<<"m_strDbType="<<m_strDbType
		<<" "<<"m_strSchema="<<m_strSchema
		<<" "<<"m_strUser="<<m_strUser
		<<" "<<"m_strPassword="<<m_strPassword
		<<" "<<"m_strIP="<<m_strIP;	
}

std::string  CDbStatusItem::getConnectionString()
{
	//DefConStrDelimiter=":"
	m_strDBConnectionStringLine = m_nDbServerType + DefConStrDelimiter 
		+ m_strSchema + DefConStrDelimiter 
		+ m_strUser + DefConStrDelimiter 
		+ m_strPassword + DefConStrDelimiter 
		+ m_strIP;

	return m_strDBConnectionStringLine;
}

bool CDbStatusItem::isValid()
{
	bool bIsValid = true;

	if (m_strDbType.empty() || 
		m_strSchema.empty() ||
		m_strUser.empty() ||
		m_strPassword.empty() ||
		m_strIP.empty())
	{
		std::string strLogInfo = "connection cfg error!";
		logInfo(strLogInfo);
		bIsValid = false;
	}

	return bIsValid;

}

NS_END(TA_Base_Core)



