#ifndef __CLASS_ORDER_MANAGER_H__
#define __CLASS_ORDER_MANAGER_H__

#include <map>
#include <list>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class COrderData;

class CDataOrderManager
{
public:
	static CDataOrderManager& getInstance();
	static void removeInstance();

private:
	static CDataOrderManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	typedef std::map<std::string, COrderData*>                      MapOrderDataItemT;//strOrderUUID
	typedef std::map<std::string, COrderData*>::iterator            MapOrderDataItemIterT;
	typedef std::map<std::string, COrderData*>::value_type          MapOrderDataItemValueTypeT;
private:
	CDataOrderManager();
	virtual ~CDataOrderManager();
public:
	void addOrder(const COrderData* pOrderData);
	void removeOrder( const std::string& strOrderUUID );
	void getNotifyOrder(std::list<COrderData*>& lstMyOrderData);

private:
	void _FreeData_Map();
	void _FreeData_Map(MapOrderDataItemT& mapStockData);
private:
	QMutex m_mutex_MapOrderDataItemT_Order;
	MapOrderDataItemT m_MapOrderDataItemT_Order;
};


#endif //__CLASS_ORDER_MANAGER_H__
