#ifndef  __DEF__CFDSEVER_COMMON_DEF_H_
#define  __DEF__CFDSEVER_COMMON_DEF_H_

//---------------------------------------------------------------
// easy usage of the namespace identifier
#define  NS_BEGIN(name)			namespace name {
#define  NS_END(name)			};
//---------------------------------------------------------------

#include <QtCore/QtGlobal>


QT_BEGIN_NAMESPACE 

#if defined(_MSC_VER) || defined(__BORLANDC__)
typedef qint64          BigInt64;//%I64d
typedef qint64			UBigInt64;// %I64u ¡¢ %I64o ¡¢ %I64x
#else
typedef qint64		BigInt64;
typedef qint64		UBigInt64;
#endif




#define  defOracleDBName          "ORACLE"
#define  defMysqlDBName           "MYSQL"
#define  defSQLiteDBName          "SQLITE"

#define  defQTMysqlDBTypeName           "QMYSQL"
#define  defQTSQLiteDBTypeName          "QSQLITE"


QT_END_NAMESPACE

#endif  // __DEF__CFDSEVER_COMMON_DEF_H_











