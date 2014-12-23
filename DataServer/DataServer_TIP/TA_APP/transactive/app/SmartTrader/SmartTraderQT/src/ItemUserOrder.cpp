#include "ItemUserOrder.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "OrderData.h"
#include "ItemUserOrderHelper.h"

#include "Log4cppLogger.h"

//QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE





CItemUserOrder::CItemUserOrder()
{
	QList<QVariant> dataTreeItem;

	//clear
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();
	m_nItemType = ItemType_ROOT;
	m_pDataHelper = NULL;

	//set value
	m_pParentItem = NULL;
	m_nItemType = ItemType_ROOT;
	m_pDataHelper = new CItemUserOrderHelper();
	m_pDataHelper->getLstClumnName(dataTreeItem);
	m_ItemData = dataTreeItem;

}



CItemUserOrder::CItemUserOrder(QList<QVariant>& ItemData, CItemUserOrder *parent)
{
	//clear
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();
	m_nItemType = ItemType_ITEM;
	m_pDataHelper = NULL;


	//set value
	m_pParentItem = parent;
	m_ItemData = ItemData;
	m_nItemType = ItemType_ITEM;
	m_pDataHelper = new CItemUserOrderHelper();

}




CItemUserOrder::~CItemUserOrder()
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	m_pParentItem = NULL;
	m_ItemData.clear();

	CItemUserOrder* pItemTmp = NULL;
	QList<CItemUserOrder*>::iterator iterList;
	iterList = m_LstChildItems.begin();
	while (iterList != m_LstChildItems.end())
	{
		pItemTmp = *iterList;

		delete pItemTmp;
		pItemTmp = NULL;

		iterList++;
	}//while

    //qDeleteAll(childItems);

	if (NULL != m_pDataHelper)
	{
		delete m_pDataHelper;
		m_pDataHelper = NULL;
	}
}



CItemUserOrder *CItemUserOrder::child(int number)
{
    return m_LstChildItems.value(number);
}

int CItemUserOrder::childCount() const
{
    return m_LstChildItems.count();
}

int CItemUserOrder::childNumber() const
{
    if (m_pParentItem)
        return m_pParentItem->m_LstChildItems.indexOf(const_cast<CItemUserOrder*>(this));

    return 0;
}

int CItemUserOrder::columnCount() const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.count();
}

QVariant CItemUserOrder::data(int column) const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.value(column);
}

bool CItemUserOrder::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row) 
	{
        QList<QVariant> data;
		data.reserve(columns);
		CItemUserOrder *item = NULL;
        item = new CItemUserOrder(data, this);
        m_LstChildItems.insert(position, item);
    }

    return true;
}

bool CItemUserOrder::insertColumns(int position, int columns)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    if (position < 0 || position > m_ItemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
	{
        m_ItemData.insert(position, QVariant());
	}

    foreach (CItemUserOrder *child, m_LstChildItems)
	{
        child->insertColumns(position, columns);
	}

    return true;
}

CItemUserOrder *CItemUserOrder::parent()
{
    return m_pParentItem;
}

bool CItemUserOrder::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_LstChildItems.takeAt(position);

    return true;
}


bool CItemUserOrder::removeColumns(int position, int columns)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

	QList<QVariant>::Iterator iterList;

    if (position < 0 || position + columns > m_ItemData.size())
	{
        return false;
	}

    for (int column = 0; column < columns; ++column)
	{
		//itemData.remove(position);

		iterList = m_ItemData.begin();
		iterList += position;
		m_ItemData.erase(iterList);
	}

    foreach (CItemUserOrder *child, m_LstChildItems)
        child->removeColumns(position, columns);

    return true;
}


bool CItemUserOrder::setData(int column, const QVariant &value)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);
	
    if (column < 0 || column >= m_ItemData.size())
        return false;

    m_ItemData[column] = value;
    return true;
}

void CItemUserOrder::appendChild( CItemUserOrder** ppItem )
{
	CItemUserOrder* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;
	m_LstChildItems.push_back(pItem);
}

//////////////////////////////////////////////////////////////////////////
void CItemUserOrder::_ResetCurrentNodeData(CItemUserOrderHelper* pDataHelper )
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

	m_ItemData.clear();
	pDataHelper->getItemNodeData(m_ItemData);
	m_nNodeKey = pDataHelper->getInstrumentID();
}
void CItemUserOrder::findAndResetSubNodeData( CItemUserOrderHelper* pDataHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemUserOrder*>::iterator iterLst;
	CItemUserOrder* pSubNode = NULL;

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pSubNode = NULL;
		pSubNode = (*iterLst);
		if (NULL != pSubNode && (pSubNode->getNodeKey() == pDataHelper->getInstrumentID()))
		{
			pSubNode->_ResetCurrentNodeData(pDataHelper);
			break;
		}
		iterLst++;
	}

}

void CItemUserOrder::appendChildByData(CItemUserOrderHelper* pDataHelper)
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	CItemUserOrder* pNewNode = NULL;
	CItemUserOrder* pParentNode = this;
	QList<QVariant> ItemDataNULL;

	pNewNode = new CItemUserOrder(ItemDataNULL, pParentNode);
	pNewNode->_ResetCurrentNodeData(pDataHelper);

	pParentNode->appendChild(&pNewNode);
	pNewNode = NULL;
	pParentNode = NULL;
}

CItemUserOrder::EItemType CItemUserOrder::getItemType()
{
	return m_nItemType;
}

unsigned int CItemUserOrder::getNodeKey()
{
	return m_nNodeKey;
}

void CItemUserOrder::removeChildByData( CItemUserOrderHelper* pDataHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemUserOrder*>::iterator iterLst;
	CItemUserOrder* pSubNode = NULL;
	int nIndex = 0;

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pSubNode = NULL;
		pSubNode = (*iterLst);
		if (NULL != pSubNode && (pSubNode->getNodeKey() == pDataHelper->getInstrumentID()))
		{
			this->removeChildren(nIndex, 1);
			break;
		}
		iterLst++;
		nIndex++;
	}
}



