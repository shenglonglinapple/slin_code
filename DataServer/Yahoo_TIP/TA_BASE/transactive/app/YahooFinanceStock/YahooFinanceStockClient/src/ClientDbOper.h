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

class CSqliteDbOperBuildSQL;
class CUserInfo;
class CUserTradeInfo;
class CHistoryData;
class CStockMinTimeMaxTime;
class CUserAccount;
class CUserHoldAccount;

class CClientDbOper
{
public:
	CClientDbOper(const QString& strSqliteDbFileName);
	virtual ~CClientDbOper();
public:
	void resetDataHistory(const QString& strSymbolUse, const QList<CHistoryData*>& lstData);
	qint32 selectDataHistory_ASC_PRICE(const QString& strSymbolUse, CHistoryData** ppData);
	qint32 selectDataHistory_DataTime(const QString& strSymbolUse,const QString& strDateTime, CHistoryData** ppData);
	void truncateTableHistoryData();
public:
	qint32 insertSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
	qint32 updateSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
	qint32 selectSymbolMinMaxTime(const QString& strSymbolUse, CStockMinTimeMaxTime** ppData);
	void truncateSymbolMinMaxTime();
public:
	qint32 insertUserTradeInfo(const CUserTradeInfo* pData);
	void truncateTableUserTradeInfo();
public:
	qint32 resetUserAccount( const CUserAccount* pData );
	qint32 insertUserAccount(const CUserAccount* pData );
public:
	qint32 resetUserHoldAccount( const QList<CUserHoldAccount*>& lstData );

public:
	QSqlDatabase* getDB();
private:
	void _UnInitDataBase();
	void _InitDataBase();
	int _StartTransaction();
	int _CommitTransaction();
	qint32 _ExecModify(const QString& strSQL);

private:
	qint32 _CreateDBTable_TABLE_USER_TRADE_INFO();
	qint32 _AddUserTradeInfo(const CUserTradeInfo* pData);
	qint32 _CreateDBTable_TABLE_BAR_DATA_1DAY();
	qint32 _AddHistoryDataLst(const QList<CHistoryData*>& lstData);
	qint32 _CreateDBTable_TABLE_MINTIME_MAXTIME();
	qint32 _AddSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
	qint32 _CreateDBTable_TABLE_USER_ACCOUNT();
	qint32 _Truncate_TABLE_USER_ACCOUNT();
	qint32 _AddUserAccount( const CUserAccount* pData );
	qint32 _CreateDBTable_TABLE_USER_HOLD_ACCOUNT();
	qint32 _Truncate_TABLE_USER_HOLD_ACCOUNT();
	qint32 _AddUserHoldAccountLst(const QList<CUserHoldAccount*>& lstData );

private:
	QSqlDatabase* m_pQSqlDataBase;
	QString m_strQTDbType;//"QSQLITE" "QMYSQL"
	QString m_strSqliteDbFileName;
	QString m_strSqliteDbKEY;
	QString m_strSqliteDbFileFullPath;
	QString m_strSqliteDbPath;
	
private:
	CSqliteDbOperBuildSQL* m_pSqliteDbOperBuildSQL;
private:
	QSqlTableModel* m_pSqlTableModel_HistoryData;
};


#endif //__CLASS_CLIENT_DB_OPER_H__
