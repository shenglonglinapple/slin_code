/**
* The source code in this file is the property of
* Ripple Systems and is not for redistribution
* in any form.
*
* Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/database/src/SimpleDb.cpp $
* @author:  Ripple
* @version: $Revision: #7 $
*
* Last modification: $DateTime: 2013/11/06 10:02:15 $
* Last modified by:  $Author: weikun.lin $
*
* <description>
*
*/
//
// SimpleDb.cpp
//
// Wrapper for the DbServerLocator class which (hopefully) takes all the pain
// out of database access. Note that it is probably not very efficient.
//
// Author: Bruce Fountain 24-Jan-2001
//


#include "core/ocl/src/ocl.h"

#include "core/utilities/src/DebugUtil.h"
#include "core/utilities/src/TAAssert.h"
#include "core/threads/src/Thread.h"
#include "ConnectionPoolManager.h"
#include "core/database/src/IQueryAdapter.h"
#include "core/database/src/DBException.h"
#include "core/database/src/SimpleDb.h"
#include "core/utilities/src/RunParams.h"
#include "core/exceptions/src/DatabaseException.h"
#include "CommonType.h"

using TA_Base_Core::DebugUtil;
using TA_Base_Core::Thread;

using namespace ocl;

NS_BEGIN(TA_Base_Core)

const unsigned long SimpleDb::MAX_ROWS = FETCH_MAX_ROWS;
const unsigned long SimpleDb::MAX_COLS = FETCH_MAX_COLS;

SimpleDb::SimpleDb(const char* pszDbType, const char* connection, const char* user, const char* passwd, const char* hostname) : 
m_pCurQuery(NULL), m_nDBType(enDBOracleDb)
{
	FUNCTION_ENTRY("SimpleDb");

	LOG_GENERIC( SourceInfo, DebugUtil::DebugDebug,
		"SimpleDb::SimpleDb(): dbType=%s, connection=%s, user=%s, passwd=%s, hostname=%s", 
		pszDbType, connection, user, passwd, hostname);

	// Create a string from the database connection details.
	// This will be used to identify the OCIConnection object.
	m_connectionStr = pszDbType;		
	m_connectionStr += DefConStrDelimiter;//":";//DefConStrDelimiter		
	m_connectionStr += connection;		
	m_connectionStr += DefConStrDelimiter;//":"
	m_connectionStr += user;		
	m_connectionStr += DefConStrDelimiter;//":"
	m_connectionStr += passwd;		
	m_connectionStr += DefConStrDelimiter;//":"
	m_connectionStr += hostname;		
	parseDBType(pszDbType);

	// The final parameter is false to indicate that the connection is
	// not being created as part of auto-reconnect.
	CConnectionPoolManager::getInstance().createConnectionPool(m_connectionStr, false);

	FUNCTION_EXIT;
}

SimpleDb::~SimpleDb()
{
	FUNCTION_ENTRY("~SimpleDb");

	try
	{
		cleanQuery();
	}
	catch( const DBException& e )
	{
		LOG( SourceInfo, DebugUtil::ExceptionCatch, "TA_Base_Core::DBException", e.getSummary().c_str() );
	}

	FUNCTION_EXIT;
}

void SimpleDb::Open()
{
	FUNCTION_ENTRY("Open");

	CConnectionPoolManager::getInstance().open( m_connectionStr );

	FUNCTION_EXIT;
}

void SimpleDb::Close()
{
	FUNCTION_ENTRY("Close");

	cleanQuery();
	//Cannot release connection on this class, it should be in charge by OCIAccess;
	LOG( SourceInfo, DebugUtil::GenericLog, DebugUtil::DebugDebug, "SimpleDb::Close(): close database = [%s]", m_connectionStr.c_str());

	FUNCTION_EXIT;
}

void SimpleDb::CloseAll()
{
	FUNCTION_ENTRY("CloseAll");

	cleanQuery();

	//CConnectionPoolManager::getInstance().closeAll();

	FUNCTION_EXIT;
}

void SimpleDb::cleanQuery()
{
	FUNCTION_ENTRY( "cleanQuery" );


	if ( NULL == m_pCurQuery )
	{
		return;
	}

	if (false == _CheckCurQuery())
	{
		return;
	}

	if ( NULL != m_pCurQuery )
	{
		CConnectionPoolManager::getInstance().cleanQuery( m_connectionStr, m_pCurQuery );
	}
	FUNCTION_EXIT;
}	

void SimpleDb::Exec(const SQLStatement& rSqlObj)
{
	FUNCTION_ENTRY("Exec");

	try
	{
		// Delegate to DbServerLocator
		CConnectionPoolManager::getInstance().exec( m_connectionStr, rSqlObj );
	}
	catch(ocl::OraException & e)
	{
		DBException db("OCI_ERROR", e.message().c_str(), e.errorCode());
		throw db;
	}
	catch(DBException & e)
	{
		std::ostringstream osMsg;
		osMsg << "Status:" << e.getStatus() << " Summary:" << e.getSummary() << " Reason:" << e.getReason() << std::endl; 
		LOG_EXCEPTION_CATCH(SourceInfo, "Database exception: ", osMsg.str().c_str());

		int nErrCode = e.getNativeCode();
		if (ER_MYSQL_CANNT_CONNECT == nErrCode ||
			ER_MYSQL_GONE_AWAY == nErrCode ||
			ER_ORA_IMMIDATE_SHUTDOWN == nErrCode ||
			ER_ORA_INITORSHUTDOWN == nErrCode ||
			ER_ORA_NOT_AVALIABLE == nErrCode ||
			ER_ORA_TNS_CLOSE == nErrCode)
		{
			CConnectionPoolManager::getInstance().setPoolUnHealth(m_connectionStr);
			// if go here, it means the db gone bad, rethrow and try another one
			throw e;				
		}
		else
		{	
			//modify by shenglong.lin
			//sql error and CE project, throw to outside
			//in CE project, param  EntityName shoule be "EntityName=ConfigurationEditor"
			if (RunParams::getInstance().get(RPARAM_ENTITYNAME).compare("ConfigurationEditor") == 0)
			{
				throw DatabaseException(e.getReason());
			}
		}
	}
	FUNCTION_EXIT;
}




void SimpleDb::Exec(const SQLStatement& rSqlObj, int numColumns,
					Buffer& data, int maxrows /*=FETCH_MAX_ROWS*/)
{
	FUNCTION_ENTRY("Exec");

	TA_ASSERT( (maxrows > 0) && (maxrows <= FETCH_MAX_ROWS), "Number of rows is out of range"   );

	try
	{
		data.clear();

		cleanQuery();

		m_pCurQuery = CConnectionPoolManager::getInstance().exec( m_connectionStr, rSqlObj, maxrows); 

		if ( NULL == m_pCurQuery )
		{
			LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugError, "Query is not got" );
		}
		else
		{
			m_pCurQuery->fetchInitial( numColumns, data, maxrows );
		}
	}
	catch(ocl::OraException & e)
	{
		DBException db("OCI_ERROR", e.message().c_str(), e.errorCode());
		throw db;
	}
	catch(DBException & e)
	{
		std::ostringstream osMsg;
		osMsg << "Status:" << e.getStatus() << " Summary:" << e.getSummary() << " Reason:" << e.getReason() << std::endl; 
		LOG_EXCEPTION_CATCH(SourceInfo, "Database exception: ", osMsg.str().c_str());

		int nErrCode = e.getNativeCode();
		if (ER_MYSQL_CANNT_CONNECT == nErrCode ||
			ER_MYSQL_GONE_AWAY == nErrCode ||
			ER_ORA_IMMIDATE_SHUTDOWN == nErrCode ||
			ER_ORA_INITORSHUTDOWN == nErrCode ||
			ER_ORA_NOT_AVALIABLE == nErrCode ||
			ER_ORA_TNS_CLOSE == nErrCode)
		{
			CConnectionPoolManager::getInstance().setPoolUnHealth(m_connectionStr);
			// if go here, it means the db gone bad, rethrow and try another one
			throw e;
		}			
	}

	FUNCTION_EXIT;
}

void SimpleDb::FetchMore(int numColumns, Buffer& data, int maxrows /*=FETCH_MAX_ROWS*/ )
{
	FUNCTION_ENTRY("FetchMore");

	if (false == _CheckCurQuery())
	{
		return;
	}

	if ( NULL != m_pCurQuery )
	{
		m_pCurQuery->fetchMore( numColumns, data, maxrows );
	}

	FUNCTION_EXIT;
	return;
}

bool SimpleDb::_CheckCurQuery()
{
	FUNCTION_ENTRY("_CheckCurQuery");
	bool bIsQueryHealth = false;

	if ( NULL == m_pCurQuery )
	{
		LOG_GENERIC( SourceInfo, TA_Base_Core::DebugUtil::DebugError, "Query is closed by timeout" );
		bIsQueryHealth = false;
		return bIsQueryHealth;
	}

	bIsQueryHealth = CConnectionPoolManager::getInstance().isQueryHealth(m_connectionStr, m_pCurQuery);
	if (false == bIsQueryHealth)
	{
		LOG_GENERIC( SourceInfo, DebugUtil::DebugWarn, 
			"SimpleDb::_CheckCurQuery  m_pCurQuery=0x%p its connection and all querys in this connection have been deleted by timeout tben set m_pCurQuery = NULL", 
			m_pCurQuery);
		m_pCurQuery = NULL;
	}

	FUNCTION_EXIT;
	return bIsQueryHealth;
}


void SimpleDb::readBLOB( const std::string& fieldName, const std::string& tableName,
						const std::string& whereClause, std::vector<unsigned char>& data )
{
	FUNCTION_ENTRY("readBLOB");

	TA_ASSERT( fieldName.length() > 0, "No field name has been specified" );
	TA_ASSERT( tableName.length() > 0, "No table name has been specified" );

	CConnectionPoolManager::getInstance().readBLOB( m_connectionStr, fieldName, tableName, whereClause, data );

	FUNCTION_EXIT;
}


void SimpleDb::writeBLOB( const std::string& fieldName, const std::string& tableName,
						 const std::string& whereClause, std::vector<unsigned char>& data )
{
	FUNCTION_ENTRY("writeBLOB");

	TA_ASSERT( fieldName.length() > 0, "No field name has been specified" );
	TA_ASSERT( tableName.length() > 0, "No table name has been specified" );

	CConnectionPoolManager::getInstance().writeBLOB( m_connectionStr, fieldName, tableName, whereClause, data );

	FUNCTION_EXIT;
}


void SimpleDb::ParseConnectStr(const std::string& str,                  // IN
							   std::vector<std::string>& components,    // OUT
							   char delimiter)                          // IN
{
	FUNCTION_ENTRY("ParseConnectStr");

	CConnectionPoolManager::getInstance().parseConnectStr( str, components, delimiter );

	FUNCTION_EXIT;
}

void SimpleDb::parseDBType(const std::string& strDBName)
{
	FUNCTION_ENTRY("parseDBType");

	m_nDBType = CConnectionPoolManager::getInstance().parseDBType(strDBName);

	FUNCTION_EXIT;
}

bool SimpleDb::IsOpen()
{
	FUNCTION_ENTRY("IsOpen");

	FUNCTION_EXIT;

	return CConnectionPoolManager::getInstance().isOpen(m_connectionStr);

}

int SimpleDb::GetDbServerType()
{
	FUNCTION_ENTRY("GetDbServerType");

	FUNCTION_EXIT;
	return m_nDBType;
}



bool SimpleDb::IsNeedChange(const std::string& strCon)
{
	FUNCTION_ENTRY("IsNeedChange");

	FUNCTION_EXIT;
	return strCon.compare(m_connectionStr);
}

bool SimpleDb::HasMore()
{
	FUNCTION_ENTRY("HasMore");

	bool bHasMoreData = false;

	if (false == _CheckCurQuery())
	{
		bHasMoreData = false;
		FUNCTION_EXIT;
		return bHasMoreData;
	}

	if ( NULL != m_pCurQuery )
	{
		bHasMoreData = m_pCurQuery->hasMore();		
	}

	FUNCTION_EXIT;
	return bHasMoreData;
}
NS_END(TA_Base_Core)




