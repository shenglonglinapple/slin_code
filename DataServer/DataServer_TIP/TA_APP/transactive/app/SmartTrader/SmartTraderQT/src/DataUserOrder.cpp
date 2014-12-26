#include "DataUserOrder.h"

#include "ItemUserOrder.h"
#include "ItemUserOrderHelper.h"
//
#include "Log4cppLogger.h"



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

CDataUserOrder::CDataUserOrder(void)
{	
	QMutexLocker lock(&m_mutex_ItemUserInstrument_Root);	
	m_pItemUserOrder_Root = NULL;
	m_pItemUserOrder_Root = new CItemUserOrder();
	m_pItemUserOrdertHelper = NULL;
	m_pItemUserOrdertHelper = new CItemUserOrderHelper();
}

CDataUserOrder::~CDataUserOrder(void)
{		
	QMutexLocker lock(&m_mutex_ItemUserInstrument_Root);
	if (NULL != m_pItemUserOrder_Root)
	{
		delete m_pItemUserOrder_Root;
		m_pItemUserOrder_Root = NULL;
	}
	if (NULL != m_pItemUserOrdertHelper)
	{
		delete m_pItemUserOrdertHelper;
		m_pItemUserOrdertHelper = NULL;
	}
}

CItemUserOrder* CDataUserOrder::getRootItem()
{
	QMutexLocker lock(&m_mutex_ItemUserInstrument_Root);
	return m_pItemUserOrder_Root;
}

void CDataUserOrder::addOrUpdate( const COrderData& order )
{
	m_pItemUserOrdertHelper->setData(order);
	m_pItemUserOrder_Root->addOrUpdateSubNode(m_pItemUserOrdertHelper);

}
