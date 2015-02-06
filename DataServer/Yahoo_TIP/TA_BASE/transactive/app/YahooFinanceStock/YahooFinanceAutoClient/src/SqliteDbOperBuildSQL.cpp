#include "SqliteDbOperBuildSQL.h"
#include <sstream>
#include "ProjectCommonData.h"
#include "Log4cppLogger.h"
#include "UserAccount.h"
#include "UserHoldAccount.h"

CSqliteDbOperBuildSQL::CSqliteDbOperBuildSQL()
{

}

CSqliteDbOperBuildSQL::~CSqliteDbOperBuildSQL()
{
}

//////////////////////////////////////////////////////////////////////////

QString CSqliteDbOperBuildSQL::buildSQL_Truncate_TABLE_BAR_DATA_1DAY()
{
	QString  strSQL;
	std::stringstream byteSQL;
	/*
	enumSqliteDb
	DELETE FROM TABLE_BAR_DATA_1DAY	
	*/

	{
		byteSQL<<"DELETE FROM"<<" "<<str_TABLE_BAR_DATA_1DAY;
	}
	
	strSQL = byteSQL.str().c_str();

	return strSQL;
}
QString CSqliteDbOperBuildSQL::getTableName_TABLE_BAR_DATA_1DAY()
{
	QString  strTableName;
	strTableName = str_TABLE_BAR_DATA_1DAY;
	return strTableName;
}

QString  CSqliteDbOperBuildSQL::buildSQL_CreateTable_TABLE_BAR_DATA_1DAY()
{
	QString  strSQL;
	QString  strTableName;
	std::stringstream byteSQL;

	strTableName = str_TABLE_BAR_DATA_1DAY;

	/*
	enumSqliteDb
	CREATE TABLE IF NOT EXISTS TABLE_BAR_DATA_1DAY
	(
	COLUMN_SYMBOLUSE TEXT NOT NULL, 
	COLUMN_DATE TIMESTAMP NOT NULL, 
	COLUMN_OPEN decimal(25,10) NOT NULL,
	COLUMN_HIGH decimal(25,10) NOT NULL,
	COLUMN_LOW decimal(25,10) NOT NULL,	
	COLUMN_CLOSE decimal(25,10) NOT NULL,
	COLUMN_VOLUME INTEGER,
	COLUMN_ADJCLOSE decimal(25,10) NOT NULL,
	PRIMARY KEY (COLUMN_DATE)
	)
	*/

	{
		byteSQL<<"CREATE TABLE IF NOT EXISTS "<<strTableName.toStdString()
			<<" "<<"("
			<<" "<<str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_BAR_DATA_Column_DATE<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_TABLE_BAR_DATA_Column_OPEN<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_BAR_DATA_Column_CLOSE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_BAR_DATA_Column_HIGH<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_BAR_DATA_Column_LOW<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_BAR_DATA_Column_VOLUME<<" "<<"INTEGER NOT NULL"<<","
			<<" "<<str_TABLE_BAR_DATA_Column_ADJCLOSE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<"PRIMARY KEY ("<<str_TABLE_BAR_DATA_Column_DATE<<")"
			//<<" "<<"PRIMARY KEY ("<<str_BarData_Column_InstrumentID<<", "<<str_BarData_Column_Timestamp<<")"
			<<" "<<")";
	}
	
	strSQL = byteSQL.str().c_str();

	return strSQL;
}


QString  CSqliteDbOperBuildSQL::buildSQL_BatchInsert_TABLE_BAR_DATA_1DAY()
{	
	QString  strSQL;
	std::stringstream byteSQL;


	/*
	INSERT INTO TABLE_BAR_DATA_1DAY
	(
	COLUMN_SYMBOLUSE,
	COLUMN_DATE, 
	COLUMN_OPEN, 
	COLUMN_HIGH, 
	COLUMN_LOW, 
	COLUMN_CLOSE, 
	COLUMN_VOLUME, 
	COLUMN_ADJCLOSE
	) 
	VALUES 
	(
	:COLUMN_SYMBOLUSE,
	:COLUMN_DATE_VOLUE,
	:COLUMN_OPEN_VOLUE,
	:COLUMN_HIGH_VOLUE,
	:COLUMN_LOW_VOLUE,
	:COLUMN_CLOSE_VOLUE,
	:COLUMN_VOLUME_VOLUE,
	:COLUMN_ADJCLOSE_VOLUE 
	);
	*/


	byteSQL<<"INSERT INTO "<<str_TABLE_BAR_DATA_1DAY
		<<" "<<"("
		<<" "<<str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_DATE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_OPEN<<","
		<<" "<<str_TABLE_BAR_DATA_Column_HIGH<<","
		<<" "<<str_TABLE_BAR_DATA_Column_LOW<<","
		<<" "<<str_TABLE_BAR_DATA_Column_CLOSE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_VOLUME<<","
		<<" "<<str_TABLE_BAR_DATA_Column_ADJCLOSE
		<<" "<<")"
		<<" "<<"VALUES"
		<<" "<<"("
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"
		<<" "<<")";

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}


QString  CSqliteDbOperBuildSQL::buildSQL_Select_TABLE_BAR_DATA_1DAY(const QString & strFrom, const QString & strTo)
{	
	QString  strSQL;	
	std::stringstream byteSQL;

	/*
	SELECT 
	COLUMN_DATE, 
	COLUMN_OPEN, 
	COLUMN_HIGH, 
	COLUMN_LOW, 
	COLUMN_CLOSE, 
	COLUMN_VOLUME, 
	COLUMN_ADJCLOSE  
	FROM 
	TABLE_BAR_DATA_1DAY 
	WHERE 
	COLUMN_DATE > "2014-12-04 07:00:00"
	AND
	COLUMN_DATE > "2014-12-14 07:00:00"
	ORDER BY COLUMN_DATE ASC;

	QSqlQuery query( "select name from customer" );
	while ( query.next() ) {
	QString name = query.value(0).toString();
	doSomething( name );
	}
	*/


	byteSQL<<"SELECT"
		<<" "<<str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_DATE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_OPEN<<","
		<<" "<<str_TABLE_BAR_DATA_Column_HIGH<<","
		<<" "<<str_TABLE_BAR_DATA_Column_LOW<<","
		<<" "<<str_TABLE_BAR_DATA_Column_CLOSE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_VOLUME<<","
		<<" "<<str_TABLE_BAR_DATA_Column_ADJCLOSE
		<<" "<<"FROM"
		<<" "<<str_TABLE_BAR_DATA_1DAY
		<<" "<<"WHERE"
		<<" "<<str_TABLE_BAR_DATA_Column_DATE<<">="<<"\""<<strFrom.toStdString()<<"\""
		<<" "<<"AND"
		<<" "<<str_TABLE_BAR_DATA_Column_DATE<<"<="<<"\""<<strTo.toStdString()<<"\""
		<<" "<<"ORDER BY"
		<<" "<<str_TABLE_BAR_DATA_Column_DATE
		<<" "<<"ASC";//min->max


	strSQL = byteSQL.str().c_str();
	return strSQL;	
}


QString  CSqliteDbOperBuildSQL::buildSQL_Select_DESC_TABLE_BAR_DATA_1DAY()
{	
	QString  strSQL;	
	std::stringstream byteSQL;

	/*
	SELECT 
	COLUMN_DATE
	FROM 
	TABLE_BAR_DATA_1DAY 
	ORDER BY COLUMN_DATE DESC LIMIT 1
	*/


	byteSQL<<"SELECT"
		<<" "<<str_TABLE_BAR_DATA_Column_DATE
		<<" "<<"FROM"
		<<" "<<str_TABLE_BAR_DATA_1DAY
		<<" "<<"ORDER BY"
		<<" "<<str_TABLE_BAR_DATA_Column_DATE
		<<" "<<"DESC LIMIT 1";

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}


QString  CSqliteDbOperBuildSQL::buildSQL_Select_ASC_TABLE_BAR_DATA_1DAY()
{	
	QString  strSQL;	
	std::stringstream byteSQL;

	/*
	SELECT 
	COLUMN_DATE
	FROM 
	TABLE_BAR_DATA_1DAY 
	ORDER BY COLUMN_DATE ASC LIMIT 1
	*/


	byteSQL<<"SELECT"
		<<" "<<str_TABLE_BAR_DATA_Column_DATE
		<<" "<<"FROM"
		<<" "<<str_TABLE_BAR_DATA_1DAY
		<<" "<<"ORDER BY"
		<<" "<<str_TABLE_BAR_DATA_Column_DATE
		<<" "<<"ASC LIMIT 1";

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}
QString CSqliteDbOperBuildSQL::buildSQL_Select_TABLE_BAR_DATA_1DAY_PRICE( const QString& strSymbolUse, const QString& strDataTime )
{
	QString  strSQL;	
	std::stringstream byteSQL;

	byteSQL<<"SELECT"
		<<" "<<str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_DATE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_OPEN<<","
		<<" "<<str_TABLE_BAR_DATA_Column_HIGH<<","
		<<" "<<str_TABLE_BAR_DATA_Column_LOW<<","
		<<" "<<str_TABLE_BAR_DATA_Column_CLOSE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_VOLUME<<","
		<<" "<<str_TABLE_BAR_DATA_Column_ADJCLOSE
		<<" "<<"FROM"
		<<" "<<str_TABLE_BAR_DATA_1DAY
		<<" "<<"WHERE"
		<<" "<<str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE<<"="<<"\""<<strSymbolUse.toStdString()<<"\""
		<<" "<<"AND"
		<<" "<<str_TABLE_BAR_DATA_Column_DATE<<"="<<"\""<<strDataTime.toStdString()<<"\"";

	strSQL = byteSQL.str().c_str();
	return strSQL;
}


QString  CSqliteDbOperBuildSQL::buildSQL_Select_ASC_TABLE_BAR_DATA_1DAY_PRICE(const QString& strSymbolUse)
{	
	QString  strSQL;	
	std::stringstream byteSQL;

	byteSQL<<"SELECT"
		<<" "<<str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_DATE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_OPEN<<","
		<<" "<<str_TABLE_BAR_DATA_Column_HIGH<<","
		<<" "<<str_TABLE_BAR_DATA_Column_LOW<<","
		<<" "<<str_TABLE_BAR_DATA_Column_CLOSE<<","
		<<" "<<str_TABLE_BAR_DATA_Column_VOLUME<<","
		<<" "<<str_TABLE_BAR_DATA_Column_ADJCLOSE
		<<" "<<"FROM"
		<<" "<<str_TABLE_BAR_DATA_1DAY
		<<" "<<"WHERE"
		<<" "<<str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE<<"="<<"\""<<strSymbolUse.toStdString()<<"\""
		<<" "<<"ORDER BY"
		<<" "<<str_TABLE_BAR_DATA_Column_CLOSE
		<<" "<<"ASC LIMIT 1";

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}


QString  CSqliteDbOperBuildSQL::buildSQL_Select_DataCount_TABLE_BAR_DATA_1DAY()
{	
	QString  strSQL;	
	std::stringstream byteSQL;

	/*
	SELECT 
	count(*)
	FROM 
	TABLE_BAR_DATA_1DAY 
	*/


	byteSQL<<"SELECT"
		<<" "<<"count(*)"
		<<" "<<"FROM"
		<<" "<<str_TABLE_BAR_DATA_1DAY;

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
QString CSqliteDbOperBuildSQL::buildSQL_CreateTable_TABLE_USER_TRADE_INFO()
{
	QString  strSQL;
	QString  strTableName;
	std::stringstream byteSQL;

	strTableName = str_TABLE_USER_TRADE_INFO;
	/*
	CREATE TABLE IF NOT EXISTS TABLE_USER_TRADE_INFO
	(
	COLUMN_USEID TEXT NOT NULL,
	COLUMN_TRADE_UUID TEXT NOT NULL,
	COLUMN_TRADE_TIME TIMESTAMP NOT NULL,
	COLUMN_TRADE_TYPE INTEGER NOT NULL,
	COLUMN_SYMBOLUSE TEXT NOT NULL,
	COLUMN_TRADE_PRICE decimal(25,10) NOT NULL,
	COLUMN_TRADE_VOLUME INTEGER NOT NULL,
	COLUMN_TRADE_AMOUNT decimal(25,10) NOT NULL,
	COLUMN_TRADE_FEES decimal(25,10) NOT NULL,
	COLUMN_TOTAL_TRADE_FEE decimal(25,10) NOT NULL,
	COLUMN_TOTAL_TRADE_AMOUNT decimal(25,10) NOT NULL
	);
	*/

	{
		byteSQL<<"CREATE TABLE IF NOT EXISTS "<<strTableName.toStdString()
			<<" "<<"("
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_USEID<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_UUID<<" "<<"TEXT NOT NULL"<<","			
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TIME<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TYPE<<" "<<"INTEGER NOT NULL"<<","
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_SYMBOLUSE<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_PRICE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_VOLUME<<" "<<"INTEGER NOT NULL"<<","	
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_AMOUNT<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_FEES<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_FEE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_USE_ACCOUNT<<" "<<"decimal(25,10) NOT NULL"
			<<" "<<")";
	}
	
	strSQL = byteSQL.str().c_str();

	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_BatchInsert_TABLE_USER_TRADE_INFO()
{
	QString  strSQL;
	std::stringstream byteSQL;
	/////
	/*
	INSERT INTO TABLE_USER_TRADE_INFO
	(
	COLUMN_USEID,
	COLUMN_TRADE_UUID,
	COLUMN_TRADE_TIME, 
	COLUMN_TRADE_TYPE, 
	COLUMN_SYMBOLUSE,
	COLUMN_TRADE_PRICE, 
	COLUMN_TRADE_VOLUME,
	COLUMN_TRADE_AMOUNT,
	COLUMN_TRADE_FEES,
	COLUMN_TOTAL_TRADE_FEE,
	COLUMN_TOTAL_TRADE_AMOUNT
	) 
	VALUES 
	(
	:COLUMN_USEID,
	:COLUMN_TRADE_UUID,
	:COLUMN_TRADE_TIME,
	:COLUMN_TRADE_TYPE,
	:COLUMN_SYMBOLUSE
	:COLUMN_TRADE_PRICE,
	:COLUMN_TRADE_VOLUME,
	:COLUMN_TRADE_AMOUNT,
	:COLUMN_TRADE_FEES,
	:COLUMN_TOTAL_TRADE_FEE,
	:COLUMN_TOTAL_TRADE_AMOUNT
	);
	*/

	byteSQL<<"INSERT INTO "<<str_TABLE_USER_TRADE_INFO
		<<" "<<"("
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_USEID<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_UUID<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TIME<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TYPE<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_PRICE<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_VOLUME<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_AMOUNT<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_FEES<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_FEE<<","
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_USE_ACCOUNT
		<<" "<<")"
		<<" "<<"VALUES"
		<<" "<<"("
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"
		<<" "<<")";

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}

QString CSqliteDbOperBuildSQL::buildSQL_Truncate_TABLE_USER_TRADE_INFO()
{
	QString  strSQL;
	std::stringstream byteSQL;
	/*
	enumSqliteDb
	DELETE FROM TABLE_USER_TRADE_INFO	
	*/

	{
		byteSQL<<"DELETE FROM"<<" "<<str_TABLE_USER_TRADE_INFO;
	}
	
	strSQL = byteSQL.str().c_str();

	return strSQL;
}


QString CSqliteDbOperBuildSQL::buildSQL_CreateTable_TABLE_MINTIME_MAXTIME()
{
	QString  strSQL;
	std::stringstream byteSQL;
	/*
	enumSqliteDb
	CREATE TABLE IF NOT EXISTS TABLE_MINTIME_MAXTIME
	(
	COLUMN_SYMBOLUSE TEXT NOT NULL, 
	COLUMN_MINTIME TIMESTAMP NOT NULL, 
	COLUMN_MAXTIME TIMESTAMP NOT NULL,
	COLUMN_COUNT INTEGER,
	PRIMARY KEY (COLUMN_SYMBOLUSE)
	)
	*/

	{
		byteSQL<<"CREATE TABLE IF NOT EXISTS "<<str_TABLE_MINTIME_MAXTIME
			<<" "<<"("
			<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_COUNT<<" "<<"INTEGER NOT NULL"<<","
			<<" "<<"PRIMARY KEY ("<<str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE<<")"
			<<" "<<")";
	}
	
	strSQL = byteSQL.str().c_str();

	return strSQL;
}


QString CSqliteDbOperBuildSQL::buildSQL_BatchInsert_TABLE_MINTIME_MAXTIME()
{
	QString  strSQL;
	std::stringstream byteSQL;
	/////
	/*
	INSERT INTO TABLE_MINTIME_MAXTIME
	(
	COLUMN_SYMBOLUSE,
	COLUMN_MINTIME,
	COLUMN_MAXTIME, 
	COLUMN_COUNT
	) 
	VALUES 
	(
	:COLUMN_SYMBOLUSE,
	:COLUMN_MINTIME,
	:COLUMN_MAXTIME,
	:COLUMN_COUNT
	);
	*/
	byteSQL<<"INSERT INTO "<<str_TABLE_MINTIME_MAXTIME
		<<" "<<"("
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME<<","
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME<<","
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_COUNT
		<<" "<<")"
		<<" "<<"VALUES"
		<<" "<<"("
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"
		<<" "<<")";

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}

QString CSqliteDbOperBuildSQL::buildSQL_Truncate_TABLE_MINTIME_MAXTIME()
{
	QString  strSQL;
	std::stringstream byteSQL;
	/*
	enumSqliteDb
	DELETE FROM TABLE_MINTIME_MAXTIME	
	*/

	{
		byteSQL<<"DELETE FROM"<<" "<<str_TABLE_MINTIME_MAXTIME;
	}
	
	strSQL = byteSQL.str().c_str();

	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_UPDATE_TABLE_MINTIME_MAXTIME( 
	const QString & strSymbolUse, const QString& strMinTime, const QString& strMaxTime, qint32 nCount )
{
	QString  strSQL;	
	std::stringstream byteSQL;

	/*
	UPDATE TABLE_MINTIME_MAXTIME SET
	COLUMN_SYMBOLUSE = "000001.SS", 
	COLUMN_MINTIME = "000",
	COLUMN_MAXTIME = "000",
	COLUMN_COUNT = 10
	WHERE 
	COLUMN_SYMBOLUSE = "USERNAME";
	*/
	byteSQL<<"UPDATE"
		<<" "<<str_TABLE_MINTIME_MAXTIME
		<<" "<<"SET"
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE<<"="<<"\""<<strSymbolUse.toStdString()<<"\""<<","
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME<<"="<<"\""<<strMinTime.toStdString()<<"\""<<","
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME<<"="<<"\""<<strMaxTime.toStdString()<<"\""<<","
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_COUNT<<"="<<nCount		
		<<" "<<"WHERE"
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE<<"="<<"\""<<strSymbolUse.toStdString()<<"\"";
	strSQL = byteSQL.str().c_str();
	return strSQL;	
}

QString CSqliteDbOperBuildSQL::buildSQL_Select_TABLE_MINTIME_MAXTIME( const QString & strSymbolUse )
{
	QString  strSQL;	
	std::stringstream byteSQL;

	byteSQL<<"SELECT"
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME<<","
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME<<","
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_COUNT
		<<" "<<"FROM"
		<<" "<<str_TABLE_MINTIME_MAXTIME
		<<" "<<"WHERE"
		<<" "<<str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE<<"="<<"\""<<strSymbolUse.toStdString()<<"\"";

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}

//////////////////////////////////////////////////////////////////////////
QString CSqliteDbOperBuildSQL::buildSQL_CreateTable_TABLE_USER_ACCOUNT()
{
	QString  strSQL;
	std::stringstream byteSQL;
	{
		byteSQL<<"CREATE TABLE IF NOT EXISTS "<<str_TABLE_USER_ACCOUNT
			<<" "<<"("
			<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_USEID<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_INIT_ACCOUNT<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_LEFT_ACCOUNT<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_HOLD_ACCOUNT<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_UPDATE_TIME<<" "<<"TIMESTAMP NOT NULL"
			<<" "<<")";
	}
	strSQL = byteSQL.str().c_str();
	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_Truncate_TABLE_USER_ACCOUNT()
{
	QString  strSQL;
	std::stringstream byteSQL;
	{
		byteSQL<<"DELETE FROM"<<" "<<str_TABLE_USER_ACCOUNT;
	}	
	strSQL = byteSQL.str().c_str();
	return strSQL;
}
QString CSqliteDbOperBuildSQL::buildSQL_BatchInsert_TABLE_USER_ACCOUNT()
{
	QString  strSQL;
	std::stringstream byteSQL;

	byteSQL<<"INSERT INTO "<<str_TABLE_USER_ACCOUNT
		<<" "<<"("
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_USEID<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_INIT_ACCOUNT<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_LEFT_ACCOUNT<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_HOLD_ACCOUNT<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_UPDATE_TIME
		<<" "<<")"
		<<" "<<"VALUES"
		<<" "<<"("
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"
		<<" "<<")";


	strSQL = byteSQL.str().c_str();
	return strSQL;
}


QString CSqliteDbOperBuildSQL::buildSQL_Update_TABLE_USER_ACCOUNT( const CUserAccount* pData )
{
	QString  strSQL;
	std::stringstream byteSQL;

	byteSQL<<"UPDATE"
		<<" "<<str_TABLE_USER_ACCOUNT
		<<" "<<"SET"
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_INIT_ACCOUNT<<"="<<pData->m_fInitAccount<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_LEFT_ACCOUNT<<"="<<pData->m_fLeftAccount<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_HOLD_ACCOUNT<<"="<<pData->m_fHoldAccount<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS<<"="<<pData->m_fFloatingProfitLoss<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE<<"="<<pData->m_fFloatingProfitLossPersentage<<","
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_UPDATE_TIME<<"="<<"\""<<pData->m_strUpdateTime.toStdString()<<"\""
		<<" "<<"WHERE"
		<<" "<<str_TABLE_USER_ACCOUNT_COLUMN_USEID<<"="<<"\""<<pData->m_strUserID.toStdString()<<"\"";
	strSQL = byteSQL.str().c_str();
	return strSQL;
}


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
QString CSqliteDbOperBuildSQL::buildSQL_CreateTable_TABLE_USER_HOLD_ACCOUNT()
{
	QString  strSQL;
	std::stringstream byteSQL;

	{
		byteSQL<<"CREATE TABLE IF NOT EXISTS "<<str_TABLE_USER_HOLD_ACCOUNT
			<<" "<<"("
			<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_USERID<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_SYMBOLUSE<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_PRICE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_VOLUME<<" "<<"INTEGER NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_TIME<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_HOLD_ACCOUNT<<" "<<"decimal(25,10) NOT NULL"
			<<" "<<")";
	}
	strSQL = byteSQL.str().c_str();
	return strSQL;
}
QString CSqliteDbOperBuildSQL::buildSQL_Truncate_TABLE_USER_HOLD_ACCOUNT()
{
	QString  strSQL;
	std::stringstream byteSQL;
	{
		byteSQL<<"DELETE FROM"<<" "<<str_TABLE_USER_HOLD_ACCOUNT;
	}	
	strSQL = byteSQL.str().c_str();
	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_BatchInsert_TABLE_USER_HOLD_ACCOUNT()
{
	QString  strSQL;
	std::stringstream byteSQL;
	byteSQL<<"INSERT INTO "<<str_TABLE_USER_HOLD_ACCOUNT
		<<" "<<"("
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_USERID<<","
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_PRICE<<","
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_VOLUME<<","
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_TIME<<","
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_HOLD_ACCOUNT
		<<" "<<")"
		<<" "<<"VALUES"
		<<" "<<"("
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"
		<<" "<<")";

	strSQL = byteSQL.str().c_str();
	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_Update_TABLE_USER_HOLD_ACCOUNT( const CUserHoldAccount* pData )
{
	QString  strSQL;
	std::stringstream byteSQL;
	byteSQL<<"UPDATE"
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT
		<<" "<<"SET"
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_PRICE<<"="<<pData->m_fPrice<<","
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_VOLUME<<"="<<pData->m_nVolume<<","
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_TIME<<"="<<"\""<<pData->m_strTime.toStdString()<<"\""<<","
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_HOLD_ACCOUNT<<"="<<pData->m_fHoldAccount
		<<" "<<"WHERE"
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_USERID<<"="<<"\""<<pData->m_strUserID.toStdString()<<"\""
		<<" "<<"AND"
		<<" "<<str_TABLE_USER_HOLD_ACCOUNT_COLUMN_SYMBOLUSE<<"="<<"\""<<pData->m_strSymbolUse.toStdString()<<"\"";

	strSQL = byteSQL.str().c_str();
	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_CreateTable_TABLE_SYMBOLUSE()
{
	QString  strSQL;
	QString  strTableName;
	std::stringstream byteSQL;
	strTableName = str_TABLE_SYMBOLUSE;

	{
		byteSQL<<"CREATE TABLE IF NOT EXISTS "<<strTableName.toStdString()
			<<" "<<"("
			<<" "<<str_TABLE_SYMBOLUSE_COLUMN_SYMBOLUSE<<" "<<"TEXT NOT NULL"
			<<" "<<")";
	}	
	strSQL = byteSQL.str().c_str();
	return strSQL;
}


QString  CSqliteDbOperBuildSQL::buildSQL_BatchInsert_TABLE_SYMBOLUSE()
{	
	QString  strSQL;
	std::stringstream byteSQL;

	byteSQL<<"INSERT INTO "<<str_TABLE_SYMBOLUSE
		<<" "<<"("
		<<" "<<str_TABLE_SYMBOLUSE_COLUMN_SYMBOLUSE
		<<" "<<")"
		<<" "<<"VALUES"
		<<" "<<"("
		<<" "<<"?"
		<<" "<<")";

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}

QString CSqliteDbOperBuildSQL::buildSQL_Truncate_TABLE_SYMBOLUSE()
{
	QString  strSQL;
	std::stringstream byteSQL;
	{
		byteSQL<<"DELETE FROM"<<" "<<str_TABLE_SYMBOLUSE;
	}
	strSQL = byteSQL.str().c_str();
	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_Select_TABLE_SYMBOLUSE()
{
	QString  strSQL;
	std::stringstream byteSQL;

	byteSQL<<"SELECT"
		<<" "<<str_TABLE_SYMBOLUSE_COLUMN_SYMBOLUSE
		<<" "<<"FROM"
		<<" "<<str_TABLE_SYMBOLUSE;
	strSQL = byteSQL.str().c_str();
	return strSQL;
}

