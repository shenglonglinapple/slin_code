#include "ItemStockHistoryData.h"
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "ItemStockHistoryDataHelper.h"

#include "Log4cppLogger.h"

CItemStockHistoryData::CItemStockHistoryData()
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
	m_pItemUserInstrumentHelper = new CItemStockHistoryDataHelper();
	m_pItemUserInstrumentHelper->getLstClumnName(dataTreeItem);
	m_ItemData = dataTreeItem;

}



CItemStockHistoryData::CItemStockHistoryData(QList<QVariant>& ItemData, CItemStockHistoryData *parent)
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
	m_pItemUserInstrumentHelper = new CItemStockHistoryDataHelper();

}




CItemStockHistoryData::~CItemStockHistoryData()
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	m_pParentItem = NULL;
	m_ItemData.clear();

	CItemStockHistoryData* pItemTmp = NULL;
	QList<CItemStockHistoryData*>::iterator iterList;
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



CItemStockHistoryData *CItemStockHistoryData::child(int number)
{
    return m_LstChildItems.value(number);
}

int CItemStockHistoryData::childCount() const
{
    return m_LstChildItems.count();
}

int CItemStockHistoryData::childNumber() const
{
    if (m_pParentItem)
        return m_pParentItem->m_LstChildItems.indexOf(const_cast<CItemStockHistoryData*>(this));

    return 0;
}

int CItemStockHistoryData::columnCount() const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.count();
}

QVariant CItemStockHistoryData::data(int column) const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.value(column);
}

bool CItemStockHistoryData::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row) 
	{
        QList<QVariant> data;
		data.reserve(columns);
		CItemStockHistoryData *item = NULL;
        item = new CItemStockHistoryData(data, this);
        m_LstChildItems.insert(position, item);
    }

    return true;
}

bool CItemStockHistoryData::insertColumns(int position, int columns)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    if (position < 0 || position > m_ItemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
	{
        m_ItemData.insert(position, QVariant());
	}

    foreach (CItemStockHistoryData *child, m_LstChildItems)
	{
        child->insertColumns(position, columns);
	}

    return true;
}

CItemStockHistoryData *CItemStockHistoryData::parent()
{
    return m_pParentItem;
}

bool CItemStockHistoryData::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_LstChildItems.takeAt(position);

    return true;
}


bool CItemStockHistoryData::removeColumns(int position, int columns)
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

    foreach (CItemStockHistoryData *child, m_LstChildItems)
        child->removeColumns(position, columns);

    return true;
}


bool CItemStockHistoryData::setData(int column, const QVariant &value)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);
	
    if (column < 0 || column >= m_ItemData.size())
        return false;

    m_ItemData[column] = value;
    return true;
}

void CItemStockHistoryData::appendChild( CItemStockHistoryData** ppItem )
{
	CItemStockHistoryData* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;
	m_LstChildItems.push_back(pItem);
}

//////////////////////////////////////////////////////////////////////////
void CItemStockHistoryData::_ResetCurrentNodeData(CItemStockHistoryDataHelper* pItemDataHelper )
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

	m_ItemData.clear();
	pItemDataHelper->getItemNodeData(m_ItemData);
	m_strNodeKey = pItemDataHelper->m_strSymbolUse;
}
void CItemStockHistoryData::findAndResetSubNodeData( CItemStockHistoryDataHelper* pItemDataHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemStockHistoryData*>::iterator iterLst;
	CItemStockHistoryData* pSubNode = NULL;

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

void CItemStockHistoryData::appendChildByData(CItemStockHistoryDataHelper* pItemDataHelper)
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	CItemStockHistoryData* pNewNode = NULL;
	CItemStockHistoryData* pParentNode = this;
	QList<QVariant> ItemDataNULL;

	pNewNode = new CItemStockHistoryData(ItemDataNULL, pParentNode);
	pNewNode->_ResetCurrentNodeData(pItemDataHelper);

	pParentNode->appendChild(&pNewNode);
	pNewNode = NULL;
	pParentNode = NULL;
}

CItemStockHistoryData::EItemType CItemStockHistoryData::getItemType()
{
	return m_nItemType;
}

QString CItemStockHistoryData::getNodeKey()
{
	return m_strNodeKey;
}

void CItemStockHistoryData::removeChildByData( CItemStockHistoryDataHelper* pItemDataHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemStockHistoryData*>::iterator iterLst;
	CItemStockHistoryData* pSubNode = NULL;
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



