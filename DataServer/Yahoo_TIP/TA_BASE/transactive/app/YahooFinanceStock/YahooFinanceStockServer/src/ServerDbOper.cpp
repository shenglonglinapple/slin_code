#include "ServerDbOper.h"

#include <QtCore/QFile>

#include <sstream>
#include "ConfigInfo.h"
#include "Log4cppLogger.h"
#include "SqliteDbOperBuildSQL.h"
#include "UserInfo.h"
#include "UserTradeInfo.h"
#include "UserHold.h"
#include "UserAccount.h"
#include "UserHoldAmount.h"

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
	m_pSqliteDbOperBuildSQL = NULL;
	m_pSqliteDbOperBuildSQL = new CSqliteDbOperBuildSQL();
	_InitDataBase();
	if (true == m_pQSqlDataBase->isValid())
	{
		_CreateDBTable_TABLE_USER_INFO();
		_CreateDBTable_TABLE_USER_TRADE_INFO();
		_CreateDBTable_TABLE_USER_ACCOUNT();
		_CreateDBTable_TABLE_USER_HOLD_AMOUNT();
	}
}

CServerDbOper::~CServerDbOper()
{
	_UnInitDataBase();
	if (NULL != m_pSqliteDbOperBuildSQL)
	{
		delete m_pSqliteDbOperBuildSQL;
		m_pSqliteDbOperBuildSQL = NULL;
	}
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
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_USER_INFO();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;

}

qint32 CServerDbOper::selectUserInfo(
	const QString& strUSERNAME, 
	const QString& strPASSWORD, CUserInfo** ppData)
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CUserInfo* pUserInfo = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_TABLE_USER_INFO(strUSERNAME, strPASSWORD);
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
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_UPDATE_TABLE_USER_INFO(
		pData->m_strUserName, pData->m_strPassWord, 
		pData->m_strLastLoginTime, pData->m_nLoginCount,
		pData->m_nState);
	nFunRes = _ExecModify(strSQL);
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


qint32 CServerDbOper::insertUserHold(const CUserHold* pData )
{
	qint32 nFunRes = 0;
	startTransaction();
	nFunRes = _AddUserHold(pData);
	commitTransaction();
	return nFunRes;
}

qint32 CServerDbOper::_AddUserInfo(const CUserInfo* pData)
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQL;

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

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_BatchInsert_TABLE_USER_INFO();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL;
	pQSqlQueryForInseert->prepare(strSQL);

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

qint32 CServerDbOper::_CreateDBTable_TABLE_USER_TRADE_INFO()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_USER_TRADE_INFO();
	nFunRes = _ExecModify(strSQL);
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
	QVariantList lst_COLUMN_TOTAL_TRADE_AMOUNT;

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
		lst_COLUMN_TOTAL_TRADE_AMOUNT << pData->m_fTotalTradeAmount;
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
	pQSqlQueryForInseert->addBindValue(lst_COLUMN_TOTAL_TRADE_AMOUNT);
	
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

qint32 CServerDbOper::_ExecModify(const QString& strSQL)
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

qint32 CServerDbOper::selectUserTradeInfo(QList<CUserTradeInfo*>& lstData, const QString& strUserID, const QString& strSymbolUse )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_TABLE_USER_TRADE_INFO(strUserID, strSymbolUse);
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
		pData->m_fTotalTradeAmount = pSqlQuery->value(nColumnIndex).toDouble();

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
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_USER_ACCOUNT();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CServerDbOper::_Truncate_TABLE_USER_ACCOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Truncate_TABLE_USER_ACCOUNT();
	nFunRes = _ExecModify(strSQL);
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
		COLUMN_INIT_AMOUNT << pData->m_fInitAmount;
		COLUMN_LEFT_AMOUNT << pData->m_fLeftAmount;
		COLUMN_HOLD_AMOUNT << pData->m_fHoldAmount;
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


qint32 CServerDbOper::selectUserAccount(const QString& strUserID, CUserAccount** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CUserAccount* pInfo = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_TABLE_USER_ACCOUNT(strUserID);
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
		pInfo = new CUserAccount();
		nColumnIndex = 0;
		pInfo->m_strUserID = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pInfo->m_fInitAmount = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pInfo->m_fLeftAmount = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pInfo->m_fHoldAmount = pSqlQuery->value(nColumnIndex).toDouble();
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
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Update_TABLE_USER_ACCOUNT(pData);
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

//////////////////////////////////////////////////////////////////////////
qint32 CServerDbOper::_CreateDBTable_TABLE_USER_HOLD_AMOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_USER_HOLD_AMOUNT();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CServerDbOper::_Truncate_TABLE_USER_HOLD_AMOUNT()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Truncate_TABLE_USER_HOLD_AMOUNT();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CServerDbOper::selectUserHoldAmount( const QString& strUserID,const QString& strSymobolUse, CUserHoldAmount** ppData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CUserHoldAmount* pInfo = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_TABLE_USER_HOLD_AMOUNT(strUserID, strSymobolUse);
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
		pInfo = new CUserHoldAmount();
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
		pInfo->m_fAmount = pSqlQuery->value(nColumnIndex).toDouble();

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

qint32 CServerDbOper::selectUserHoldAmount(const QString& strUserID, QList<CUserHoldAmount*>& LstData)
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;
	CUserHoldAmount* pInfo = NULL;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_TABLE_USER_HOLD_AMOUNT(strUserID);
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
		pInfo = new CUserHoldAmount();
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
		pInfo->m_fAmount = pSqlQuery->value(nColumnIndex).toDouble();

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

qint32 CServerDbOper::insertUserHoldAmount( CUserHoldAmount* pData )
{
	qint32 nFunRes = 0;
	startTransaction();
	nFunRes = _AddUserHoldAmount(pData);
	commitTransaction();
	return nFunRes;
}

qint32 CServerDbOper::_AddUserHoldAmount( const CUserHoldAmount* pData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQL;

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

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_BatchInsert_TABLE_USER_HOLD_AMOUNT();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL;
	pQSqlQueryForInseert->prepare(strSQL);

	{
		COLUMN_USEID << pData->m_strUserID;
		COLUMN_SYMBOLUSE << pData->m_strSymbolUse;
		COLUMN_PRICE << pData->m_fPrice;
		COLUMN_VOLUME << pData->m_nVolume;
		COLUMN_TIME << pData->m_strTime;
		COLUMN_AMOUNT << pData->m_fAmount;
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

qint32 CServerDbOper::updateUserHoldAmount( CUserHoldAmount* pData )
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Update_TABLE_USER_HOLD_AMOUNT(pData);
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
qint32 CServerDbOper::_CreateDBTable_TABLE_USER_HOLD()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_CreateTable_TABLE_USER_HOLD();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CServerDbOper::_Truncate_TABLE_USER_HOLD()
{
	qint32 nFunRes = 0;
	QString  strSQL;
	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Truncate_TABLE_USER_HOLD();
	nFunRes = _ExecModify(strSQL);
	return nFunRes;
}

qint32 CServerDbOper::_AddUserHold( const CUserHold* pData )
{
	qint32 nFunRes = 0;
	bool bExecRes = false;
	QString  strSQL;

	QVariantList COLUMN_USEID;
	QVariantList COLUMN_SYMBOLUSE;
	QVariantList COLUMN_BUY_UUID;
	QVariantList COLUMN_BUY_TIME;


	QVariantList COLUMN_BUY_PRICE;
	QVariantList COLUMN_BUY_VOLUME;
	QVariantList COLUMN_BUY_FEES;

	QVariantList COLUMN_BUY_AMOUNT;
	QVariantList COLUMN_CURRENT_TIME;
	QVariantList COLUMN_CURRENT_PRICE;

	QVariantList COLUMN_CURRENT_FEES;
	QVariantList COLUMN_CURRENT_AMOUNT;
	QVariantList COLUMN_PROFIT_LOSS;

	QVariantList COLUMN_PROFIT_LOSS_PERSENTAGE;

	QSqlQuery* pQSqlQueryForInseert = NULL;

	if (NULL == pData)
	{
		nFunRes = 0;
		return nFunRes;
	}

	pQSqlQueryForInseert = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_BatchInsert_TABLE_USER_HOLD();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL;
	pQSqlQueryForInseert->prepare(strSQL);

	{
		COLUMN_USEID << pData->m_strUserID;
		COLUMN_SYMBOLUSE << pData->m_strSymbolUse;
		COLUMN_BUY_UUID << pData->m_strBuyUUID;
		COLUMN_BUY_TIME << pData->m_strBuyTime;

		COLUMN_BUY_PRICE << pData->m_fBuyPrice;
		COLUMN_BUY_VOLUME << pData->m_nBuyVolume;
		COLUMN_BUY_FEES << pData->m_fBuyFees;

		COLUMN_BUY_AMOUNT << pData->m_fBuyAmount;
		COLUMN_CURRENT_TIME << pData->m_strCurrentTime;
		COLUMN_CURRENT_PRICE << pData->m_fCurrentPrice;

		COLUMN_CURRENT_FEES << pData->m_fCurrentFees;
		COLUMN_CURRENT_AMOUNT << pData->m_fCurrentAmount;
		COLUMN_PROFIT_LOSS << pData->m_fProfitLoss;

		COLUMN_PROFIT_LOSS_PERSENTAGE << pData->m_fProfitLossPersentage;
	}

	//pQSqlQueryForInseert->addBindValue(lstInstrumentID);
	pQSqlQueryForInseert->addBindValue(COLUMN_USEID);
	pQSqlQueryForInseert->addBindValue(COLUMN_SYMBOLUSE);
	pQSqlQueryForInseert->addBindValue(COLUMN_BUY_UUID);
	pQSqlQueryForInseert->addBindValue(COLUMN_BUY_TIME);

	pQSqlQueryForInseert->addBindValue(COLUMN_BUY_PRICE);
	pQSqlQueryForInseert->addBindValue(COLUMN_BUY_VOLUME);
	pQSqlQueryForInseert->addBindValue(COLUMN_BUY_FEES);

	pQSqlQueryForInseert->addBindValue(COLUMN_BUY_AMOUNT);
	pQSqlQueryForInseert->addBindValue(COLUMN_CURRENT_TIME);
	pQSqlQueryForInseert->addBindValue(COLUMN_CURRENT_PRICE);

	pQSqlQueryForInseert->addBindValue(COLUMN_CURRENT_FEES);
	pQSqlQueryForInseert->addBindValue(COLUMN_CURRENT_AMOUNT);
	pQSqlQueryForInseert->addBindValue(COLUMN_PROFIT_LOSS);

	pQSqlQueryForInseert->addBindValue(COLUMN_PROFIT_LOSS_PERSENTAGE);

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

qint32 CServerDbOper::select_UserHold( const QString& strUserID, const QString& strSymbolUse, QList<CUserHold*>& lstData )
{
	qint32 nFunRes = 0;
	bool bExecRes = true;
	QString  strSQL;
	QSqlQuery* pSqlQuery = NULL;
	int nColumnIndex = 0;

	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = m_pSqliteDbOperBuildSQL->buildSQL_Select_TABLE_USER_HOLD(strUserID, strSymbolUse);
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
		CUserHold* pData = NULL;
		pData = new CUserHold();
		nColumnIndex = 0;
		pData->m_strUserID = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pData->m_strSymbolUse = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pData->m_strBuyUUID = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pData->m_strBuyTime = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pData->m_fBuyPrice = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pData->m_nBuyVolume = pSqlQuery->value(nColumnIndex).toInt();
		nColumnIndex++;
		pData->m_fBuyFees = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pData->m_fBuyAmount = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pData->m_strCurrentTime = pSqlQuery->value(nColumnIndex).toString();
		nColumnIndex++;
		pData->m_fCurrentPrice = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pData->m_fCurrentFees = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pData->m_fCurrentAmount = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pData->m_fProfitLoss = pSqlQuery->value(nColumnIndex).toDouble();
		nColumnIndex++;
		pData->m_fProfitLossPersentage = pSqlQuery->value(nColumnIndex).toDouble();

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
//////////////////////////////////////////////////////////////////////////

