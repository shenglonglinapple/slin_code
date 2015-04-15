#ifndef __CLASS_STOCKS_DB_OPER_H__
#define __CLASS_STOCKS_DB_OPER_H__


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
class CStockInfo;

class CStocksDbOper
{
public:
	CStocksDbOper();
	virtual ~CStocksDbOper();
public:
	int selectAllStock(QList<CStockInfo*>& lstData);
	void freeLstData(QList<CStockInfo*>& lstData);

private:
	QString m_strSqliteDbFileFullPath;
	QString m_strSqliteDbPath;
	IDbConnection* m_pDbConnection;
	CDbStatusItem* m_pDbStatusItem;

};


#endif //__CLASS_STOCKS_DB_OPER_H__
