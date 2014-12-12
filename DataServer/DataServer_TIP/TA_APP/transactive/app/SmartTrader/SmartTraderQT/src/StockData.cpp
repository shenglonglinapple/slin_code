#include "StockData.h"

#include "Log4cppLogger.h"

CStockData::CStockData()
{
	_Clear();
}

CStockData::~CStockData()
{

}

CStockData& CStockData::operator=( const CStockData& objectCopy )
{
	m_strSymbol = objectCopy.m_strSymbol;
	m_strNamePinYin = objectCopy.m_strNamePinYin;
	m_strSymbolExtern = objectCopy.m_strSymbolExtern;
	m_nIndex = objectCopy.m_nIndex;
	m_nStockID = objectCopy.m_nStockID;
	m_strSymbolUse = objectCopy.m_strSymbolUse;
	m_strName = objectCopy.m_strName;


	return *this;
}

void CStockData::_Clear()
{
	m_strSymbol.clear();
	m_strNamePinYin.clear();
	m_strSymbolExtern.clear();
	m_nIndex = 0;
	m_nStockID = 0;
	m_strSymbolUse.clear();
	m_strName.clear();
}

void CStockData::logInfo()
{
	/*
	MYLOG4CPP_DEBUG<<"CStockData"
		<<" "<<"m_nIndex="<<m_nIndex
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strNamePinYin="<<m_strNamePinYin;
		*/
}
void CStockData::logInfo(const std::string &fileName, unsigned lineNumber, const std::string &errorMessage)
{
	/*
	MYLOG4CPP_ERROR_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"errorMessage:"<<errorMessage
		<<" "<<"m_nIndex="<<m_nIndex
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strNamePinYin="<<m_strNamePinYin;
		*/

}
