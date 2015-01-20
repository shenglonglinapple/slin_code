#ifndef  __DEF__HISTORY_DATA_SERVER_COMMON_DATA_H_
#define  __DEF__HISTORY_DATA_SERVER_COMMON_DATA_H_

#include "ProjectCommonDef.h"
#include "ProjectSysInclude.h"
#include "ProjectQTInclude.h"



static const char* DEFVALUE_String_DataTime_Format = "yyyy-MM-dd hh:mm:ss";
static const char* DEFVALUE_String_Data_Format = "yyyy-MM-dd";
static const char* DEF_VALUE_STRING_UTC_START_TIME = "08:00:00";

//[client begin]
static const char* DEFVALUE_String_UserName = "UserNameValue";
static const char* DEFVALUE_String_PassWord = "PassWordValue";
static const char* DEFVALUE_String_ServerIP = "127.0.0.1";
static const int   DEFVALUE_Int_ServerPort = 5000;
//[client begin]



//[DB begin]
static const char*  str_QtDbType_QSQLITE = "QSQLITE";
static const char*  str_QtDbType_QMYSQL = "QMYSQL";

//truncate a table in SQLite
//DELETE FROM someTable

/////
static const char*  str_TABLE_BAR_DATA_1DAY = "TABLE_BAR_DATA_1DAY";
//
static const char*  str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE = "SymbolUse";
static const char*  str_TABLE_BAR_DATA_Column_DATE = "Date";
static const char*  str_TABLE_BAR_DATA_Column_OPEN = "Open";
static const char*  str_TABLE_BAR_DATA_Column_HIGH = "High";
static const char*  str_TABLE_BAR_DATA_Column_LOW = "Low";
static const char*  str_TABLE_BAR_DATA_Column_CLOSE = "Close";
static const char*  str_TABLE_BAR_DATA_Column_VOLUME = "Volume";
static const char*  str_TABLE_BAR_DATA_Column_ADJCLOSE = "AdjClose";

/////
static const char*  str_TABLE_MINTIME_MAXTIME = "TABLE_MINTIME_MAXTIME";
//
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE = "SymbolUse";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME = "MinTime";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME = "MaxTime";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_COUNT = "Count";


/////
static const char*  str_TABLE_USER_INFO = "TABLE_USER_INFO";
//
static const char*  str_TABLE_USER_INFO_COLUMN_USEID = "COLUMN_USEID";
static const char*  str_TABLE_USER_INFO_COLUMN_USERNAME = "COLUMN_USERNAME";
static const char*  str_TABLE_USER_INFO_COLUMN_PASSWORD = "COLUMN_PASSWORD";
static const char*  str_TABLE_USER_INFO_COLUMN_LASTLOGINTIME = "COLUMN_LASTLOGINTIME";
static const char*  str_TABLE_USER_INFO_COLUMN_LOGINCOUNT = "COLUMN_LOGINCOUNT";
static const char*  str_TABLE_USER_INFO_COLUMN_STATE = "COLUMN_STATE";
/////
static const char*  str_TABLE_USER_TRADE_INFO = "TABLE_USER_TRADE_INFO";
//
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_USEID = "UseID";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_UUID = "TradeUUID";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TIME = "TradeTime";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TYPE = "TradeType";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_SYMBOLUSE = "SymbolUse";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_PRICE = "TradePrice";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_VOLUME = "TradeVolume";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_AMOUNT = "TradeAmount";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_FEES = "TradeFees";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_FEE = "TotalTradeFee";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_AMOUNT = "TotalTradeAmount";
/////
//[DB end]

#endif  // __DEF__HISTORY_DATA_SERVER_COMMON_DATA_H_








