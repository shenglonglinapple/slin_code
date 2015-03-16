#include "SqliteDbOper.h"

#include <QtCore/QFile>

#include <sstream>
#include "HistoryData.h"
#include "ConfigInfo.h"
#include "Log4cppLogger.h"
#include "UserInfo.h"
#include "SymbolUseManager.h"

#include "ProjectSQLManager.h"
#include "ProjectDBStruct.h"
#include "DbStatusItem.h"
#include "QtDBConnection.h"
#include "IQueryAdapter.h"


static const char* DEF_VALUE_STRING_UTC_START_DATE = "1970-01-01";
static const char* DEF_VALUE_STRING_UTC_START_TIME = "08:00:00";
static const char* DEF_VALUE_STRING_UTC_START_DATE_TIME = "1970-01-01 08:00:00";

static const int DEF_INT_MAX_LINE_LENGTH = 1024*10;
static const int DEF_INT_ONE_DAY_SECONDS = 60*60*24;


//strSymbolUse
CSqliteDbOper::CSqliteDbOper( const QString& strSymbolUse )//"002567.SZ";
{
	m_strSymbolUse = strSymbolUse;
	m_pDbConnection = NULL;
	m_pDbStatusItem = NULL;

	m_strSqliteDbPath = CConfigInfo::getInstance().getSQLiteDBPath();//"C:/LSL/LSL_DATA/SaveDataFile/002567.SZ"
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + m_strSymbolUse;

	m_pDbStatusItem = new CDbStatusItem();
	m_pDbStatusItem->m_nDBType = CDbStatusItem::DBType_QSQLITE;
	m_pDbStatusItem->m_strSchema = m_strSqliteDbFileFullPath;//"C:/LSL/LSL_DATA/ServerDB/5001.db"
	m_pDbStatusItem->setProperties();

	m_pDbConnection = new CQtDBConnection(m_pDbStatusItem);
	m_pDbConnection->open();

	if (true == m_pDbConnection->isOpen())
	{
		_CreateDBTable_TABLE_BAR_DATA_1DAY();
		_CreateDBTable_TABLE_SYMBOLUSE_MANAGER();
		_InitDBTable_TABLE_SYMBOLUSE_MANAGER();
	}
}

CSqliteDbOper::~CSqliteDbOper()
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



int CSqliteDbOper::_CreateDBTable_TABLE_BAR_DATA_1DAY()
{
	qint32 nFunRes = 0;
	CSQLData sqlData;
	QString  strSQLKey = "TABLE_BAR_DATA_1DAY__CREATE_TABLE__0000";

	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	
	return nFunRes;

}

int CSqliteDbOper::saveData(const QString& strSymbolUse, LstHistoryDataT* pLstData)
{
	int nFunRes = 0;
	bool bExecRes = false;
	CSQLData sqlData;
	QString  strSQLKey;
	LstHistoryDataIterT iterLst;
	CHistoryData* pDataTmp = NULL;

	QVariantList lst_COLUMN_SYMBOLUSE;
	QVariantList lst_COLUMN_DATE;
	QVariantList lst_COLUMN_OPEN;
	QVariantList lst_COLUMN_HIGH;
	QVariantList lst_COLUMN_LOW;
	QVariantList lst_COLUMN_CLOSE;
	QVariantList lst_COLUMN_VOLUME;
	QVariantList lst_COLUMN_ADJCLOSE;
	QList<QVariantList*> LstData;

	if (pLstData->empty())
	{
		nFunRes = 0;
		return nFunRes;
	}


	iterLst = pLstData->begin();
	while (iterLst != pLstData->end())
	{
		pDataTmp = (*iterLst);

		//lst_COLUMN_SYMBOLUSE << pDataTmp->m_strSymbolUse;
		lst_COLUMN_SYMBOLUSE << strSymbolUse;
		lst_COLUMN_DATE << pDataTmp->m_strDate;
		lst_COLUMN_OPEN << pDataTmp->m_strOpen;
		lst_COLUMN_HIGH << pDataTmp->m_strHigh;
		lst_COLUMN_LOW << pDataTmp->m_strLow;
		lst_COLUMN_CLOSE << pDataTmp->m_strClose;
		lst_COLUMN_VOLUME << pDataTmp->m_strVolume;
		lst_COLUMN_ADJCLOSE << pDataTmp->m_strAdjClose;

		iterLst++;
	}//while

	LstData.append(&lst_COLUMN_SYMBOLUSE);
	LstData.append(&lst_COLUMN_DATE);
	LstData.append(&lst_COLUMN_OPEN);
	LstData.append(&lst_COLUMN_HIGH);
	LstData.append(&lst_COLUMN_LOW);
	LstData.append(&lst_COLUMN_CLOSE);
	LstData.append(&lst_COLUMN_VOLUME);
	LstData.append(&lst_COLUMN_ADJCLOSE);

	strSQLKey = "TABLE_BAR_DATA_1DAY__INSERT__0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	nFunRes = m_pDbConnection->commitTransaction();
	LstData.clear();

	return nFunRes;
}

int CSqliteDbOper::selectData(const QString & strFrom, const QString & strTo, LstHistoryDataT& lstData)
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	QStringList lstColumnName;
	IQueryAdapter* pQueryAdapter = NULL;

	/*
	SELECT COLUMN_SYMBOLUSE, COLUMN_DATE, COLUMN_OPEN, COLUMN_HIGH, COLUMN_LOW, COLUMN_CLOSE, COLUMN_VOLUME, COLUMN_ADJCLOSE
	FROM TABLE_BAR_DATA_1DAY
	WHERE COLUMN_DATE >="%1" AND COLUMN_DATE <="%2" ORDER BY COLUMN_DATE ASC
	*/
	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT__0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strFrom, strTo);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE);
	lstColumnName.append(str_TABLE_BAR_DATA_Column_DATE);
	lstColumnName.append(str_TABLE_BAR_DATA_Column_OPEN);
	lstColumnName.append(str_TABLE_BAR_DATA_Column_HIGH);
	lstColumnName.append(str_TABLE_BAR_DATA_Column_LOW);
	lstColumnName.append(str_TABLE_BAR_DATA_Column_CLOSE);
	lstColumnName.append(str_TABLE_BAR_DATA_Column_VOLUME);
	lstColumnName.append(str_TABLE_BAR_DATA_Column_ADJCLOSE);

	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	lstData.clear();
	while (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		CHistoryData* pHistoryData = NULL;
		pHistoryData = new CHistoryData();
		nColumnIndex = 0;
		pHistoryData->m_strSymbolUse = pQueryAdapter->getStringData(str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE);
		nColumnIndex++;
		pHistoryData->m_strDate = pQueryAdapter->getStringData(str_TABLE_BAR_DATA_Column_DATE);
		nColumnIndex++;
		pHistoryData->m_strOpen = pQueryAdapter->getStringData(str_TABLE_BAR_DATA_Column_OPEN);
		nColumnIndex++;
		pHistoryData->m_strHigh = pQueryAdapter->getStringData(str_TABLE_BAR_DATA_Column_HIGH);
		nColumnIndex++;
		pHistoryData->m_strLow = pQueryAdapter->getStringData(str_TABLE_BAR_DATA_Column_LOW);
		nColumnIndex++;
		pHistoryData->m_strClose = pQueryAdapter->getStringData(str_TABLE_BAR_DATA_Column_CLOSE);
		nColumnIndex++;
		pHistoryData->m_strVolume = pQueryAdapter->getStringData(str_TABLE_BAR_DATA_Column_VOLUME);
		nColumnIndex++;
		pHistoryData->m_strAdjClose = pQueryAdapter->getStringData(str_TABLE_BAR_DATA_Column_ADJCLOSE);
		nColumnIndex++;

		lstData.push_back(pHistoryData);
		pHistoryData = NULL;
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}


int CSqliteDbOper::selectData_MinTime(QString& strValueGet)
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	QStringList lstColumnName;
	IQueryAdapter* pQueryAdapter = NULL;

	/*
	SELECT COLUMN_DATE FROM TABLE_BAR_DATA_1DAY	ORDER BY COLUMN_DATE ASC LIMIT 1
	*/
	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT_DATEASC_0005";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(str_TABLE_BAR_DATA_Column_DATE);

	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	strValueGet.clear();
	if (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		nColumnIndex = 0;
		strValueGet= pQueryAdapter->getStringData(str_TABLE_BAR_DATA_Column_DATE);
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}

int CSqliteDbOper::selectData_MaxTime(QString& strValueGet)
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	QStringList lstColumnName;
	IQueryAdapter* pQueryAdapter = NULL;

	/*
	SELECT COLUMN_DATE	FROM TABLE_BAR_DATA_1DAY	ORDER BY COLUMN_DATE DESC LIMIT 1
	*/
	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT_DATEDESC_0004";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(str_TABLE_BAR_DATA_Column_DATE);

	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	strValueGet.clear();
	if (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		nColumnIndex = 0;
		strValueGet= pQueryAdapter->getStringData(str_TABLE_BAR_DATA_Column_DATE);
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}

int CSqliteDbOper::selectData_Count( int& nValueGet )
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	QStringList lstColumnName;
	IQueryAdapter* pQueryAdapter = NULL;
	QString strColumnName_COUNT = "COUNT";
	/*
	SELECT COUNT(*)	as COUNT FROM TABLE_BAR_DATA_1DAY
	*/
	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT_COUNT_0006";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(strColumnName_COUNT);

	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	nValueGet = 0;
	if (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		nColumnIndex = 0;
		nValueGet= pQueryAdapter->getStringData(lstColumnName[0]).toInt();
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}



int CSqliteDbOper::selectData_LowHigh(double& fLowValueGet, double& fHighValueGet)
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	QStringList lstColumnName;
	IQueryAdapter* pQueryAdapter = NULL;
	QString str_Column_Low = "LOW";
	QString str_Column_High = "HIGH";

	//TABLE_BAR_DATA_1DAY__SELECT_LOWHIGH_0007
	/*
	SELECT MIN(COLUMN_CLOSE) AS LOW, MAX(COLUMN_CLOSE) AS HIGH FROM TABLE_BAR_DATA_1DAY;
	*/
	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT_LOWHIGH_0007";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(str_Column_Low);
	lstColumnName.append(str_Column_High);

	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	fLowValueGet = 0;
	fHighValueGet = 0;
	if (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		fLowValueGet= pQueryAdapter->getStringData(str_Column_Low).toDouble();
		fHighValueGet= pQueryAdapter->getStringData(str_Column_High).toDouble();
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}



int CSqliteDbOper::selectData_Current(double& fCurrentValueGet)
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	QStringList lstColumnName;
	IQueryAdapter* pQueryAdapter = NULL;
	QString str_Column_Current = "CURRENT";

	//TABLE_BAR_DATA_1DAY__SELECT_CURRENT_0008
	/*
	SELECT COLUMN_CLOSE AS CURRENT FROM TABLE_BAR_DATA_1DAY ORDER BY COLUMN_DATE DESC LIMIT 1;
	*/
	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT_CURRENT_0008";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(str_Column_Current);

	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	fCurrentValueGet = 0;
	if (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		fCurrentValueGet= pQueryAdapter->getStringData(str_Column_Current).toDouble();
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}



int CSqliteDbOper::_CreateDBTable_TABLE_SYMBOLUSE_MANAGER()
{
	qint32 nFunRes = 0;
	CSQLData sqlData;
	QString  strSQLKey;

	/*
	TABLE_SYMBOLUSE_MANAGER__CREATE_TABLE__0000
	CREATE TABLE IF NOT EXISTS TABLE_SYMBOLUSE_MANAGER (
	COLUMN_SYMBOLUSE TEXT NOT NULL,
	COLUMN_MAXTIME TIMESTAMP NOT NULL,
	COLUMN_UPDATFAILED INTEGER,
	PRIMARY KEY (COLUMN_SYMBOLUSE))
	*/
	strSQLKey = "TABLE_SYMBOLUSE_MANAGER__CREATE_TABLE__0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);

	return nFunRes;

}


int CSqliteDbOper::_InitDBTable_TABLE_SYMBOLUSE_MANAGER()
{	
	int nFunRes = 0;
	CSymbolUseManager* pSymbolUseManager = NULL; 


	select_TABLE_SYMBOLUSE_MANAGER(&pSymbolUseManager);
	if (NULL != pSymbolUseManager)
	{
		delete pSymbolUseManager;
		pSymbolUseManager = NULL;
		return nFunRes;
	}
	pSymbolUseManager = new CSymbolUseManager();
	pSymbolUseManager->m_strSymbolUse = m_strSymbolUse;
	pSymbolUseManager->m_nUpdateFailed = 0;
	pSymbolUseManager->m_strMaxTime = DEF_VALUE_STRING_UTC_START_DATE_TIME;

	insert_TABLE_SYMBOLUSE_MANAGER(pSymbolUseManager);

	if (NULL != pSymbolUseManager)
	{
		delete pSymbolUseManager;
		pSymbolUseManager = NULL;
	}


	return nFunRes;

}

int CSqliteDbOper::select_TABLE_SYMBOLUSE_MANAGER(CSymbolUseManager** ppData)
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	QStringList lstColumnName;
	IQueryAdapter* pQueryAdapter = NULL;
	CSymbolUseManager* pData = NULL;
	

	/*
	TABLE_SYMBOLUSE_MANAGER__SELECT__0001
	SELECT COLUMN_SYMBOLUSE, COLUMN_MAXTIME, COLUMN_UPDATFAILED FROM TABLE_SYMBOLUSE_MANAGER WHERE COLUMN_SYMBOLUSE = "%1"
	*/
	strSQLKey = "TABLE_SYMBOLUSE_MANAGER__SELECT__0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, m_strSymbolUse);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(str_TABLE_SYMBOLUSE_MANAGER_COLUMN_SYMBOLUSE);
	lstColumnName.append(str_TABLE_SYMBOLUSE_MANAGER_COLUMN_COLUMN_MAXTIME);
	lstColumnName.append(str_TABLE_SYMBOLUSE_MANAGER_COLUMN_UPDATFAILED);

	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	if (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		pData = new CSymbolUseManager();
		nColumnIndex = 0;
		pData->m_strSymbolUse = pQueryAdapter->getStringData(str_TABLE_SYMBOLUSE_MANAGER_COLUMN_SYMBOLUSE);
		nColumnIndex++;
		pData->m_strMaxTime = pQueryAdapter->getStringData(str_TABLE_SYMBOLUSE_MANAGER_COLUMN_COLUMN_MAXTIME);
		nColumnIndex++;
		pData->m_nUpdateFailed = pQueryAdapter->getStringData(str_TABLE_SYMBOLUSE_MANAGER_COLUMN_UPDATFAILED).toInt();

		*ppData = pData;
		pData = NULL;
	}

	if (NULL != pQueryAdapter)
	{
		m_pDbConnection->cleanQuery(pQueryAdapter);
		pQueryAdapter = NULL;
	}
	return nFunRes;
}


int CSqliteDbOper::insert_TABLE_SYMBOLUSE_MANAGER(const CSymbolUseManager* pData)
{
	int nFunRes = 0;
	bool bExecRes = false;
	CSQLData sqlData;
	QString  strSQLKey;

	QVariantList lst_COLUMN_SYMBOLUSE;
	QVariantList lst_COLUMN_MAXTIME;
	QVariantList lst_COLUMN_UPDATFAILED;
	QList<QVariantList*> LstData;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}
	{
		lst_COLUMN_SYMBOLUSE << pData->m_strSymbolUse;
		lst_COLUMN_MAXTIME << pData->m_strMaxTime;
		lst_COLUMN_UPDATFAILED << pData->m_nUpdateFailed;

	}//while

	LstData.append(&lst_COLUMN_SYMBOLUSE);
	LstData.append(&lst_COLUMN_MAXTIME);
	LstData.append(&lst_COLUMN_UPDATFAILED);

	strSQLKey = "TABLE_SYMBOLUSE_MANAGER__INSERT__0002";
	/*
	//TABLE_SYMBOLUSE_MANAGER__INSERT__0002
	//INSERT INTO TABLE_SYMBOLUSE_MANAGER (COLUMN_SYMBOLUSE, COLUMN_MAXTIME, COLUMN_UPDATFAILED) VALUES (?, ?, ?)
	*/
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	nFunRes = m_pDbConnection->commitTransaction();
	LstData.clear();

	return nFunRes;
}


int CSqliteDbOper::update_TABLE_SYMBOLUSE_MANAGER(const CSymbolUseManager* pData)
{
	int nFunRes = 0;
	bool bExecRes = false;
	CSQLData sqlData;
	QString  strSQLKey;
	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}
	strSQLKey = "TABLE_SYMBOLUSE_MANAGER__UPDATE__0003";
	/*
	TABLE_SYMBOLUSE_MANAGER__UPDATE__0003
	UPDATE TABLE_SYMBOLUSE_MANAGER SET  COLUMN_MAXTIME = "%1", COLUMN_UPDATFAILED = %2 WHERE COLUMN_SYMBOLUSE = "%3"
	*/
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, pData->m_strMaxTime, pData->m_nUpdateFailed, pData->m_strSymbolUse);
	nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModify(sqlData);
	nFunRes = m_pDbConnection->commitTransaction();

	return nFunRes;
}
