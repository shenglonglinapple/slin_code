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
	QString getTableName_TABLE_BAR_DATA_1DAY();
public:
	QString buildSQL_CreateTable_TABLE_MINTIME_MAXTIME();
	QString buildSQL_BatchInsert_TABLE_MINTIME_MAXTIME();
	QString buildSQL_Truncate_TABLE_MINTIME_MAXTIME();
	QString buildSQL_UPDATE_TABLE_MINTIME_MAXTIME( const QString & strSymbolUse, const QString& strMinTime, const QString& strMaxTime, qint32 nCount);
	QString buildSQL_Select_TABLE_MINTIME_MAXTIME(const QString & strSymbolUse);

public:
	QString buildSQL_CreateTable_TABLE_USER_INFO();
	QString buildSQL_BatchInsert_TABLE_USER_INFO();
	QString buildSQL_Select_TABLE_USER_INFO(const QString & strUSERNAME, const QString& strPASSWORD);
	QString buildSQL_UPDATE_TABLE_USER_INFO( const QString & strUSERNAME, const QString& strPASSWORD, const QString& strLASTLOGINTIME, qint32 nLOGINCOUNT, qint32 nSTATE);

public:
	QString buildSQL_CreateTable_TABLE_USER_TRADE_INFO();
	QString buildSQL_BatchInsert_TABLE_USER_TRADE_INFO();
	QString buildSQL_Truncate_TABLE_USER_TRADE_INFO();

};


#endif //__CLASS_SQLITE_DB_OPER_BUILD_SQL_H__
