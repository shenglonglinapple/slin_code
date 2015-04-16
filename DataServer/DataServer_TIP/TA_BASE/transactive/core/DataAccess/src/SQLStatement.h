#ifndef _CLASS_SQL_STETEMENT_H__
#define _CLASS_SQL_STETEMENT_H__

#include <iostream>
#include "core/DataAccess/src/DataAccessCommonData.h"

NS_BEGIN(TA_Base_Core)

class SQLStatement
{
public:
	SQLStatement();
	~SQLStatement();
public:
	SQLStatement& operator=(const SQLStatement& objectCopy);

public:
	int m_nSQLID;                                // the SQL ID map in the sqlcode.txt
	std::string m_strSQLID;                      // the SQL ID map in the sqlcode.txt
	std::string m_strCommonSQL;                     // the common SQL which can run at all supported db
	std::string m_strOracleSQL;                     // the oracle SQL statement
	std::string m_strMySQLSQL;                      // the mysql SQL statement
	std::string m_strSQLiteSQL;                     // the SQLite SQL statement

public:
	void clear();
	void logInfo();
	void checkAndBuildAQSQL();
private:
	bool _ChkAQSQL();
	std::string _GetAQSQLFirstPart(const std::string& strAQSQL);
	std::string _GetAQSQLSecondPart(const std::string& strAQSQL);
	std::string _GetAQSQLThirdPart(const std::string& strAQSQL);
	void _BuildCallProcedureSQL(const std::string& strProcedureParam);
};//class SQLStatement

NS_END(TA_Base_Core)

#endif //_CLASS_SQL_STETEMENT_H__



