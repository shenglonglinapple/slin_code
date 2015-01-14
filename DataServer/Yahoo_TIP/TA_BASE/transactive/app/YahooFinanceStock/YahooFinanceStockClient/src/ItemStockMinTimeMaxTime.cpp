#include "ItemStockMinTimeMaxTime.h"
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "ItemStockMinTimeMaxTimeHelper.h"

#include "Log4cppLogger.h"

CItemStockMinTimeMaxTime::CItemStockMinTimeMaxTime()
{
	QList<QVariant> dataTreeItem;

	//clear
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();
	m_nItemType = ItemType_ROOT;
	m_pItemUserInstrumentHelper = NULL;

	//set value
	m_pParentItem = NULL;
	m_nItemType = ItemType_ROOT;
	m_pItemUserInstrumentHelper = new CItemStockMinTimeMaxTimeHelper();
	m_pItemUserInstrumentHelper->getLstClumnName(dataTreeItem);
	m_ItemData = dataTreeItem;

}



CItemStockMinTimeMaxTime::CItemStockMinTimeMaxTime(QList<QVariant>& ItemData, CItemStockMinTimeMaxTime *parent)
{
	//clear
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();
	m_nItemType = ItemType_ITEM;
	m_pItemUserInstrumentHelper = NULL;


	//set value
	m_pParentItem = parent;
	m_ItemData = ItemData;
	m_nItemType = ItemType_ITEM;
	m_pItemUserInstrumentHelper = new CItemStockMinTimeMaxTimeHelper();

}




CItemStockMinTimeMaxTime::~CItemStockMinTimeMaxTime()
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	m_pParentItem = NULL;
	m_ItemData.clear();

	CItemStockMinTimeMaxTime* pItemTmp = NULL;
	QList<CItemStockMinTimeMaxTime*>::iterator iterList;
	iterList = m_LstChildItems.begin();
	while (iterList != m_LstChildItems.end())
	{
		pItemTmp = *iterList;

		delete pItemTmp;
		pItemTmp = NULL;

		iterList++;
	}//while

    //qDeleteAll(childItems);

	if (NULL != m_pItemUserInstrumentHelper)
	{
		delete m_pItemUserInstrumentHelper;
		m_pItemUserInstrumentHelper = NULL;
	}
}



CItemStockMinTimeMaxTime *CItemStockMinTimeMaxTime::child(int number)
{
    return m_LstChildItems.value(number);
}

int CItemStockMinTimeMaxTime::childCount() const
{
    return m_LstChildItems.count();
}

int CItemStockMinTimeMaxTime::childNumber() const
{
    if (m_pParentItem)
        return m_pParentItem->m_LstChildItems.indexOf(const_cast<CItemStockMinTimeMaxTime*>(this));

    return 0;
}

int CItemStockMinTimeMaxTime::columnCount() const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.count();
}

QVariant CItemStockMinTimeMaxTime::data(int column) const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.value(column);
}

bool CItemStockMinTimeMaxTime::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row) 
	{
        QList<QVariant> data;
		data.reserve(columns);
		CItemStockMinTimeMaxTime *item = NULL;
        item = new CItemStockMinTimeMaxTime(data, this);
        m_LstChildItems.insert(position, item);
    }

    return true;
}

bool CItemStockMinTimeMaxTime::insertColumns(int position, int columns)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    if (position < 0 || position > m_ItemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
	{
        m_ItemData.insert(position, QVariant());
	}

    foreach (CItemStockMinTimeMaxTime *child, m_LstChildItems)
	{
        child->insertColumns(position, columns);
	}

    return true;
}

CItemStockMinTimeMaxTime *CItemStockMinTimeMaxTime::parent()
{
    return m_pParentItem;
}

bool CItemStockMinTimeMaxTime::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_LstChildItems.takeAt(position);

    return true;
}


bool CItemStockMinTimeMaxTime::removeColumns(int position, int columns)
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

    foreach (CItemStockMinTimeMaxTime *child, m_LstChildItems)
        child->removeColumns(position, columns);

    return true;
}


bool CItemStockMinTimeMaxTime::setData(int column, const QVariant &value)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);
	
    if (column < 0 || column >= m_ItemData.size())
        return false;

    m_ItemData[column] = value;
    return true;
}

void CItemStockMinTimeMaxTime::appendChild( CItemStockMinTimeMaxTime** ppItem )
{
	CItemStockMinTimeMaxTime* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;
	m_LstChildItems.push_back(pItem);
}

//////////////////////////////////////////////////////////////////////////
void CItemStockMinTimeMaxTime::_ResetCurrentNodeData(CItemStockMinTimeMaxTimeHelper* pItemUserInstrumentHelper )
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

	m_ItemData.clear();
	pItemUserInstrumentHelper->getItemNodeData(m_ItemData);
	m_strNodeKey = pItemUserInstrumentHelper->m_strSymbolUse;
}
void CItemStockMinTimeMaxTime::findAndResetSubNodeData( CItemStockMinTimeMaxTimeHelper* pItemDataHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemStockMinTimeMaxTime*>::iterator iterLst;
	CItemStockMinTimeMaxTime* pSubNode = NULL;

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pSubNode = NULL;
		pSubNode = (*iterLst);
		if (NULL != pSubNode && (pSubNode->getNodeKey() == pItemDataHelper->m_strSymbolUse))
		{
			pSubNode->_ResetCurrentNodeData(pItemDataHelper);
			break;
		}
		iterLst++;
	}

}

void CItemStockMinTimeMaxTime::appendChildByData(CItemStockMinTimeMaxTimeHelper* pItemDataHelper)
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	CItemStockMinTimeMaxTime* pNewNode = NULL;
	CItemStockMinTimeMaxTime* pParentNode = this;
	QList<QVariant> ItemDataNULL;

	pNewNode = new CItemStockMinTimeMaxTime(ItemDataNULL, pParentNode);
	pNewNode->_ResetCurrentNodeData(pItemDataHelper);

	pParentNode->appendChild(&pNewNode);
	pNewNode = NULL;
	pParentNode = NULL;
}

CItemStockMinTimeMaxTime::EItemType CItemStockMinTimeMaxTime::getItemType()
{
	return m_nItemType;
}

QString CItemStockMinTimeMaxTime::getNodeKey()
{
	return m_strNodeKey;
}

void CItemStockMinTimeMaxTime::removeChildByData( CItemStockMinTimeMaxTimeHelper* pItemDataHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemStockMinTimeMaxTime*>::iterator iterLst;
	CItemStockMinTimeMaxTime* pSubNode = NULL;
	int nIndex = 0;

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pSubNode = NULL;
		pSubNode = (*iterLst);
		if (NULL != pSubNode && (pSubNode->getNodeKey() == pItemDataHelper->m_strSymbolUse))
		{
			this->removeChildren(nIndex, 1);
			break;
		}
		iterLst++;
		nIndex++;
	}
}



