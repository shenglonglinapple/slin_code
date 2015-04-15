#ifndef __CLASS_STOCK_INFO_H__
#define __CLASS_STOCK_INFO_H__

#include <QtCore/QString>
#include <QtCore/QStringList>

class CStockInfo
{
public:
	CStockInfo();
	virtual ~CStockInfo();
public:
	CStockInfo& operator=(const CStockInfo& objectCopy);
private:
	void _Init();
public:
	//QString m_strSymbol;//not use
	//QString m_strSymbolExtern;//not use
	QString m_strSymbolUse;//index
	QString m_strNamePinYinFirst;
	QString m_strNamePinYinFull0;
	QString m_strNamePinYinFull4;
	QString m_strNameUtf8;//const wchar_t* m_pwsz_NameUtf8;
};


#endif //__CLASS_STOCK_INFO_H__
