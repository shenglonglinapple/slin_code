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


