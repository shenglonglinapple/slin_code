#include "ItemWaitingInstrument.h"
#include "ItemWaitingInstrumentHelper.h"

#include "Log4cppLogger.h"


CItemWaitingInstrument::CItemWaitingInstrument()
{
	QList<QVariant> dataTreeItem;

	//clear
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_nItemType = ItemType_ROOT;
	m_pItemWaitingInstrumentHelper = NULL;
	_FreeMap();

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
	m_nItemType = ItemType_ITEM1_ExchangeName;
	m_pItemWaitingInstrumentHelper = NULL;
	_FreeMap();

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
	_FreeMap();

    //qDeleteAll(childItems);

	if (NULL != m_pItemWaitingInstrumentHelper)
	{
		delete m_pItemWaitingInstrumentHelper;
		m_pItemWaitingInstrumentHelper = NULL;
	}
}

void CItemWaitingInstrument::_FreeMap()
{
	QMap<QString, CItemWaitingInstrument*>::iterator iterMap;
	CItemWaitingInstrument* pTreeItem = NULL;

	iterMap = m_MapChildItems.begin();
	while (iterMap != m_MapChildItems.end())
	{
		pTreeItem = iterMap.value();

		if (NULL != pTreeItem)
		{
			delete pTreeItem;
			pTreeItem = NULL;
		}

		iterMap++;
	}
	m_MapChildItems.clear();
}

CItemWaitingInstrument *CItemWaitingInstrument::child(int number)//row
{
	int nIndex = 0;
	CItemWaitingInstrument* pTreeItem = NULL;
	QMap<QString, CItemWaitingInstrument*>::iterator iterMap;

	iterMap = m_MapChildItems.begin();
	nIndex = 0;
	while (iterMap != m_MapChildItems.end())
	{
		if (nIndex == number)
		{
			pTreeItem = iterMap.value();
			break;
		}
		nIndex++;
		iterMap++;
	}

	return pTreeItem;
}

int CItemWaitingInstrument::childCount() const
{
    return m_MapChildItems.count();
}

int CItemWaitingInstrument::childNumber() const
{
	int nIndex = 0;

	if (NULL != m_pParentItem)
	{
		//nIndex = m_pParentItem->m_LstChildItems.indexOf(const_cast<TreeItem*>(this));
		nIndex = m_pParentItem->indexOfChildren(const_cast<CItemWaitingInstrument*>(this));
		return nIndex;
	}

	return nIndex;
}

int CItemWaitingInstrument::indexOfChildren(CItemWaitingInstrument* pChildrenItem) const
{
	int nIndex = 0;
	CItemWaitingInstrument* pTreeItemTmp = NULL;
	QMap<QString,CItemWaitingInstrument*>::const_iterator iterMap;

	iterMap = m_MapChildItems.constBegin();
	nIndex = 0;
	while (iterMap != m_MapChildItems.constEnd())
	{
		pTreeItemTmp = iterMap.value();

		if (pChildrenItem == pTreeItemTmp)
		{
			break;
		}
		nIndex++;
		iterMap++;
	}

	return nIndex;
}



int CItemWaitingInstrument::columnCount() const
{
    return m_ItemData.count();
}

QVariant CItemWaitingInstrument::data(int column) const
{
    return m_ItemData.value(column);
}



CItemWaitingInstrument *CItemWaitingInstrument::parent()
{
    return m_pParentItem;
}

bool CItemWaitingInstrument::removeChildren(int position, int count)
{
	int nIndex = 0;
	CItemWaitingInstrument* pTreeItemTmp = NULL;
	QMap<QString,CItemWaitingInstrument*>::iterator iterMap;

	if (position < 0 || position > m_MapChildItems.size())
	{
		// 		MYLOG4CPP_ERROR<<"removeChildren() error!"
		// 			<<" "<<"position="<<position
		// 			<<" "<<"m_MapChildItems.size()="<<m_MapChildItems.size();

		return false;
	}

	nIndex = 0;
	iterMap = m_MapChildItems.begin();
	while (iterMap != m_MapChildItems.end())
	{
		if (nIndex == position)
		{
			pTreeItemTmp = iterMap.value();

			delete pTreeItemTmp;
			pTreeItemTmp = NULL;

			m_MapChildItems.erase(iterMap);
			break;
		}//if (nIndex == position)

		nIndex++;
		iterMap++;
	}//while

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
	QString strMapKey;

	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;
	strMapKey = pItem->data(0).toString();


	if (m_MapChildItems.contains(strMapKey))
	{
		delete pItem;
		pItem = NULL;
	}
	else
	{
		m_MapChildItems.insert(strMapKey, pItem);
	}
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
		/*MYLOG4CPP_DEBUG<<"ItemType_ITEM2_UnderlyingCode appendChild"
			<<" "<<"m_strInstrumentCode="<<pHelper->m_strInstrumentCode.toStdString();*/

	}
	pNewNode = NULL;
}


void CItemWaitingInstrument::AnalysisAndAppendChild( CItemWaitingInstrumentHelper* pHelper)
{
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
		QMap<QString, CItemWaitingInstrument*>::iterator iterFind;
		iterFind = this->m_MapChildItems.find(strAnalysisKey);
		if (iterFind != this->m_MapChildItems.end())
		{
			//find ok
			if (ItemType_ITEM2_UnderlyingCode == m_nItemType)
			{
				bFind = true;//instrumentCode
			}
			else
			{
				pData = iterFind.value();
				pData->AnalysisAndAppendChild(pHelper);
				bFind = true;
			}
		}
		else
		{
			//not find
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
		QMap<QString, CItemWaitingInstrument*>::iterator iterFind;
		iterFind = this->m_MapChildItems.find(strAnalysisKey);
		if (iterFind != this->m_MapChildItems.end())
		{
			//find ok
			if (ItemType_ITEM2_UnderlyingCode == m_nItemType)
			{
				this->removeChildren(nChildIndex, 1);
				bFind = true;
			}
			else
			{
				pData = iterFind.value();
				pData->AnalysisAndRemoveChild(pHelper);
				bFind = true;
			}
		}
		else
		{
			//not find
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



