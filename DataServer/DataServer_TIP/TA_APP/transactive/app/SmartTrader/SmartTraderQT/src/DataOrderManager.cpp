#include "DataOrderManager.h"

#include "BaseException.h"
#include "OrderData.h"
#include "Log4cppLogger.h"


CDataOrderManager* CDataOrderManager::m_pInstance = 0;
QMutex CDataOrderManager::m_mutexInstance;

CDataOrderManager& CDataOrderManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataOrderManager();
	}
	return (*m_pInstance);
}

void CDataOrderManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;
}

CDataOrderManager::CDataOrderManager()
{
	_FreeData_Map();
}

CDataOrderManager::~CDataOrderManager()
{	
	_FreeData_Map();	
}




void CDataOrderManager::_FreeData_Map()
{
	QMutexLocker lock(&m_mutex_MapOrderDataItemT_Order);	
	_FreeData_Map(m_MapOrderDataItemT_Order);
}


void CDataOrderManager::_FreeData_Map(MapOrderDataItemT& mapStockData)
{
	MapOrderDataItemIterT iterMap;
	COrderData* pData = NULL;

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

void CDataOrderManager::removeOrder( const std::string& strOrderUUID )
{
	QMutexLocker lock(&m_mutex_MapOrderDataItemT_Order);	

	MapOrderDataItemIterT iterMap;
	COrderData* pData = NULL;

	iterMap = m_MapOrderDataItemT_Order.find(strOrderUUID);
	if (iterMap != m_MapOrderDataItemT_Order.end())
	{
		pData = (iterMap->second);
		delete pData;
		pData = NULL;
		m_MapOrderDataItemT_Order.erase(iterMap);
	}
	
}

void CDataOrderManager::addOrder( const COrderData* pOrderData )
{
	COrderData* pData = NULL;
	pData = new COrderData();

	*pData = *pOrderData;
	QMutexLocker lock(&m_mutex_MapOrderDataItemT_Order);	
	m_MapOrderDataItemT_Order.insert(
		MapOrderDataItemValueTypeT(pData->m_strUUID.toStdString(), pData));

	pData = NULL;
}


void CDataOrderManager::getNotifyOrder( std::list<COrderData*>& lstMyOrderData )
{
	QMutexLocker lock(&m_mutex_MapOrderDataItemT_Order);	

	MapOrderDataItemIterT iterMap;
	COrderData* pData = NULL;
	std::string strData;
	COrderData* pOrderData = NULL;

	iterMap = m_MapOrderDataItemT_Order.begin();
	while (iterMap != m_MapOrderDataItemT_Order.end())
	{
		pData = (iterMap->second);

		pOrderData = new COrderData();
		*pOrderData = *pData;

		lstMyOrderData.push_back(pOrderData);
		pOrderData = NULL;

		iterMap++;
	}//while

}
