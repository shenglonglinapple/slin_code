#include "SqliteDbOperBuildSQL.h"
#include <sstream>
#include "ProjectCommonData.h"
#include "Log4cppLogger.h"





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
	//InstrumentID INTEGER NOT NULL, 
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
			//<<" "<<str_BarData_Column_InstrumentID<<" "<<"INTEGER NOT NULL"<<","
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




QString CSqliteDbOperBuildSQL::buildSQL_CreateTable_TABLE_USER_INFO()
{
	QString  strSQL;
	QString  strTableName;
	std::stringstream byteSQL;

	strTableName = str_TABLE_USER_INFO;

	/*
	CREATE TABLE IF NOT EXISTS TABLE_USER_INFO
	(
	COLUMN_USEID TEXT NOT NULL,
	COLUMN_USERNAME TEXT NOT NULL,
	COLUMN_PASSWORD TEXT NOT NULL,
	COLUMN_LASTLOGINTIME TIMESTAMP NOT NULL,
	COLUMN_LOGINCOUNT INTEGER NOT NULL,
	COLUMN_STATE INTEGER NOT NULL,
	PRIMARY KEY (COLUMN_USEID)
	);
	*/

	{
		byteSQL<<"CREATE TABLE IF NOT EXISTS "<<strTableName.toStdString()
			<<" "<<"("
			<<" "<<str_TABLE_USER_INFO_COLUMN_USEID<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_USER_INFO_COLUMN_USERNAME<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_USER_INFO_COLUMN_PASSWORD<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_USER_INFO_COLUMN_LASTLOGINTIME<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_TABLE_USER_INFO_COLUMN_LOGINCOUNT<<" "<<"INTEGER NOT NULL"<<","	
			<<" "<<str_TABLE_USER_INFO_COLUMN_STATE<<" "<<"INTEGER NOT NULL"<<","
			<<" "<<"PRIMARY KEY ("<<str_TABLE_USER_INFO_COLUMN_USEID<<")"
			<<" "<<")";
	}
	
	strSQL = byteSQL.str().c_str();

	return strSQL;
}


QString  CSqliteDbOperBuildSQL::buildSQL_BatchInsert_TABLE_USER_INFO()
{	
	QString  strSQL;
	std::stringstream byteSQL;
	/*
	INSERT INTO TABLE_USER_INFO
	(
	COLUMN_USEID, 
	COLUMN_USERNAME, 
	COLUMN_PASSWORD, 
	COLUMN_LASTLOGINTIME, 
	COLUMN_LOGINCOUNT
	COLUMN_STATE
	) 
	VALUES 
	(
	:COLUMN_USEID,
	:COLUMN_USERNAME,
	:COLUMN_PASSWORD,
	:COLUMN_LASTLOGINTIME,
	:COLUMN_LOGINCOUNT
	);
	*/
	byteSQL<<"INSERT INTO "<<str_TABLE_USER_INFO
		<<" "<<"("
		<<" "<<str_TABLE_USER_INFO_COLUMN_USEID<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_USERNAME<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_PASSWORD<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_LASTLOGINTIME<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_LOGINCOUNT<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_STATE		
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


QString  CSqliteDbOperBuildSQL::buildSQL_Select_TABLE_USER_INFO(const QString & strUSERNAME, const QString& strPASSWORD)
{	
	QString  strSQL;	
	std::stringstream byteSQL;
	/*
	SELECT 
	COLUMN_USEID, 
	COLUMN_USERNAME, 
	COLUMN_PASSWORD, 
	COLUMN_LASTLOGINTIME, 
	COLUMN_LOGINCOUNT
	COLUMN_STATE
	FROM 
	TABLE_USER_INFO 
	WHERE 
	COLUMN_USERNAME = "USERNAME"
	AND
	COLUMN_PASSWORD = "PASSWORD";
	*/
	byteSQL<<"SELECT"
		<<" "<<str_TABLE_USER_INFO_COLUMN_USEID<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_USERNAME<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_PASSWORD<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_LASTLOGINTIME<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_LOGINCOUNT<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_STATE		
		<<" "<<"FROM"
		<<" "<<str_TABLE_USER_INFO
		<<" "<<"WHERE"
		<<" "<<str_TABLE_USER_INFO_COLUMN_USERNAME<<">="<<"\""<<strUSERNAME.toStdString()<<"\""
		<<" "<<"AND"
		<<" "<<str_TABLE_USER_INFO_COLUMN_PASSWORD<<"<="<<"\""<<strPASSWORD.toStdString()<<"\"";

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}

QString  CSqliteDbOperBuildSQL::buildSQL_UPDATE_TABLE_USER_INFO(
	const QString & strUSERNAME, const QString& strPASSWORD,
	const QString& strLASTLOGINTIME, qint32 nLOGINCOUNT, qint32 nSTATE)
{	
	QString  strSQL;	
	std::stringstream byteSQL;
	/*
	UPDATE TABLE_USER_INFO SET
	COLUMN_LASTLOGINTIME = "2012-02-02 01:02:03", 
	COLUMN_LOGINCOUNT = 12
	WHERE 
	COLUMN_USERNAME = "USERNAME"
	AND
	COLUMN_PASSWORD = "PASSWORD";
	*/
	byteSQL<<"UPDATE"
		<<" "<<str_TABLE_USER_INFO
		<<" "<<"SET"
		<<" "<<str_TABLE_USER_INFO_COLUMN_LASTLOGINTIME<<"="<<"\""<<strLASTLOGINTIME.toStdString()<<"\""<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_LOGINCOUNT<<"="<<nLOGINCOUNT<<","
		<<" "<<str_TABLE_USER_INFO_COLUMN_STATE<<"="<<nSTATE		
		<<" "<<"WHERE"
		<<" "<<str_TABLE_USER_INFO_COLUMN_USERNAME<<"="<<"\""<<strUSERNAME.toStdString()<<"\""
		<<" "<<"AND"
		<<" "<<str_TABLE_USER_INFO_COLUMN_PASSWORD<<"="<<"\""<<strUSERNAME.toStdString()<<"\"";

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
			<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_AMOUNT<<" "<<"decimal(25,10) NOT NULL"
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
		<<" "<<str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_AMOUNT
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

QString CSqliteDbOperBuildSQL::buildSQL_CreateTable_TABLE_USER_HOLD()
{
	QString  strSQL;
	std::stringstream byteSQL;

	{
		byteSQL<<"CREATE TABLE IF NOT EXISTS "<<str_TABLE_USER_HOLD
			<<" "<<"("
			<<" "<<str_TABLE_USER_HOLD_COLUMN_USEID<<" "<<"TEXT NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_SYMBOLUSE<<" "<<"TEXT NOT NULL"<<","			
			<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_TIME<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_PRICE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_VOLUME<<" "<<"INTEGER NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_FEES<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_AMOUNT<<" "<<"decimal(25,10) NOT NULL"<<","	
			<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_TIME<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_PRICE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_FEES<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_AMOUNT<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_PROFIT_LOSS<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_TABLE_USER_HOLD_COLUMN_PROFIT_LOSS_PERSENTAGE<<" "<<"decimal(25,10) NOT NULL"
			<<" "<<")";
	}
	
	strSQL = byteSQL.str().c_str();

	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_Truncate_TABLE_USER_HOLD()
{
	QString  strSQL;
	std::stringstream byteSQL;
	{
		byteSQL<<"DELETE FROM"<<" "<<str_TABLE_USER_HOLD;
	}
	strSQL = byteSQL.str().c_str();
	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_BatchInsert_TABLE_USER_HOLD()
{
	QString  strSQL;
	std::stringstream byteSQL;

	byteSQL<<"INSERT INTO "<<str_TABLE_USER_HOLD
		<<" "<<"("
		<<" "<<str_TABLE_USER_HOLD_COLUMN_USEID<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_TIME<<","

		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_PRICE<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_VOLUME<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_FEES<<","

		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_AMOUNT<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_TIME<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_PRICE<<","

		<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_FEES<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_AMOUNT<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_PROFIT_LOSS<<","

		<<" "<<str_TABLE_USER_HOLD_COLUMN_PROFIT_LOSS_PERSENTAGE
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
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"
		<<" "<<")";

	strSQL = byteSQL.str().c_str();
	return strSQL;
}

QString CSqliteDbOperBuildSQL::buildSQL_Select_TABLE_USER_HOLD( const QString& strUserID )
{
	QString  strSQL;	
	std::stringstream byteSQL;

	byteSQL<<"SELECT"
		<<" "<<str_TABLE_USER_HOLD_COLUMN_USEID<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_SYMBOLUSE<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_TIME<<","

		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_PRICE<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_VOLUME<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_FEES<<","

		<<" "<<str_TABLE_USER_HOLD_COLUMN_BUY_AMOUNT<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_TIME<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_PRICE<<","

		<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_FEES<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_AMOUNT<<","
		<<" "<<str_TABLE_USER_HOLD_COLUMN_PROFIT_LOSS<<","

		<<" "<<str_TABLE_USER_HOLD_COLUMN_PROFIT_LOSS_PERSENTAGE

		<<" "<<"FROM"
		<<" "<<str_TABLE_USER_HOLD
		<<" "<<"WHERE"
		<<" "<<str_TABLE_USER_HOLD_COLUMN_USEID<<"="<<"\""<<strUserID.toStdString()<<"\""
		<<" "<<"ORDER BY"
		<<" "<<str_TABLE_USER_HOLD_COLUMN_CURRENT_TIME
		<<" "<<"ASC";//ASC min->max   DESC max->min

	strSQL = byteSQL.str().c_str();
	return strSQL;	
}
