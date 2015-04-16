#include "SQLCode.h"
#include "SQLFileHelper.h"

#include "core/DataAccess/src/DataAccessException.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)


boost::mutex SQLCode::m_mutexInstance;
SQLCode* SQLCode::m_pInstance = 0;

static const int  DEF_INT_MAXLINELEN = 1024*1024;


SQLCode& SQLCode::getInstance()
{
	BOOST_LOG_FUNCTION();
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new SQLCode();
	}
	return (*m_pInstance);
}

void SQLCode::removeInstance()
{
	BOOST_LOG_FUNCTION();
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if ( NULL != m_pInstance )
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


SQLCode::SQLCode()
{
	BOOST_LOG_FUNCTION();
	LOG_DEBUG<<"Begin build the Hash table...";
	{
		boost::mutex::scoped_lock lock(m_mutexSQLFileHelper);	
		m_pSqlFileHelper = new SQLFileHelper();
	}

	LOG_DEBUG<<"End build the Hash table...";
}

SQLCode::~SQLCode()
{
	BOOST_LOG_FUNCTION();

	{
		boost::mutex::scoped_lock lock(m_mutexSQLFileHelper);	
		if (NULL != m_pSqlFileHelper)
		{
			delete m_pSqlFileHelper;
			m_pSqlFileHelper = NULL;
		}
	}

}

void SQLCode::_BuildSQLStatement(SQLVarParms& varParms, SQLStatement& rSqlStatement)
{
	BOOST_LOG_FUNCTION();
	std::string strSQLKey;
	SQLStatement SQLFormats;
	int nDbType = 0;
	size_t uiTotalSQLSize = 0;	

	try
	{
		size_t uVarCount = varParms.size();
		if (uVarCount < 1)
		{
			throw DataAccessException(ER_DB_ERR_SQLCode, "the PrepareStatement parameter count error!");
		}

		_GetDbTypeAndSQLKey(varParms, strSQLKey);//strSQLID=strSQLKey=varParms[0]
		_GetSQLFormat(strSQLKey, SQLFormats);
		rSqlStatement = SQLFormats;//copy sqlID
		_BuildNormalSQL(varParms, SQLFormats, rSqlStatement);
		
		rSqlStatement.checkAndBuildAQSQL();
		rSqlStatement.logInfo();
	}
	catch (DataAccessException& e)
	{
		e.logInfo(LogFLInfo);
		throw e;
	}
	catch (...)
	{
		throw DataAccessException(ER_DB_ERR_UNKNOWN, "buildSQLStatement error!");
	}

}


void  SQLCode::_GetDbTypeAndSQLKey(const SQLVarParms& varParms, std::string& strSQLKey)
{
	BOOST_LOG_FUNCTION();
	
	//first param in varParms is SQLKey
	//varParms [0]
	//SQLTypeAdapter need to support SQLStatement so uset 4 std::string
	//use the first std::string data[0]
	strSQLKey = varParms[0].data(0);//DbServerType_BeginDbType
}



void  SQLCode::_BuildSQL(const SQLVarParms& varParms, const std::string& strSQLFormat, std::string& strSQL, int nSQLType)
{	
	BOOST_LOG_FUNCTION();

	size_t uVarCount = varParms.size();

	/*
	uVarCount == 1, varParms[0] is SQLKey 
	uVarCount == 2, varParms[0] is SQLKey, varParms[1] is Value1 
	SQLTypeAdapter need to support SQLStatement so uset 4 std::string   DbBeginType=0 DbOracle=1 DbMysql=2 DbSQLite=3
	use the first std::string data[0]
	sql_snprintf(szSQL, SQLSTRING_LEN, strSQLFormat.c_str(), varParms[1].data(SQLTYPE));
	*/

	{
		int nSQLLen = DEF_INT_MAXLINELEN;
		char* szSQL = new char[nSQLLen];

		memset(szSQL, 0, nSQLLen);

		DEF_CONSTRUCT_SQLCODE(DEF_INT_MAXLINELEN, nSQLType);		

		strSQL = szSQL;
		delete[] szSQL;
		szSQL = NULL;
	}
}

void  SQLCode::_GetSQLFormat(const std::string& strSQLKey, SQLStatement& strSQLFormats)
{
	BOOST_LOG_FUNCTION();

	boost::mutex::scoped_lock lock(m_mutexSQLFileHelper);	

	m_pSqlFileHelper->getSQLString(strSQLKey, strSQLFormats);

	if (strSQLFormats.m_strCommonSQL.empty() 
		&& strSQLFormats.m_strOracleSQL.empty() 
		&& strSQLFormats.m_strMySQLSQL.empty() 
		&& strSQLFormats.m_strSQLiteSQL.empty())
	{
		throw DataAccessException(ER_DB_ERR_SQLCode, "Cannot find the SQL statement in the hash-table");
	}
}








void  SQLCode::_BuildNormalSQL(const SQLVarParms& varParms, SQLStatement& rSQLFormats, SQLStatement& rSqlStatement)
{
	BOOST_LOG_FUNCTION();

	if (!rSQLFormats.m_strCommonSQL.empty())
	{
		_BuildSQL(varParms, rSQLFormats.m_strCommonSQL, rSqlStatement.m_strCommonSQL);
	}
	else
	{
		if (rSQLFormats.m_strOracleSQL.empty() 
			|| rSQLFormats.m_strMySQLSQL.empty() 
			|| rSQLFormats.m_strSQLiteSQL.empty())
		{
			throw DataAccessException(ER_DB_ERR_SQLCode, "The MySQL or Oracle SQL or SQLite Format is empty");
		}
		
		// build Oracle SQL Statement
		_BuildSQL(varParms, rSQLFormats.m_strOracleSQL, rSqlStatement.m_strOracleSQL, DbServerType_OracleDb);

		// build MySQL SQL statement
		_BuildSQL(varParms, rSQLFormats.m_strMySQLSQL, rSqlStatement.m_strMySQLSQL, DbServerType_MysqlDb);

		// build SqliteDb SQL Statement
		_BuildSQL(varParms, rSQLFormats.m_strSQLiteSQL, rSqlStatement.m_strSQLiteSQL, DbServerType_SqliteDb);
	}	

}



void SQLCode::prepareSQLStatement(SQLStatement& rSqlStatement, const SQLTypeAdapter& arg0)
{
	BOOST_LOG_FUNCTION();

	return prepareSQLStatement(rSqlStatement, SQLVarParms() << arg0);
}

void SQLCode::prepareSQLStatement(SQLStatement& rSqlStatement, SQLVarParms& varParms)
{
	BOOST_LOG_FUNCTION();

	try
	{
		LOG_DEBUG<< "Begin prepare SQL statement...";
		rSqlStatement.clear();
		_BuildSQLStatement(varParms, rSqlStatement);
		LOG_DEBUG<< "End prepare SQL statement...";
	}
	catch (DataAccessException& e)
	{
		e.logInfo(LogFLInfo);
		throw e;
	}
	catch (...)
	{			
		throw DataAccessException(ER_DB_ERR_UNKNOWN, "unknow buildSQLStatement erro!");
	}
}	

std::string SQLCode::escapeInsertString(const std::string& theString)
{
	BOOST_LOG_FUNCTION();

	// create a new string to hold the parsed string
	std::string escapedString = theString;
	int pos = escapedString.find_first_of("'");
	while (-1 != pos)
	{
		char charToInsert = escapedString.at(pos);
		escapedString.insert(pos,&charToInsert, 1);
		pos = escapedString.find_first_of("'", pos + 2);
	}
	return escapedString;
}


NS_END(TA_Base_Core)
