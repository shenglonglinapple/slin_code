#include "ItemUserInstrument.h"
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "ItemUserInstrumentHelper.h"

//QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE





CItemUserInstrument::CItemUserInstrument()
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
	m_pItemUserInstrumentHelper = new CItemUserInstrumentHelper();
	m_pItemUserInstrumentHelper->getLstClumnName(dataTreeItem);
	m_ItemData = dataTreeItem;

}



CItemUserInstrument::CItemUserInstrument(QList<QVariant>& ItemData, CItemUserInstrument *parent)
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
	m_pItemUserInstrumentHelper = new CItemUserInstrumentHelper();

}




CItemUserInstrument::~CItemUserInstrument()
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	m_pParentItem = NULL;
	m_ItemData.clear();

	CItemUserInstrument* pItemTmp = NULL;
	QList<CItemUserInstrument*>::iterator iterList;
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



CItemUserInstrument *CItemUserInstrument::child(int number)
{
    return m_LstChildItems.value(number);
}

int CItemUserInstrument::childCount() const
{
    return m_LstChildItems.count();
}

int CItemUserInstrument::childNumber() const
{
    if (m_pParentItem)
        return m_pParentItem->m_LstChildItems.indexOf(const_cast<CItemUserInstrument*>(this));

    return 0;
}

int CItemUserInstrument::columnCount() const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.count();
}

QVariant CItemUserInstrument::data(int column) const
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    return m_ItemData.value(column);
}

bool CItemUserInstrument::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row) 
	{
        QList<QVariant> data;
		data.reserve(columns);
		CItemUserInstrument *item = NULL;
        item = new CItemUserInstrument(data, this);
        m_LstChildItems.insert(position, item);
    }

    return true;
}

bool CItemUserInstrument::insertColumns(int position, int columns)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

    if (position < 0 || position > m_ItemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
	{
        m_ItemData.insert(position, QVariant());
	}

    foreach (CItemUserInstrument *child, m_LstChildItems)
	{
        child->insertColumns(position, columns);
	}

    return true;
}

CItemUserInstrument *CItemUserInstrument::parent()
{
    return m_pParentItem;
}

bool CItemUserInstrument::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_LstChildItems.takeAt(position);

    return true;
}


bool CItemUserInstrument::removeColumns(int position, int columns)
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

    foreach (CItemUserInstrument *child, m_LstChildItems)
        child->removeColumns(position, columns);

    return true;
}


bool CItemUserInstrument::setData(int column, const QVariant &value)
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);
	
    if (column < 0 || column >= m_ItemData.size())
        return false;

    m_ItemData[column] = value;
    return true;
}

void CItemUserInstrument::appendChild( CItemUserInstrument** ppItem )
{
	CItemUserInstrument* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;
	m_LstChildItems.push_back(pItem);
}

//////////////////////////////////////////////////////////////////////////
void CItemUserInstrument::_ResetCurrentNodeData(CItemUserInstrumentHelper* pItemUserInstrumentHelper )
{
	QMutexLocker lock((QMutex*)&m_mutex_ItemData);

	m_ItemData.clear();
	pItemUserInstrumentHelper->getItemNodeData(m_ItemData);
	m_nNodeKey = pItemUserInstrumentHelper->getInstrumentID();
}
void CItemUserInstrument::findAndResetSubNodeData( CItemUserInstrumentHelper* pItemUserInstrumentHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemUserInstrument*>::iterator iterLst;
	CItemUserInstrument* pSubNode = NULL;

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pSubNode = NULL;
		pSubNode = (*iterLst);
		if (NULL != pSubNode && (pSubNode->getNodeKey() == pItemUserInstrumentHelper->getInstrumentID()))
		{
			pSubNode->_ResetCurrentNodeData(pItemUserInstrumentHelper);
			break;
		}
		iterLst++;
	}

}

void CItemUserInstrument::appendChildByData(CItemUserInstrumentHelper* pItemUserInstrumentHelper)
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	CItemUserInstrument* pNewNode = NULL;
	CItemUserInstrument* pParentNode = this;
	QList<QVariant> ItemDataNULL;

	pNewNode = new CItemUserInstrument(ItemDataNULL, pParentNode);
	pNewNode->_ResetCurrentNodeData(pItemUserInstrumentHelper);

	pParentNode->appendChild(&pNewNode);
	pNewNode = NULL;
	pParentNode = NULL;
}

CItemUserInstrument::EItemType CItemUserInstrument::getItemType()
{
	return m_nItemType;
}

unsigned int CItemUserInstrument::getNodeKey()
{
	return m_nNodeKey;
}

void CItemUserInstrument::removeChildByData( CItemUserInstrumentHelper* pItemUserInstrumentHelper )
{
	QMutexLocker lock(&m_mutex_LstChildItems);

	QList<CItemUserInstrument*>::iterator iterLst;
	CItemUserInstrument* pSubNode = NULL;
	int nIndex = 0;

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pSubNode = NULL;
		pSubNode = (*iterLst);
		if (NULL != pSubNode && (pSubNode->getNodeKey() == pItemUserInstrumentHelper->getInstrumentID()))
		{
			this->removeChildren(nIndex, 1);
			break;
		}
		iterLst++;
		nIndex++;
	}
}



