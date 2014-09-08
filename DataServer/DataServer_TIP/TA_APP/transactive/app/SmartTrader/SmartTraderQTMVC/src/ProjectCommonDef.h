#ifndef  __DEF__HISTORY_DATA_SERVER_COMMON_DEF_H_
#define  __DEF__HISTORY_DATA_SERVER_COMMON_DEF_H_


#define  DEF_VALUE_STRING_DB_ORACLE          "ORACLE"
#define  DEF_VALUE_STRING_DB_MYSQL           "MYSQL"
#define  DEF_VALUE_STRING_DB_SQLITE          "SQLITE"

#define  DEF_VALUE_STRING_QT_SUPPORT_DB_QMYSQL           "QMYSQL"
#define  DEF_VALUE_STRING_QT_SUPPORT_DB_QSQLITE          "QSQLITE"








// the database server type support in the system
enum DbServerType
{
	enumBeginDbType = 0,    // the begin of the supported database type.

	enumOracleDb = 1,   // Oracle database  (Support) //defOracleDBName
	enumMysqlDb  = 2,   // MYSQL database   (Support) //defMysqlDBName
	enumSqliteDb = 3,   // SQLITE database  (support) //defSqliteDBName

	enumEndDbType,          // the end tag of supported database type, all supported database should list above this line.

	enumReserve         // For other database system should add below
};


// the BarInfo type support in the system
enum BarInfoType
{
	enumBeginBarInfoType = 0,

	enumBarInfoType_5second,
	enumBarInfoType_1min,
	enumBarInfoType_5min,
	enumBarInfoType_15min,
	enumBarInfoType_30min,
	enumBarInfoType_60min,
	enumBarInfoType_1day,
	enumBarInfoType_30day,
	enumBarInfoType_1year,


	enumEndBarInfoTypeEnd,
	enumBarInfoTypeReserve
};


enum TimeBaseSecond
{	
	TIME_BASE_S_1S          = 1,
	TIME_BASE_S_5S          = 5 * TIME_BASE_S_1S,

	TIME_BASE_S_1MIN		= 60   * TIME_BASE_S_1S,
	TIME_BASE_S_5MIN		= 5   * TIME_BASE_S_1MIN,
	TIME_BASE_S_15MIN		= 15   * TIME_BASE_S_1MIN,
	TIME_BASE_S_30MIN		= 30   * TIME_BASE_S_1MIN,

	TIME_BASE_S_1HOUR		= 60   * TIME_BASE_S_1MIN,
	TIME_BASE_S_1DAY		= 24   * TIME_BASE_S_1HOUR,
	TIME_BASE_S_1MON		= 30   * TIME_BASE_S_1DAY,
	TIME_BASE_S_1YEAR		= 365   * TIME_BASE_S_1DAY,

};








enum enLanguageType
{
	LanguageType_EN,
	LanguageType_ZH
};















//NS_END(TA_App_App)

#endif  // __DEF__HISTORY_DATA_SERVER_COMMON_DEF_H_











