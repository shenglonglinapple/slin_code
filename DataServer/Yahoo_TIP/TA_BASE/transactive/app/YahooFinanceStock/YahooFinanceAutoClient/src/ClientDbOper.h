#ifndef __CLASS_CLIENT_DB_OPER_H__
#define __CLASS_CLIENT_DB_OPER_H__


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

class CUserInfo;
class CUserTradeInfo;
class CHistoryData;
class CStockMinTimeMaxTime;
class CUserAccount;
class CUserHoldAccount;
class CStockInfo;

class CClientDbOper
{
public:
	CClientDbOper(const QString& strUserID);//m_strUserID
	virtual ~CClientDbOper();
public:
	void reset_TABLE_BAR_DATA_1DAY(const QString& strSymbolUse, const QList<CHistoryData*>& lstData);
	void truncate_TABLE_BAR_DATA_1DAY();
public:
	qint32 insertSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
	qint32 updateSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
	qint32 selectSymbolMinMaxTime(const QString& strSymbolUse, CStockMinTimeMaxTime** ppData);
	void truncateSymbolMinMaxTime();
public:
	qint32 insertUserTradeInfo(const CUserTradeInfo* pData);
	void truncate_TABLE_USER_TRADE_INFO();
public:
	qint32 resetUserAccount( const CUserAccount* pData );
	qint32 insertUserAccount(const CUserAccount* pData );
public:
	qint32 resetUserHoldAccount( const QList<CUserHoldAccount*>& lstData );
public:
	qint32 resetAllStockInfo(const QList<CStockInfo*>& lstData);

private:
	//
	qint32 _CreateDBTable_TABLE_STOCKSSQLITE();
	qint32 _Truncate_TABLE_STOCKSSQLITE();
	qint32 _AddStockInfoList( const QList<CStockInfo*>& lstData );
	//
	qint32 _CreateDBTable_TABLE_USER_TRADE_INFO();
	qint32 _CreateDBTable_TABLE_BAR_DATA_1DAY();
	qint32 _AddHistoryDataLst(const QList<CHistoryData*>& lstData);
	qint32 _CreateDBTable_TABLE_MINTIME_MAXTIME();
	qint32 _CreateDBTable_TABLE_USER_ACCOUNT();
	qint32 _Truncate_TABLE_USER_ACCOUNT();
	qint32 _CreateDBTable_TABLE_USER_HOLD_ACCOUNT();
	qint32 _Truncate_TABLE_USER_HOLD_ACCOUNT();
	qint32 _AddUserHoldAccountLst(const QList<CUserHoldAccount*>& lstData );

private:
	QString m_strSqliteDbFileFullPath;
	QString m_strSqliteDbPath;
	IDbConnection* m_pDbConnection;
	CDbStatusItem* m_pDbStatusItem;
};


#endif //__CLASS_CLIENT_DB_OPER_H__
