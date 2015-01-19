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

class CClientDbOper
{
public:
	CClientDbOper(const QString& strSqliteDbFileName);
	virtual ~CClientDbOper();
public:
	void resetDataHistory(const QString& strSymbolUse, const QList<CHistoryData*>& lstData);
	qint32 selectDataHistory_ASC_PRICE(const QString& strSymbolUse, CHistoryData** ppData);
	void truncateTableHistoryData();
public:
	qint32 insertSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
	qint32 updateSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
	qint32 selectSymbolMinMaxTime(const QString& strSymbolUse, CStockMinTimeMaxTime** ppData);
	void truncateSymbolMinMaxTime();

public:
	qint32 selectUserInfo(quint16 nListenPort,const QString & strUSERNAME, const QString& strPASSWORD, CUserInfo** ppData);
	qint32 updateUserInfo(quint16 nListenPort, const CUserInfo* pData);
	qint32 insertUserInfo(quint16 nListenPort, const CUserInfo* pData);
public:
	qint32 insertUserTradeInfo(const CUserTradeInfo* pData);
	void truncateTableUserTradeInfo();

public:
	QSqlDatabase* getDB();
private:
	void _UnInitDataBase();
	void _InitDataBase();
	int _StartTransaction();
	int _CommitTransaction();
	qint32 _ExecModify(const QString& strSQL);

private:
	qint32 _CreateDBTable_TABLE_USER_INFO();
	qint32 _AddUserInfo(const CUserInfo* pData);
	qint32 _CreateDBTable_TABLE_USER_TRADE_INFO();
	qint32 _AddUserTradeInfo(const CUserTradeInfo* pData);
	qint32 _CreateDBTable_TABLE_BAR_DATA_1DAY();
	qint32 _AddHistoryDataLst(const QList<CHistoryData*>& lstData);
	qint32 _CreateDBTable_TABLE_MINTIME_MAXTIME();
	qint32 _AddSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
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
