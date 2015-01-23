#ifndef __CLASS_SQLITE_DB_OPER_BUILD_SQL_H__
#define __CLASS_SQLITE_DB_OPER_BUILD_SQL_H__

#include <QtCore/QString>

class CSqliteDbOperBuildSQL
{
public:
	CSqliteDbOperBuildSQL();
	virtual ~CSqliteDbOperBuildSQL();
public:
	QString buildSQL_CreateTable_TABLE_BAR_DATA_1DAY();
	QString buildSQL_BatchInsert_TABLE_BAR_DATA_1DAY();
	QString buildSQL_Select_TABLE_BAR_DATA_1DAY(const QString & strFrom, const QString & strTo);
	QString buildSQL_Select_DESC_TABLE_BAR_DATA_1DAY();
	QString buildSQL_Select_ASC_TABLE_BAR_DATA_1DAY();
	QString buildSQL_Select_DataCount_TABLE_BAR_DATA_1DAY();
	QString buildSQL_Truncate_TABLE_BAR_DATA_1DAY();
public:
	QString buildSQL_CreateTable_TABLE_USER_INFO();
	QString buildSQL_BatchInsert_TABLE_USER_INFO();
	QString buildSQL_Select_TABLE_USER_INFO(const QString & strUSERNAME, const QString& strPASSWORD);
	QString buildSQL_UPDATE_TABLE_USER_INFO( const QString & strUSERNAME, const QString& strPASSWORD, const QString& strLASTLOGINTIME, qint32 nLOGINCOUNT, qint32 nSTATE);

public:
	QString buildSQL_CreateTable_TABLE_USER_TRADE_INFO();
	QString buildSQL_BatchInsert_TABLE_USER_TRADE_INFO();
	QString buildSQL_Truncate_TABLE_USER_TRADE_INFO();
	QString buildSQL_Select_TABLE_USER_TRADE_INFO(const QString & strUserID);

public:
	QString buildSQL_CreateTable_TABLE_USER_HOLD();
	QString buildSQL_Truncate_TABLE_USER_HOLD();
	QString buildSQL_BatchInsert_TABLE_USER_HOLD();
	QString buildSQL_Select_TABLE_USER_HOLD(const QString& strUserID);
	QString buildSQL_Select_TABLE_USER_HOLD( const QString& strUserID, const QString& strSymbolUse );


};


#endif //__CLASS_SQLITE_DB_OPER_BUILD_SQL_H__
