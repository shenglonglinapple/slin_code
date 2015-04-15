#include "StockInfo.h"
#include "QtTimeHelper.h"



CStockInfo::CStockInfo()
{
	_Init();
}

CStockInfo::~CStockInfo()
{
	
}

CStockInfo& CStockInfo::operator=( const CStockInfo& objectCopy )
{
	//m_strSymbol = objectCopy.m_strSymbol;
	//m_strSymbolExtern = objectCopy.m_strSymbolExtern;
	m_strSymbolUse = objectCopy.m_strSymbolUse;
	m_strNamePinYinFirst = objectCopy.m_strNamePinYinFirst;
	m_strNamePinYinFull0 = objectCopy.m_strNamePinYinFull0;
	m_strNamePinYinFull4 = objectCopy.m_strNamePinYinFull4;
	m_strNameUtf8 = objectCopy.m_strNameUtf8;

	return *this;
}


void CStockInfo::_Init()
{
	//m_strSymbol.clear();
	//m_strSymbolExtern.clear();
	m_strSymbolUse.clear();
	m_strNamePinYinFirst.clear();
	m_strNamePinYinFull0.clear();
	m_strNamePinYinFull4.clear();
	m_strNameUtf8.clear();

}


