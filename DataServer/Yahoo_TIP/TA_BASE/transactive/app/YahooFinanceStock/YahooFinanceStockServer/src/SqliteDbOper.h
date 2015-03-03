#ifndef __CLASS_SQLITE_DB_OPER_H__
#define __CLASS_SQLITE_DB_OPER_H__


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

#include "ProjectSQLManager.h"

class CHistoryData;
class CSqliteDbOperBuildSQL;

class CSqliteDbOper
{
public:
	typedef QList<CHistoryData*>			LstHistoryDataT;
	typedef QList<CHistoryData*>::iterator	LstHistoryDataIterT;

public:
	CSqliteDbOper(const QString& strSqliteDbFileName);//strSymbolUse
	virtual ~CSqliteDbOper();
public:
	void saveData(const QString& strSymbolUse, LstHistoryDataT* pLstData);
public:
	int selectData(const QString & strFrom, const QString & strTo, LstHistoryDataT& lstData);
	int selectData_MinTime(QString& strValueGet);
	int selectData_MaxTime(QString& strValueGet);
	int selectData_Count(int& nValueGet);

private:
	void _UnInitDataBase();
	void _InitDataBase();
	int _StartTransaction();
	int _CommitTransaction();
	qint32 _ExecModify(const CSQLData& sqlData);
private:
	int _AddDataArray(const QString& strSymbolUse,LstHistoryDataT* pLstData);
	int _CreateDBTable_TABLE_BAR_DATA_1DAY();

private:
	QSqlDatabase* m_pQSqlDataBase;
	QString m_strQTDbType;//"QSQLITE" "QMYSQL"
	QString m_strSqliteDbFileName;
	QString m_strSqliteDbKEY;
	QString m_strSqliteDbFileFullPath;
	QString m_strSqliteDbPath;
	
};


#endif //__CLASS_SQLITE_DB_OPER_H__
