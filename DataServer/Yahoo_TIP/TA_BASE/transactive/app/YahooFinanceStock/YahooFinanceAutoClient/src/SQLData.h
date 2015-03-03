#ifndef __CLASS_SQL_DATA_H__
#define __CLASS_SQL_DATA_H__

#include <QtCore/QString>
#include <QtCore/QStringList>

class CSQLData
{
public:
	CSQLData();
	virtual ~CSQLData();
public:
	CSQLData& operator=(const CSQLData& objectCopy);
public:
	void setSQLKeyValue(const QString& strSQLKeyValue);
	void setXMLValue(const QString& strDBType, const QString& strSQL);
public:
	QString getSQLKey();
	void clear();
public:
	qint32 buildSQL();
	qint32 buildSQL(const QString& arg0);
	qint32 buildSQL(const QString& arg0, const QString& arg1);

private:
	QString m_strXMLSQLKey;
	QString m_strXMLSQL_QSQLITE;
	QString m_strXMLSQL_QMYSQL;
private:
	QString m_strUseSQL_QSQLITE;
	QString m_strUseSQL_QMYSQL;
};


#endif //__CLASS_SQL_DATA_H__
