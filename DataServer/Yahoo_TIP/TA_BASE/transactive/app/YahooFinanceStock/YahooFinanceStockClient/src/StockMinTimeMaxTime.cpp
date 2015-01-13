#include "StockMinTimeMaxTime.h"

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
