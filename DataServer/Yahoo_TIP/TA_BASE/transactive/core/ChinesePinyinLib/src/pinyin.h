#ifndef PINYIN_H
#define PINYIN_H


//
//wchar_t stddef.h
//win32 wchar_t 16bits 2bytes;  linux wchar_t 32bits 4bytes
//wchar_t wstr=L"tv"; %S(not %s) %ls; just use wprintf to replace printf;wprintf(L"%ls",wstr);
//setlocale(LC_ALL,"zh_CN.utf8"); set env; #include <locale.h> setlocale(LC_ALL, "");
//doc http://www.cnblogs.com/michaelowen/articles/2128771.html
#include "stddef.h"
//
#include <map>
#include <deque>

class QString;

enum EC2PType
{
    WIZ_C2P_NORMAL = 0x0,
    WIZ_C2P_FIRST_LETTER_ONLY = 0x1,
    WIZ_C2P_POLYPHONE = 0x2
};

typedef std::deque<QString> CWizStdStringArray;

struct WIZCHINESEWORDPINYINDATA
{
	const char* pinyin;
	int yindiao;
	wchar_t chWord;
};

class CWizPinYin
{
public:
	CWizPinYin();
	~CWizPinYin();
public:
	const char* GetPinYin(wchar_t ch);
	int WizToolsChinese2PinYinEx(const wchar_t* lpszText, EC2PType flags, const char* lpszSplitter, QString& pbstrTextResult);
	int WizToolsChinese2PinYin(const wchar_t* lpszText, EC2PType flags, QString& pbstrTextResult);
	int chinese2pinyin(const QString& strChinese, QString& strPinYin, EC2PType flags);
	void TestPinYin();
private:
	void _Init();
	QString Utf8_To_GB(QString strUtf8);
	QString GB_To_Utf8(char *strGB);
private:
	std::multimap<wchar_t, WIZCHINESEWORDPINYINDATA> m_data;

};

#endif // PINYIN_H
