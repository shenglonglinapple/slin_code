#ifndef __CLASS_SQLITE_DB_OPER_BUILD_SQL_H__
#define __CLASS_SQLITE_DB_OPER_BUILD_SQL_H__

#include <QtCore/QString>

class CUserAccount;
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
	QString getTableName_TABLE_BAR_DATA_1DAY();
	QString buildSQL_Select_ASC_TABLE_BAR_DATA_1DAY_PRICE(const QString& strSymbolUse);
	QString buildSQL_Select_TABLE_BAR_DATA_1DAY_PRICE(const QString& strSymbolUse, const QString& strDataTime);
public:
	QString buildSQL_CreateTable_TABLE_MINTIME_MAXTIME();
	QString buildSQL_BatchInsert_TABLE_MINTIME_MAXTIME();
	QString buildSQL_Truncate_TABLE_MINTIME_MAXTIME();
	QString buildSQL_UPDATE_TABLE_MINTIME_MAXTIME( const QString & strSymbolUse, const QString& strMinTime, const QString& strMaxTime, qint32 nCount);
	QString buildSQL_Select_TABLE_MINTIME_MAXTIME(const QString & strSymbolUse);
public:
	QString buildSQL_CreateTable_TABLE_USER_TRADE_INFO();
	QString buildSQL_BatchInsert_TABLE_USER_TRADE_INFO();
	QString buildSQL_Truncate_TABLE_USER_TRADE_INFO();
public:
	QString buildSQL_CreateTable_TABLE_USER_ACCOUNT();
	QString buildSQL_Truncate_TABLE_USER_ACCOUNT();
	QString buildSQL_Update_TABLE_USER_ACCOUNT( const CUserAccount* pData );
	QString buildSQL_BatchInsert_TABLE_USER_ACCOUNT();
};


#endif //__CLASS_SQLITE_DB_OPER_BUILD_SQL_H__
