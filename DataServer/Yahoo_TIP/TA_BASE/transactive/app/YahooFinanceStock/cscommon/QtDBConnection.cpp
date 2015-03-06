#include "QtDBConnection.h"

#include "DbStatusItem.h"
#include "WorkTime.h"
#include "QtDBQueryAdapter.h"
#include "Log4cppLogger.h"

CQtDBConnection::CQtDBConnection( const CDbStatusItem* pDbStatusItem )
{
	m_pDbStatusItem = NULL;
	m_pConnection = NULL;
	m_pWorkTimeConnecion = NULL;
	m_pWorkTimeUsingConnecion = NULL;
	m_pWorkTimeNotUsingConnecion = NULL;

	m_pDbStatusItem = new CDbStatusItem();
	*m_pDbStatusItem  = *pDbStatusItem;

	m_pWorkTimeConnecion = new CWorkTimeLock(0);
	m_pWorkTimeUsingConnecion = new CWorkTimeLock(0);
	m_pWorkTimeNotUsingConnecion = new CWorkTimeLock(0);	
	m_bIsHealth = true;

	{
		QMutexLocker lockQuery(&m_LockMapActiveQuery);		
		m_mapActiveQuery.clear();
	}
	_CreateConnection();	
}

CQtDBConnection::~CQtDBConnection()
{
	_CleanAllQuery();
	_Close();

	if (NULL != m_pWorkTimeNotUsingConnecion)
	{
		delete m_pWorkTimeNotUsingConnecion;
		m_pWorkTimeNotUsingConnecion = NULL;
	}

	if (NULL != m_pWorkTimeUsingConnecion)
	{
		delete m_pWorkTimeUsingConnecion;
		m_pWorkTimeUsingConnecion = NULL;
	}

	if (NULL != m_pWorkTimeConnecion)
	{
		delete m_pWorkTimeConnecion;
		m_pWorkTimeConnecion = NULL;
	}

	if (NULL != m_pDbStatusItem)
	{
		delete m_pDbStatusItem;
		m_pDbStatusItem = NULL;
	}
}

bool CQtDBConnection::isAnyQueryActive( unsigned long ulMaxTimeoutInSecs )
{
	bool bFunRes = true;

	return bFunRes;
}

QString CQtDBConnection::getConnectionString() const
{
	QString strFunRes;
	return strFunRes;
}

void CQtDBConnection::open()
{
	if (isOpen())
	{
		MYLOG4CPP_DEBUG<<"use established connection";
		return;
	}
	// connection closed, reconnect to the database server
	_CreateConnection();
}

bool CQtDBConnection::isOpen()
{
	bool bIsOpen = false;

	QMutexLocker lock(&m_lockConnection);
	if (NULL != m_pConnection)
	{
		bIsOpen = m_pConnection->isOpen();
	}
	return bIsOpen;
}
qint32 CQtDBConnection::execQuery(const CSQLData& sqlData, IQueryAdapter*& pQueryAdapter)
{
	open();

	QMutexLocker lock(&m_lockConnection);

	qint32 nFunRes = 0;
	QString strSQL;
	bool bExecRes = true;
	QSqlQuery* pSqlQuery = NULL;
	QString strQueryUUID;

	if ( NULL != pQueryAdapter )
	{
		MYLOG4CPP_ERROR<<"pQueryAdapter should not be other value except NULL!";
		cleanQuery( pQueryAdapter );
	}

	strSQL = _GetSQL(sqlData);

	if (strSQL.isEmpty())
	{
		MYLOG4CPP_ERROR<<"_GetSQL error!";
		sqlData.logInfo(__FILE__, __LINE__);
		nFunRes = -1;
		return nFunRes;		
	}


	MYLOG4CPP_DEBUG<<"Begin execute the SQL"
		<<" "<<"m_strXMLSQLKey="<<sqlData.m_strXMLSQLKey
		<<" "<<"strSQL="<<strSQL;

	pSqlQuery = new QSqlQuery(*m_pConnection);
	bExecRes = pSqlQuery->exec(strSQL);
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_DEBUG<<"Fail execute the SQL"
			<<" "<<"m_strXMLSQLKey="<<sqlData.m_strXMLSQLKey
			<<" "<<"strSQL="<<strSQL
			<<" "<<"error:"<<pSqlQuery->lastError().text();

		delete pSqlQuery;
		pSqlQuery = NULL;
	}
	else
	{
		pQueryAdapter = NULL;
		pQueryAdapter = new CQtDBQueryAdapter(pSqlQuery);
		strQueryUUID = pQueryAdapter->getQueryUUID();
		QMutexLocker lockQuery(&m_LockMapActiveQuery);		
		m_mapActiveQuery.insert(strQueryUUID, pQueryAdapter);
	}

	MYLOG4CPP_DEBUG<<"End execute the SQL"
		<<" "<<"m_strXMLSQLKey="<<sqlData.m_strXMLSQLKey
		<<" "<<"strSQL="<<strSQL;

	return nFunRes;	
}
qint32 CQtDBConnection::execModify( const CSQLData& sqlData )
{
	open();

	QMutexLocker lock(&m_lockConnection);

	qint32 nFunRes = 0;
	QString strSQL;
	bool bExecRes = true;
	QSqlQuery* pSqlQuery = NULL;

	strSQL = _GetSQL(sqlData);

	if (strSQL.isEmpty())
	{
		MYLOG4CPP_ERROR<<"_GetSQL error!";
		sqlData.logInfo(__FILE__, __LINE__);
		nFunRes = -1;
		return nFunRes;		
	}


	MYLOG4CPP_DEBUG<<"Begin execute the SQL"
		<<" "<<"m_strXMLSQLKey="<<sqlData.m_strXMLSQLKey
		<<" "<<"strSQL="<<strSQL;

	pSqlQuery = new QSqlQuery(*m_pConnection);
	bExecRes = pSqlQuery->exec(strSQL);
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_DEBUG<<"Fail execute the SQL"
			<<" "<<"m_strXMLSQLKey="<<sqlData.m_strXMLSQLKey
			<<" "<<"strSQL="<<strSQL
			<<" "<<"error:"<<pSqlQuery->lastError().text();
	}

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	MYLOG4CPP_DEBUG<<"End execute the SQL"
		<<" "<<"m_strXMLSQLKey="<<sqlData.m_strXMLSQLKey
		<<" "<<"strSQL="<<strSQL;

	return nFunRes;	
}

qint32 CQtDBConnection::execModifyBatch( const CSQLData& sqlData, const QList<QVariantList*>& LstData )
{
	open();

	QMutexLocker lock(&m_lockConnection);

	qint32 nFunRes = 0;
	QString strSQL;
	bool bExecRes = true;
	QSqlQuery* pSqlQuery = NULL;
	QList<QVariantList*>::const_iterator constIter;
	QVariantList* pData = NULL;

	strSQL = _GetSQL(sqlData);

	if (strSQL.isEmpty())
	{
		MYLOG4CPP_ERROR<<"_GetSQL error!";
		sqlData.logInfo(__FILE__, __LINE__);
		nFunRes = -1;
		return nFunRes;		
	}


	MYLOG4CPP_DEBUG<<"Begin execBatch the SQL"
		<<" "<<"m_strXMLSQLKey="<<sqlData.m_strXMLSQLKey
		<<" "<<"strSQL="<<strSQL;

	pSqlQuery = new QSqlQuery(*m_pConnection);

	pSqlQuery->prepare(strSQL);

	constIter = LstData.constBegin();
	while (constIter != LstData.constEnd())
	{
		pData = *constIter;
		pSqlQuery->addBindValue(*pData);
		constIter++;
	}

	bExecRes = pSqlQuery->execBatch();
	if (!bExecRes)
	{
		nFunRes = -1;
		MYLOG4CPP_DEBUG<<"Fail execBatch the SQL"
			<<" "<<"m_strXMLSQLKey="<<sqlData.m_strXMLSQLKey
			<<" "<<"strSQL="<<strSQL
			<<" "<<"error:"<<pSqlQuery->lastError().text();
	}

	if (NULL != pSqlQuery)
	{
		delete pSqlQuery;
		pSqlQuery = NULL;
	}

	MYLOG4CPP_DEBUG<<"End execBatch the SQL"
		<<" "<<"m_strXMLSQLKey="<<sqlData.m_strXMLSQLKey
		<<" "<<"strSQL="<<strSQL;

	return nFunRes;	
}


void CQtDBConnection::incrementExecutionCount()
{

}

void CQtDBConnection::decrementExecutionCount()
{

}

qint32 CQtDBConnection::getExecutionCount()
{
	qint32 nFunRes = 0;

	return nFunRes;
}

bool CQtDBConnection::isHealth()
{
	bool bFunRes = true;

	return bFunRes;
}

void CQtDBConnection::setConStatus( bool bIsHealth )
{

}

void CQtDBConnection::cleanQuery( IQueryAdapter*& pQueryAdapter )
{
	QMutexLocker lockQuery(&m_LockMapActiveQuery);		

	QMap<QString, IQueryAdapter*>::iterator iterMap;
	IQueryAdapter* pQueryAdapterFind = NULL;
	QString strQueyUUID;

	if (NULL == pQueryAdapter)
	{
		return;
	}
	strQueyUUID = pQueryAdapter->getQueryUUID();

	iterMap = m_mapActiveQuery.find(strQueyUUID);
	if (iterMap != m_mapActiveQuery.end())
	{
		pQueryAdapterFind = iterMap.value();

		if (NULL != pQueryAdapterFind && pQueryAdapterFind == pQueryAdapter)
		{
			delete pQueryAdapter;
			pQueryAdapter = NULL;

			pQueryAdapterFind = NULL;
			pQueryAdapter = NULL;

			m_mapActiveQuery.erase(iterMap);
		}
	}
	
}

void CQtDBConnection::_Close()
{
	QMutexLocker lock(&m_lockConnection);

	if (NULL != m_pConnection)
	{
		MYLOG4CPP_DEBUG<<" "<<"begin delete Database"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"Class_Handle=0x"<<this
			<<" "<<"DB_handle=0x"<<m_pConnection
			<<" "<<"m_bIsHealth="<<m_bIsHealth;

		m_pConnection->close();
		delete m_pConnection;
		m_pConnection = NULL;

		QSqlDatabase::removeDatabase(m_pDbStatusItem->m_strDBKey);
		m_pWorkTimeConnecion->workEnd();

		MYLOG4CPP_DEBUG<<" "<<"end delete Database"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"Class_Handle=0x"<<this
			<<" "<<"DB_handle=0x"<<m_pConnection
			<<" "<<"m_bIsHealth="<<m_bIsHealth;
	}
}

void CQtDBConnection::_CreateConnection()
{
	_Close();


	QMutexLocker lock(&m_lockConnection);

	m_pConnection = new QSqlDatabase(
		QSqlDatabase::addDatabase(m_pDbStatusItem->m_strDbType, m_pDbStatusItem->m_strDBKey));
	m_pConnection->setDatabaseName(m_pDbStatusItem->m_strSchema);//full path

	MYLOG4CPP_DEBUG<<" "<<"begin new Database"
		<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString()
		<<" "<<"Class_Handle=0x"<<this
		<<" "<<"DB_handle=0x"<<m_pConnection
		<<" "<<"m_bIsHealth="<<m_bIsHealth;

	if (false == m_pConnection->open())
	{
		MYLOG4CPP_ERROR<<" "<<"Fail to open Database!"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"error:"<<m_pConnection->lastError().text();
	}

	//check
	if (false == m_pConnection->isValid())
	{
		MYLOG4CPP_ERROR<<" "<<"not Valid Database"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString();
	}

	if (false == m_pConnection->driver()->hasFeature(QSqlDriver::Transactions)) 
	{
		MYLOG4CPP_ERROR<<" "<<"Database not support Transactions"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString();
	}
	else
	{
		MYLOG4CPP_DEBUG<<" "<<"Database support Transactions"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString();

	}

	m_pWorkTimeConnecion->workBegin();
	m_pWorkTimeUsingConnecion->workBegin();
	m_pWorkTimeNotUsingConnecion->workBegin();
	setConStatus(true);

	MYLOG4CPP_DEBUG<<" "<<"end new Database"
		<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString()
		<<" "<<"Class_Handle=0x"<<this
		<<" "<<"DB_handle=0x"<<m_pConnection
		<<" "<<"m_bIsHealth="<<m_bIsHealth;

}

void CQtDBConnection::_CleanAllQuery()
{
	QMutexLocker lockQuery(&m_LockMapActiveQuery);		

	QMap<QString, IQueryAdapter*>::iterator iterMap;
	IQueryAdapter* pQueryAdapter = NULL;

	iterMap = m_mapActiveQuery.begin();
	while (iterMap != m_mapActiveQuery.end())
	{
		pQueryAdapter = iterMap.value();

		delete pQueryAdapter;
		pQueryAdapter = NULL;

		iterMap++;
	}
	m_mapActiveQuery.clear();
}



bool CQtDBConnection::_CheckAnyNotQueryActive( qint32 ulMaxTimeoutInSecs )
{
	bool bFunRes = true;

	return bFunRes;
}

QString CQtDBConnection::_GetSQL( const CSQLData& sqlData )
{
	return sqlData.getSqliteSQL();
}

qint32 CQtDBConnection::startTransaction()
{
	qint32 nFunRes = 0;
	QMutexLocker lock(&m_lockConnection);

	if (false == m_pConnection->driver()->hasFeature(QSqlDriver::Transactions)) 
	{
		MYLOG4CPP_ERROR<<" "<<"Database not support Transactions"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString();
		nFunRes = -1;
		return nFunRes;
	}

	if (false == m_pConnection->transaction())
	{
		MYLOG4CPP_ERROR<<" "<<"Database start transaction error"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"error: "<<QSqlDatabase::database().lastError().text();
		nFunRes = -1;
	}
	else
	{
		MYLOG4CPP_DEBUG<<" "<<"Database start transaction"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString();
		nFunRes = 0;
	}

	return nFunRes;
}



qint32 CQtDBConnection::commitTransaction()
{
	qint32 nFunRes = 0;
	QMutexLocker lock(&m_lockConnection);

	if (NULL == m_pConnection)
	{
		nFunRes = -1;
		return nFunRes;
	}

	if (false == m_pConnection->commit())  
	{  
		MYLOG4CPP_ERROR<<" "<<"Database commit transaction error"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString()
			<<" "<<"error: "<<QSqlDatabase::database().lastError().text();

		if(false == m_pConnection->rollback())  
		{  
			MYLOG4CPP_ERROR<<" "<<"Database rollback transaction error"
				<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString()
				<<" "<<"error: "<<QSqlDatabase::database().lastError().text();
		}//if 
	}//if
	else
	{
		MYLOG4CPP_DEBUG<<" "<<"Database commit transaction"
			<<" "<<"getConnectionString="<<m_pDbStatusItem->getConnectionString();
	}
	return nFunRes;
}

QSqlDatabase* CQtDBConnection::getQTDBHandle()
{
	return m_pConnection;
}
