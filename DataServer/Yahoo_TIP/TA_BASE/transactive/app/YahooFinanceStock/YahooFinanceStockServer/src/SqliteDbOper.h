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


class IDbConnection;
class CDbStatusItem;

class CHistoryData;
class CSqliteDbOperBuildSQL;

class CSqliteDbOper
{
public:
	typedef QList<CHistoryData*>			LstHistoryDataT;
	typedef QList<CHistoryData*>::iterator	LstHistoryDataIterT;

public:
	CSqliteDbOper(const QString& strSymbolUse);//strSymbolUse
	virtual ~CSqliteDbOper();
public:
	int saveData(const QString& strSymbolUse, LstHistoryDataT* pLstData);
public:
	int selectData(const QString & strFrom, const QString & strTo, LstHistoryDataT& lstData);
	int selectData_MinTime(QString& strValueGet);
	int selectData_MaxTime(QString& strValueGet);
	int selectData_Count(int& nValueGet);
private:
	int _CreateDBTable_TABLE_BAR_DATA_1DAY();


private:
	QString m_strSqliteDbFileFullPath;
	QString m_strSqliteDbPath;
	IDbConnection* m_pDbConnection;
	CDbStatusItem* m_pDbStatusItem;

};


#endif //__CLASS_SQLITE_DB_OPER_H__
