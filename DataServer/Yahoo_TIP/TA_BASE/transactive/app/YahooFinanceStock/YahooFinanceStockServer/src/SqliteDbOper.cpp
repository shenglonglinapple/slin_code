#include "SqliteDbOper.h"

#include <QtCore/QFile>

#include <sstream>
#include "HistoryData.h"
#include "ConfigInfo.h"
#include "Log4cppLogger.h"
#include "UserInfo.h"
#include "ProjectSQLManager.h"

static const char*  str_QtDbType_QSQLITE = "QSQLITE";
static const char*  str_QtDbType_QMYSQL = "QMYSQL";



//strSymbolUse
CSqliteDbOper::CSqliteDbOper( const QString& strSqliteDbFileName )
{
	m_pQSqlDataBase = NULL;
	m_strQTDbType = str_QtDbType_QSQLITE;
	m_strSqliteDbFileName = strSqliteDbFileName;//"002567.SZ";
	m_strSqliteDbKEY = m_strSqliteDbFileName;
	m_strSqliteDbPath = CConfigInfo::getInstance().getSQLiteDBPath();
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + m_strSqliteDbFileName;
	_InitDataBase();
	if (true == m_pQSqlDataBase->isValid())
	{
		_CreateDBTable_TABLE_BAR_DATA_1DAY();
	}
}

CSqliteDbOper::~CSqliteDbOper()
{
	_UnInitDataBase();

}


void CSqliteDbOper::_InitDataBase()
{
	_UnInitDataBase();
	
	m_pQSqlDataBase = new QSqlDatabase(QSqlDatabase::addDatabase(m_strQTDbType, m_strSqliteDbKEY));
	m_pQSqlDataBase->setDatabaseName(m_strSqliteDbFileFullPath);

	MYLOG4CPP_DEBUG<<m_strQTDbType.toStdString()
		<<" "<<"new Database  m_strQTDbType="<<m_strQTDbType.toStdString()
		<<" "<<"m_strSqliteDbFileName="<<m_strSqliteDbFileName.toStdString()
		<<" "<<"m_strSqliteDbKEY="<<m_strSqliteDbKEY.toStdString()
		<<" "<<"m_strSqliteDbFileFullPath="<<m_strSqliteDbFileFullPath.toStdString();


	if (false == m_pQSqlDataBase->open())
	{
		MYLOG4CPP_ERROR<<m_strQTDbType.toStdString()
			<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"Fail to open!"
			<<" "<<"error:"<<m_pQSqlDataBase->lastError().text().toStdString();
	}

	//check
	if (false == m_pQSqlDataBase->isValid())
	{
		MYLOG4CPP_ERROR<<m_strQTDbType.toStdString()
			<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"is not Valid";
	}

	if (false == m_pQSqlDataBase->driver()->hasFeature(QSqlDriver::Transactions)) 
	{
		MYLOG4CPP_ERROR<<m_strQTDbType.toStdString()
			<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"not support Transactions";
	}
	else
	{
		MYLOG4CPP_DEBUG<<m_strQTDbType.toStdString()
			<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"support Transactions";
	}
	///////


}

void CSqliteDbOper::_UnInitDataBase()
{

	if (NULL != m_pQSqlDataBase)
	{
		MYLOG4CPP_DEBUG<<m_strQTDbType.toStdString()
			<<" "<<"delete Database  m_strSqliteDbFileName="<<m_strSqliteDbFileName.toStdString();

		m_pQSqlDataBase->close();
		delete m_pQSqlDataBase;
		m_pQSqlDataBase = NULL;
		QSqlDatabase::removeDatabase(m_strSqliteDbKEY);
	}
}




int CSqliteDbOper::_StartTransaction()
{
	int nFunRes = 0;

	if (false == m_pQSqlDataBase->driver()->hasFeature(QSqlDriver::Transactions)) 
	{
		MYLOG4CPP_ERROR<<m_strQTDbType.toStdString()
			<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"not support Transactions";
		nFunRes = -1;
		return nFunRes;
	}

	if (false == m_pQSqlDataBase->transaction())
	{
		MYLOG4CPP_ERROR<<m_strQTDbType.toStdString()
			<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"support Transactions but start transaction error!"
			<<" "<<"error: "<<QSqlDatabase::database().lastError().text().toStdString();
		nFunRes = -1;
	}
	else
	{
		MYLOG4CPP_DEBUG<<m_strQTDbType.toStdString()
			<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"start Transaction";
		nFunRes = 0;
	}

	return nFunRes;
}



int CSqliteDbOper::_CommitTransaction()
{
	int nFunRes = 0;

	if (NULL == m_pQSqlDataBase)
	{
		nFunRes = -1;
		return nFunRes;
	}

	if(false == m_pQSqlDataBase->commit())  
	{  
		MYLOG4CPP_ERROR<<m_strQTDbType.toStdString()
			<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"commit error!"
			<<" "<<"error: "<<QSqlDatabase::database().lastError().text().toStdString();

		if(false == m_pQSqlDataBase->rollback())  
		{  
			MYLOG4CPP_ERROR<<m_strQTDbType.toStdString()
				<<" "<<m_strSqliteDbFileFullPath.toStdString()
				<<" "<<"rollback error!"
				<<" "<<"error: "<<QSqlDatabase::database().lastError().text().toStdString();
		}//if 
	}//if
	else
	{
		MYLOG4CPP_DEBUG<<m_strQTDbType.toStdString()
			<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"commit Transaction";
	}
	return nFunRes;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void CSqliteDbOper::saveData(LstHistoryDataT* pLstData)
{
	_StartTransaction();
	_AddDataArray(pLstData);
	_CommitTransaction();
}


int CSqliteDbOper::_CreateDBTable_TABLE_BAR_DATA_1DAY()
{
	qint32 nFunRes = 0;
	CSQLData sqlData;
	QString  strSQLKey = "TABLE_BAR_DATA_1DAY__CREATE_TABLE__0000";

	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = _ExecModify(sqlData);
	return nFunRes;

}


int CSqliteDbOper::_AddDataArray(LstHistoryDataT* pLstData)
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
	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (pLstData->empty())
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQLKey = "TABLE_BAR_DATA_1DAY__INSERT__0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<sqlData.getSqliteSQL()
		<<" "<<"LstHistoryDataT.size="<<pLstData->size();

	pQSqlQueryForInseert->prepare(sqlData.getSqliteSQL());

	iterLst = pLstData->begin();
	while (iterLst != pLstData->end())
	{
		pDataTmp = (*iterLst);

		lst_COLUMN_SYMBOLUSE << pDataTmp->m_strSymbolUse;
		lst_COLUMN_DATE << pDataTmp->m_strDate;
		lst_COLUMN_OPEN << pDataTmp->m_strOpen;
		lst_COLUMN_HIGH << pDataTmp->m_strHigh;
		lst_COLUMN_LOW << pDataTmp->m_strLow;
		lst_COLUMN_CLOSE << pDataTmp->m_strClose;
		lst_COLUMN_VOLUME << pDataTmp->m_strVolume;
		lst_COLUMN_ADJCLOSE << pDataTmp->m_strAdjClose;

		iterLst++;
	}//while

	pQSqlQueryForInseert->addBindValue(lst_COLUMN_SYMBOLUSE);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_DATE);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_OPEN);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_HIGH);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_LOW);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_CLOSE);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_VOLUME);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_ADJCLOSE);

	bExecRes = pQSqlQueryForInseert->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR<<"execBatch strSQL="<<sqlData.getSqliteSQL()
			<<" "<<"LstHistoryDataT.size="<<pLstData->size()
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

int CSqliteDbOper::selectData(const QString & strFrom, const QString & strTo, LstHistoryDataT& lstData)
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString strSQLKey;
	CSQLData sqlData;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;

	lstData.clear();
	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);
	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT__0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strFrom, strTo);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();

	bExecRes = pSqlQuery->exec(sqlData.getSqliteSQL());

	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR	<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"Fail to exec strSQL="<<sqlData.getSqliteSQL()
			<<" "<<"error:"<<pSqlQuery->lastError().text().toStdString();

		delete pSqlQuery;
		pSqlQuery = NULL;		
		return nFunRes;
	}

	while ( pSqlQuery->next() )
	{
		CHistoryData* pHistoryData = NULL;
		pHistoryData = new CHistoryData();
		nColumnIndex = 0;

		pHistoryData->m_strSymbolUse = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pHistoryData->m_strDate = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pHistoryData->m_strOpen = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pHistoryData->m_strHigh = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pHistoryData->m_strLow = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pHistoryData->m_strClose = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pHistoryData->m_strVolume = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pHistoryData->m_strAdjClose = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
	
		lstData.push_back(pHistoryData);
		pHistoryData = NULL;
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}


int CSqliteDbOper::selectData_MinTime(QString& strValueGet)
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT_DATEASC_0005";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
	bExecRes = pSqlQuery->exec(sqlData.getSqliteSQL());
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR	<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"Fail to exec strSQL="<<sqlData.getSqliteSQL()
			<<" "<<"error:"<<pSqlQuery->lastError().text().toStdString();

		delete pSqlQuery;
		pSqlQuery = NULL;		
		return nFunRes;
	}

	strValueGet.clear();
	if ( pSqlQuery->next() )
	{
		nColumnIndex = 0;
		strValueGet = pSqlQuery->value(nColumnIndex).toString();	
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}

int CSqliteDbOper::selectData_MaxTime(QString& strValueGet)
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT_DATEDESC_0004";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
	bExecRes = pSqlQuery->exec(sqlData.getSqliteSQL());
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR	<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"Fail to exec strSQL="<<sqlData.getSqliteSQL()
			<<" "<<"error:"<<pSqlQuery->lastError().text().toStdString();

		delete pSqlQuery;
		pSqlQuery = NULL;		
		return nFunRes;
	}

	strValueGet.clear();
	if ( pSqlQuery->next() )
	{
		nColumnIndex = 0;
		strValueGet = pSqlQuery->value(nColumnIndex).toString();	
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}

int CSqliteDbOper::selectData_Count( int& nValueGet )
{
	int nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQLKey = "TABLE_BAR_DATA_1DAY__SELECT_COUNT_0006";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
	bExecRes = pSqlQuery->exec(sqlData.getSqliteSQL());
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR	<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"Fail to exec strSQL="<<sqlData.getSqliteSQL()
			<<" "<<"error:"<<pSqlQuery->lastError().text().toStdString();

		delete pSqlQuery;
		pSqlQuery = NULL;		
		return nFunRes;
	}

	nValueGet = 0;
	if ( pSqlQuery->next() )
	{
		nColumnIndex = 0;
		nValueGet = pSqlQuery->value(nColumnIndex).toInt();	
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}

qint32 CSqliteDbOper::_ExecModify(const CSQLData& sqlData)
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString strSQL = sqlData.getSqliteSQL();

	QSqlQuery* pSqlQuery = NULL;
	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL);
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR	<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"Fail to exec strSQL="<<strSQL
			<<" "<<"error:"<<pSqlQuery->lastError().text().toStdString();
	}

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}
	return nFunRes;
}