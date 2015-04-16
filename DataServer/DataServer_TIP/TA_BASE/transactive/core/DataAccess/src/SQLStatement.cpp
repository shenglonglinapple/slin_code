#include "SQLStatement.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)


static const char*  s_pcAQOraclePrefix  = "BEGIN audit_data_queue_pkg.enqueue_audit_data";
static const char*  s_pcAQOracleSubfix  = "; END;";
static const char*  s_pcAQMySQLPrefix   = "CALL PRC_ENQ";
static const char*  s_pcAQMySQLSubfix   = "";
static const char*  s_pcAQTag           = "AQ:";
static const char*  s_pcAQOracleDelim   = "||";
static const char*  s_pcAQMySQLDelim    = ",";
static const char*  s_pcAQMySQLConStr   = "CONCAT(";
static const char*  s_pcAQStrTag        ="'";
static const size_t s_nAQTagLen         = 3;//"AQ:"
static const size_t s_nStrBeginPos      = 0;

// #define  defAQSQL_Demit           0x2c  // ','
// #define  defAQSQL_EndTag          0x29  // ')'
static const std::string DEF_String_defAQSQL_Demit = ",";//0x2c
static const std::string DEF_String_defAQSQL_BeginTag = "(";//0x29
static const std::string DEF_String_defAQSQL_EndTag = ")";//0x29




SQLStatement::SQLStatement()
{
	clear();
}

SQLStatement::~SQLStatement()
{
	clear();
}

SQLStatement& SQLStatement::operator=( const SQLStatement& objectCopy )
{
	m_nSQLID = objectCopy.m_nSQLID;
	m_strSQLID = objectCopy.m_strSQLID;
	m_strCommonSQL = objectCopy.m_strCommonSQL;
	m_strOracleSQL = objectCopy.m_strOracleSQL;
	m_strMySQLSQL = objectCopy.m_strMySQLSQL;
	m_strSQLiteSQL = objectCopy.m_strSQLiteSQL;

	return *this;
}

void SQLStatement::clear()
{
	this->m_nSQLID = 0;
	this->m_strSQLID.clear();
	this->m_strCommonSQL.clear();
	this->m_strOracleSQL.clear();
	this->m_strMySQLSQL.clear();
	this->m_strSQLiteSQL.clear();
}


void  SQLStatement::logInfo()
{
	LOG_DEBUG<<"SQL Info:"<<" "<<"nSQLID="<<m_nSQLID<<" "<<"strSQLID="<<m_strSQLID<<std::endl
		<<" "<<"strCommonSQL="<<m_strCommonSQL<<std::endl
		<<" "<<"strOracleSQL="<<m_strOracleSQL<<std::endl
		<<" "<<"strMySQLSQL="<<m_strMySQLSQL<<std::endl
		<<" "<<"strSQLiteSQL="<<m_strSQLiteSQL<<std::endl;
	
}

void  SQLStatement::checkAndBuildAQSQL()
{
	if (false == _ChkAQSQL())
	{
		return;
	}

	std::string strFirstPart;
	std::string strSecondPart_mysql;
	std::string strSecondPart_oracle;
	std::string strSecondPart_sqlite;
	std::string strThirdPart;
	std::string strProcedureParam;

	strFirstPart = _GetAQSQLFirstPart(m_strMySQLSQL);//('%s','PUBLIC'
	strSecondPart_mysql = _GetAQSQLSecondPart(m_strMySQLSQL);//'DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID = %s AND TEST_TYPE = 'AAAAA''
	strSecondPart_oracle = _GetAQSQLSecondPart(m_strOracleSQL);//'DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID = %s AND TEST_TYPE = 'AAAAA''
	strSecondPart_sqlite = _GetAQSQLSecondPart(m_strSQLiteSQL);//'DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID = %s AND TEST_TYPE = 'AAAAA''
	strThirdPart = _GetAQSQLThirdPart(m_strMySQLSQL);//")"

	strProcedureParam = strFirstPart + DEF_String_defAQSQL_Demit
		+ strSecondPart_mysql + DEF_String_defAQSQL_Demit
		+ strSecondPart_sqlite + strThirdPart;

	_BuildCallProcedureSQL(strProcedureParam);
	
}

void SQLStatement::_BuildCallProcedureSQL(const std::string& strProcedureParam)
{
	m_strMySQLSQL = s_pcAQMySQLPrefix + strProcedureParam;

	m_strOracleSQL = s_pcAQOraclePrefix + strProcedureParam + s_pcAQOracleSubfix;

	m_strSQLiteSQL = s_pcAQMySQLPrefix + strProcedureParam;	
}

std::string SQLStatement::_GetAQSQLFirstPart(const std::string& strAQSQL)
{
	//m_strMySQLSQL
	//TABLETESTDAITEST_DELETE_4001=AQ:('%s','%s','PUBLIC', 'DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID = %s AND TEST_TYPE = 'AAAAA'')
	int nTempPos_firstDemit = 0;
	int nTempPos_SecondDemit = 0;
	int nTempPos_ThirdDemit = 0;
	int nBeginTag = 0;
	std::string strTempSQL;

	nBeginTag = strAQSQL.find_first_of(DEF_String_defAQSQL_BeginTag);

	nTempPos_firstDemit   = strAQSQL.find_first_of(DEF_String_defAQSQL_Demit);
	nTempPos_SecondDemit   = strAQSQL.find_first_of(DEF_String_defAQSQL_Demit, nTempPos_firstDemit + 1);
	nTempPos_ThirdDemit   = strAQSQL.find_first_of(DEF_String_defAQSQL_Demit, nTempPos_SecondDemit + 1);
	strTempSQL = strAQSQL.substr(nBeginTag, nTempPos_ThirdDemit - nBeginTag);//('%s','%s','PUBLIC'

	return strTempSQL;
}

std::string SQLStatement::_GetAQSQLSecondPart(const std::string& strAQSQL)
{
	//m_strMySQLSQL
	//TABLETESTDAITEST_DELETE_4001=AQ:('%s','%s','PUBLIC', 'DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID = %s AND TEST_TYPE = 'AAAAA'')
	int nTempPos_firstDemit = 0;
	int nTempPos_SecondDemit = 0;
	int nTempPos_ThirdDemit = 0;
	int nTempEnd = 0;
	int nInsertPos = 0;
	std::string strTempSQL;

	nTempPos_firstDemit   = strAQSQL.find_first_of(DEF_String_defAQSQL_Demit);
	nTempPos_SecondDemit   = strAQSQL.find_first_of(DEF_String_defAQSQL_Demit, nTempPos_firstDemit + 1);
	nTempPos_ThirdDemit   = strAQSQL.find_first_of(DEF_String_defAQSQL_Demit, nTempPos_SecondDemit + 1);
	nTempEnd   = strAQSQL.find_last_of(DEF_String_defAQSQL_EndTag);
	//'DELETE FROM TABLE_TEST_DAITEST WHERE LINE_ID = %s AND TEST_TYPE = 'AAAAA''
	strTempSQL = strAQSQL.substr(nTempPos_ThirdDemit + 1, (nTempEnd - nTempPos_ThirdDemit - 1));

	return strTempSQL;
}

std::string SQLStatement::_GetAQSQLThirdPart(const std::string& strAQSQL)
{
	std::string strTempSQL;
	strTempSQL = DEF_String_defAQSQL_EndTag;
	return strTempSQL;
}

bool  SQLStatement::_ChkAQSQL()
{
	bool bRetCode = false;

	if (m_strMySQLSQL.empty() && m_strOracleSQL.empty() && m_strSQLiteSQL.empty())
	{
		return bRetCode;
	}

	if (!strnicmp(m_strMySQLSQL.c_str(), s_pcAQTag, s_nAQTagLen))
	{
		bRetCode = true;
	}

	return bRetCode;
}


NS_END(TA_Base_Core)



