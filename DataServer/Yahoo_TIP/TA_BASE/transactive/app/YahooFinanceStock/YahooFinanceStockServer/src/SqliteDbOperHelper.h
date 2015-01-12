#ifndef __CLASS_SQLITE_DB_OPER_HELPER_H__
#define __CLASS_SQLITE_DB_OPER_HELPER_H__


#include <string>
#include <list>

#include <QtCore/QStringList>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QList>

class CHistoryData;
class CSqliteDbOper;

class CSqliteDbOperHelper
{
public:
	typedef QList<CHistoryData*>	LstHistoryDataT;
	typedef QList<CHistoryData*>::iterator	LstHistoryDataIterT;
public:
	CSqliteDbOperHelper(const QString & strSymbolUse);
	virtual ~CSqliteDbOperHelper();
public:
	void saveData(const QString & strHistoryData);
public:
	int selectData(const QString & strFrom, const QString & strTo, LstHistoryDataT& lstData );
	QString  getSymbolUse();
private:
	void _AnalysisData(QStringList& strLstLines, LstHistoryDataT& lstData);
	void _FreeData(LstHistoryDataT* pLstData);
	void _RemoveEmptyString(QStringList& strList);
private:
	QMutex m_mutex_SqliteDbOper;
	CSqliteDbOper* m_pSqliteDbOper;
	QString  m_strSymbolUse;
};


#endif //__CLASS_SQLITE_DB_OPER_HELPER_H__
