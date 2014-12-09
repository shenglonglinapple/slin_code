#include "SqliteDbOper.h"

#include "HistoryData.h"
#include "ConfigInfo.h"
#include "Log4cppLogger.h"

static const std::string str_QtDbType_QSQLITE = "QSQLITE";
static const std::string str_QtDbType_QMYSQL = "QMYSQL";

static const std::string str_Table_bar_data_1day = "TABLE_BAR_DATA_1DAY";

static const std::string str_BarData_Column_DATE = "COLUMN_DATE";
static const std::string str_BarData_Column_OPEN = "COLUMN_OPEN";
static const std::string str_BarData_Column_HIGH = "COLUMN_HIGH";
static const std::string str_BarData_Column_LOW = "COLUMN_LOW";
static const std::string str_BarData_Column_CLOSE = "COLUMN_CLOSE";
static const std::string str_BarData_Column_VOLUME = "COLUMN_VOLUME";
static const std::string str_BarData_Column_ADJCLOSE = "COLUMN_ADJCLOSE";



CSqliteDbOper::CSqliteDbOper()
{
	m_pQSqlDataBase = NULL;
	m_strQTDbType = str_QtDbType_QSQLITE.c_str();//"QSQLITE";//"QSQLITE" "QMYSQL"
	m_strSqliteDbFileName = "002567.SZ";
	m_strSqliteDbKEY = m_strSqliteDbFileName;
	m_strSqliteDbPath = CConfigInfo::getInstance().getSQLiteDBPath();
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + m_strSqliteDbFileName;

}

CSqliteDbOper::~CSqliteDbOper()
{
	_UnInitDataBase();
}

void CSqliteDbOper::setDataBaseValue(const QString& strSqliteDbFileName)
{
	_UnInitDataBase();

	m_pQSqlDataBase = NULL;
	m_strQTDbType = str_QtDbType_QSQLITE.c_str();
	m_strSqliteDbFileName = strSqliteDbFileName;//"002567.SZ";
	m_strSqliteDbKEY = m_strSqliteDbFileName;
	m_strSqliteDbPath = CConfigInfo::getInstance().getSQLiteDBPath();
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + m_strSqliteDbFileName;


}

void CSqliteDbOper::resetDataBaseValue(const QString& strSqliteDbFileName)
{
	_UnInitDataBase();

	m_pQSqlDataBase = NULL;
	m_strQTDbType = str_QtDbType_QSQLITE.c_str();
	m_strSqliteDbFileName = strSqliteDbFileName;//"002567.SZ";
	m_strSqliteDbKEY = m_strSqliteDbFileName;
	m_strSqliteDbPath = CConfigInfo::getInstance().getSQLiteDBPath();
	m_strSqliteDbFileFullPath = m_strSqliteDbPath + m_strSqliteDbFileName;

	remove(m_strSqliteDbFileFullPath.toStdString().c_str());//remove old file

}



void CSqliteDbOper::_InitDataBase()
{
	_UnInitDataBase();
	
	m_pQSqlDataBase = new QSqlDatabase(
		QSqlDatabase::addDatabase(m_strQTDbType, m_strSqliteDbKEY));

	
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
	_InitDataBase();
	_CreateDBTable();
	_StartTransaction();
	_AddDataArray(pLstData);
	_CommitTransaction();
	_UnInitDataBase();
}


std::string CSqliteDbOper::_BuildSQLForCreateDBTable()
{
	std::ostringstream sreaamTmp;
	std::string strSQL;
	std::string strTableName;

	strTableName = str_Table_bar_data_1day;

	/*
	enumSqliteDb
	CREATE TABLE IF NOT EXISTS TABLE_BAR_DATA_1DAY
	(
	//InstrumentID INTEGER NOT NULL, 
	COLUMN_DATE TIMESTAMP NOT NULL, 
	COLUMN_OPEN decimal(25,10) NOT NULL,
	COLUMN_HIGH decimal(25,10) NOT NULL,
	COLUMN_LOW decimal(25,10) NOT NULL,	
	COLUMN_CLOSE decimal(25,10) NOT NULL,
	COLUMN_VOLUME NUMBER,
	COLUMN_ADJCLOSE decimal(25,10) NOT NULL,
	PRIMARY KEY (COLUMN_DATE)
	)
	*/

	{
		sreaamTmp.str("");
		sreaamTmp<<"CREATE TABLE IF NOT EXISTS "<<strTableName
			<<" "<<"("
			//<<" "<<str_BarData_Column_InstrumentID<<" "<<"INTEGER NOT NULL"<<","
			<<" "<<str_BarData_Column_DATE<<" "<<"TIMESTAMP NOT NULL"<<","
			<<" "<<str_BarData_Column_OPEN<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_BarData_Column_CLOSE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_BarData_Column_HIGH<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_BarData_Column_LOW<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<str_BarData_Column_VOLUME<<" "<<"INTEGER NOT NULL"<<","
			<<" "<<str_BarData_Column_ADJCLOSE<<" "<<"decimal(25,10) NOT NULL"<<","
			<<" "<<"PRIMARY KEY ("<<str_BarData_Column_DATE<<")"
			//<<" "<<"PRIMARY KEY ("<<str_BarData_Column_InstrumentID<<", "<<str_BarData_Column_Timestamp<<")"
			<<" "<<")";
	}
	
	strSQL = sreaamTmp.str();
	return strSQL;
}


std::string CSqliteDbOper::_BuildSQLForInsert()
{	
	std::ostringstream sreaamTmp;
	std::string strSQL;	

	/*
	INSERT INTO TABLE_BAR_DATA_1DAY
	(
	COLUMN_DATE, 
	COLUMN_OPEN, 
	COLUMN_HIGH, 
	COLUMN_LOW, 
	COLUMN_CLOSE, 
	COLUMN_VOLUME, 
	COLUMN_ADJCLOSE
	) 
	VALUES 
	(
	:COLUMN_DATE_VOLUE,
	:COLUMN_OPEN_VOLUE,
	:COLUMN_HIGH_VOLUE,
	:COLUMN_LOW_VOLUE,
	:COLUMN_CLOSE_VOLUE,
	:COLUMN_VOLUME_VOLUE,
	:COLUMN_ADJCLOSE_VOLUE 
	);
	*/


	sreaamTmp.str("");
	sreaamTmp<<"INSERT INTO "<<str_Table_bar_data_1day
		<<" "<<"("
		<<" "<<str_BarData_Column_DATE<<","
		<<" "<<str_BarData_Column_OPEN<<","
		<<" "<<str_BarData_Column_HIGH<<","
		<<" "<<str_BarData_Column_LOW<<","
		<<" "<<str_BarData_Column_CLOSE<<","
		<<" "<<str_BarData_Column_VOLUME<<","
		<<" "<<str_BarData_Column_ADJCLOSE
		<<" "<<")"
		<<" "<<"VALUES"
		<<" "<<"("
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"<<","
		<<" "<<"?"
		<<" "<<")";


	strSQL = sreaamTmp.str();
	return strSQL;	
}


int CSqliteDbOper::_CreateDBTable()
{
	int nFunRes = 0;
	bool bExecRes = true;
	std::string strSQL;

	QSqlQuery* pSqlQuery = NULL;
	pSqlQuery = new QSqlQuery(*m_pQSqlDataBase);

	strSQL = _BuildSQLForCreateDBTable();

	MYLOG4CPP_DEBUG	<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL;
	bExecRes = pSqlQuery->exec(strSQL.c_str());
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


int CSqliteDbOper::_AddDataArray(LstHistoryDataT* pLstData)
{
	int nFunRes = 0;
	bool bExecRes = false;
	std::string strDBTableName;
	std::string strSQL;
	LstHistoryDataIterT iterLst;
	CHistoryData* pDataTmp = NULL;
	//QVariantList lstInstrumentID;
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

	strDBTableName = str_Table_bar_data_1day;
	strSQL = _BuildSQLForInsert();

	MYLOG4CPP_DEBUG<<" "<<m_strSqliteDbFileFullPath.toStdString()
		<<" "<<"exec strSQL="<<strSQL
		<<" "<<"LstHistoryDataT.size="<<pLstData->size();

	pQSqlQueryForInseert->prepare(strSQL.c_str());

	iterLst = pLstData->begin();
	while (iterLst != pLstData->end())
	{
		pDataTmp = (*iterLst);

		//lstInstrumentID<<m_pDBOperParam->m_nInstrumentID;
		lst_COLUMN_DATE << pDataTmp->m_strDate;
		lst_COLUMN_OPEN << pDataTmp->m_strOpen;
		lst_COLUMN_HIGH << pDataTmp->m_strHigh;
		lst_COLUMN_LOW << pDataTmp->m_strLow;
		lst_COLUMN_CLOSE << pDataTmp->m_strClose;
		lst_COLUMN_VOLUME << pDataTmp->m_strVolume;
		lst_COLUMN_ADJCLOSE << pDataTmp->m_strAdjClose;

		iterLst++;
	}//while

	//pQSqlQueryForInseert->addBindValue(lstInstrumentID);
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
