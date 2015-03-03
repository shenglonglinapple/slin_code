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
	QString getSQLKey() const;
	QString getSqliteSQL() const;
	void clear();
public:
	qint32 buildSQL();
	qint32 buildSQL(const QString& arg0);
	qint32 buildSQL(const QString& arg0, const QString& arg1);
	qint32 buildSQL(const QString& arg0, const QString& arg1,const QString& arg2);
	qint32 buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, const QString& arg3);
	qint32 buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4);
	qint32 buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4, const QString& arg5 );
	qint32 buildSQL( const QString& arg0, const QString& arg1, const QString& arg2, const QString& arg3, const QString& arg4, const QString& arg5, const QString& arg6);
private:
	QString m_strXMLSQLKey;
	QString m_strXMLSQL_QSQLITE;
	QString m_strXMLSQL_QMYSQL;
private:
	QString m_strUseSQL_QSQLITE;
	QString m_strUseSQL_QMYSQL;
};


#endif //__CLASS_SQL_DATA_H__
