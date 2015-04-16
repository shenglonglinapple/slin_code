#ifndef  __DEF_DATA_ACCESS__COMMON_DATA_HH__
#define  __DEF_DATA_ACCESS__COMMON_DATA_HH__

#include "core/utilities/src/UtilitiesCommonData.h"
#include "core/DataAccess/src/DataAccessCommonDef.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>


NS_BEGIN(TA_Base_Core)



// Data will be retrieved in Rows into a Buffer.
typedef std::vector<std::string> DbDataRow;
typedef std::vector<DbDataRow> DbDataRowBuffers;

typedef std::vector<unsigned char> DataClob;
typedef std::vector<DataClob> DataClobArray;



// the database server type support in the system
enum EDbServerType
{
	DbServerType_BeginDbType = 0,    // the begin of the supported database type.

	DbServerType_OracleDb = 1,   // Oracle database  (Support) //defOracleDBName
	DbServerType_MysqlDb  = 2,   // Mysql database   (Support) //defMysqlDBName
	DbServerType_SqliteDb = 3,   // SQLiet database  (support) //defSqliteDBName

	DbServerType_EndDbType,          // the end tag of supported database type, all supported database should list above this line.

	MaxDbServerType      
};




enum EDbServerState
{
	DbServerState_Pending,
	DbServerState_Online,
	DbServerState_Offline,
	MaxDbServerState
};




enum EDataTypes
{
	DataTypes_DbSync,
	DataTypes_Alarm,
	
	// for new added item should put above this item		
	NotExists_d,  
	MaxDataTypes
};

enum EDbServerPriority
{
	DbServerPriority_0 = 0,

	DbServerPriority_1,
	DbServerPriority_2,
	DbServerPriority_3,
	DbServerPriority_4,


	MaxDbServerPriority
};





enum DB_ERR_CODE
{
	ER_DB_ERR_UNKNOWN			 = 0,

	ER_MYSQL_CANNT_CONNECT		 = 2003, // Can't connect to MySQL server 
	ER_MYSQL_GONE_AWAY			 = 2006, // MySQL server has gone away

	ER_ORA_IMMIDATE_SHUTDOWN     = 1089, // immediate shutdown in progress - no operations are permitted
	ER_ORA_INITORSHUTDOWN        = 1033, // ORACLE initialization or shutdown in progress
	ER_ORA_NOT_AVALIABLE         = 1034, // ORACLE not available
	ER_ORA_TNS_CLOSE             = 12537, // TNS:connection closed


	ER_DB_ERR_SQLFileHelper,		 // "the SQLKey cannot match in Hash table"
	ER_DB_ERR_SQLCode,		     //"the PrepareStatement parameter count error"
	ER_DB_ERR_SQLTypeAdapter,  //"Not enough chars in SQLTypeAdapter"
};


// Various errors we are interested in.
enum  DB_ERR_CODE_ORACLE
{
	VIOLATED_ERROR     =     1,
	SESSION_KILLED                   =    12,
	NOT_LOGGED_IN                    =  1012,
	COLUMN_NULL_ERROR                =  1405,
	END_OF_FILE_ON_COMMS_CHANNEL     =  3113,
	NO_LISTENER                      = 12541,
	NO_SUCH_DATABASE                 = 12545,
	ALREADY_CONNECTED_ERROR          = 24309,
	ALREADY_AUTHENTICATED            = 24313,
	REQUIRE_EXPLICT_ATTACH           = 24327
};

NS_END(TA_Base_Core)

#endif  // __DEF_DATA_ACCESS__COMMON_DATA_HH__








