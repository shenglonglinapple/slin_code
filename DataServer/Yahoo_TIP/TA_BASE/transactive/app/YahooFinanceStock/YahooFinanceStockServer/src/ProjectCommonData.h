#ifndef  __DEF__HISTORY_DATA_SERVER_COMMON_DATA_H_
#define  __DEF__HISTORY_DATA_SERVER_COMMON_DATA_H_

#include "ProjectCommonDef.h"
#include "ProjectSysInclude.h"
#include "ProjectQTInclude.h"

static const char* DEFVALUE_String_DataTime_Format = "yyyy-MM-dd hh:mm:ss";
static const char* DEFVALUE_String_Data_Format = "yyyy-MM-dd";
static const char* DEF_VALUE_STRING_UTC_START_TIME = "08:00:00";


//[DB begin]
static const char*  str_QtDbType_QSQLITE = "QSQLITE";
static const char*  str_QtDbType_QMYSQL = "QMYSQL";

//truncate a table in SQLite
//DELETE FROM someTable

/////
static const char*  str_TABLE_BAR_DATA_1DAY = "TABLE_BAR_DATA_1DAY";
//
static const char*  str_TABLE_BAR_DATA_Column_DATE = "COLUMN_DATE";
static const char*  str_TABLE_BAR_DATA_Column_OPEN = "COLUMN_OPEN";
static const char*  str_TABLE_BAR_DATA_Column_HIGH = "COLUMN_HIGH";
static const char*  str_TABLE_BAR_DATA_Column_LOW = "COLUMN_LOW";
static const char*  str_TABLE_BAR_DATA_Column_CLOSE = "COLUMN_CLOSE";
static const char*  str_TABLE_BAR_DATA_Column_VOLUME = "COLUMN_VOLUME";
static const char*  str_TABLE_BAR_DATA_Column_ADJCLOSE = "COLUMN_ADJCLOSE";
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
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_USEID = "COLUMN_USEID";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_UUID = "COLUMN_TRADE_UUID";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TIME = "COLUMN_TRADE_TIME";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TYPE = "COLUMN_TRADE_TYPE";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_SYMBOLUSE = "COLUMN_SYMBOLUSE";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_PRICE = "COLUMN_TRADE_PRICE";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_VOLUME = "COLUMN_TRADE_VOLUME";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_AMOUNT = "COLUMN_TRADE_AMOUNT";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_FEES = "COLUMN_TRADE_FEES";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_FEE = "COLUMN_TOTAL_TRADE_FEE";
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_AMOUNT = "COLUMN_TOTAL_TRADE_AMOUNT";
/////
//[DB end]


#endif  // __DEF__HISTORY_DATA_SERVER_COMMON_DATA_H_








