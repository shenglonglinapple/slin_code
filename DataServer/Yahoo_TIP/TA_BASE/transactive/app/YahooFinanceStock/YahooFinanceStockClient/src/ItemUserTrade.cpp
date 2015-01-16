#include "ItemUserTrade.h"
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "ItemUserTradeHelper.h"

#include "Log4cppLogger.h"

CItemUserTrade::CItemUserTrade()
{
	QList<QVariant> dataTreeItem;

	//clear
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();
	m_nItemType = ItemType_ROOT;
	m_pItemHelper = NULL;

	//set value
	m_pParentItem = NULL;
	m_nItemType = ItemType_ROOT;
	m_pItemHelper = new CItemUserTradeHelper();
	m_pItemHelper->getLstClumnName(dataTreeItem);
	m_ItemData = dataTreeItem;

}



CItemUserTrade::CItemUserTrade(QList<QVariant>& ItemData, CItemUserTrade *parent)
{
	//clear
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();
	m_nItemType = ItemType_ITEM;
	m_pItemHelper = NULL;


	//set value
	m_pParentItem = parent;
	m_ItemData = ItemData;
	m_nItemType = ItemType_ITEM;
	m_pItemHelper = new CItemUserTradeHelper();

}




CItemUserTrade::~CItemUserTrade()
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	m_pParentItem = NULL;
	m_ItemData.clear();

	CItemUserTrade* pItemTmp = NULL;
	QList<CItemUserTrade*>::iterator iterList;
	iterList = m_LstChildItems.begin();
	while (iterList != m_LstChildItems.end())
	{
		pItemTmp = *iterList;

		delete pItemTmp;
		pItemTmp = NULL;

		iterList++;
	}//while

    //qDeleteAll(childItems);

	if (NULL != m_pItemHelper)
	{
		delete m_pItemHelper;
		m_pItemHelper = NULL;
	}
}



CItemUserTrade *CItemUserTrade::child(int number)
{
    return m_LstChildItems.value(number);
}

int CItemUserTrade::childCount() const
{
    return m_LstChildItems.count();
}

int CItemUserTrade::childNumber() const
{
    if (m_pParentItem)
        return m_pParentItem->m_LstChildItems.indexOf(const_cast<CItemUserTrade*>(this));

    return 0;
}

int CItemUserTrade::columnCount() const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.count();
}

QVariant CItemUserTrade::data(int column) const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.value(column);
}

bool CItemUserTrade::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row) 
	{
        QList<QVariant> data;
		data.reserve(columns);
		CItemUserTrade *item = NULL;
        item = new CItemUserTrade(data, this);
        m_LstChildItems.insert(position, item);
    }

    return true;
}

bool CItemUserTrade::insertColumns(int position, int columns)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    if (position < 0 || position > m_ItemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
	{
        m_ItemData.insert(position, QVariant());
	}

    foreach (CItemUserTrade *child, m_LstChildItems)
	{
        child->insertColumns(position, columns);
	}

    return true;
}

CItemUserTrade *CItemUserTrade::parent()
{
    return m_pParentItem;
}

bool CItemUserTrade::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_LstChildItems.takeAt(position);

    return true;
}


bool CItemUserTrade::removeColumns(int position, int columns)
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

    foreach (CItemUserTrade *child, m_LstChildItems)
        child->removeColumns(position, columns);

    return true;
}


bool CItemUserTrade::setData(int column, const QVariant &value)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);
	
    if (column < 0 || column >= m_ItemData.size())
        return false;

    m_ItemData[column] = value;
    return true;
}

void CItemUserTrade::appendChild( CItemUserTrade** ppItem )
{
	CItemUserTrade* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;
	m_LstChildItems.push_back(pItem);
}

//////////////////////////////////////////////////////////////////////////
void CItemUserTrade::_ResetCurrentNodeData(CItemUserTradeHelper* pItemDataHelper )
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

	m_ItemData.clear();
	pItemDataHelper->getItemNodeData(m_ItemData);
	m_strNodeKey = pItemDataHelper->m_strSymbolUse;
}
void CItemUserTrade::findAndResetSubNodeData( CItemUserTradeHelper* pItemDataHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemUserTrade*>::iterator iterLst;
	CItemUserTrade* pSubNode = NULL;

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

void CItemUserTrade::appendChildByData(CItemUserTradeHelper* pItemDataHelper)
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	CItemUserTrade* pNewNode = NULL;
	CItemUserTrade* pParentNode = this;
	QList<QVariant> ItemDataNULL;

	pNewNode = new CItemUserTrade(ItemDataNULL, pParentNode);
	pNewNode->_ResetCurrentNodeData(pItemDataHelper);

	pParentNode->appendChild(&pNewNode);
	pNewNode = NULL;
	pParentNode = NULL;
}

CItemUserTrade::EItemType CItemUserTrade::getItemType()
{
	return m_nItemType;
}

QString CItemUserTrade::getNodeKey()
{
	return m_strNodeKey;
}

void CItemUserTrade::removeChildByData( CItemUserTradeHelper* pItemDataHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemUserTrade*>::iterator iterLst;
	CItemUserTrade* pSubNode = NULL;
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



