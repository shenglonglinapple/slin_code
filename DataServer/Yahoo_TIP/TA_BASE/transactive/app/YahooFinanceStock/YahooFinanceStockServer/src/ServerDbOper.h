#ifndef __CLASS_SERVER_DB_OPER_H__
#define __CLASS_SERVER_DB_OPER_H__


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
class CUserHold;
class CUserAmount;

class CServerDbOper
{
public:
	CServerDbOper(const QString& strSqliteDbFileName);
	virtual ~CServerDbOper();
public:
	qint32 selectUserInfo(quint16 nListenPort,const QString & strUSERNAME, const QString& strPASSWORD, CUserInfo** ppData);
	qint32 updateUserInfo(quint16 nListenPort, const CUserInfo* pData);
	qint32 insertUserInfo(quint16 nListenPort, const CUserInfo* pData);
public:
	qint32 insertUserTradeInfo(quint16 nListenPort, const CUserTradeInfo* pData);
	qint32 insertUserHold(quint16 nListenPort, const CUserHold* pData);
public:
	qint32 select_UserHold(const QString& strUserID, const QString& strSymbolUse, QList<CUserHold*>& lstData );
public:
	qint32 selectUserTradeInfo( quint16 nListenPort, QList<CUserTradeInfo*>& lstData, const QString& strUserID, const QString& strSymbolUse );
public:
	qint32 insertUserAmount(quint16 nListenPort, const CUserAmount* pData);
	qint32 selectUserAmount(quint16 nListenPort, const QString& strUserID, CUserAmount** ppData);

	
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
	qint32 _CreateDBTable_TABLE_USER_HOLD();
	qint32 _Truncate_TABLE_USER_HOLD();
	qint32 _AddUserHold(const CUserHold* pData);
	qint32 _CreateDBTable_TABLE_USER_AMOUNT();
	qint32 _AddUserAmount(const CUserAmount* pData);
	qint32 _Truncate_TABLE_USER_AMOUNT();

private:
	QSqlDatabase* m_pQSqlDataBase;
	QString m_strQTDbType;//"QSQLITE" "QMYSQL"
	QString m_strSqliteDbFileName;
	QString m_strSqliteDbKEY;
	QString m_strSqliteDbFileFullPath;
	QString m_strSqliteDbPath;
	
private:
	CSqliteDbOperBuildSQL* m_pSqliteDbOperBuildSQL;
};


#endif //__CLASS_SERVER_DB_OPER_H__
