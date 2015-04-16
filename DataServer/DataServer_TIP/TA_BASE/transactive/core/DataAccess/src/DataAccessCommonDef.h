#ifndef  __DEF_DATA_ACCESS__COMMON_DEF_HH__
#define  __DEF_DATA_ACCESS__COMMON_DEF_HH__

#include "core/utilities/src/UtilitiesCommonDef.h"

NS_BEGIN(TA_Base_Core) 



#define  defSupportDBCount        3     // the number of database which supported in the system.

#define  defOracleDBName          "ORACLE"
#define  defMysqlDBName           "MYSQL"
#define  defSQLiteDBName          "SQLITE"


#define  DefOCConnectionStringsDelimiter           ','
#define  DefConCharDelimiter					   ':'
#define  DefConStrDelimiter					       ":"




//const unsigned long MAX_FIELDSIZE  = 4000;
const unsigned long FETCH_MAX_ROWS = 110;//maybe 200 is too large for first startup, change it to 100
const unsigned long FETCH_MAX_COLS = 100; 
const unsigned int  CONN_STR_PARAM_COUNT = 5;  // the number of Db connection string parameters 
const unsigned long DEFMAXLOGLEN = 1700;       // the max number of characters for log module
const int			EXEC_NUM_RETRIES = 3;       //the max number of retry exec sql

//
const int           DEF_INITIAL_POOLSIZE = 1;	//first init connection pool size
const int           DEF_MIN_POOLSIZE = 1;	//connection min size in pool
const int           DEF_MAX_POOLSIZE = 5;	//max connections in pool
const int           DEF_ACQUIRE_INCREMENT = 1;	//acquire once connection size
const long          DEF_CON_MAX_IDLETIME = 60*60*2;	//(seconds) connection idle time, idle time > DEF_MAX_IDLETIEM pool will monitor and close this connection
const int           DEF_REMOVE_UNHEALTH_CON_TIME = 60*5;//(seconds)Pool Manager set ConPoll unhealth, Pool Monitor will add unhealth connection to monitor list after delay DEF_REMOVE_UNHEALTH_CON_TIME seconds.
const int           DEF_ACQUIRE_RETRYATTEMPTS = 3;	//acquire one connection retry times
const int           DEF_ACQUIRE_RETRYDELAY = 5000;	//(millseconds)acquire one connection each retry delay 
//
const long          DEF_QUERY_MAX_SIZE = 100; // the number of query exists at the same time in one connection
const long          DEF_QUERY_MAX_IDLETIME = 60*60*1;	//(seconds) query idle time, idle time > DEF_QUERY_MAX_IDLETIEM pool will monitor and close this connection
const long          QUERY_EXIST = 1;





NS_END(TA_Base_Core)

#endif  // __DEF_DATA_ACCESS__COMMON_DEF_HH__











