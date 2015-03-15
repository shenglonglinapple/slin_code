#include "StockMinTimeMaxTime.h"
#include "Log4cppLogger.h"

CStockMinTimeMaxTime::CStockMinTimeMaxTime( void )
{
	_Clear();
}

CStockMinTimeMaxTime::~CStockMinTimeMaxTime( void )
{
	_Clear();
}


CStockMinTimeMaxTime& CStockMinTimeMaxTime::operator=( const CStockMinTimeMaxTime& objectCopy )
{
	m_strSymbolUse = objectCopy.m_strSymbolUse;
	m_strMinTime = objectCopy.m_strMinTime;
	m_strMaxTime = objectCopy.m_strMaxTime;
	m_nCount = objectCopy.m_nCount;


	return *this;
}

void CStockMinTimeMaxTime::_Clear()
{
	m_strSymbolUse.clear();
	m_strMinTime.clear();
	m_strMaxTime.clear();
	m_nCount = 0;
}

void CStockMinTimeMaxTime::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CStockMinTimeMaxTime:"
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strMinTime="<<m_strMinTime
		<<" "<<"m_strMaxTime="<<m_strMaxTime
		<<" "<<"m_nCount="<<m_nCount
		<<" "<<"m_fLow="<<m_fLow
		<<" "<<"m_fHigh="<<m_fHigh
		<<" "<<"m_fCurrent="<<m_fCurrent
		<<" "<<"m_fCurrentPercentage="<<m_fCurrentPercentage;

}
