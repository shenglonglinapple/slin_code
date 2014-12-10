#ifndef __CLASS_HISTORY_STOCK_MANAGER_H__
#define __CLASS_HISTORY_STOCK_MANAGER_H__

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>


class CHistoryData;
class CSqliteDbOperHelper;

class CHistoryStockManager
{
public:
	typedef std::list<CHistoryData*>	LstHistoryDataT;
	typedef std::list<CHistoryData*>::iterator	LstHistoryDataIterT;
public:
	static CHistoryStockManager& getInstance();
	static void removeInstance();

private:
	static CHistoryStockManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	typedef std::map<std::string, CSqliteDbOperHelper*>                      MapSqliteDbOperItemT;
	typedef std::map<std::string, CSqliteDbOperHelper*>::iterator            MapSqliteDbOperItemIterT;
	typedef std::map<std::string, CSqliteDbOperHelper*>::value_type          MapSqliteDbOperItemValueTypeT;
private:
	CHistoryStockManager();
	virtual ~CHistoryStockManager();
public:
	void downloadHistoryData(const std::string& strSymbolUse, const std::string& strFrom, const std::string& strTo, LstHistoryDataT& lstData);
private:
	void _FreeData_Map_HistoryStock();
	void _FreeData_Map(MapSqliteDbOperItemT& mapStockData);
	void _AddItem(const std::string& strSymbolUse);
	CSqliteDbOperHelper* _FindItem(const std::string& strSymbolUse);
private:
	QMutex m_mutex_Map_HistoryStock;
	MapSqliteDbOperItemT m_Map_HistoryStock;
};


#endif //__CLASS_HISTORY_STOCK_MANAGER_H__
