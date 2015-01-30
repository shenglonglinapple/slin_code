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
class CUserAccount;
class CUserHoldAccount;

class CServerDbOper
{
public:
	CServerDbOper(const QString& strSqliteDbFileName);
	virtual ~CServerDbOper();
public:
	qint32 selectUserInfo(const QString & strUSERNAME, const QString& strPASSWORD, CUserInfo** ppData);
	qint32 updateUserInfo(const CUserInfo* pData);
	qint32 insertUserInfo(const CUserInfo* pData);
public:
	qint32 insertUserTradeInfo(const CUserTradeInfo* pData);
	qint32 selectUserTradeInfo(QList<CUserTradeInfo*>& lstData, const QString& strUserID, const QString& strSymbolUse );
public:
	qint32 insertUserAccount(const CUserAccount* pData);
	qint32 selectUserAccount(const QString& strUserID, CUserAccount** ppData);
	qint32 updateUserAccount(CUserAccount* pData);
public:
	qint32 selectUserHoldAccount(const QString& strUserID,const QString& strSymobolUse, CUserHoldAccount** ppData);
	qint32 selectUserHoldAccount(const QString& strUserID, QList<CUserHoldAccount*>& LstData);
	qint32 insertUserHoldAccount(CUserHoldAccount* pData);
	qint32 updateUserHoldAccount(CUserHoldAccount* pData);

public:
	int startTransaction();
	int commitTransaction();

//////////////////////////////////////////////////////////////////////////
private:
	qint32 _CreateDBTable_TABLE_USER_HOLD();
	qint32 insertUserHold(const CUserHold* pData);
	qint32 select_UserHold(const QString& strUserID, const QString& strSymbolUse, QList<CUserHold*>& lstData );
	qint32 _Truncate_TABLE_USER_HOLD();
	qint32 _AddUserHold(const CUserHold* pData);
//////////////////////////////////////////////////////////////////////////
private:
	void _UnInitDataBase();
	void _InitDataBase();
	qint32 _ExecModify(const QString& strSQL);

private:
	qint32 _CreateDBTable_TABLE_USER_INFO();
	qint32 _AddUserInfo(const CUserInfo* pData);
	qint32 _CreateDBTable_TABLE_USER_TRADE_INFO();
	qint32 _AddUserTradeInfo(const CUserTradeInfo* pData);
	qint32 _CreateDBTable_TABLE_USER_ACCOUNT();
	qint32 _AddUserAccount(const CUserAccount* pData);
	qint32 _Truncate_TABLE_USER_ACCOUNT();
	qint32 _CreateDBTable_TABLE_USER_HOLD_ACCOUNT();
	qint32 _Truncate_TABLE_USER_HOLD_ACCOUNT();
	qint32 _AddUserHoldAccount(const CUserHoldAccount* pData);

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
