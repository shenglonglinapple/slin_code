#include "ClientDbOper.h"

#include <QtCore/QFile>


#include "ConfigInfo.h"
#include "Log4cppLogger.h"
#include "UserInfo.h"
#include "UserTradeInfo.h"
#include "HistoryData.h"
#include "StockMinTimeMaxTime.h"
#include "UserAccount.h"
#include "UserHoldAccount.h"

#include "ProjectSQLManager.h"
#include "ProjectDBStruct.h"
#include "DbStatusItem.h"
#include "QtDBConnection.h"
#include "IQueryAdapter.h"

//5001.db
CClientDbOper::CClientDbOper( const QString& strUserID )
{
	m_pDbConnection = NULL;
	m_pDbStatusItem = NULL;
	
	m_strSqliteDbPath = CConfigInfo::getInstance().getClientDBPath();
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + strUserID + ".db";//"C:/LSL/LSL_DATA/ClientDB/UserID.db"

	m_pDbStatusItem = new CDbStatusItem();
	m_pDbStatusItem->m_nDBType = CDbStatusItem::DBType_QSQLITE;
	m_pDbStatusItem->m_strSchema = m_strSqliteDbFileFullPath;//"C:\\LSL\\LSL_DATA\\ClientDB\\UserNameValuelsl_PassWordValuelsl.db";
	m_pDbStatusItem->setProperties();

	m_pDbConnectionQtRef = new CQtDBConnection(m_pDbStatusItem);
	m_pDbConnection = (IDbConnection*)m_pDbConnectionQtRef;
	m_pDbConnection->open();

	if (true == m_pDbConnection->isOpen())
	{
		_CreateDBTable_TABLE_SYMBOLUSE();
		_Truncate_TABLE_SYMBOLUSE();
		_CreateDBTable_TABLE_USER_TRADE_INFO();
		truncate_TABLE_USER_TRADE_INFO();
		_CreateDBTable_TABLE_BAR_DATA_1DAY();
		truncate_TABLE_BAR_DATA_1DAY();
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
	m_pDbConnectionQtRef = NULL;
}

//////////////////////////////////////////////////////////////////////////
qint32 CClientDbOper::_CreateDBTable_TABLE_MINTIME_MAXTIME()
{
	qint32 nFunRes = 0;
	CSQLData sqlData;
	QString  strSQLKey = "TABLE_MINTIME_MAXTIME__CREATE_TABLE_0000";

	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}

qint32 CClientDbOper::_CreateDBTable_TABLE_BAR_DATA_1DAY()
{
	qint32 nFunRes = 0;
	CSQLData sqlData;
	QString  strSQLKey = "TABLE_BAR_DATA_1DAY__CREATE_TABLE__0000";

	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}

qint32 CClientDbOper::insertUserTradeInfo( const CUserTradeInfo* pData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQLKey;
	CSQLData sqlData;

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

	QList<QVariantList*> LstData;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	strSQLKey = "TABLE_USER_TRADE_INFO__INSERT_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);


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
	LstData.append(&lst_COLUMN_USEID);
	LstData.append(&lst_COLUMN_TRADE_UUID);
	LstData.append(&lst_COLUMN_TRADE_TIME);
	LstData.append(&lst_COLUMN_TRADE_TYPE);
	LstData.append(&lst_COLUMN_SYMBOLUSE);
	LstData.append(&lst_COLUMN_TRADE_PRICE);
	LstData.append(&lst_COLUMN_TRADE_VOLUME);
	LstData.append(&lst_COLUMN_TRADE_AMOUNT);
	LstData.append(&lst_COLUMN_TRADE_FEES);
	LstData.append(&lst_COLUMN_TOTAL_TRADE_FEE);
	LstData.append(&lst_COLUMN_USE_ACCOUNT);


	nFunRes = m_pDbConnection->startTransaction();
	bExecRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	nFunRes = m_pDbConnection->commitTransaction();
	LstData.clear();

	return nFunRes;
}


void CClientDbOper::reset_TABLE_BAR_DATA_1DAY( const QString& strSymbolUse, const QList<CHistoryData*>& lstData )
{
	qint32 nFunRes = 0;
	truncate_TABLE_BAR_DATA_1DAY();
	nFunRes = m_pDbConnection->startTransaction();
	_AddHistoryDataLst(lstData);
	nFunRes = m_pDbConnection->commitTransaction();
}

qint32 CClientDbOper::_AddHistoryDataLst( const QList<CHistoryData*>& lstData )
{
	int nFunRes = 0;
	CSQLData sqlData;
	QString  strSQLKey;
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
	QList<QVariantList*> LstData;

	if (lstData.isEmpty())
	{
		nFunRes = 0;
		return nFunRes;
	}

	strSQLKey = "TABLE_BAR_DATA_1DAY__INSERT__0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

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

	LstData.append(&lst_COLUMN_SYMBOLUSE);
	LstData.append(&lst_COLUMN_DATE);
	LstData.append(&lst_COLUMN_OPEN);
	LstData.append(&lst_COLUMN_HIGH);
	LstData.append(&lst_COLUMN_LOW);
	LstData.append(&lst_COLUMN_CLOSE);
	LstData.append(&lst_COLUMN_VOLUME);
	LstData.append(&lst_COLUMN_ADJCLOSE);

	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);

	return nFunRes;
}

void CClientDbOper::truncate_TABLE_BAR_DATA_1DAY()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_BAR_DATA_1DAY__DELETE__0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);

}


qint32 CClientDbOper::insertSymbolMinMaxTime( const CStockMinTimeMaxTime* pData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQLKey;
	CSQLData sqlData;

	QVariantList lst_COLUMN_SYMBOLUSE;
	QVariantList lst_COLUMN_MINTIME;
	QVariantList lst_COLUMN_MAXTIME;
	QVariantList lst_COLUMN_COUNT;
	QVariantList lst_COLUMN_LOW;
	QVariantList lst_COLUMN_HIGH;
	QVariantList lst_COLUMN_CURRENT;
	QVariantList lst_COLUMN_CURRENTPERCENTAGE;
	QList<QVariantList*> LstData;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	strSQLKey = "TABLE_MINTIME_MAXTIME__INSERT_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	{
		lst_COLUMN_SYMBOLUSE << pData->m_strSymbolUse;
		lst_COLUMN_MINTIME << pData->m_strMinTime;
		lst_COLUMN_MAXTIME << pData->m_strMaxTime;
		lst_COLUMN_COUNT << pData->m_nCount;
		lst_COLUMN_LOW << pData->m_fLow;
		lst_COLUMN_HIGH << pData->m_fHigh;
		lst_COLUMN_CURRENT << pData->m_fCurrent;
		lst_COLUMN_CURRENTPERCENTAGE << pData->m_fCurrentPercentage;
	}
	LstData.append(&lst_COLUMN_SYMBOLUSE);
	LstData.append(&lst_COLUMN_MINTIME);
	LstData.append(&lst_COLUMN_MAXTIME);
	LstData.append(&lst_COLUMN_COUNT);
	LstData.append(&lst_COLUMN_LOW);
	LstData.append(&lst_COLUMN_HIGH);
	LstData.append(&lst_COLUMN_CURRENT);
	LstData.append(&lst_COLUMN_CURRENTPERCENTAGE);

	nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	nFunRes = m_pDbConnection->commitTransaction();
	LstData.clear();

	return nFunRes;
}



qint32 CClientDbOper::updateSymbolMinMaxTime( const CStockMinTimeMaxTime* pData )
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;

	strSQLKey = "TABLE_MINTIME_MAXTIME__UPDATE_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey,
		pData->m_strSymbolUse,
		pData->m_strMinTime,
		pData->m_strMaxTime,
		pData->m_nCount,
		pData->m_fLow,
		pData->m_fHigh,
		pData->m_fCurrent,
		pData->m_fCurrentPercentage,
		pData->m_strSymbolUse);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}

qint32 CClientDbOper::selectSymbolMinMaxTime( const QString& strSymbolUse, CStockMinTimeMaxTime** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;

	int nColumnIndex = 0;
	CStockMinTimeMaxTime* pDataGet = NULL;
	IQueryAdapter* pQueryAdapter = NULL;
	QStringList lstColumnName;

	strSQLKey = "TABLE_MINTIME_MAXTIME__SELECT_0004";
	/*
	SELECT COLUMN_SYMBOLUSE, COLUMN_MINTIME, COLUMN_MAXTIME, COLUMN_COUNT, COLUMN_LOW, COLUMN_HIGH, COLUMN_CURRENT, COLUMN_CURRENTPERCENTAGE
	FROM TABLE_MINTIME_MAXTIME WHERE COLUMN_SYMBOLUSE = "%1"
	*/
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strSymbolUse);
	m_pDbConnection->execQuery(sqlData, pQueryAdapter);
	lstColumnName.clear();
	lstColumnName.append(str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE);
	lstColumnName.append(str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME);
	lstColumnName.append(str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME);
	lstColumnName.append(str_TABLE_MINTIME_MAXTIME_COLUMN_COUNT);
	lstColumnName.append(str_TABLE_MINTIME_MAXTIME_COLUMN_LOW);
	lstColumnName.append(str_TABLE_MINTIME_MAXTIME_COLUMN_HIGH);
	lstColumnName.append(str_TABLE_MINTIME_MAXTIME_COLUMN_CURRENT);
	lstColumnName.append(str_TABLE_MINTIME_MAXTIME_COLUMN_CURRENTPERCENTAGE);

	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}

	if (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		pDataGet = new CStockMinTimeMaxTime();
		nColumnIndex = 0;
		pDataGet->m_strSymbolUse = pQueryAdapter->getStringData(str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE);
		nColumnIndex++;
		pDataGet->m_strMinTime = pQueryAdapter->getStringData(str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME);
		nColumnIndex++;
		pDataGet->m_strMaxTime = pQueryAdapter->getStringData(str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME);
		nColumnIndex++;
		pDataGet->m_nCount = pQueryAdapter->getStringData(str_TABLE_MINTIME_MAXTIME_COLUMN_COUNT).toInt();
		nColumnIndex++;
		pDataGet->m_fLow = pQueryAdapter->getStringData(str_TABLE_MINTIME_MAXTIME_COLUMN_LOW).toDouble();
		nColumnIndex++;
		pDataGet->m_fHigh = pQueryAdapter->getStringData(str_TABLE_MINTIME_MAXTIME_COLUMN_HIGH).toDouble();
		nColumnIndex++;
		pDataGet->m_fCurrent = pQueryAdapter->getStringData(str_TABLE_MINTIME_MAXTIME_COLUMN_CURRENT).toDouble();
		nColumnIndex++;
		pDataGet->m_fCurrentPercentage = pQueryAdapter->getStringData(str_TABLE_MINTIME_MAXTIME_COLUMN_CURRENTPERCENTAGE).toDouble();

		(*ppData) = pDataGet;
		pDataGet = NULL;
	}//while
	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}
//////////////////////////////////////////////////////////////////////////
qint32 CClientDbOper::_CreateDBTable_TABLE_USER_TRADE_INFO()
{
	qint32 nFunRes = 0;
	CSQLData sqlData;
	QString  strSQLKey = "TABLE_USER_TRADE_INFO__CREATE_TABLE_0000";

	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}
void CClientDbOper::truncate_TABLE_USER_TRADE_INFO()
{
	qint32 nFunRes = 0;
	CSQLData sqlData;
	QString  strSQLKey = "TABLE_USER_TRADE_INFO__DELETE_0002";

	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return;
}

void CClientDbOper::truncateSymbolMinMaxTime()
{
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_MINTIME_MAXTIME__DELETE_0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	m_pDbConnection->execModify(sqlData);
	
}

//////////////////////////////////////////////////////////////////////////
qint32 CClientDbOper::_CreateDBTable_TABLE_USER_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_ACCOUNT__CREATE_TABLE_0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}

qint32 CClientDbOper::_Truncate_TABLE_USER_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_ACCOUNT__DELETE_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}

qint32 CClientDbOper::resetUserAccount( const CUserAccount* pData )
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_ACCOUNT__UPDATE_0004";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey,
		pData->m_fInitAccount, pData->m_fLeftAccount, pData->m_fHoldAccount,
		pData->m_fFloatingProfitLoss, pData->m_fFloatingProfitLossPersentage, pData->m_strUpdateTime,
		pData->m_strUserID);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}


qint32 CClientDbOper::insertUserAccount( const CUserAccount* pData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQLKey;
	CSQLData sqlData;

	QVariantList COLUMN_USEID;
	QVariantList COLUMN_INIT_AMOUNT;
	QVariantList COLUMN_LEFT_AMOUNT;
	QVariantList COLUMN_HOLD_AMOUNT;
	QVariantList COLUMN_FLOATINT_PROFIT_LOSS;
	QVariantList COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE;
	QVariantList COLUMN_UPDATE_TIME;
	QList<QVariantList*> LstData;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}
	
	{
		COLUMN_USEID << pData->m_strUserID;
		COLUMN_INIT_AMOUNT << pData->m_fInitAccount;
		COLUMN_LEFT_AMOUNT << pData->m_fLeftAccount;
		COLUMN_HOLD_AMOUNT << pData->m_fHoldAccount;
		COLUMN_FLOATINT_PROFIT_LOSS << pData->m_fFloatingProfitLoss;
		COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE << pData->m_fFloatingProfitLossPersentage;
		COLUMN_UPDATE_TIME << pData->m_strUpdateTime;
	}
	LstData.append(&COLUMN_USEID);
	LstData.append(&COLUMN_INIT_AMOUNT);
	LstData.append(&COLUMN_LEFT_AMOUNT);
	LstData.append(&COLUMN_HOLD_AMOUNT);
	LstData.append(&COLUMN_FLOATINT_PROFIT_LOSS);
	LstData.append(&COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE);
	LstData.append(&COLUMN_UPDATE_TIME);

	strSQLKey = "TABLE_USER_ACCOUNT__INSERT_0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	nFunRes = m_pDbConnection->commitTransaction();
	LstData.clear();

	return nFunRes;
}

qint32 CClientDbOper::resetUserHoldAccount( const QList<CUserHoldAccount*>& lstData )
{
	_Truncate_TABLE_USER_HOLD_ACCOUNT();

	qint32 nFunRes = 0;
	nFunRes = _AddUserHoldAccountLst(lstData);
	return nFunRes;
}



//////////////////////////////////////////////////////////////////////////
qint32 CClientDbOper::_CreateDBTable_TABLE_USER_HOLD_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__CREATE_TABLE_0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}

qint32 CClientDbOper::_Truncate_TABLE_USER_HOLD_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__DELETE_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}

qint32 CClientDbOper::_AddUserHoldAccountLst( const QList<CUserHoldAccount*>& lstData)
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQLKey;
	CSQLData sqlData;
	QList<CUserHoldAccount*>::const_iterator iterLst;
	CUserHoldAccount* pData = NULL;

	QVariantList COLUMN_USEID;
	QVariantList COLUMN_SYMBOLUSE;
	QVariantList COLUMN_PRICE;
	QVariantList COLUMN_VOLUME;
	QVariantList COLUMN_TIME;
	QVariantList COLUMN_AMOUNT;
	QList<QVariantList*> LstData;

	if (0 >= lstData.size())
	{
		nFunRes = 0;
		return nFunRes;
	}

	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__INSERT_0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

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
	LstData.append(&COLUMN_USEID);
	LstData.append(&COLUMN_SYMBOLUSE);
	LstData.append(&COLUMN_PRICE);
	LstData.append(&COLUMN_VOLUME);
	LstData.append(&COLUMN_TIME);
	LstData.append(&COLUMN_AMOUNT);

	nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	nFunRes = m_pDbConnection->commitTransaction();

	return nFunRes;
}

qint32 CClientDbOper::_CreateDBTable_TABLE_SYMBOLUSE()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_SYMBOLUSE__CREATE_TABLE_0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}
qint32 CClientDbOper::_Truncate_TABLE_SYMBOLUSE()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_SYMBOLUSE__DELETE_0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}
qint32 CClientDbOper::resetSymbolUse( const QList<QString>& lstData )
{
	_Truncate_TABLE_SYMBOLUSE();

	qint32 nFunRes = 0;
	nFunRes = _AddSymbolLst(lstData);
	return nFunRes;
}
qint32 CClientDbOper::_AddSymbolLst( const QList<QString>& lstData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQLKey;
	CSQLData sqlData;
	QList<QString>::const_iterator iterLst;
	QString strData;
	QVariantList COLUMN_SYMBOLUSE;
	QList<QVariantList*> LstData;

	if (0 >= lstData.size())
	{
		nFunRes = 0;
		return nFunRes;
	}

	iterLst = lstData.constBegin();
	while (iterLst != lstData.constEnd())
	{
		strData = (*iterLst);
		COLUMN_SYMBOLUSE << strData;
		iterLst++;
	}//while

	LstData.append(&COLUMN_SYMBOLUSE);

	strSQLKey = "TABLE_SYMBOLUSE__INSERT_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	nFunRes = m_pDbConnection->commitTransaction();
	LstData.clear();
	return nFunRes;
}



qint32 CClientDbOper::getSymbolUseLst(QList<QString>& lstData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	QString strSymbolUse;
	IQueryAdapter* pQueryAdapter = NULL;
	QStringList lstColumnName;

	strSQLKey = "TABLE_SYMBOLUSE__SELECT_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append("COLUMN_SYMBOLUSE");
	lstColumnName.clear();
	lstColumnName.append(str_TABLE_SYMBOLUSE_COLUMN_SYMBOLUSE);
	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	while (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		strSymbolUse.clear();
		nColumnIndex = 0;
		strSymbolUse = pQueryAdapter->getStringData(str_TABLE_SYMBOLUSE_COLUMN_SYMBOLUSE);
		lstData.push_back(strSymbolUse);
		strSymbolUse.clear();
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;
	return nFunRes;
}

QSqlDatabase* CClientDbOper::getDB()
{
	QSqlDatabase* pQtDBRef = NULL;
	if (NULL != m_pDbConnectionQtRef)
	{
		pQtDBRef = m_pDbConnectionQtRef->getQTDBHandle();
	}
	return pQtDBRef;
}
