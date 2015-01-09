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

void CStockData::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"m_strSymbol="<<m_strSymbol
		<<" "<<"m_strNamePinYin="<<m_strNamePinYin
		<<" "<<"m_strSymbolExtern="<<m_strSymbolExtern
		<<" "<<"m_nIndex="<<m_nIndex
		<<" "<<"m_nStockID="<<m_nStockID
		<<" "<<"m_strSymbolUse="<<m_strSymbolUse
		<<" "<<"m_strName="<<m_strName;
}

void CStockData::setValue(qint32 nIndex, const QString& strSymbol, const QString& strNamePinYin, const QString& strSymbolExtern )
{
	QString  strSymbolUse;
	QString  strStockID;
	qint32 nStockID = 0;

	strSymbolUse = strSymbol + strSymbolExtern;
	strStockID = strSymbolUse.mid(0, strSymbolUse.indexOf("."));
	nStockID = strStockID.toInt();

	this->m_nIndex = nIndex;
	this->m_nStockID = nStockID;
	this->m_strSymbol = strSymbol;
	this->m_strNamePinYin = strNamePinYin;
	this->m_strSymbolExtern = strSymbolExtern;
	this->m_strSymbolUse = strSymbolUse;
	this->m_strName = strNamePinYin;
}
