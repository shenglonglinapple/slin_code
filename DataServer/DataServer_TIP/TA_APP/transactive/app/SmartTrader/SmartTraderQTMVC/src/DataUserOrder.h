#ifndef __CLASS_DATA_USER_ORDER_HH__
#define __CLASS_DATA_USER_ORDER_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include "Order.h"

class CProjectLogHelper;
class COrderInfo;
class CTreeItemOrder;

class CDataUserOrder
{ 
public:
	static CDataUserOrder& getInstance();
	static void removeInstance();

private:
	static CDataUserOrder* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataUserOrder(); 
	virtual ~CDataUserOrder(); 
private:
	void _InitMVCDataForOrder();
	void _UnInitMVCDataForOrder();
public:
	void addAndUpdateData(const Order &order);
	CTreeItemOrder* getRootHandle();
public:
	void _Test();
private:
	QMutex m_mutexForMapOrder;
	QMap<unsigned int, Order*> m_MapOrder;//OrderID
	COrderInfo* m_pOrderInfo;
	CTreeItemOrder* m_pTreeItemOrder_root;
private:
	CProjectLogHelper* m_pProjectLogHelper;

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_USER_ORDER_HH__



