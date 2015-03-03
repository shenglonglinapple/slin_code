#include "SQLData.h"
#include "Log4cppLogger.h"

static const char*   DEF_VALUE_STR_DBTYPE_QSQLITE = "QSQLITE";
static const char*   DEF_VALUE_STR_DBTYPE_QMYSQL = "QMYSQL";


CSQLData::CSQLData()
{
	clear();
}

CSQLData::~CSQLData()
{
	clear();
}


CSQLData& CSQLData::operator=( const CSQLData& objectCopy )
{
	m_strXMLSQLKey = objectCopy.m_strXMLSQLKey;
	m_strXMLSQL_QSQLITE = objectCopy.m_strXMLSQL_QSQLITE;
	m_strXMLSQL_QMYSQL = objectCopy.m_strXMLSQL_QMYSQL;

	m_strUseSQL_QSQLITE = objectCopy.m_strUseSQL_QSQLITE;
	m_strUseSQL_QMYSQL = objectCopy.m_strUseSQL_QMYSQL;

	return *this;
}

void CSQLData::clear()
{
	m_strXMLSQLKey.clear();
	m_strXMLSQL_QSQLITE.clear();
	m_strXMLSQL_QMYSQL.clear();

	m_strUseSQL_QSQLITE.clear();
	m_strUseSQL_QMYSQL.clear();
}


void CSQLData::setSQLKeyValue(const QString& strSQLKeyValue)
{
	m_strXMLSQLKey = strSQLKeyValue.trimmed();
	m_strXMLSQLKey = strSQLKeyValue.toUpper();
}
void CSQLData::setXMLValue(const QString& strDBType, const QString& strSQL)
{
	if (strDBType.toUpper() == QString(DEF_VALUE_STR_DBTYPE_QSQLITE).toUpper())
	{
		m_strXMLSQL_QSQLITE = strSQL.trimmed();
	}
	else if (strDBType.toUpper() == QString(DEF_VALUE_STR_DBTYPE_QMYSQL).toUpper())
	{
		m_strXMLSQL_QMYSQL = strSQL.trimmed();
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
	return m_strXMLSQLKey;
}

qint32 CSQLData::buildSQL()
{
	qint32 nFunRes = 0;

	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL);

	return nFunRes;
}

qint32 CSQLData::buildSQL( const QString& arg0 )
{
	qint32 nFunRes = 0;

	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE).arg(arg0);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL).arg(arg0);

	return nFunRes;
}

qint32 CSQLData::buildSQL( const QString& arg0, const QString& arg1 )
{
	qint32 nFunRes = 0;

	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE).arg(arg0).arg(arg1);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL).arg(arg0).arg(arg1);

	return nFunRes;
}

