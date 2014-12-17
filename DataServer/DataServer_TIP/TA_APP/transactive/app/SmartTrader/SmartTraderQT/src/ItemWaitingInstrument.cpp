#include "ItemWaitingInstrument.h"
#include "ItemWaitingInstrumentHelper.h"

#include "Log4cppLogger.h"


CItemWaitingInstrument::CItemWaitingInstrument()
{
	QList<QVariant> dataTreeItem;

	//clear
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();
	m_nItemType = ItemType_ROOT;
	m_pItemWaitingInstrumentHelper = NULL;

	//set value
	m_pParentItem = NULL;
	m_nItemType = ItemType_ROOT;
	m_pItemWaitingInstrumentHelper = new CItemWaitingInstrumentHelper();
	m_pItemWaitingInstrumentHelper->getLstClumnName(dataTreeItem);
	m_ItemData = dataTreeItem;

}



CItemWaitingInstrument::CItemWaitingInstrument(QList<QVariant>& ItemData, CItemWaitingInstrument *parent)
{
	//clear
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();
	m_nItemType = ItemType_ITEM1_ExchangeName;
	m_pItemWaitingInstrumentHelper = NULL;

	//set value
	m_pParentItem = parent;
	m_ItemData = ItemData;
	m_nItemType = ItemType_ITEM1_ExchangeName;
	m_pItemWaitingInstrumentHelper = new CItemWaitingInstrumentHelper();

}




CItemWaitingInstrument::~CItemWaitingInstrument()
{
	m_pParentItem = NULL;
	m_ItemData.clear();

	CItemWaitingInstrument* pItemTmp = NULL;
	QList<CItemWaitingInstrument*>::iterator iterList;
	iterList = m_LstChildItems.begin();
	while (iterList != m_LstChildItems.end())
	{
		pItemTmp = *iterList;

		delete pItemTmp;
		pItemTmp = NULL;

		iterList++;
	}//while

    //qDeleteAll(childItems);

	if (NULL != m_pItemWaitingInstrumentHelper)
	{
		delete m_pItemWaitingInstrumentHelper;
		m_pItemWaitingInstrumentHelper = NULL;
	}
}



CItemWaitingInstrument *CItemWaitingInstrument::child(int number)
{
    return m_LstChildItems.value(number);
}

int CItemWaitingInstrument::childCount() const
{
    return m_LstChildItems.count();
}

int CItemWaitingInstrument::childNumber() const
{
    if (m_pParentItem)
        return m_pParentItem->m_LstChildItems.indexOf(const_cast<CItemWaitingInstrument*>(this));

    return 0;
}

int CItemWaitingInstrument::columnCount() const
{
    return m_ItemData.count();
}

QVariant CItemWaitingInstrument::data(int column) const
{
    return m_ItemData.value(column);
}

bool CItemWaitingInstrument::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row) 
	{
        QList<QVariant> data;
		data.reserve(columns);
		CItemWaitingInstrument *item = NULL;
        item = new CItemWaitingInstrument(data, this);
        m_LstChildItems.insert(position, item);
    }

    return true;
}

bool CItemWaitingInstrument::insertColumns(int position, int columns)
{
    if (position < 0 || position > m_ItemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        m_ItemData.insert(position, QVariant());

    foreach (CItemWaitingInstrument *child, m_LstChildItems)
        child->insertColumns(position, columns);

    return true;
}

CItemWaitingInstrument *CItemWaitingInstrument::parent()
{
    return m_pParentItem;
}

bool CItemWaitingInstrument::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_LstChildItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_LstChildItems.takeAt(position);

    return true;
}


bool CItemWaitingInstrument::removeColumns(int position, int columns)
{
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

    foreach (CItemWaitingInstrument *child, m_LstChildItems)
        child->removeColumns(position, columns);

    return true;
}


bool CItemWaitingInstrument::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= m_ItemData.size())
        return false;

    m_ItemData[column] = value;
    return true;
}

void CItemWaitingInstrument::appendChild( CItemWaitingInstrument** ppItem )
{
	CItemWaitingInstrument* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;
	m_LstChildItems.push_back(pItem);
}

//////////////////////////////////////////////////////////////////////////
void CItemWaitingInstrument::resetCurrentNodeData(CItemWaitingInstrumentHelper* pHelper )
{
	m_ItemData.clear();
	m_nNodeKey = pHelper->m_nInstrumentID;

	if (ItemType_ITEM1_ExchangeName == m_nItemType)
	{
		pHelper->getItemNodeData(m_ItemData, ItemType_ITEM1_ExchangeName);
		return;
	}

	if (ItemType_ITEM2_UnderlyingCode == m_nItemType)
	{
		pHelper->getItemNodeData(m_ItemData, ItemType_ITEM2_UnderlyingCode);
		return;
	}

	if (ItemType_ITEM3_InstrumentCode == m_nItemType)
	{
		pHelper->getItemNodeData(m_ItemData, ItemType_ITEM3_InstrumentCode);
		return;
	}
}

void CItemWaitingInstrument::appendChildByData(CItemWaitingInstrumentHelper* pHelper)
{
	CItemWaitingInstrument* pNewNode = NULL;
	QList<QVariant> ItemDataNULL;

	if (ItemType_ROOT == m_nItemType)
	{
		pNewNode = new CItemWaitingInstrument(ItemDataNULL, this);
		pNewNode->setItemType(ItemType_ITEM1_ExchangeName);
		pNewNode->resetCurrentNodeData(pHelper);	
		this->appendChild(&pNewNode);
		pNewNode->appendChildByData(pHelper);
		MYLOG4CPP_DEBUG<<"ItemType_ROOT appendChild"
			<<" "<<"m_strExchangeName="<<pHelper->m_strExchangeName.toStdString();
	}

	if (ItemType_ITEM1_ExchangeName == m_nItemType)
	{
		pNewNode = new CItemWaitingInstrument(ItemDataNULL, this);
		pNewNode->setItemType(ItemType_ITEM2_UnderlyingCode);
		pNewNode->resetCurrentNodeData(pHelper);	
		this->appendChild(&pNewNode);
		pNewNode->appendChildByData(pHelper);
		MYLOG4CPP_DEBUG<<"ItemType_ITEM1_ExchangeName appendChild"
			<<" "<<"m_strUnderlyingCode="<<pHelper->m_strUnderlyingCode.toStdString();

	}

	if (ItemType_ITEM2_UnderlyingCode == m_nItemType)
	{
		pNewNode = new CItemWaitingInstrument(ItemDataNULL, this);
		pNewNode->setItemType(ItemType_ITEM3_InstrumentCode);
		pNewNode->resetCurrentNodeData(pHelper);	
		this->appendChild(&pNewNode);
		MYLOG4CPP_DEBUG<<"ItemType_ITEM2_UnderlyingCode appendChild"
			<<" "<<"m_strInstrumentCode="<<pHelper->m_strInstrumentCode.toStdString();

	}
	pNewNode = NULL;
}


void CItemWaitingInstrument::AnalysisAndAppendChild( CItemWaitingInstrumentHelper* pHelper)
{
	int nChildCount = 0;
	int nChildIndex = 0;
	CItemWaitingInstrument* pData = NULL;
	bool bFind = false;
	QString strAnalysisKey;

	pData = NULL;
	bFind = false;
	if (ItemType_ROOT == m_nItemType)
	{
		strAnalysisKey = pHelper->m_strExchangeName;
	}
	else if (ItemType_ITEM1_ExchangeName == m_nItemType)
	{
		strAnalysisKey = pHelper->m_strUnderlyingCode;
	}
	else if (ItemType_ITEM2_UnderlyingCode == m_nItemType)
	{
		strAnalysisKey = pHelper->m_strInstrumentCode;
	}


	{
		nChildCount = this->childCount();
		for (nChildIndex = 0; nChildIndex < nChildCount; nChildIndex++)
		{
			pData = NULL;
			pData = this->child(nChildIndex);
			if (pData->data(0).toString() == strAnalysisKey)
			{
				if (ItemType_ITEM2_UnderlyingCode == m_nItemType)
				{
					bFind = true;//instrumentCode
				}
				else
				{
					pData->AnalysisAndAppendChild(pHelper);
					bFind = true;
				}
				return;
			}
		}
	}


	if (false == bFind)
	{
		this->appendChildByData(pHelper);
	}


}


void CItemWaitingInstrument::AnalysisAndRemoveChild(CItemWaitingInstrumentHelper* pHelper)
{
	int nChildCount = 0;
	int nChildIndex = 0;
	CItemWaitingInstrument* pData = NULL;
	bool bFind = false;
	QString strAnalysisKey;


	pData = NULL;
	bFind = false;
	if (ItemType_ROOT == m_nItemType)
	{
		strAnalysisKey = pHelper->m_strExchangeName;
	}
	else if (ItemType_ITEM1_ExchangeName == m_nItemType)
	{
		strAnalysisKey = pHelper->m_strUnderlyingCode;
	}
	else if (ItemType_ITEM2_UnderlyingCode == m_nItemType)
	{
		strAnalysisKey = pHelper->m_strInstrumentCode;
	}


	{
		nChildCount = this->childCount();
		for (nChildIndex = 0; nChildIndex < nChildCount; nChildIndex++)
		{
			pData = NULL;
			pData = this->child(nChildIndex);
			if (pData->data(0).toString() == strAnalysisKey)
			{
				if (ItemType_ITEM2_UnderlyingCode == m_nItemType)
				{
					pData->removeChildren(nChildIndex, 1);
					bFind = true;
				}
				else
				{
					pData->AnalysisAndRemoveChild(pHelper);
					bFind = true;
				}

				return;
			}
		}
	}



}


CItemWaitingInstrument::EItemType CItemWaitingInstrument::getItemType()
{
	return m_nItemType;
}

unsigned int CItemWaitingInstrument::getNodeKey()
{
	return m_nNodeKey;
}

void CItemWaitingInstrument::setItemType( EItemType nType )
{
	m_nItemType = nType;
}



