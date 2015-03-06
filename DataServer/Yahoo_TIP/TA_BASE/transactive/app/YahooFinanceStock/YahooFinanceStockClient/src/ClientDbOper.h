#ifndef __CLASS_CLIENT_DB_OPER_H__
#define __CLASS_CLIENT_DB_OPER_H__


#include <QtSql/QtSql>
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>

#include "ProjectSQLManager.h"

class IDbConnection;
class CQtDBConnection;
class CDbStatusItem;
class QSqlDatabase;

class CUserInfo;
class CUserTradeInfo;
class CHistoryData;
class CStockMinTimeMaxTime;
class CUserAccount;
class CUserHoldAccount;

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
	qint32 resetSymbolUse(const QList<QString>& lstData);
	qint32 getSymbolUseLst(QList<QString>& lstData);
public:
	QSqlDatabase* getDB();
private:
	//
	qint32 _CreateDBTable_TABLE_SYMBOLUSE();
	qint32 _Truncate_TABLE_SYMBOLUSE();
	qint32 _AddSymbolLst(const QList<QString>& lstData);

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
	CQtDBConnection* m_pDbConnectionQtRef;
	CDbStatusItem* m_pDbStatusItem;
};


#endif //__CLASS_CLIENT_DB_OPER_H__
