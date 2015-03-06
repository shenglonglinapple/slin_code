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
#include "ProjectSQLManager.h"

class IDbConnection;
class CDbStatusItem;


class CUserInfo;
class CUserTradeInfo;
class CUserHold;
class CUserAccount;
class CUserHoldAccount;

class CServerDbOper
{
public:
	CServerDbOper(const QString& strServerListenPort);
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
	qint32 insertUserHoldAccount(const CUserHoldAccount* pData);
	qint32 updateUserHoldAccount(const CUserHoldAccount* pData);

public:
	int startTransaction();
	int commitTransaction();

//////////////////////////////////////////////////////////////////////////


private:
	qint32 _CreateDBTable_TABLE_USER_INFO();
	qint32 _CreateDBTable_TABLE_USER_TRADE_INFO();
	qint32 _CreateDBTable_TABLE_USER_ACCOUNT();
	qint32 _Truncate_TABLE_USER_ACCOUNT();
	qint32 _CreateDBTable_TABLE_USER_HOLD_ACCOUNT();
	qint32 _Truncate_TABLE_USER_HOLD_ACCOUNT();

private:
	QString m_strSqliteDbFileFullPath;
	QString m_strSqliteDbPath;
	IDbConnection* m_pDbConnection;
	CDbStatusItem* m_pDbStatusItem;
	
};


#endif //__CLASS_SERVER_DB_OPER_H__
