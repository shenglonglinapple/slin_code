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
	void setValue(const QString& strDBType, const QString& strSQL);
public:
	QString getSQLKey();
	
private:
	QString m_strSQLKey;
	QString m_strSQL_QSQLITE;
	QString m_strSQL_QMYSQL;
};


#endif //__CLASS_SQL_DATA_H__
