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

QString CSQLData::getSQLKey() const
{
	return m_strXMLSQLKey;
}
QString CSQLData::getSqliteSQL() const
{
	return m_strUseSQL_QSQLITE;
}

//////////////////////////////////////////////////////////////////////////
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

qint32 CSQLData::buildSQL( const QString& arg0, const QString& arg1,const QString& arg2 )
{
	qint32 nFunRes = 0;

	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE).arg(arg0).arg(arg1).arg(arg2);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL).arg(arg0).arg(arg1).arg(arg2);

	return nFunRes;
}
qint32 CSQLData::buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, const QString& arg3)
{
	qint32 nFunRes = 0;

	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE).arg(arg0).arg(arg1).arg(arg2).arg(arg3);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL).arg(arg0).arg(arg1).arg(arg2).arg(arg3);

	return nFunRes;
}

qint32 CSQLData::buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4 )
{
	qint32 nFunRes = 0;

	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4);

	return nFunRes;
}

qint32 CSQLData::buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, 
						  const QString& arg3, const QString& arg4, const QString& arg5 )
{
	qint32 nFunRes = 0;

	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5);

	return nFunRes;
}
qint32 CSQLData::buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, 
						  const QString& arg3, const QString& arg4, const QString& arg5, const QString& arg6)
{
	qint32 nFunRes = 0;
	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5).arg(arg6);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5).arg(arg6);
	return nFunRes;
}

qint32 CSQLData::buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, 
						  const QString& arg3, const QString& arg4, const QString& arg5, 
						  const QString& arg6, const QString& arg7)
{
	qint32 nFunRes = 0;
	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5).arg(arg6).arg(arg7);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5).arg(arg6).arg(arg7);
	return nFunRes;
}
qint32 CSQLData::buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, 
						  const QString& arg3, const QString& arg4, const QString& arg5,
						  const QString& arg6, const QString& arg7, const QString& arg8)
{
	qint32 nFunRes = 0;
	m_strUseSQL_QSQLITE = QString(m_strXMLSQL_QSQLITE).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5).arg(arg6).arg(arg7).arg(arg8);
	m_strUseSQL_QMYSQL = QString(m_strXMLSQL_QMYSQL).arg(arg0).arg(arg1).arg(arg2).arg(arg3).arg(arg4).arg(arg5).arg(arg6).arg(arg7).arg(arg8);
	return nFunRes;
}

void CSQLData::logInfo( const QString& fileName, qint32 lineNumber ) const
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CReqLogin:"
		<<" "<<"m_strXMLSQLKey="<<m_strXMLSQLKey
		<<" "<<"m_strXMLSQL_QSQLITE="<<m_strXMLSQL_QSQLITE
		<<" "<<"m_strXMLSQL_QMYSQL="<<m_strXMLSQL_QMYSQL
		<<" "<<"m_strUseSQL_QSQLITE="<<m_strUseSQL_QSQLITE
		<<" "<<"m_strUseSQL_QMYSQL="<<m_strUseSQL_QMYSQL;
}
