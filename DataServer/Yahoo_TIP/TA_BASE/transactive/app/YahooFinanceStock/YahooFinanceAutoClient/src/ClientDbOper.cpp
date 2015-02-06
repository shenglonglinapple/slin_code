#include "ClientDbOper.h"

#include <QtCore/QFile>

#include <sstream>
#include "ProjectCommonData.h"

#include "ConfigInfo.h"
#include "Log4cppLogger.h"
#include "SqliteDbOperBuildSQL.h"
#include "UserInfo.h"
#include "UserTradeInfo.h"
#include "HistoryData.h"
#include "StockMinTimeMaxTime.h"
#include "UserAccount.h"
#include "UserHoldAccount.h"

//5001.db
CClientDbOper::CClientDbOper( const QString& strSqliteDbFileName )
{
	m_pQSqlDataBase = NULL;
	m_strQTDbType = str_QtDbType_QSQLITE;
	m_strSqliteDbFileName = strSqliteDbFileName;//"002567.SZ";
	m_strSqliteDbKEY = m_strSqliteDbFileName;
	m_strSqliteDbPath = CConfigInfo::getInstance().getClientDBPath();
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + m_strSqliteDbFileName + ".db";//"C:/LSL/LSL_DATA/ClientDB/UserID.db"
	m_pSqliteDbOperBuildSQL = NULL;
	m_pSqliteDbOperBuildSQL = new CSqliteDbOperBuildSQL();
	m_pSqlTableModel_HistoryData = NULL;
	_InitDataBase();
	if (true == m_pQSqlDataBase->isValid())
	{
		_CreateDBTable_TABLE_SYMBOLUSE();
		_Truncate_TABLE_SYMBOLUSE();

		_CreateDBTable_TABLE_USER_TRADE_INFO();
		truncateTableUserTradeInfo();
		_CreateDBTable_TABLE_BAR_DATA_1DAY();
		truncateTableHistoryData();
		_CreateDBTable_TABLE_MINTIME_MAXTIME();
		truncateSymbolMinMaxTime();
		_CreateDBTable_TABLE_USER_ACCOUNT();
		_Truncate_TABLE_USER_ACCOUNT();
		_CreateDBTable_TABLE_USER_HOLD_ACCOUNT();
		_Truncate_TABLE_USER_HOLD_ACCOUNT();
	}
}

CClientDbOper::~CClientDbOper()
{
	_UnInitDataBase();
	if (NULL != m_pSqliteDbOperBuildSQL)
	{
		delete m_pSqliteDbOperBuildSQL;
		m_pSqliteDbOperBuildSQL = NULL;
	}
	if (NULL != m_pSqlTableModel_HistoryData)
	{
		delete m_pSqlTableModel_HistoryData;
		m_pSqlTableModel_HistoryData = NULL;
	}
}

QSqlDatabase* CClientDbOper::getDB()
{
	return m_pQSqlDataBase;
}

void CClientDbOper::_InitDataBase()
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

void CClientDbOper::_UnInitDataBase()
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




int CClientDbOper::_StartTransaction()
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



int CClientDbOper::_CommitTransaction()
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
qint32 CClientDbOper::_CreateDBTable_TABLE_MINTIME_MAXTIME()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_MINTIME_MAXTIME();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CClientDbOper::_CreateDBTable_TABLE_BAR_DATA_1DAY()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_BAR_DATA_1DAY();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CClientDbOper::insertUserTradeInfo(const CUserTradeInfo* pData )
{
	qint32 nFunRes = 0;
	_StartTransaction();
	nFunRes = _AddUserTradeInfo(pData);
	_CommitTransaction();
	return nFunRes;
}

qint32 CClientDbOper::_AddUserTradeInfo( const CUserTradeInfo* pData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQL;

	QVariantList lst_COLUMN_USEID;
	QVariantList lst_COLUMN_TRADE_UUID;
	QVariantList lst_COLUMN_TRADE_TIME;
	QVariantList lst_COLUMN_TRADE_TYPE;
	QVariantList lst_COLUMN_SYMBOLUSE;
	QVariantList lst_COLUMN_TRADE_PRICE;
	QVariantList lst_COLUMN_TRADE_VOLUME;
	QVariantList lst_COLUMN_TRADE_AMOUNT;
	QVariantList lst_COLUMN_TRADE_FEES;
	QVariantList lst_COLUMN_TOTAL_TRADE_FEE;
	QVariantList lst_COLUMN_USE_ACCOUNT;

	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_BatchInsert_TABLE_USER_TRADE_INFO();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL;
	pQSqlQueryForInseert->prepare(strSQL);

	{
		lst_COLUMN_USEID << pData->m_strUserID;
		lst_COLUMN_TRADE_UUID << pData->m_strTradeUUID;
		lst_COLUMN_TRADE_TIME << pData->m_strTradeTime;
		lst_COLUMN_TRADE_TYPE << (qint32)pData->m_nTradeType;
		lst_COLUMN_SYMBOLUSE << pData->m_strSymbolUse;
		lst_COLUMN_TRADE_PRICE << pData->m_fTradePrice;
		lst_COLUMN_TRADE_VOLUME << pData->m_nTradeVolume;
		lst_COLUMN_TRADE_AMOUNT << pData->m_fTradeAmount;
		lst_COLUMN_TRADE_FEES << pData->m_fTradeFees;
		lst_COLUMN_TOTAL_TRADE_FEE << pData->m_fTotalTradeFee;
		lst_COLUMN_USE_ACCOUNT << pData->m_fUseAccount;
	}

	pQSqlQueryForInseert->addBindValue(lst_COLUMN_USEID);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_TRADE_UUID);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_TRADE_TIME);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_TRADE_TYPE);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_SYMBOLUSE);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_TRADE_PRICE);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_TRADE_VOLUME);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_TRADE_AMOUNT);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_TRADE_FEES);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_TOTAL_TRADE_FEE);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_USE_ACCOUNT);
	
	bExecRes = pQSqlQueryForInseert->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<strSQL
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}


qint32 CClientDbOper::selectDataHistory_ASC_PRICE( const QString& strSymbolUse, CHistoryData** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CHistoryData* pSelectData = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_ASC_TABLE_BAR_DATA_1DAY_PRICE(strSymbolUse);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL);
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR	<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"Fail to exec strSQL="<<strSQL
			<<" "<<"error:"<<pSqlQuery->lastError().text().toStdString();

		delete pSqlQuery;
		pSqlQuery = NULL;		
		return nFunRes;
	}

	if ( pSqlQuery->next() )
	{
		pSelectData = new CHistoryData();
		nColumnIndex = 0;
		pSelectData->m_strSymbolUse = pSqlQuery->value(nColumnIndex).toString();
		//pSelectData->m_strSymbolUse = pSqlQuery->value(str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE).toString();
		nColumnIndex++;
		pSelectData->m_strDate = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strOpen = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strHigh = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strLow = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strClose = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strVolume = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strAdjClose = pSqlQuery->value(nColumnIndex).toString();


		(*ppData) = pSelectData;
		pSelectData = NULL;
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}
qint32 CClientDbOper::selectDataHistory_DataTime( const QString& strSymbolUse,const QString& strDateTime, CHistoryData** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CHistoryData* pSelectData = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_TABLE_BAR_DATA_1DAY_PRICE(strSymbolUse, strDateTime);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL);
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR	<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"Fail to exec strSQL="<<strSQL
			<<" "<<"error:"<<pSqlQuery->lastError().text().toStdString();

		delete pSqlQuery;
		pSqlQuery = NULL;		
		return nFunRes;
	}

	if ( pSqlQuery->next() )
	{
		pSelectData = new CHistoryData();
		nColumnIndex = 0;
		pSelectData->m_strSymbolUse = pSqlQuery->value(nColumnIndex).toString();
		//pSelectData->m_strSymbolUse = pSqlQuery->value(str_TABLE_BAR_DATA_COLUMN_SYMBOLUSE).toString();
		nColumnIndex++;
		pSelectData->m_strDate = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strOpen = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strHigh = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strLow = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strClose = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strVolume = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pSelectData->m_strAdjClose = pSqlQuery->value(nColumnIndex).toString();


		(*ppData) = pSelectData;
		pSelectData = NULL;
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}

void CClientDbOper::resetHistoryData( const QString& strSymbolUse, const QList<CHistoryData*>& lstData )
{
	_StartTransaction();
	truncateTableHistoryData();
	_AddHistoryDataLst(lstData);
	_CommitTransaction();
}

qint32 CClientDbOper::_AddHistoryDataLst( const QList<CHistoryData*>& lstData )
{
	int nFunRes = 0;
	bool bExecRes = false;
	QString  strSQL;
	QList<CHistoryData*>::const_iterator iterLst;
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

	if (lstData.isEmpty())
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_BatchInsert_TABLE_BAR_DATA_1DAY();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL
		<<" "<<"lstData.size="<<lstData.size();

	pQSqlQueryForInseert->prepare(strSQL);

	iterLst = lstData.begin();
	while (iterLst != lstData.end())
	{
		pDataTmp = (*iterLst);

		lst_COLUMN_SYMBOLUSE<<pDataTmp->m_strSymbolUse;
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
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<strSQL
			<<" "<<"lstData.size="<<lstData.size()
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

void CClientDbOper::truncateTableHistoryData()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Truncate_TABLE_BAR_DATA_1DAY();
	nFunRes = _ExecModify(strSQL);
}


qint32 CClientDbOper::_AddSymbolMinMaxTime( const CStockMinTimeMaxTime* pData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQL;

	QVariantList lst_COLUMN_SYMBOLUSE;
	QVariantList lst_COLUMN_MINTIME;
	QVariantList lst_COLUMN_MAXTIME;
	QVariantList lst_COLUMN_COUNT;

	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_BatchInsert_TABLE_MINTIME_MAXTIME();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<strSQL;
	pQSqlQueryForInseert->prepare(strSQL);

	{
		lst_COLUMN_SYMBOLUSE << pData->m_strSymbolUse;
		lst_COLUMN_MINTIME << pData->m_strMinTime;
		lst_COLUMN_MAXTIME << pData->m_strMaxTime;
		lst_COLUMN_COUNT << pData->m_nCount;
	}

	pQSqlQueryForInseert->addBindValue(lst_COLUMN_SYMBOLUSE);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_MINTIME);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_MAXTIME);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_COUNT);

	bExecRes = pQSqlQueryForInseert->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<strSQL
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

qint32 CClientDbOper::insertSymbolMinMaxTime( const CStockMinTimeMaxTime* pData )
{
	qint32 nFunRes = 0;
	_StartTransaction();
	nFunRes = _AddSymbolMinMaxTime(pData);
	_CommitTransaction();
	return nFunRes;
}

qint32 CClientDbOper::updateSymbolMinMaxTime( const CStockMinTimeMaxTime* pData )
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_UPDATE_TABLE_MINTIME_MAXTIME(
		pData->m_strSymbolUse, pData->m_strMinTime, 
		pData->m_strMaxTime, pData->m_nCount);
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CClientDbOper::selectSymbolMinMaxTime( const QString& strSymbolUse, CStockMinTimeMaxTime** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CStockMinTimeMaxTime* pDataGet = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_TABLE_MINTIME_MAXTIME(strSymbolUse);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL);
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR	<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"Fail to exec strSQL="<<strSQL
			<<" "<<"error:"<<pSqlQuery->lastError().text().toStdString();

		delete pSqlQuery;
		pSqlQuery = NULL;		
		return nFunRes;
	}

	if ( pSqlQuery->next() )
	{
		pDataGet = new CStockMinTimeMaxTime();
		nColumnIndex = 0;
		pDataGet->m_strSymbolUse = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pDataGet->m_strMinTime = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pDataGet->m_strMaxTime = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pDataGet->m_nCount = pSqlQuery->value(nColumnIndex).toInt();

		(*ppData) = pDataGet;
		pDataGet = NULL;
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}
//////////////////////////////////////////////////////////////////////////
qint32 CClientDbOper::_CreateDBTable_TABLE_USER_TRADE_INFO()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_USER_TRADE_INFO();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}
void CClientDbOper::truncateTableUserTradeInfo()
{
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Truncate_TABLE_USER_TRADE_INFO();
	_ExecModify(strSQL);
}

void CClientDbOper::truncateSymbolMinMaxTime()
{
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Truncate_TABLE_MINTIME_MAXTIME();
	_ExecModify(strSQL);
	
}
qint32 CClientDbOper::_ExecModify(const QString& strSQL)
{
	qint32 nFunRes = 0;
	bool bExecRes = true;

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
//////////////////////////////////////////////////////////////////////////
qint32 CClientDbOper::_CreateDBTable_TABLE_USER_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_USER_ACCOUNT();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CClientDbOper::_Truncate_TABLE_USER_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Truncate_TABLE_USER_ACCOUNT();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CClientDbOper::resetUserAccount( const CUserAccount* pData )
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Update_TABLE_USER_ACCOUNT(pData);
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CClientDbOper::insertUserAccount(const CUserAccount* pData )
{
	qint32 nFunRes = 0;
	_StartTransaction();
	nFunRes = _AddUserAccount(pData);
	_CommitTransaction();
	return nFunRes;
}
qint32 CClientDbOper::_AddUserAccount( const CUserAccount* pData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQL;

	QVariantList COLUMN_USEID;
	QVariantList COLUMN_INIT_AMOUNT;
	QVariantList COLUMN_LEFT_AMOUNT;
	QVariantList COLUMN_HOLD_AMOUNT;
	QVariantList COLUMN_FLOATINT_PROFIT_LOSS;
	QVariantList COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE;
	QVariantList COLUMN_UPDATE_TIME;


	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_BatchInsert_TABLE_USER_ACCOUNT();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL;
	pQSqlQueryForInseert->prepare(strSQL);

	{
		COLUMN_USEID << pData->m_strUserID;
		COLUMN_INIT_AMOUNT << pData->m_fInitAccount;
		COLUMN_LEFT_AMOUNT << pData->m_fLeftAccount;
		COLUMN_HOLD_AMOUNT << pData->m_fHoldAccount;
		COLUMN_FLOATINT_PROFIT_LOSS << pData->m_fFloatingProfitLoss;
		COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE << pData->m_fFloatingProfitLossPersentage;
		COLUMN_UPDATE_TIME << pData->m_strUpdateTime;
	}
	pQSqlQueryForInseert->addBindValue(COLUMN_USEID);
	pQSqlQueryForInseert->addBindValue(COLUMN_INIT_AMOUNT);
	pQSqlQueryForInseert->addBindValue(COLUMN_LEFT_AMOUNT);
	pQSqlQueryForInseert->addBindValue(COLUMN_HOLD_AMOUNT);
	pQSqlQueryForInseert->addBindValue(COLUMN_FLOATINT_PROFIT_LOSS);
	pQSqlQueryForInseert->addBindValue(COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE);
	pQSqlQueryForInseert->addBindValue(COLUMN_UPDATE_TIME);

	bExecRes = pQSqlQueryForInseert->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<strSQL
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

qint32 CClientDbOper::resetUserHoldAccount( const QList<CUserHoldAccount*>& lstData )
{
	qint32 nFunRes = 0;
	_StartTransaction();
	_Truncate_TABLE_USER_HOLD_ACCOUNT();
	nFunRes = _AddUserHoldAccountLst(lstData);
	_CommitTransaction();
	return nFunRes;
}



//////////////////////////////////////////////////////////////////////////
qint32 CClientDbOper::_CreateDBTable_TABLE_USER_HOLD_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_USER_HOLD_ACCOUNT();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CClientDbOper::_Truncate_TABLE_USER_HOLD_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Truncate_TABLE_USER_HOLD_ACCOUNT();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CClientDbOper::_AddUserHoldAccountLst( const QList<CUserHoldAccount*>& lstData)
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQL;
	QList<CUserHoldAccount*>::const_iterator iterLst;
	CUserHoldAccount* pData = NULL;

	QVariantList COLUMN_USEID;
	QVariantList COLUMN_SYMBOLUSE;
	QVariantList COLUMN_PRICE;
	QVariantList COLUMN_VOLUME;
	QVariantList COLUMN_TIME;
	QVariantList COLUMN_AMOUNT;

	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (0 >= lstData.size())
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_BatchInsert_TABLE_USER_HOLD_ACCOUNT();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL;
	pQSqlQueryForInseert->prepare(strSQL);


	iterLst = lstData.constBegin();
	while (iterLst != lstData.constEnd())
	{
		pData = (*iterLst);

		COLUMN_USEID << pData->m_strUserID;
		COLUMN_SYMBOLUSE << pData->m_strSymbolUse;
		COLUMN_PRICE << pData->m_fPrice;
		COLUMN_VOLUME << pData->m_nVolume;
		COLUMN_TIME << pData->m_strTime;
		COLUMN_AMOUNT << pData->m_fHoldAccount;

		iterLst++;
	}//while


	pQSqlQueryForInseert->addBindValue(COLUMN_USEID);
	pQSqlQueryForInseert->addBindValue(COLUMN_SYMBOLUSE);
	pQSqlQueryForInseert->addBindValue(COLUMN_PRICE);
	pQSqlQueryForInseert->addBindValue(COLUMN_VOLUME);
	pQSqlQueryForInseert->addBindValue(COLUMN_TIME);
	pQSqlQueryForInseert->addBindValue(COLUMN_AMOUNT);

	bExecRes = pQSqlQueryForInseert->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<strSQL
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

qint32 CClientDbOper::_CreateDBTable_TABLE_SYMBOLUSE()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_SYMBOLUSE();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}
qint32 CClientDbOper::_Truncate_TABLE_SYMBOLUSE()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Truncate_TABLE_SYMBOLUSE();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CClientDbOper::_AddSymbolLst( const QList<QString>& lstData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQL;
	QList<QString>::const_iterator iterLst;
	QString strData;
	QVariantList COLUMN_SYMBOLUSE;

	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (0 >= lstData.size())
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_BatchInsert_TABLE_SYMBOLUSE();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL;
	pQSqlQueryForInseert->prepare(strSQL);

	iterLst = lstData.constBegin();
	while (iterLst != lstData.constEnd())
	{
		strData = (*iterLst);
		COLUMN_SYMBOLUSE << strData;
		iterLst++;
	}//while
	pQSqlQueryForInseert->addBindValue(COLUMN_SYMBOLUSE);
	bExecRes = pQSqlQueryForInseert->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<strSQL
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

qint32 CClientDbOper::resetSymbolUse( const QList<QString>& lstData )
{
	qint32 nFunRes = 0;
	_StartTransaction();
	_Truncate_TABLE_SYMBOLUSE();
	nFunRes = _AddSymbolLst(lstData);
	_CommitTransaction();
	return nFunRes;
}

qint32 CClientDbOper::getSymbolUseLst(QList<QString>& lstData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	QString strSymbolUse;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_TABLE_SYMBOLUSE();
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL);
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_ERROR	<<" "<<m_strSqliteDbFileFullPath.toStdString()
			<<" "<<"Fail to exec strSQL="<<strSQL
			<<" "<<"error:"<<pSqlQuery->lastError().text().toStdString();

		delete pSqlQuery;
		pSqlQuery = NULL;		
		return nFunRes;
	}

	while ( pSqlQuery->next() )
	{
		strSymbolUse.clear();
		nColumnIndex = 0;
		strSymbolUse = pSqlQuery->value(nColumnIndex).toString();
		lstData.push_back(strSymbolUse);
		strSymbolUse.clear();
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}
