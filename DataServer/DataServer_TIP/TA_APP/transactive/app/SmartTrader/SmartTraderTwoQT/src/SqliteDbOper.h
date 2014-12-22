#ifndef __CLASS_SQLITE_DB_OPER_H__
#define __CLASS_SQLITE_DB_OPER_H__

#include <string>

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

class CHistoryData;

class CSqliteDbOper
{
public:
	typedef std::list<CHistoryData*>	LstHistoryDataT;
	typedef std::list<CHistoryData*>::iterator	LstHistoryDataIterT;

public:
	CSqliteDbOper();
	virtual ~CSqliteDbOper();
public:
	void setDataBaseValue(const QString& strSqliteDbFileName);

	void resetDataBaseValue(const QString& strSqliteDbFileName);
	
	void saveData(LstHistoryDataT* pLstData);
public:
	int selectData(const std::string& strFrom, const std::string& strTo, LstHistoryDataT& lstData);

private:
	void _UnInitDataBase();
	void _InitDataBase();
	int _StartTransaction();
	int _CommitTransaction();
	int _CreateDBTable();
	std::string _BuildSQL_CreateTable();
	std::string _BuildSQL_Insert();
	int _AddDataArray(LstHistoryDataT* pLstData);
	std::string _BuildSQL_Select(const std::string& strFrom, const std::string& strTo);
private:
	QSqlDatabase* m_pQSqlDataBase;
	QString m_strQTDbType;//"QSQLITE" "QMYSQL"
	QString m_strSqliteDbFileName;
	QString m_strSqliteDbKEY;
	QString m_strSqliteDbFileFullPath;
	QString m_strSqliteDbPath;
	

};


#endif //__CLASS_SQLITE_DB_OPER_H__
