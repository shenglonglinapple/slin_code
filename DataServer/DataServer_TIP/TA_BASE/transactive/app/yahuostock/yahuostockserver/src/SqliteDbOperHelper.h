#ifndef __CLASS_SQLITE_DB_OPER_HELPER_H__
#define __CLASS_SQLITE_DB_OPER_HELPER_H__


#include <string>
#include <list>

#include <QtCore/QStringList>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CHistoryData;
class CSqliteDbOper;

class CSqliteDbOperHelper
{
public:
	typedef std::list<CHistoryData*>	LstHistoryDataT;
	typedef std::list<CHistoryData*>::iterator	LstHistoryDataIterT;
public:
	CSqliteDbOperHelper(const std::string& strSymbolUse);
	virtual ~CSqliteDbOperHelper();
public:
	void saveData(const std::string& strSymbolUse, const std::string& strHistoryData);
public:
	int selectData( const std::string& strSymbolUse, const std::string& strFrom, const std::string& strTo, LstHistoryDataT& lstData );
	std::string getSymbolUse();
private:
	void _AnalysisData(QStringList& strLstLines, LstHistoryDataT& lstData);
	void _FreeData(LstHistoryDataT* pLstData);
private:
	QMutex m_mutex_SqliteDbOper;
	CSqliteDbOper* m_pSqliteDbOper;
	std::string m_strSymbolUse;
};


#endif //__CLASS_SQLITE_DB_OPER_HELPER_H__
