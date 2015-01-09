#ifndef __CLASS_STOCK_DATA_H__
#define __CLASS_STOCK_DATA_H__

#include <QtCore/QString>

class CStockData 
{
public:
	CStockData();
	virtual ~CStockData();
public:
	CStockData& operator=(const CStockData& objectCopy);
public:
	QString  m_strSymbol;// = s_SSSZ_Stocks[nIndex].m_psz_Symbol;
	QString  m_strNamePinYin;// = s_SSSZ_Stocks[nIndex].m_psz_NamePinYin;
	QString  m_strSymbolExtern;// = s_SSSZ_Stocks[nIndex].m_psz_SymbolExtern;
public:
	qint32 m_nIndex;
	qint32 m_nStockID;
	QString  m_strSymbolUse;//m_strSymbol+m_strSymbolExtern
	QString  m_strName;// = s_SSSZ_Stocks[nIndex].m_psz_Name;
private:
	void _Clear();
public:
	void setValue(qint32 nIndex,
		const QString& strSymbol,
		const QString& strNamePinYin,
		const QString& strSymbolExtern);
public:
	void logInfo( const QString& fileName, qint32 lineNumber );
	
};


#endif //__CLASS_STOCK_DATA_H__
