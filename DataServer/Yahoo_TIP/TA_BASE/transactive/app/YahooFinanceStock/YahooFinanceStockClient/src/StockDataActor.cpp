#include "StockDataActor.h"

#include "Log4cppLogger.h"

CStockDataActor::CStockDataActor( QObject* parent/*=0*/ )
{
	m_strSymbolUse.clear();
}

CStockDataActor::~CStockDataActor()
{
}



void CStockDataActor::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CStockDataActor:m_strSymbolUse="<<m_strSymbolUse;
}

void CStockDataActor::setValue( const QString& strSymbolUse)
{
	QString  strStockID;
	qint32 nStockID = 0;

	strStockID = strSymbolUse.mid(0, strSymbolUse.indexOf("."));
	nStockID = strStockID.toInt();
	this->m_strSymbolUse = strSymbolUse;

}


