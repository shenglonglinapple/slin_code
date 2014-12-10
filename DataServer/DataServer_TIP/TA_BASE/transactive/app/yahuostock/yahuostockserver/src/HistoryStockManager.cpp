#include "HistoryStockManager.h"

#include "BaseException.h"
#include "StockData.h"
#include "SqliteDbOperHelper.h"
#include "Log4cppLogger.h"
#include "YahuoRealTimeReqAck.h"



CHistoryStockManager* CHistoryStockManager::m_pInstance = 0;
QMutex CHistoryStockManager::m_mutexInstance;

CHistoryStockManager& CHistoryStockManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CHistoryStockManager();
	}
	return (*m_pInstance);
}

void CHistoryStockManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;
}

CHistoryStockManager::CHistoryStockManager()
{
	_FreeData_Map_HistoryStock();
}

CHistoryStockManager::~CHistoryStockManager()
{	
	_FreeData_Map_HistoryStock();	
}




void CHistoryStockManager::_FreeData_Map_HistoryStock()
{
	QMutexLocker lock(&m_mutex_Map_HistoryStock);	
	_FreeData_Map(m_Map_HistoryStock);
}


void CHistoryStockManager::_FreeData_Map(MapSqliteDbOperItemT& mapStockData)
{
	MapSqliteDbOperItemIterT iterMap;
	CSqliteDbOperHelper* pData = NULL;

	iterMap = mapStockData.begin();
	while (iterMap != mapStockData.end())
	{
		pData = (iterMap->second);

		delete pData;
		pData = NULL;

		iterMap++;
	}
	mapStockData.clear();
	return;
}


void CHistoryStockManager::downloadHistoryData(const std::string& strSymbolUse, const std::string& strFrom, const std::string& strTo, LstHistoryDataT& lstData)
{
	CSqliteDbOperHelper* pDataFind = NULL;

	pDataFind = NULL;
	pDataFind = _FindItem(strSymbolUse);
	if (NULL == pDataFind)
	{
		_AddItem(strSymbolUse);
	}

	pDataFind->selectData(strSymbolUse, strFrom, strTo, lstData);
	
}

void CHistoryStockManager::_AddItem(const std::string& strSymbolUse)
{
	QMutexLocker lock(&m_mutex_Map_HistoryStock);	

	CSqliteDbOperHelper* pData = NULL;
	pData = new CSqliteDbOperHelper(strSymbolUse);

	m_Map_HistoryStock.insert(MapSqliteDbOperItemValueTypeT(strSymbolUse,pData));
}
CSqliteDbOperHelper* CHistoryStockManager::_FindItem(const std::string& strSymbolUse)
{
	QMutexLocker lock(&m_mutex_Map_HistoryStock);	

	MapSqliteDbOperItemIterT iterMap;
	CSqliteDbOperHelper* pDataFind = NULL;

	iterMap = m_Map_HistoryStock.begin();
	while (iterMap != m_Map_HistoryStock.end())
	{
		pDataFind = (iterMap->second);

		if (pDataFind->getSymbolUse() == strSymbolUse)
		{
			return pDataFind;
		}

		pDataFind = NULL;
		iterMap++;
	}
	
	return pDataFind;
}
