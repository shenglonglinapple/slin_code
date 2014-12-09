#ifndef __CLASS_SQLITE_DB_OPER_HELPER_H__
#define __CLASS_SQLITE_DB_OPER_HELPER_H__


#include <string>
#include <list>

#include <QtCore/QStringList>

class CHistoryData;
class CSqliteDbOper;

class CSqliteDbOperHelper
{
public:
	typedef std::list<CHistoryData*>	LstHistoryDataT;
	typedef std::list<CHistoryData*>::iterator	LstHistoryDataIterT;
public:
	CSqliteDbOperHelper();
	virtual ~CSqliteDbOperHelper();
public:
	void saveData(const std::string& strSymbolUse, const std::string& strHistoryData);

private:
	void _AnalysisData(QStringList& strLstLines, LstHistoryDataT& lstData);
	void _FreeData(LstHistoryDataT* pLstData);
private:
	CSqliteDbOper* m_pSqliteDbOper;

};


#endif //__CLASS_SQLITE_DB_OPER_HELPER_H__
