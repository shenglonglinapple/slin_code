#ifndef __CLASS_TOTAL_STOCK_DATA_H__
#define __CLASS_TOTAL_STOCK_DATA_H__

#include <iostream>

//
//wchar_t stddef.h
//win32 wchar_t 16bits 2bytes;  linux wchar_t 32bits 4bytes
//wchar_t wstr=L"tv"; %S(not %s) %ls; just use wprintf to replace printf;wprintf(L"%ls",wstr);
//setlocale(LC_ALL,"zh_CN.utf8"); set env; #include <locale.h> setlocale(LC_ALL, "");
//doc http://www.cnblogs.com/michaelowen/articles/2128771.html
#include "stddef.h"

//TotalStocksData

//int m_nArrSize = sizeof(s_SSSZ_Stocks) / sizeof (*s_SSSZ_Stocks);


struct st_sssz_stocks	
{
	const char*  m_psz_Symbol;
	const char*  m_psz_SymbolExtern;
	const char*  m_psz_SymbolUse;
	const char*  m_psz_NamePinYinFirst;
	const char*  m_psz_NamePinYinFull0;
	const char*  m_psz_NamePinYinFull4;	
	const wchar_t* m_pwsz_NameUtf8;
};


//yahuo hava data fro this stocks
static const st_sssz_stocks  s_SSSZ_Stocks[]=	
{   

//////////////////////////////////////////////////////////////////////////////////////////////////////
{
	/*Symbol*/("600000"),
	/*SymbolExtern*/(".SS"),
	/*SymbolUse*/("600000.SS"),
	/*NamePinYinFirst*/("PFYH"),
	/*NamePinYinFull0*/("PU FA YIN HANG"),
	/*NamePinYinFull4*/("PU3 FA1 YIN2 HANG2"),
	/*NameUtf8*/(L"浦发银行")
},
{
	/*Symbol*/("600004"),
	/*SymbolExtern*/(".SS"),
	/*SymbolUse*/("600004.SS"),
	/*NamePinYinFirst*/("BYJC"),
	/*NamePinYinFull0*/("BAI YUN JI CHANG"),
	/*NamePinYinFull4*/("BAI2 YUN2 JI1 CHANG2"),
	/*NameUtf8*/(L"白云机场")
},
{
	/*Symbol*/("600005"),
	/*SymbolExtern*/(".SS"),
	/*SymbolUse*/("600005.SS"),
	/*NamePinYinFirst*/("WGGF"),
	/*NamePinYinFull0*/("WU GANG GU FEN"),
	/*NamePinYinFull4*/("WU3 GANG1 GU3 FEN4"),
	/*NameUtf8*/(L"武钢股份")
},
//////////////////////////////////////////////////////////////////////////////////////////////////////

};

#endif //__CLASS_TOTAL_STOCK_DATA_H__
