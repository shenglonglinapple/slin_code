#include "DataUserOrder.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "Instrument.h"
#include "ProjectLogHelper.h"
#include "Log4cppLogger.h"


#include "OrderInfoHelper.h"
#include "UserOrderInfo.h"
#include "ItemOrderInfo.h"


CDataUserOrder* CDataUserOrder::m_pInstance = 0;
QMutex CDataUserOrder::m_mutexInstance;

CDataUserOrder& CDataUserOrder::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataUserOrder();
	}
	return (*m_pInstance);
}

void CDataUserOrder::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataUserOrder::CDataUserOrder()
{
	m_pProjectLogHelper = NULL;
	m_pProjectLogHelper = new CProjectLogHelper();

	m_pOrderInfo = NULL;
	m_pTreeItemOrder_root = NULL;

	_InitMVCDataForOrder();

}

CDataUserOrder::~CDataUserOrder()
{
	_UnInitMVCDataForOrder();


	if (NULL != m_pProjectLogHelper)
	{
		delete m_pProjectLogHelper;
		m_pProjectLogHelper = NULL;
	}

}


void CDataUserOrder::_InitMVCDataForOrder()
{
	QMutexLocker lock(&m_mutexForMapOrder);	
	if (NULL != m_pTreeItemOrder_root)
	{
		delete m_pTreeItemOrder_root;
		m_pTreeItemOrder_root = NULL;
	}

	//root node save all column Names
	QList<QVariant> dataTreeItem;
	CTreeItemOrder::getLstClumnName(dataTreeItem);
	m_pTreeItemOrder_root = new CTreeItemOrder(dataTreeItem, NULL);
	m_pTreeItemOrder_root->setDataType(CTreeItemOrder::ItemDataType_ROOT);
	m_pTreeItemOrder_root->rootNodeSetColumnsName();

	m_pOrderInfo = new COrderInfo();

}
void CDataUserOrder::_UnInitMVCDataForOrder()
{
	QMutexLocker lock(&m_mutexForMapOrder);	

	if (NULL != m_pTreeItemOrder_root)
	{
		delete m_pTreeItemOrder_root;
		m_pTreeItemOrder_root = NULL;
	}

	if (NULL != m_pOrderInfo)
	{
		delete m_pOrderInfo;
		m_pOrderInfo = NULL;
	}

}


void CDataUserOrder::addAndUpdateData(const Order &order)
{
	QMap<unsigned int, Order*>::iterator iterMap;
	Order* pOrder = NULL;

	{
		QMutexLocker lock(&m_mutexForMapOrder);

		m_pOrderInfo->setValue(order);

		if (m_MapOrder.contains(order.getOrderID()))
		{
			iterMap = m_MapOrder.find(order.getOrderID());
			pOrder = iterMap.value();
			*pOrder = order;
			m_pTreeItemOrder_root->resetChildrenData(m_pOrderInfo);
		}
		else
		{
			pOrder = (Order*)&order;
			m_MapOrder.insert(order.getOrderID(), pOrder);
			m_pTreeItemOrder_root->appendChildByData(m_pOrderInfo);
		}
	}

}//update

CTreeItemOrder* CDataUserOrder::getRootHandle()
{
	QMutexLocker lock(&m_mutexForMapOrder);

	return m_pTreeItemOrder_root;
}






