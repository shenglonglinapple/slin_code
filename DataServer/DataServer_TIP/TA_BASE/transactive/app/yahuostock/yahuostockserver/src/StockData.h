#ifndef __CLASS_STOCK_DATA_H__
#define __CLASS_STOCK_DATA_H__

#include <string>

class CStockData 
{
public:
	CStockData();
	virtual ~CStockData();
public:
	CStockData& operator=(const CStockData& objectCopy);
public:
	std::string m_strSymbol;// = s_SSSZ_Stocks[nIndex].m_psz_Symbol;
	std::string m_strNamePinYin;// = s_SSSZ_Stocks[nIndex].m_psz_NamePinYin;
	std::string m_strSymbolExtern;// = s_SSSZ_Stocks[nIndex].m_psz_SymbolExtern;
public:
	int m_nIndex;
	std::string m_strSymbolUse;//m_strSymbol+m_strSymbolExtern
	std::string m_strName;// = s_SSSZ_Stocks[nIndex].m_psz_Name;
public:
	void logInfo();
	void logInfo(const std::string &fileName, 
		unsigned lineNumber, 
		const std::string &errorMessage);
public:
	std::string getStringInfo();
};


#endif //__CLASS_STOCK_DATA_H__
