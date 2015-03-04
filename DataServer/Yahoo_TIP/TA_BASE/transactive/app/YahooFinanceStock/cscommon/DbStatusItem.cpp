#include "DbStatusItem.h"

#include "Log4cppLogger.h"

static const char* DefConStrDelimiter = ":";

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
	m_nDataType = objectCopy.m_nDataType;
	m_nDBPriority = objectCopy.m_nDBPriority;
	m_nDBType = objectCopy.m_nDBType;
	m_nDBState = objectCopy.m_nDBState;
	m_strDBConnectionString = objectCopy.m_strDBConnectionString;
	m_strDbType = objectCopy.m_strDbType;
	m_strSchema = objectCopy.m_strSchema;
	m_strUser = objectCopy.m_strUser;
	m_strPassword = objectCopy.m_strPassword;
	m_strIP = objectCopy.m_strIP;

	return *this;
}

void CDbStatusItem::clear()
{
	m_nDataType = DataTypes_CSData;
	m_nDBPriority = DBPriority_0;
	m_nDBType = DBType_QSQLITE;
	m_nDBState = EDBState_Pending;
	m_strDBConnectionString.clear();
	m_strDbType.clear();
	m_strSchema.clear();
	m_strUser.clear();
	m_strPassword.clear();
	m_strIP.clear();

}

void CDbStatusItem::logInfo( const QString& file, qint32 line )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<file<<":"<<line<<"]"<<" "
		<<" "<<"m_nDataType="<<getString(m_nDataType)
		<<" "<<"m_nDBPriority="<<getString(m_nDBPriority)
		<<" "<<"m_nDBType="<<getString(m_nDBType)
		<<" "<<"m_nDBState="<<getString(m_nDBState)
		<<" "<<"m_strDBConnectionString="<<m_strDBConnectionString
		<<" "<<"m_strDbType="<<m_strDbType
		<<" "<<"m_strSchema="<<m_strSchema
		<<" "<<"m_strUser="<<m_strUser
		<<" "<<"m_strPassword="<<m_strPassword
		<<" "<<"m_strIP="<<m_strIP;

}

QString  CDbStatusItem::getConnectionString()
{
	//DefConStrDelimiter=":"
	m_strDBConnectionString = m_strDbType + DefConStrDelimiter 
		+ m_strSchema + DefConStrDelimiter 
		+ m_strUser + DefConStrDelimiter 
		+ m_strPassword + DefConStrDelimiter 
		+ m_strIP;

	return m_strDBConnectionString;
}

bool CDbStatusItem::isValid()
{
	bool bIsValid = true;

	if (m_strDbType.isEmpty() || 
		m_strSchema.isEmpty() ||
		m_strUser.isEmpty() ||
		m_strPassword.isEmpty() ||
		m_strIP.isEmpty())
	{
		logInfo(__FILE__, __LINE__);
		MYLOG4CPP_ERROR<<"connection cfg error!";
		bIsValid = false;
	}

	return bIsValid;

}

QString CDbStatusItem::getString( EDBType nValue )
{
	QString strValue;

	switch (nValue)
	{
	case DBType_QSQLITE:
		strValue = QString("DBType_QSQLITE");
		break;
	case DBType_QMYSQL:
		strValue = QString("DBType_QMYSQL");
		break;
	default:
		strValue = QString("Error! EDBType nValue=%1").arg(nValue);
		break;
	}

	return strValue;
}

QString CDbStatusItem::getString( EDBState nValue )
{
	QString strValue;

	switch (nValue)
	{
	case EDBState_Pending:
		strValue = QString("EDBState_Pending");
		break;
	case EDBState_Online:
		strValue = QString("EDBState_Online");
		break;
	case EDBState_Offline:
		strValue = QString("EDBState_Offline");
		break;
	default:
		strValue = QString("Error! EDBState nValue=%1").arg(nValue);
		break;
	}

	return strValue;
}

QString CDbStatusItem::getString( EDataTypes nValue )
{
	QString strValue;

	switch (nValue)
	{
	case DataTypes_CSData:
		strValue = QString("DataTypes_CSData");
		break;
	case DataTypes_YahuoData:
		strValue = QString("DataTypes_YahuoData");
		break;
	default:
		strValue = QString("Error! EDataTypes nValue=%1").arg(nValue);
		break;
	}

	return strValue;
}

QString CDbStatusItem::getString( EDBPriority nValue )
{
	QString strValue;

	switch (nValue)
	{
	case DBPriority_0:
		strValue = QString("DBPriority_0");
		break;
	case DBPriority_1:
		strValue = QString("DBPriority_1");
		break;
	default:
		strValue = QString("Error! EDBPriority nValue=%1").arg(nValue);
		break;
	}

	return strValue;
}



