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
#include "StockInfo.h"


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

	m_pDbConnection = NULL;
	//m_pDbConnection = new CQtDBConnection(m_pDbStatusItem);
	//m_pDbConnection->open();
	//if (true == m_pDbConnection->isOpen()){ }
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

void CStocksDbOper::freeLstData(QList<CStockInfo*>& lstData)
{
	foreach (CStockInfo* pData, lstData)
	{
		delete pData;
		pData = NULL;
	}
	lstData.clear();
}
int CStocksDbOper::selectAllStock( QList<CStockInfo*>& lstData )
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	QStringList lstColumnName;
	IQueryAdapter* pQueryAdapter = NULL;

	m_pDbConnection = new CQtDBConnection(m_pDbStatusItem);
	m_pDbConnection->open();
	if (false == m_pDbConnection->isOpen())
	{
		MYLOG4CPP_ERROR<<"open Failed!! m_pDbStatusItem->m_strSchema="<<m_pDbStatusItem->m_strSchema;
		nFunRes = -1;
		return nFunRes;
	}

	/*
	TABLE_STOCKSSQLITE__SELECT__0002
	SELECT COLUMN_SYMBOLUSE, COLUMN_NAMEPINYINFIRST, COLUMN_NAMEPINYINFULL0, COLUMN_NAMEPINYINFULL4, COLUMN_NAMEUTF8 FROM TABLE_STOCKSSQLITE ORDER BY COLUMN_SYMBOLUSE ASC
	*/
	strSQLKey = "TABLE_STOCKSSQLITE__SELECT__0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(str_TABLE_STOCKSSQLITE_COLUMN_SYMBOLUSE);
	lstColumnName.append(str_TABLE_STOCKSSQLITE_COLUMN_NAMEPINYINFIRST);
	lstColumnName.append(str_TABLE_STOCKSSQLITE_COLUMN_NAMEPINYINFULL0);
	lstColumnName.append(str_TABLE_STOCKSSQLITE_COLUMN_NAMEPINYINFULL4);
	lstColumnName.append(str_TABLE_STOCKSSQLITE_COLUMN_NAMEUTF8);

	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	freeLstData(lstData);
	lstData.clear();
	while (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		CStockInfo* pDataGet = NULL;
		pDataGet = new CStockInfo();
		nColumnIndex = 0;
		pDataGet->m_strSymbolUse = pQueryAdapter->getStringData(str_TABLE_STOCKSSQLITE_COLUMN_SYMBOLUSE);
		nColumnIndex++;
		pDataGet->m_strNamePinYinFirst = pQueryAdapter->getStringData(str_TABLE_STOCKSSQLITE_COLUMN_NAMEPINYINFIRST);
		nColumnIndex++;
		pDataGet->m_strNamePinYinFull0 = pQueryAdapter->getStringData(str_TABLE_STOCKSSQLITE_COLUMN_NAMEPINYINFULL0);
		nColumnIndex++;
		pDataGet->m_strNamePinYinFull4 = pQueryAdapter->getStringData(str_TABLE_STOCKSSQLITE_COLUMN_NAMEPINYINFULL4);
		nColumnIndex++;
		pDataGet->m_strNameUtf8 = pQueryAdapter->getStringData(str_TABLE_STOCKSSQLITE_COLUMN_NAMEUTF8);

		lstData.push_back(pDataGet);
		pDataGet = NULL;
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	if (NULL != m_pDbConnection)
	{
		delete m_pDbConnection;
		m_pDbConnection = NULL;
	}

	return nFunRes;
}

//////////////////////////////////////////////////////////////////////////

