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
class CSymbolUseManager;

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

	int selectData_MinTime(QString& strValueGet);
	int selectData_MaxTime(QString& strValueGet);
	int selectData_Count(int& nValueGet);
	int selectData_LowHigh(double& fLowValueGet, double& fHighValueGet);
	int selectData_Current(double& fCurrentValueGet);
public:
	int select_TABLE_SYMBOLUSE_MANAGER(CSymbolUseManager** ppData);
	int update_TABLE_SYMBOLUSE_MANAGER(const CSymbolUseManager* pData);

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
