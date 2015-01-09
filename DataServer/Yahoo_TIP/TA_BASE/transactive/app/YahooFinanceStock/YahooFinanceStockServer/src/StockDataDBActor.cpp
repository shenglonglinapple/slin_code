#include "StockDataDBActor.h"

#include "YahuoHistoryReqAck.h"
#include "RequestYahuoDataHelper.h"
#include "FileDBOperHelper.h"
#include "SqliteDbOperHelper.h"
#include "Log4cppLogger.h"

CStockDataDBActor::CStockDataDBActor( const QString& strSymbolUse, QObject *parent /*= 0*/ )
{
	m_strSymbolUse = strSymbolUse;

	m_pYahuoHistoryReqAck = NULL;
	m_pRequestYahuoDataHelper = NULL;
	m_pFileDBOperHelper = NULL;
	m_pSqliteDbOperHelper = NULL;

	m_pYahuoHistoryReqAck = new CYahuoHistoryReqAck();
	m_pRequestYahuoDataHelper = new CRequestYahuoDataHelper(strSymbolUse);
	m_pFileDBOperHelper = new CFileDBOperHelper(strSymbolUse);
	m_pSqliteDbOperHelper = new CSqliteDbOperHelper(strSymbolUse);
}


CStockDataDBActor::~CStockDataDBActor()
{
	if (NULL != m_pSqliteDbOperHelper)
	{
		delete m_pSqliteDbOperHelper;
		m_pSqliteDbOperHelper = NULL;
	}
	if (NULL != m_pFileDBOperHelper)
	{
		delete m_pFileDBOperHelper;
		m_pFileDBOperHelper = NULL;
	}


	if (NULL != m_pRequestYahuoDataHelper)
	{
		delete m_pRequestYahuoDataHelper;
		m_pRequestYahuoDataHelper = NULL;
	}

	if (NULL != m_pYahuoHistoryReqAck)
	{
		delete m_pYahuoHistoryReqAck;
		m_pYahuoHistoryReqAck = NULL;
	}

}




void CStockDataDBActor::saveData(const QString& strHistoryData) 
{
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"saveData to FileDB begin";

	if (NULL != m_pFileDBOperHelper)
	{
		m_pFileDBOperHelper->saveData(strHistoryData);
	}
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"saveData to FileDB end";
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"saveData to SqliteDb begin";
	if (NULL != m_pSqliteDbOperHelper)
	{
		m_pSqliteDbOperHelper->saveData(strHistoryData);
	}
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"saveData to SqliteDb end";
}




