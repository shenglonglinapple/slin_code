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

class CHistoryData;

class CSqliteDbOper
{
public:
	typedef QList<CHistoryData*>			LstHistoryDataT;
	typedef QList<CHistoryData*>::iterator	LstHistoryDataIterT;

public:
	CSqliteDbOper(const QString& strSqliteDbFileName);
	virtual ~CSqliteDbOper();
public:
	void saveData(LstHistoryDataT* pLstData);
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
	int _CreateDBTable();
	int _AddDataArray(LstHistoryDataT* pLstData);
private:
	QString _BuildSQL_CreateTable();
	QString _BuildSQL_Insert();
	QString _BuildSQL_Select(const QString & strFrom, const QString & strTo);
	QString _BuildSQL_Select_COLUMN_DATE_by_DESC();
	QString _BuildSQL_Select_COLUMN_DATE_by_ASC();
	QString _BuildSQL_Select_Count();
private:
	QSqlDatabase* m_pQSqlDataBase;
	QString m_strQTDbType;//"QSQLITE" "QMYSQL"
	QString m_strSqliteDbFileName;
	QString m_strSqliteDbKEY;
	QString m_strSqliteDbFileFullPath;
	QString m_strSqliteDbPath;
	

};


#endif //__CLASS_SQLITE_DB_OPER_H__
