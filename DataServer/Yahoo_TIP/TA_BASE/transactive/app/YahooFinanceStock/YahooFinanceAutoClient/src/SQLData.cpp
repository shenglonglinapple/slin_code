#include "SQLData.h"

#include "Log4cppLogger.h"

static const char*   DEF_VALUE_STR_DBTYPE_QSQLITE = "QSQLITE";
static const char*   DEF_VALUE_STR_DBTYPE_QMYSQL = "QMYSQL";


CSQLData::CSQLData()
{
	m_strSQLKey.clear();
	m_strSQL_QSQLITE.clear();
	m_strSQL_QMYSQL.clear();
}

CSQLData::~CSQLData()
{
	m_strSQLKey.clear();
	m_strSQL_QSQLITE.clear();
	m_strSQL_QMYSQL.clear();
}

CSQLData& CSQLData::operator=( const CSQLData& objectCopy )
{
	m_strSQLKey = objectCopy.m_strSQLKey;
	m_strSQL_QSQLITE = objectCopy.m_strSQL_QSQLITE;
	m_strSQL_QMYSQL = objectCopy.m_strSQL_QMYSQL;

	return *this;
}

void CSQLData::setSQLKeyValue(const QString& strSQLKeyValue)
{
	m_strSQLKey = strSQLKeyValue.trimmed();
}
void CSQLData::setValue(const QString& strDBType, const QString& strSQL)
{
	if (strDBType.toUpper() == QString(DEF_VALUE_STR_DBTYPE_QSQLITE).toUpper())
	{
		m_strSQL_QSQLITE = strSQL.trimmed();
	}
	else if (strDBType.toUpper() == QString(DEF_VALUE_STR_DBTYPE_QMYSQL).toUpper())
	{
		m_strSQL_QMYSQL = strSQL.trimmed();
	}
	else
	{
		MYLOG4CPP_ERROR<<"error! not support strDBType="<<strDBType
			<<" "<<"strSQL="<<strSQL
			<<" "<<"just support dbtype "<<DEF_VALUE_STR_DBTYPE_QSQLITE
			<<" "<<DEF_VALUE_STR_DBTYPE_QMYSQL;
	}
}

QString CSQLData::getSQLKey()
{
	return m_strSQLKey;
}

