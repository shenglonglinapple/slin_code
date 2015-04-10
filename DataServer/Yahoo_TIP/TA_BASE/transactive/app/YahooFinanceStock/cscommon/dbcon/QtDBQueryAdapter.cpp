#include "QtDBQueryAdapter.h"

#include <QtSql/QtSql>
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QUuid>


CQtDBQueryAdapter::CQtDBQueryAdapter( QSqlQuery* pQuery )
{
	QUuid newUuid = QUuid::createUuid();
	m_strQueryUUID = newUuid.toString();

	m_pQuery = pQuery;
	//if (m_pQuery->isSelect())
	
	_GetAllColumnName();
}

CQtDBQueryAdapter::~CQtDBQueryAdapter()
{
	if (NULL != m_pQuery)
	{
		delete m_pQuery;
		m_pQuery = NULL;
	}
	m_LstColumnName.clear();
	m_mapColumnNameValue.clear();
}
QString CQtDBQueryAdapter::getQueryUUID()
{
	return m_strQueryUUID;
}

void CQtDBQueryAdapter::_GetAllColumnName()
{
	QSqlRecord rec;
	QString strColumName;
	m_nColumnCount = 0;

	rec = m_pQuery->record();
	m_nColumnCount = rec.count();

	for (qint32 nIndex = 0; nIndex < m_nColumnCount; nIndex++)
	{
		strColumName.clear();
		strColumName = rec.fieldName(nIndex);
		m_LstColumnName.append(strColumName);
	}
}

QStringList CQtDBQueryAdapter::getLstColumnName()
{
	return m_LstColumnName;
}

qint32 CQtDBQueryAdapter::getColumnCount()
{
	return m_nColumnCount;
}


bool CQtDBQueryAdapter::isNull( const QString & fieldName )
{
	bool bFunRes = true;
	QSqlRecord rec;
	rec = m_pQuery->record();

	bFunRes = rec.isNull(fieldName);
	return bFunRes;
}


bool CQtDBQueryAdapter::hasMore()
{
	bool bFunRes = true;
	QString strColumName;
	QString strColumValue;

	if (NULL == m_pQuery)
	{
		bFunRes = false;
		return bFunRes;
	}

	m_mapColumnNameValue.clear();
	bFunRes = m_pQuery->next();

	if (bFunRes)
	{
		for (qint32 nIndex = 0; nIndex < m_nColumnCount; nIndex++)
		{
			strColumName = m_LstColumnName[nIndex];
			strColumValue = m_pQuery->value(nIndex).toString();
			m_mapColumnNameValue.insert(strColumName, strColumValue);
		}
	}
	return bFunRes;
}

QString CQtDBQueryAdapter::getStringData(const QString& fieldName, const QString defaultValue /*= ""*/ )
{
	QString strValue = defaultValue;
	bool bNullColumn = true;
	
	bNullColumn = isNull(fieldName);
	if (bNullColumn)
	{
		return strValue;
	}

	strValue = m_mapColumnNameValue[fieldName];

	return strValue;
}

