#include "StockDataDBActor.h"

#include "YahuoHistoryReqAck.h"
#include "RequestYahuoDataHelper.h"
#include "FileDBOperHelper.h"
#include "SqliteDbOperHelper.h"
#include "Log4cppLogger.h"
#include "StockMinTimeMaxTime.h"
#include "SymbolUseManager.h"

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

	_Update_SymbolUseManager();
}

void CStockDataDBActor::_Update_SymbolUseManager()
{
	CStockMinTimeMaxTime* pStockMinTimeMaxTime = NULL;
	CSymbolUseManager* pSymbolUseManager = NULL;

	getStockMinTimeMaxTime(m_strSymbolUse, &pStockMinTimeMaxTime);
	m_pSqliteDbOperHelper->select_TABLE_SYMBOLUSE_MANAGER(&pSymbolUseManager);

	if (NULL != pSymbolUseManager && NULL != pStockMinTimeMaxTime)
	{
		pSymbolUseManager->m_strSymbolUse = pStockMinTimeMaxTime->m_strSymbolUse;
		pSymbolUseManager->m_strMaxTime = pStockMinTimeMaxTime->m_strMaxTime;
		pSymbolUseManager->m_nUpdateFailed = 0;
	}

	if (NULL != pStockMinTimeMaxTime)
	{
		delete pStockMinTimeMaxTime;
		pStockMinTimeMaxTime = NULL;
	}
	if (NULL != pSymbolUseManager)
	{
		delete pSymbolUseManager;
		pSymbolUseManager = NULL;
	}
}

void CStockDataDBActor::updateFailedCount( const QString& strSymbolUse )
{
	CSymbolUseManager* pSymbolUseManager = NULL;

	m_pSqliteDbOperHelper->select_TABLE_SYMBOLUSE_MANAGER(&pSymbolUseManager);

	if (NULL != pSymbolUseManager)
	{
		pSymbolUseManager->m_nUpdateFailed++;
		m_pSqliteDbOperHelper->update_TABLE_SYMBOLUSE_MANAGER(pSymbolUseManager);
	}
	
	if (NULL != pSymbolUseManager)
	{
		delete pSymbolUseManager;
		pSymbolUseManager = NULL;
	}
}

void CStockDataDBActor::getStockMinTimeMaxTime( const QString& strSymbolUse, CStockMinTimeMaxTime** ppValueGet )
{
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"getStockMinTimeMaxTime begin";
	QString strMinTime;
	QString strMaxTime;
	int nCount = 0;
	double fLowValue = 0;
	double fHighValue = 0;
	double fCurrentValue = 0;
	double fCurrentPercentage = 0;

	if (NULL != m_pSqliteDbOperHelper)
	{
		m_pSqliteDbOperHelper->selectData_MinTime(strMinTime);
		m_pSqliteDbOperHelper->selectData_MaxTime(strMaxTime);
		m_pSqliteDbOperHelper->selectData_Count(nCount);
		m_pSqliteDbOperHelper->selectData_LowHigh(fLowValue, fHighValue);
		m_pSqliteDbOperHelper->selectData_Current(fCurrentValue);
	}

	if ((fHighValue - fLowValue) > 0)
	{
		fCurrentPercentage = (fCurrentValue - fLowValue)/(fHighValue - fLowValue);
	}
	else
	{
		fCurrentPercentage = (fCurrentValue - fLowValue);
	}

	(*ppValueGet) = new CStockMinTimeMaxTime();
	(*ppValueGet)->m_strSymbolUse = m_strSymbolUse;
	(*ppValueGet)->m_strMinTime = strMinTime;
	(*ppValueGet)->m_strMaxTime = strMaxTime;
	(*ppValueGet)->m_nCount = nCount;
	(*ppValueGet)->m_fHigh = fHighValue;
	(*ppValueGet)->m_fLow = fLowValue;
	(*ppValueGet)->m_fCurrent = fCurrentValue;
	(*ppValueGet)->m_fCurrentPercentage = fCurrentPercentage;

	(*ppValueGet)->logInfo(__FILE__, __LINE__);

	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"getStockMinTimeMaxTime end";

}

int CStockDataDBActor::selectData( const QString & strFrom, const QString & strTo, QList<CHistoryData*>& lstData )
{
	int nFunRes = 0;
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"selectData begin";

	if (NULL != m_pSqliteDbOperHelper)
	{
		nFunRes = m_pSqliteDbOperHelper->selectData(strFrom, strTo, lstData);
	}
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"selectData"
		<<" "<<"strFrom="<<strFrom
		<<" "<<"strTo="<<strTo
		<<" "<<"lstData.size="<<lstData.size();
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"selectData end";
	return nFunRes;
}

int CStockDataDBActor::select_TABLE_SYMBOLUSE_MANAGER( CSymbolUseManager** ppData )
{
	int nFunRes = 0;
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"select_TABLE_SYMBOLUSE_MANAGER begin";

	if (NULL != m_pSqliteDbOperHelper)
	{
		nFunRes = m_pSqliteDbOperHelper->select_TABLE_SYMBOLUSE_MANAGER(ppData);
	}
	MYLOG4CPP_DEBUG<<"m_strSymbolUse="<<m_strSymbolUse<<" "<<"select_TABLE_SYMBOLUSE_MANAGER end";
	return nFunRes;
}




