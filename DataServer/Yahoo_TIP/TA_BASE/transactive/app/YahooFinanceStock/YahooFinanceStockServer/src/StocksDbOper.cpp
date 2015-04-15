#include "StocksDbOper.h"

#include <QtCore/QFile>

#include <sstream>
#include "ConfigInfo.h"
#include "Log4cppLogger.h"

#include "ProjectSQLManager.h"
#include "ProjectDBStruct.h"
#include "DbStatusItem.h"
#include "QtDBConnection.h"
#include "IQueryAdapter.h"

////"C:/LSL/LSL_DATA/ServerDB/SSSZ_SQLITE_DB.db"
static const char* DEF_VALUE_STOCK_SSSZ_SQLITE_DBNAME = "STOCKSSQLITE_DB.db";

//strSymbolUse
CStocksDbOper::CStocksDbOper()
{
	m_pDbConnection = NULL;
	m_pDbStatusItem = NULL;

	//serverdbpath=C:/LSL/LSL_DATA/ServerDB/
	m_strSqliteDbPath = CConfigInfo::getInstance().getServerDBPath();
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + DEF_VALUE_STOCK_SSSZ_SQLITE_DBNAME;

	m_pDbStatusItem = new CDbStatusItem();
	m_pDbStatusItem->m_nDBType = CDbStatusItem::DBType_QSQLITE;
	m_pDbStatusItem->m_strSchema = m_strSqliteDbFileFullPath;//"C:/LSL/LSL_DATA/ServerDB/STOCKSSQLITE_DB.db"
	m_pDbStatusItem->setProperties();

	m_pDbConnection = new CQtDBConnection(m_pDbStatusItem);
	m_pDbConnection->open();

	if (true == m_pDbConnection->isOpen())
	{

	}
}

CStocksDbOper::~CStocksDbOper()
{
	if (NULL != m_pDbStatusItem)
	{
		delete m_pDbStatusItem;
		m_pDbStatusItem = NULL;
	}

	if (NULL != m_pDbConnection)
	{
		delete m_pDbConnection;
		m_pDbConnection = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////

