#include "ServerDbOper.h"

#include <QtCore/QFile>

#include <sstream>
#include "ConfigInfo.h"
#include "Log4cppLogger.h"
#include "UserInfo.h"
#include "UserTradeInfo.h"
#include "UserHold.h"
#include "UserAccount.h"
#include "UserHoldAccount.h"
#include "ProjectSQLManager.h"

static const char*  str_QtDbType_QSQLITE = "QSQLITE";
static const char*  str_QtDbType_QMYSQL = "QMYSQL";

//5001.db
CServerDbOper::CServerDbOper( const QString& strSqliteDbFileName )
{
	m_pQSqlDataBase = NULL;
	m_strQTDbType = str_QtDbType_QSQLITE;
	m_strSqliteDbFileName = strSqliteDbFileName;//"002567.SZ";
	m_strSqliteDbKEY = m_strSqliteDbFileName;
	m_strSqliteDbPath = CConfigInfo::getInstance().getServerDBPath();
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + m_strSqliteDbFileName;//"C:/LSL/LSL_DATA/ServerDB/5001.db"
	_InitDataBase();
	if (true == m_pQSqlDataBase->isValid())
	{
		_CreateDBTable_TABLE_USER_INFO();
		_CreateDBTable_TABLE_USER_TRADE_INFO();
		_CreateDBTable_TABLE_USER_ACCOUNT();
		_CreateDBTable_TABLE_USER_HOLD_ACCOUNT();
	}
}

CServerDbOper::~CServerDbOper()
{
	_UnInitDataBase();
}


void CServerDbOper::_InitDataBase()
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

void CServerDbOper::_UnInitDataBase()
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




int CServerDbOper::startTransaction()
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



int CServerDbOper::commitTransaction()
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
qint32 CServerDbOper::_CreateDBTable_TABLE_USER_INFO()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_INFO__CREATE_TABLE_0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = _ExecModify(sqlData);
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
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CUserInfo* pUserInfo = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQLKey = "TABLE_USER_INFO__SELECT_0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUSERNAME, strPASSWORD);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
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

	if ( pSqlQuery->next() )
	{
		pUserInfo = new CUserInfo();
		nColumnIndex = 0;
		pUserInfo->m_strUserID = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pUserInfo->m_strUserName = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pUserInfo->m_strPassWord = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pUserInfo->m_strLastLoginTime = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pUserInfo->m_nLoginCount = pSqlQuery->value(nColumnIndex).toInt();
		nColumnIndex++;
		pUserInfo->m_nState = pSqlQuery->value(nColumnIndex).toInt();

		(*ppData) = pUserInfo;
		pUserInfo = NULL;
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}
qint32 CServerDbOper::updateUserInfo(const CUserInfo* pData)
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;

	strSQLKey = "TABLE_USER_INFO__UPDATE_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey,
		pData->m_strLastLoginTime, pData->m_nLoginCount, 
		pData->m_strUserName, pData->m_strPassWord);
	nFunRes = _ExecModify(sqlData);

	return nFunRes;

}
qint32 CServerDbOper::insertUserInfo(const CUserInfo* pData)
{
	qint32 nFunRes = 0;
	startTransaction();
	nFunRes = _AddUserInfo(pData);
	commitTransaction();
	return nFunRes;
}


qint32 CServerDbOper::_AddUserInfo(const CUserInfo* pData)
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

	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQLKey = "TABLE_USER_INFO__INSERT_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
	pQSqlQueryForInseert->prepare(sqlData.getSqliteSQL());

	{
		lst_COLUMN_USEID << pData->m_strUserID;
		lst_COLUMN_USERNAME << pData->m_strUserName;
		lst_COLUMN_PASSWORD << pData->m_strPassWord;
		lst_COLUMN_LASTLOGINTIME << pData->m_strLastLoginTime;
		lst_COLUMN_LOGINCOUNT << pData->m_nLoginCount;
		lst_COLUMN_STATE << pData->m_nState;
	}

	//pQSqlQueryForInseert->addBindValue(lstInstrumentID);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_USEID);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_USERNAME);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_PASSWORD);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_LASTLOGINTIME);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_LOGINCOUNT);
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_STATE);

	bExecRes = pQSqlQueryForInseert->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<sqlData.getSqliteSQL()
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

qint32 CServerDbOper::_CreateDBTable_TABLE_USER_TRADE_INFO()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_TRADE_INFO__CREATE_TABLE_0000";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = _ExecModify(sqlData);
	return nFunRes;
}

qint32 CServerDbOper::insertUserTradeInfo(const CUserTradeInfo* pData )
{
	qint32 nFunRes = 0;
	//startTransaction();
	nFunRes = _AddUserTradeInfo(pData);
	//commitTransaction();
	return nFunRes;
}

qint32 CServerDbOper::_AddUserTradeInfo( const CUserTradeInfo* pData )
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

	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQLKey = "TABLE_USER_TRADE_INFO__INSERT_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
	pQSqlQueryForInseert->prepare(sqlData.getSqliteSQL());

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
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<sqlData.getSqliteSQL()
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}
qint32 CServerDbOper::_ExecModify(const CSQLData& sqlData)
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString strSQL;

	QSqlQuery* pSqlQuery = NULL;
	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);
	strSQL = sqlData.getSqliteSQL();
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

qint32 CServerDbOper::selectUserTradeInfo(QList<CUserTradeInfo*>& lstData, const QString& strUserID, const QString& strSymbolUse )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);
	strSQLKey = "TABLE_USER_TRADE_INFO__SELECT_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUserID, strSymbolUse);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
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
		CUserTradeInfo* pData = NULL;
		pData = new CUserTradeInfo();

		nColumnIndex = 0;
		pData->m_strUserID = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pData->m_strTradeUUID = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pData->m_strTradeTime = pSqlQuery->value(nColumnIndex).toString();

		nColumnIndex++;
		pData->m_nTradeType = (CTcpComProtocol::ETradeType)(pSqlQuery->value(nColumnIndex).toInt());
		nColumnIndex++;
		pData->m_strSymbolUse = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pData->m_fTradePrice = pSqlQuery->value(nColumnIndex).toDouble();

		nColumnIndex++;
		pData->m_nTradeVolume = pSqlQuery->value(nColumnIndex).toInt();
		nColumnIndex++;
		pData->m_fTradeAmount = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pData->m_fTradeFees = pSqlQuery->value(nColumnIndex).toDouble();

		nColumnIndex++;
		pData->m_fTotalTradeFee = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pData->m_fUseAccount = pSqlQuery->value(nColumnIndex).toDouble();

		lstData.push_back(pData);
		pData = NULL;
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

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
	nFunRes = _ExecModify(sqlData);
	return nFunRes;
}

qint32 CServerDbOper::_Truncate_TABLE_USER_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_ACCOUNT__DELETE_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = _ExecModify(sqlData);
	return nFunRes;
}

qint32 CServerDbOper::insertUserAccount(const CUserAccount* pData )
{
	qint32 nFunRes = 0;
	startTransaction();
	nFunRes = _AddUserAccount(pData);
	commitTransaction();
	return nFunRes;
}

qint32 CServerDbOper::_AddUserAccount( const CUserAccount* pData )
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


	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);
	strSQLKey = "TABLE_USER_ACCOUNT__INSERT_0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
	pQSqlQueryForInseert->prepare(sqlData.getSqliteSQL());

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
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<sqlData.getSqliteSQL()
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}


qint32 CServerDbOper::selectUserAccount(const QString& strUserID, CUserAccount** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CUserAccount* pInfo = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);
	strSQLKey = "TABLE_USER_ACCOUNT__SELECT_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUserID);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
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

	if ( pSqlQuery->next() )
	{
		pInfo = new CUserAccount();
		nColumnIndex = 0;
		pInfo->m_strUserID = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pInfo->m_fInitAccount = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pInfo->m_fLeftAccount = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pInfo->m_fHoldAccount = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pInfo->m_fFloatingProfitLoss = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pInfo->m_fFloatingProfitLossPersentage = pSqlQuery->value(nColumnIndex).toDouble();

		(*ppData) = pInfo;
		pInfo = NULL;
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

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
	nFunRes = _ExecModify(sqlData);
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
	nFunRes = _ExecModify(sqlData);
	return nFunRes;

}

qint32 CServerDbOper::_Truncate_TABLE_USER_HOLD_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__DELETE_0001";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);
	nFunRes = _ExecModify(sqlData);
	return nFunRes;
}

qint32 CServerDbOper::selectUserHoldAccount( const QString& strUserID,const QString& strSymobolUse, CUserHoldAccount** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CUserHoldAccount* pInfo = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__SELECT_0004";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUserID, strSymobolUse);
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
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

	if ( pSqlQuery->next() )
	{
		pInfo = new CUserHoldAccount();
		nColumnIndex = 0;
		pInfo->m_strUserID = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pInfo->m_strSymbolUse = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pInfo->m_fPrice = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pInfo->m_nVolume = pSqlQuery->value(nColumnIndex).toInt();
		nColumnIndex++;
		pInfo->m_strTime = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pInfo->m_fHoldAccount = pSqlQuery->value(nColumnIndex).toDouble();

		(*ppData) = pInfo;
		pInfo = NULL;
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}

qint32 CServerDbOper::selectUserHoldAccount(const QString& strUserID, QList<CUserHoldAccount*>& LstData)
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQLKey;
	CSQLData sqlData;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CUserHoldAccount* pInfo = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__SELECT_0003";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, strUserID);

	
	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
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
		pInfo = new CUserHoldAccount();
		nColumnIndex = 0;
		pInfo->m_strUserID = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pInfo->m_strSymbolUse = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pInfo->m_fPrice = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pInfo->m_nVolume = pSqlQuery->value(nColumnIndex).toInt();
		nColumnIndex++;
		pInfo->m_strTime = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pInfo->m_fHoldAccount = pSqlQuery->value(nColumnIndex).toDouble();

		LstData.push_back(pInfo);
		pInfo = NULL;
	}//while

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	return nFunRes;
}

qint32 CServerDbOper::insertUserHoldAccount( CUserHoldAccount* pData )
{
	qint32 nFunRes = 0;
	startTransaction();
	nFunRes = _AddUserHoldAccount(pData);
	commitTransaction();
	return nFunRes;
}

qint32 CServerDbOper::_AddUserHoldAccount( const CUserHoldAccount* pData )
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

	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);
	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__INSERT_0002";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey);

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<sqlData.getSqliteSQL();
	pQSqlQueryForInseert->prepare(sqlData.getSqliteSQL());

	{
		COLUMN_USEID << pData->m_strUserID;
		COLUMN_SYMBOLUSE << pData->m_strSymbolUse;
		COLUMN_PRICE << pData->m_fPrice;
		COLUMN_VOLUME << pData->m_nVolume;
		COLUMN_TIME << pData->m_strTime;
		COLUMN_AMOUNT << pData->m_fHoldAccount;
	}
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
		MYLOG4CPP_DEBUG<<"execBatch strSQL="<<sqlData.getSqliteSQL()
			<<" "<<"error:"<<pQSqlQueryForInseert->lastError().text().toStdString();
	}

	if (NULL != pQSqlQueryForInseert)
	{
		delete pQSqlQueryForInseert;
		pQSqlQueryForInseert = NULL;
	}
	return nFunRes;
}

qint32 CServerDbOper::updateUserHoldAccount( CUserHoldAccount* pData )
{
	qint32 nFunRes = 0;
	QString  strSQLKey;
	CSQLData sqlData;

	strSQLKey = "TABLE_USER_HOLD_ACCOUNT__UPDATE_0005";
	CProjectSQLManager::getInstance().prepareSQLData(sqlData, strSQLKey, 
		pData->m_fPrice,
		pData->m_nVolume,
		pData->m_strTime,
		pData->m_fHoldAccount,
		pData->m_strUserID,
		pData->m_strSymbolUse
		);

	nFunRes = _ExecModify(sqlData);
	return nFunRes;
}

