#include "ServerDbOper.h"

#include <QtCore/QFile>


#include "ConfigInfo.h"
#include "Log4cppLogger.h"
#include "UserInfo.h"
#include "UserTradeInfo.h"
#include "UserHold.h"
#include "UserAccount.h"
#include "UserHoldAccount.h"

#include "ProjectSQLManager.h"
#include "ProjectDBStruct.h"
#include "DbStatusItem.h"
#include "QtDBConnection.h"
#include "IQueryAdapter.h"


//5001.db
CServerDbOper::CServerDbOper( const QString& strServerListenPort )
{
	m_pDbConnection = NULL;
	m_pDbStatusItem = NULL;

	m_strSqliteDbPath = CConfigInfo::getInstance().getServerDBPath();
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + strServerListenPort + ".db";//"C:/LSL/LSL_DATA/ServerDB/5001.db"

	m_pDbStatusItem = new CDbStatusItem();
	m_pDbStatusItem->m_nDBType = CDbStatusItem::DBType_QSQLITE;
	m_pDbStatusItem->m_strSchema = m_strSqliteDbFileFullPath;//"C:/LSL/LSL_DATA/ServerDB/5001.db"
	m_pDbStatusItem->setProperties();

	m_pDbConnection = new CQtDBConnection(m_pDbStatusItem);
	m_pDbConnection->open();

	if (true == m_pDbConnection->isOpen())
	{
		_CreateDBTable_TABLE_USER_INFO();
		_CreateDBTable_TABLE_USER_TRADE_INFO();
		_CreateDBTable_TABLE_USER_ACCOUNT();
		_CreateDBTable_TABLE_USER_HOLD_ACCOUNT();
	}
}

CServerDbOper::~CServerDbOper()
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


int CServerDbOper::startTransaction()
{
	int nFunRes = 0;

	nFunRes = m_pDbConnection->startTransaction();

	return nFunRes;
}

int CServerDbOper::commitTransaction()
{
	int nFunRes = 0;

	nFunRes = m_pDbConnection->commitTransaction();

	return nFunRes;
	
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
qint32 CServerDbOper::_CreateDBTable_TABLE_USER_INFO()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_INFO__CREATE_TABLE_0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;

}

qint32 CServerDbOper::selectUserInfo(
	const QString& strUSERNAME, 
	const QString& strPASSWORD, CUserInfo** ppData)
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	CUserInfo* pUserInfo = NULL;
	QStringList lstColumnName;
	IQueryAdapter* pQueryAdapter = NULL;

	strSQLKey = "TABLE_USER_INFO__SELECT_0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUSERNAME, strPASSWORD);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(str_TABLE_USER_INFO_COLUMN_USEID);
	lstColumnName.append(str_TABLE_USER_INFO_COLUMN_USERNAME);
	lstColumnName.append(str_TABLE_USER_INFO_COLUMN_PASSWORD);
	lstColumnName.append(str_TABLE_USER_INFO_COLUMN_LASTLOGINTIME);
	lstColumnName.append(str_TABLE_USER_INFO_COLUMN_LOGINCOUNT);
	lstColumnName.append(str_TABLE_USER_INFO_COLUMN_STATE);
	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	while (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		pUserInfo = new CUserInfo();
		nColumnIndex = 0;
		pUserInfo->m_strUserID = pQueryAdapter->getStringData(str_TABLE_USER_INFO_COLUMN_USEID);
		nColumnIndex++;
		pUserInfo->m_strUserName = pQueryAdapter->getStringData(str_TABLE_USER_INFO_COLUMN_USERNAME);
		nColumnIndex++;
		pUserInfo->m_strPassWord = pQueryAdapter->getStringData(str_TABLE_USER_INFO_COLUMN_PASSWORD);
		nColumnIndex++;
		pUserInfo->m_strLastLoginTime = pQueryAdapter->getStringData(str_TABLE_USER_INFO_COLUMN_LASTLOGINTIME);
		nColumnIndex++;
		pUserInfo->m_nLoginCount = pQueryAdapter->getStringData(str_TABLE_USER_INFO_COLUMN_LOGINCOUNT).toInt();
		nColumnIndex++;
		pUserInfo->m_nState = pQueryAdapter->getStringData(str_TABLE_USER_INFO_COLUMN_STATE).toInt();

		(*ppData) = pUserInfo;
		pUserInfo = NULL;
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}
qint32 CServerDbOper::updateUserInfo(const CUserInfo* pData)
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;

	strSQLKey = "TABLE_USER_INFO__UPDATE_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey,
		pData->m_strLastLoginTime, pData->m_nLoginCount, pData->m_nState,
		pData->m_strUserName, pData->m_strPassWord);
	nFunRes = m_pDbConnection->execModify(sqlData);

	return nFunRes;
}

qint32 CServerDbOper::insertUserInfo(const CUserInfo* pData)
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQLKey;
	CSQLData sqlData;

	QVariantList lst_COLUMN_USEID;
	QVariantList lst_COLUMN_USERNAME;
	QVariantList lst_COLUMN_PASSWORD;
	QVariantList lst_COLUMN_LASTLOGINTIME;
	QVariantList lst_COLUMN_LOGINCOUNT;
	QVariantList lst_COLUMN_STATE;
	QList<QVariantList*> LstData;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	{
		lst_COLUMN_USEID << pData->m_strUserID;
		lst_COLUMN_USERNAME << pData->m_strUserName;
		lst_COLUMN_PASSWORD << pData->m_strPassWord;
		lst_COLUMN_LASTLOGINTIME << pData->m_strLastLoginTime;
		lst_COLUMN_LOGINCOUNT << pData->m_nLoginCount;
		lst_COLUMN_STATE << pData->m_nState;
	}
	LstData.append(&lst_COLUMN_USEID);
	LstData.append(&lst_COLUMN_USERNAME);
	LstData.append(&lst_COLUMN_PASSWORD);
	LstData.append(&lst_COLUMN_LASTLOGINTIME);
	LstData.append(&lst_COLUMN_LOGINCOUNT);
	LstData.append(&lst_COLUMN_STATE);

	strSQLKey = "TABLE_USER_INFO__INSERT_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	nFunRes = m_pDbConnection->commitTransaction();
	LstData.clear();

	return nFunRes;
}

qint32 CServerDbOper::_CreateDBTable_TABLE_USER_TRADE_INFO()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_TRADE_INFO__CREATE_TABLE_0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);

	return nFunRes;
}


qint32 CServerDbOper::insertUserTradeInfo( const CUserTradeInfo* pData )
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

	strSQLKey = "TABLE_USER_TRADE_INFO__INSERT_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	//not use transaction here, use outside
	//nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	//nFunRes = m_pDbConnection->commitTransaction();
	LstData.clear();

	return nFunRes;
}
qint32 CServerDbOper::selectUserTradeInfo(QList<CUserTradeInfo*>& lstData, const QString& strUserID, const QString& strSymbolUse )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	IQueryAdapter* pQueryAdapter = NULL;
	QStringList lstColumnName;

	strSQLKey = "TABLE_USER_TRADE_INFO__SELECT_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUserID, strSymbolUse);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);
	lstColumnName.clear();
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_USEID);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_UUID);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TIME);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TYPE);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_SYMBOLUSE);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_PRICE);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_VOLUME);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_AMOUNT);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_FEES);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_FEE);
	lstColumnName.append(str_TABLE_USER_TRADE_INFO_COLUMN_USE_ACCOUNT);
	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	while (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		CUserTradeInfo* pData = NULL;
		pData = new CUserTradeInfo();

		nColumnIndex = 0;
		pData->m_strUserID = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_USEID);
		nColumnIndex++;
		pData->m_strTradeUUID = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_UUID);
		nColumnIndex++;
		pData->m_strTradeTime = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TIME);
		nColumnIndex++;
		pData->m_nTradeType = (CTcpComProtocol::ETradeType)(pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_TYPE).toInt());
		nColumnIndex++;
		pData->m_strSymbolUse = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_SYMBOLUSE);
		nColumnIndex++;
		pData->m_fTradePrice = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_PRICE).toDouble();

		nColumnIndex++;
		pData->m_nTradeVolume = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_VOLUME).toInt();
		nColumnIndex++;
		pData->m_fTradeAmount = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_AMOUNT).toDouble();
		nColumnIndex++;
		pData->m_fTradeFees = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_TRADE_FEES).toDouble();

		nColumnIndex++;
		pData->m_fTotalTradeFee = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_TOTAL_TRADE_FEE).toDouble();
		nColumnIndex++;
		pData->m_fUseAccount = pQueryAdapter->getStringData(str_TABLE_USER_TRADE_INFO_COLUMN_USE_ACCOUNT).toDouble();

		lstData.push_back(pData);
		pData = NULL;
	}//while

	return nFunRes;
}



//////////////////////////////////////////////////////////////////////////
qint32 CServerDbOper::_CreateDBTable_TABLE_USER_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_ACCOUNT__CREATE_TABLE_0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	
	nFunRes = m_pDbConnection->execModify(sqlData);

	return nFunRes;
}

qint32 CServerDbOper::_Truncate_TABLE_USER_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_ACCOUNT__DELETE_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}

qint32 CServerDbOper::insertUserAccount( const CUserAccount* pData )
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


qint32 CServerDbOper::selectUserAccount(const QString& strUserID, CUserAccount** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	CUserAccount* pInfo = NULL;
	IQueryAdapter* pQueryAdapter = NULL;
	QStringList lstColumnName;

	/*
	SELECT 
	COLUMN_USEID, COLUMN_INIT_ACCOUNT, COLUMN_LEFT_ACCOUNT, COLUMN_HOLD_ACCOUNT,
	COLUMN_FLOATINT_PROFIT_LOSS, COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE, COLUMN_UPDATE_TIME
	FROM TABLE_USER_ACCOUNT
	WHERE COLUMN_USEID = "%1" ORDER BY COLUMN_UPDATE_TIME ASC			
	*/
	strSQLKey = "TABLE_USER_ACCOUNT__SELECT_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUserID);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);

	lstColumnName.clear();
	lstColumnName.append(str_TABLE_USER_ACCOUNT_COLUMN_USEID);
	lstColumnName.append(str_TABLE_USER_ACCOUNT_COLUMN_INIT_ACCOUNT);
	lstColumnName.append(str_TABLE_USER_ACCOUNT_COLUMN_LEFT_ACCOUNT);
	lstColumnName.append(str_TABLE_USER_ACCOUNT_COLUMN_HOLD_ACCOUNT);
	lstColumnName.append(str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS);
	lstColumnName.append(str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE);
	lstColumnName.append(str_TABLE_USER_ACCOUNT_COLUMN_UPDATE_TIME);
	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	if (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		pInfo = new CUserAccount();
		nColumnIndex = 0;
		pInfo->m_strUserID = pQueryAdapter->getStringData(str_TABLE_USER_ACCOUNT_COLUMN_USEID);
		nColumnIndex++;
		pInfo->m_fInitAccount = pQueryAdapter->getStringData(str_TABLE_USER_ACCOUNT_COLUMN_INIT_ACCOUNT).toDouble();
		nColumnIndex++;
		pInfo->m_fLeftAccount = pQueryAdapter->getStringData(str_TABLE_USER_ACCOUNT_COLUMN_LEFT_ACCOUNT).toDouble();
		nColumnIndex++;
		pInfo->m_fHoldAccount = pQueryAdapter->getStringData(str_TABLE_USER_ACCOUNT_COLUMN_HOLD_ACCOUNT).toDouble();
		nColumnIndex++;
		pInfo->m_fFloatingProfitLoss = pQueryAdapter->getStringData(str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS).toDouble();
		nColumnIndex++;
		pInfo->m_fFloatingProfitLossPersentage = pQueryAdapter->getStringData(str_TABLE_USER_ACCOUNT_COLUMN_FLOATINT_PROFIT_LOSS_PERSENTAGE).toDouble();
		nColumnIndex++;
		pInfo->m_strUpdateTime = pQueryAdapter->getStringData(str_TABLE_USER_ACCOUNT_COLUMN_UPDATE_TIME);

		(*ppData) = pInfo;
		pInfo = NULL;
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}

qint32 CServerDbOper::updateUserAccount(CUserAccount* pData )
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

//////////////////////////////////////////////////////////////////////////
qint32 CServerDbOper::_CreateDBTable_TABLE_USER_HOLD_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__CREATE_TABLE_0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;

}

qint32 CServerDbOper::_Truncate_TABLE_USER_HOLD_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__DELETE_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->execModify(sqlData);
	return nFunRes;
}

qint32 CServerDbOper::selectUserHoldAccount( const QString& strUserID,const QString& strSymobolUse, CUserHoldAccount** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	CUserHoldAccount* pInfo = NULL;
	IQueryAdapter* pQueryAdapter = NULL;
	QStringList lstColumnName;

	/*
	SELECT 
	COLUMN_USERID, COLUMN_SYMBOLUSE, COLUMN_PRICE, COLUMN_VOLUME, COLUMN_TIME, COLUMN_HOLDACCOUNT
	FROM TABLE_USER_HOLD_ACCOUNT 
	WHERE COLUMN_USERID = "%1" AND COLUMN_SYMBOLUSE = "%2" ORDER BY COLUMN_SYMBOLUSE ASC
	*/
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__SELECT_0004";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUserID, strSymobolUse);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);
	lstColumnName.clear();
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_USERID);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_SYMBOLUSE);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_PRICE);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_VOLUME);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_TIME);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_HOLD_ACCOUNT);
	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	if (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		pInfo = new CUserHoldAccount();
		nColumnIndex = 0;
		pInfo->m_strUserID =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_USERID);
		nColumnIndex++;
		pInfo->m_strSymbolUse =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_SYMBOLUSE);
		nColumnIndex++;
		pInfo->m_fPrice =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_PRICE).toDouble();
		nColumnIndex++;
		pInfo->m_nVolume =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_VOLUME).toInt();
		nColumnIndex++;
		pInfo->m_strTime =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_TIME);
		nColumnIndex++;
		pInfo->m_fHoldAccount =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_HOLD_ACCOUNT).toDouble();

		(*ppData) = pInfo;
		pInfo = NULL;
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;

	return nFunRes;
}

qint32 CServerDbOper::selectUserHoldAccount(const QString& strUserID, QList<CUserHoldAccount*>& LstData)
{

	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	int nColumnIndex = 0;
	CUserHoldAccount* pInfo = NULL;
	IQueryAdapter* pQueryAdapter = NULL;
	QStringList lstColumnName;

	/*
	SELECT 
	COLUMN_USERID, COLUMN_SYMBOLUSE, COLUMN_PRICE, COLUMN_VOLUME, COLUMN_TIME, COLUMN_HOLDACCOUNT
	FROM TABLE_USER_HOLD_ACCOUNT 
	WHERE COLUMN_USERID = "%1" ORDER BY COLUMN_SYMBOLUSE ASC
	*/
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__SELECT_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUserID);

	nFunRes = m_pDbConnection->execQuery(sqlData, pQueryAdapter);
	lstColumnName.clear();
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_USERID);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_SYMBOLUSE);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_PRICE);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_VOLUME);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_TIME);
	lstColumnName.append(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_HOLD_ACCOUNT);
	lstColumnName.clear();
	if (NULL != pQueryAdapter)
	{
		lstColumnName = pQueryAdapter->getLstColumnName();
	}
	while (NULL != pQueryAdapter && pQueryAdapter->hasMore())
	{
		pInfo = new CUserHoldAccount();
		nColumnIndex = 0;
		pInfo->m_strUserID =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_USERID);
		nColumnIndex++;
		pInfo->m_strSymbolUse =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_SYMBOLUSE);
		nColumnIndex++;
		pInfo->m_fPrice =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_PRICE).toDouble();
		nColumnIndex++;
		pInfo->m_nVolume =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_VOLUME).toInt();
		nColumnIndex++;
		pInfo->m_strTime =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_TIME);
		nColumnIndex++;
		pInfo->m_fHoldAccount =  pQueryAdapter->getStringData(str_TABLE_USER_HOLD_ACCOUNT_COLUMN_HOLD_ACCOUNT).toDouble();

		LstData.push_back(pInfo);
		pInfo = NULL;
	}

	m_pDbConnection->cleanQuery(pQueryAdapter);
	pQueryAdapter = NULL;
	return nFunRes;
}


qint32 CServerDbOper::insertUserHoldAccount( const CUserHoldAccount* pData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQLKey;
	CSQLData sqlData;

	QVariantList COLUMN_USEID;
	QVariantList COLUMN_SYMBOLUSE;
	QVariantList COLUMN_PRICE;
	QVariantList COLUMN_VOLUME;
	QVariantList COLUMN_TIME;
	QVariantList COLUMN_AMOUNT;
	QList<QVariantList*> LstData;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	{
		COLUMN_USEID << pData->m_strUserID;
		COLUMN_SYMBOLUSE << pData->m_strSymbolUse;
		COLUMN_PRICE << pData->m_fPrice;
		COLUMN_VOLUME << pData->m_nVolume;
		COLUMN_TIME << pData->m_strTime;
		COLUMN_AMOUNT << pData->m_fHoldAccount;
	}
	LstData.append(&COLUMN_USEID);
	LstData.append(&COLUMN_SYMBOLUSE);
	LstData.append(&COLUMN_PRICE);
	LstData.append(&COLUMN_VOLUME);
	LstData.append(&COLUMN_TIME);
	LstData.append(&COLUMN_AMOUNT);

	/*
	INSERT INTO TABLE_USER_HOLD_ACCOUNT 
	(COLUMN_USERID, COLUMN_SYMBOLUSE, COLUMN_PRICE, COLUMN_VOLUME, COLUMN_TIME, COLUMN_HOLDACCOUNT)
	VALUES (?, ?, ?, ?, ?, ?)
	*/
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__INSERT_0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = m_pDbConnection->startTransaction();
	nFunRes = m_pDbConnection->execModifyBatch(sqlData, LstData);
	nFunRes = m_pDbConnection->commitTransaction();
	LstData.clear();

	return nFunRes;
}

qint32 CServerDbOper::updateUserHoldAccount(const CUserHoldAccount* pData )
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;

	/*
	UPDATE TABLE_USER_HOLD_ACCOUNT
	SET COLUMN_PRICE = %1, COLUMN_VOLUME = %2, COLUMN_TIME = "%3", COLUMN_HOLDACCOUNT = %4
	WHERE COLUMN_USERID = "%5" AND COLUMN_SYMBOLUSE = "%6"
	*/
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__UPDATE_0005";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, 
		pData->m_fPrice,
		pData->m_nVolume,
		pData->m_strTime,
		pData->m_fHoldAccount,
		pData->m_strUserID,
		pData->m_strSymbolUse
		);

	nFunRes = m_pDbConnection->execModify(sqlData);

	return nFunRes;
}

