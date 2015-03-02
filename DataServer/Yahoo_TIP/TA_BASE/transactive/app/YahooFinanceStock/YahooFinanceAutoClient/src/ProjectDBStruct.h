#ifndef  __DEF__PROJECT_DB_STRUCT_H__
#define  __DEF__PROJECT_DB_STRUCT_H__


//DB TYPE
static const char*  str_QtDbType_QSQLITE = "QSQLITE";
static const char*  str_QtDbType_QMYSQL = "QMYSQL";

//truncate a table in SQLite
//DELETE FROM someTable

//[[TABLE_SYMBOLUSE]]
static const char*  str_TABLE_SYMBOLUSE = "TABLE_SYMBOLUSE";
static const char*  str_TABLE_SYMBOLUSE_COLUMN_SYMBOLUSE = "SymbolUse";

//[[TABLE_BAR_DATA_1DAY]]
static const char*  str_TABLE_BAR_DATA_1DAY = "TABLE_BAR_DATA_1DAY";
static const char*  str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE = "SymbolUse";
static const char*  str_TABLE_BAR_DATA_Column_DATE = "Date";
static const char*  str_TABLE_BAR_DATA_Column_OPEN = "Open";
static const char*  str_TABLE_BAR_DATA_Column_HIGH = "High";
static const char*  str_TABLE_BAR_DATA_Column_LOW = "Low";
static const char*  str_TABLE_BAR_DATA_Column_CLOSE = "Close";
static const char*  str_TABLE_BAR_DATA_Column_VOLUME = "Volume";
static const char*  str_TABLE_BAR_DATA_Column_ADJCLOSE = "AdjClose";

//[[TABLE_MINTIME_MAXTIME]]
static const char*  str_TABLE_MINTIME_MAXTIME = "TABLE_MINTIME_MAXTIME";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE = "SymbolUse";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME = "MinTime";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME = "MaxTime";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_COUNT = "Count";



//[[TABLE_USER_TRADE_INFO]]
static const char*  str_TABLE_USER_TRADE_INFO = "TABLE_USER_TRADE_INFO";
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
static const char*  str_TABLE_USER_TRADE_INFO_COLUMN_USE_ACCOUNT = "UseAccount";

//[[TABLE_USER_ACCOUNT]]
static const char*  str_TABLE_USER_ACCOUNT = "TABLE_USER_ACCOUNT";
static const char*  str_TABLE_USER_ACCOUNT_COLUMN_USEID = "UseID";
static const char*  str_TABLE_USER_ACCOUNT_COLUMN_INIT_ACCOUNT = "InitAccount";
static const char*  str_TABLE_USER_ACCOUNT_COLUMN_LEFT_ACCOUNT = "LeftAccount";
static const char*  str_TABLE_USER_ACCOUNT_COLUMN_HOLD_ACCOUNT = "HoldAccount";
static const char*  str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS = "FloatingProfitAndLoss";//Floating profit and loss
static const char*  str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE = "FloatingProfitAndLossPersentage";//Floating profit and loss PERSENTAGE
static const char*  str_TABLE_USER_ACCOUNT_COLUMN_UPDATE_TIME = "Time";



//[[TABLE_USER_HOLD_ACCOUNT]]
static const char*  str_TABLE_USER_HOLD_ACCOUNT = "TABLE_USER_HOLD_ACCOUNT";
static const char*  str_TABLE_USER_HOLD_ACCOUNT_COLUMN_USERID = "UserID";
static const char*  str_TABLE_USER_HOLD_ACCOUNT_COLUMN_SYMBOLUSE = "SymbolUse";
static const char*  str_TABLE_USER_HOLD_ACCOUNT_COLUMN_PRICE = "price";
static const char*  str_TABLE_USER_HOLD_ACCOUNT_COLUMN_VOLUME = "volume";
static const char*  str_TABLE_USER_HOLD_ACCOUNT_COLUMN_TIME = "time";
static const char*  str_TABLE_USER_HOLD_ACCOUNT_COLUMN_HOLD_ACCOUNT = "HoldAccount";




#endif  // __DEF__PROJECT_DB_STRUCT_H__








