#include "StockDataActor.h"

#include "Log4cppLogger.h"
#include "StockDataDBActor.h"

CStockDataActor::CStockDataActor( QObject* parent/*=0*/ )
{
	m_strSymbolUse.clear();
	m_pStockDataDBActor = NULL;



}

CStockDataActor::~CStockDataActor()
{
	if (NULL != m_pStockDataDBActor)
	{
		delete m_pStockDataDBActor;
		m_pStockDataDBActor = NULL;
	}


}



void CStockDataActor::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CStockDataActor:m_strSymbolUse="<<m_strSymbolUse;
}

void CStockDataActor::setValue( const QString& strSymbol, const QString& strSymbolExtern )
{
	QString  strSymbolUse;
	QString  strStockID;
	qint32 nStockID = 0;

	strSymbolUse = strSymbol + strSymbolExtern;
	strStockID = strSymbolUse.mid(0, strSymbolUse.indexOf("."));
	nStockID = strStockID.toInt();

	this->m_strSymbolUse = strSymbolUse;

	m_pStockDataDBActor = new CStockDataDBActor(strSymbolUse);
}

void CStockDataActor::saveData( const QString& strHistoryData )
{
	if (NULL != m_pStockDataDBActor)
	{
		m_pStockDataDBActor->saveData(strHistoryData);
	}
}

void CStockDataActor::getStockMinTimeMaxTime( const QString& strSymbolUse, CStockMinTimeMaxTime** ppValueGet )
{
	if (NULL != m_pStockDataDBActor)
	{
		m_pStockDataDBActor->getStockMinTimeMaxTime(strSymbolUse, ppValueGet);
	}
}

int CStockDataActor::selectData( const QString & strFrom, const QString & strTo, QList<CHistoryData*>& lstData )
{
	int nFunRes = 0;
	if (NULL != m_pStockDataDBActor)
	{
		nFunRes = m_pStockDataDBActor->selectData(strFrom, strTo, lstData);
	}
	return nFunRes;
}

void CStockDataActor::updateFailedCount( const QString& strSymbolUse )
{
	if (NULL != m_pStockDataDBActor)
	{
		m_pStockDataDBActor->updateFailedCount(strSymbolUse);
	}
	return;
}

int CStockDataActor::select_TABLE_SYMBOLUSE_MANAGER( CSymbolUseManager** ppData )
{
	int nFunRes = 0;
	if (NULL != m_pStockDataDBActor)
	{
		nFunRes = m_pStockDataDBActor->select_TABLE_SYMBOLUSE_MANAGER(ppData);
	}
	return nFunRes;
}



