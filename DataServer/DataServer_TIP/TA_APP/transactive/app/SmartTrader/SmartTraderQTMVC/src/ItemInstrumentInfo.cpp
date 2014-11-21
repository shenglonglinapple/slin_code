#include "ItemInstrumentInfo.h"


//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QObject>


#include "InstrumentInfoHelper.h"

//#include "Log4cppLogger.h"
//

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


CItemInstrumentInfo::CItemInstrumentInfo(const QList<QVariant> &data, CItemInstrumentInfo *parent /*= 0*/ )
{
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_MapStringChildren.clear();

	m_pParentItem = parent;
	m_ItemData = data;
	m_nDataTypeExchange = CItemInstrumentInfo::DataTypeContract_InstrumentCode;
	m_nInstrumentID = 0;
}

CItemInstrumentInfo::CItemInstrumentInfo()
{
	QList<QVariant> dataTmp;
	CItemInstrumentInfo* parent = NULL;
	QString strTmp = "NULL";
	dataTmp.push_back(strTmp);
	parent = NULL;

	m_pParentItem = NULL;
	m_ItemData.clear();
	m_MapStringChildren.clear();

	m_pParentItem = parent;
	m_ItemData = dataTmp;
	m_nDataTypeExchange = CItemInstrumentInfo::DataTypeContract_InstrumentCode;

}


CItemInstrumentInfo::~CItemInstrumentInfo()
{
	CItemInstrumentInfo* pTreeItem = NULL;
	QMap<QString, CItemInstrumentInfo*>::iterator iterMap;

	iterMap = m_MapStringChildren.begin();
	while (iterMap != m_MapStringChildren.end())
	{
		pTreeItem = iterMap.value();

		if (NULL != pTreeItem)
		{
			delete pTreeItem;
			pTreeItem = NULL;
		}

		iterMap++;
	}
	m_MapStringChildren.clear();


	m_pParentItem = NULL;
	m_ItemData.clear();

}

void CItemInstrumentInfo::appendChild(const QString& strMapKey, CItemInstrumentInfo** ppItem)
{
	CItemInstrumentInfo* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem || strMapKey.isEmpty())
	{
		return;
	}
	pItem = *ppItem;

	if (m_MapStringChildren.contains(strMapKey))
	{
		delete pItem;
		pItem = NULL;
	}
	else
	{
		m_MapStringChildren.insert(strMapKey, pItem);
	}
	

}

CItemInstrumentInfo* CItemInstrumentInfo::child(int row)
{
  //  return m_LstChildItems.value(row);

	int nIndex = 0;
	CItemInstrumentInfo* pTreeItem = NULL;
	QMap<QString, CItemInstrumentInfo*>::iterator iterMap;

	iterMap = m_MapStringChildren.begin();
	nIndex = 0;
	while (iterMap != m_MapStringChildren.end())
	{
		if (nIndex == row)
		{
			pTreeItem = iterMap.value();
			break;
		}
		nIndex++;
		iterMap++;
	}

	return pTreeItem;
}

int CItemInstrumentInfo::childCount() const
{
    //return m_LstChildItems.count();
	return m_MapStringChildren.size();
}

int CItemInstrumentInfo::columnCount() const
{
    return m_ItemData.count();
}

QVariant CItemInstrumentInfo::data(int column) const
{
    return m_ItemData.value(column);
}

CItemInstrumentInfo* CItemInstrumentInfo::parent()
{
    return m_pParentItem;
}

int CItemInstrumentInfo::row() const
{
	int nIndex = 0;

    if (NULL != m_pParentItem)
	{
		//nIndex = m_pParentItem->m_LstChildItems.indexOf(const_cast<TreeItem*>(this));
		nIndex = m_pParentItem->indexOfChildren(const_cast<CItemInstrumentInfo*>(this));
        return nIndex;
	}

    return nIndex;
}

int CItemInstrumentInfo::indexOfChildren(CItemInstrumentInfo* pChildrenItem) const
{
	int nIndex = 0;
	CItemInstrumentInfo* pTreeItemTmp = NULL;
	QMap<QString,CItemInstrumentInfo*>::const_iterator iterMap;
	
	iterMap = m_MapStringChildren.constBegin();
	nIndex = 0;
	while (iterMap != m_MapStringChildren.constEnd())
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

void CItemInstrumentInfo::appendThreeChild(const CInstrumentInfoHelper* pExchangeInfo)
{
	_AppendChildExchangeName(pExchangeInfo);
}

void CItemInstrumentInfo::_AppendChildExchangeName( const CInstrumentInfoHelper* pExchangeInfo )
{
	QString strItemValue;
	QList<QVariant> dataTreeItem;
	CItemInstrumentInfo* pTreeItemExchangeName = NULL;
	QMap<QString, CItemInstrumentInfo*>::iterator iterFind;
	strItemValue = pExchangeInfo->getExchangeName();

	dataTreeItem.clear();
	dataTreeItem.push_back(strItemValue);
	pTreeItemExchangeName = new CItemInstrumentInfo(dataTreeItem, this);
	pTreeItemExchangeName->setDataType(CItemInstrumentInfo::DataTypeContract_ExchangeName);
	pTreeItemExchangeName->setInstrumentID(pExchangeInfo->getInstrumentID());

	this->setDataType(CItemInstrumentInfo::DataTypeContract_Root);
	this->appendChild(strItemValue, &pTreeItemExchangeName);
	pTreeItemExchangeName = NULL;


	iterFind = m_MapStringChildren.find(strItemValue);
	if (iterFind != m_MapStringChildren.end())
	{
		pTreeItemExchangeName = iterFind.value();
		pTreeItemExchangeName->appendChildUnderlyingCode(pExchangeInfo);
	}


}
void CItemInstrumentInfo::appendChildUnderlyingCode( const CInstrumentInfoHelper* pExchangeInfo )
{
	QString strItemValue;
	QList<QVariant> dataTreeItem;
	CItemInstrumentInfo* pTreeItemUnderlyingCode = NULL;
	QMap<QString, CItemInstrumentInfo*>::iterator iterFind;

	strItemValue = pExchangeInfo->getUnderlyingCode();

	dataTreeItem.clear();
	dataTreeItem.push_back(strItemValue);
	pTreeItemUnderlyingCode = new CItemInstrumentInfo(dataTreeItem, this);
	pTreeItemUnderlyingCode->setDataType(CItemInstrumentInfo::DataTypeContract_UnderlyingCode);
	pTreeItemUnderlyingCode->setInstrumentID(pExchangeInfo->getInstrumentID());

	this->setDataType(CItemInstrumentInfo::DataTypeContract_ExchangeName);
	this->appendChild(strItemValue, &pTreeItemUnderlyingCode);
	pTreeItemUnderlyingCode = NULL;


	iterFind = m_MapStringChildren.find(strItemValue);
	if (iterFind != m_MapStringChildren.end())
	{
		pTreeItemUnderlyingCode = iterFind.value();
		pTreeItemUnderlyingCode->appendChildInstrumentCode(pExchangeInfo);
	}



}

void CItemInstrumentInfo::appendChildInstrumentCode( const CInstrumentInfoHelper* pExchangeInfo )
{	

	QString strItemValue;
	QList<QVariant> dataTreeItem;
	CItemInstrumentInfo* pTreeItemInstrumentCode = NULL;
	QMap<QString, CItemInstrumentInfo*>::iterator iterFind;

	strItemValue = pExchangeInfo->getInstrumentCode();

	dataTreeItem.clear();
	dataTreeItem.push_back(strItemValue);
	pTreeItemInstrumentCode = new CItemInstrumentInfo(dataTreeItem, this);
	pTreeItemInstrumentCode->setDataType(CItemInstrumentInfo::DataTypeContract_InstrumentCode);
	pTreeItemInstrumentCode->setInstrumentID(pExchangeInfo->getInstrumentID());

	this->setDataType(CItemInstrumentInfo::DataTypeContract_UnderlyingCode);
	this->appendChild(strItemValue, &pTreeItemInstrumentCode);
	pTreeItemInstrumentCode = NULL;

}

bool CItemInstrumentInfo::removeChildren(int position)
{
	int nIndex = 0;
	CItemInstrumentInfo* pTreeItemTmp = NULL;
	QMap<QString,CItemInstrumentInfo*>::iterator iterMap;

	if (position < 0 || position > m_MapStringChildren.size())
	{
// 		MYLOG4CPP_ERROR<<"removeChildren() error!"
// 			<<" "<<"position="<<position
// 			<<" "<<"m_MapStringChildren.size()="<<m_MapStringChildren.size();

		return false;
	}

	nIndex = 0;
	iterMap = m_MapStringChildren.begin();
	while (iterMap != m_MapStringChildren.end())
	{
		if (nIndex == position)
		{
			pTreeItemTmp = iterMap.value();

			delete pTreeItemTmp;
			pTreeItemTmp = NULL;

			m_MapStringChildren.erase(iterMap);
			break;
		}//if (nIndex == position)

		nIndex++;
		iterMap++;
	}//while

	return true;
}


bool CItemInstrumentInfo::removeChildrenByData(const CInstrumentInfoHelper* pExchangeInfo)
{
	int nIndex = 0;
	CItemInstrumentInfo* pTreeItemTmp = NULL;
	QMap<QString,CItemInstrumentInfo*>::iterator iterMap;

	iterMap = m_MapStringChildren.begin();

	if (DataTypeContract_Root == this->m_nDataTypeExchange )
	{
		if (m_MapStringChildren.contains(pExchangeInfo->getExchangeName()))
		{
			iterMap = m_MapStringChildren.find(pExchangeInfo->getExchangeName());
			pTreeItemTmp = iterMap.value();
			pTreeItemTmp->removeChildrenByData(pExchangeInfo);

		}
	}
	else if (DataTypeContract_ExchangeName == this->m_nDataTypeExchange )
	{
		if (m_MapStringChildren.contains(pExchangeInfo->getUnderlyingCode()))
		{
			iterMap = m_MapStringChildren.find(pExchangeInfo->getUnderlyingCode());
			pTreeItemTmp = iterMap.value();
			pTreeItemTmp->removeChildrenByData(pExchangeInfo);
		}
	}
	else if (DataTypeContract_UnderlyingCode == this->m_nDataTypeExchange )
	{
		if (m_MapStringChildren.contains(pExchangeInfo->getInstrumentCode()))
		{
			iterMap = m_MapStringChildren.find(pExchangeInfo->getInstrumentCode());
			pTreeItemTmp = iterMap.value();//find ok


			nIndex = m_ItemData.indexOf(QVariant(pExchangeInfo->getInstrumentCode()), 0);
			m_ItemData.removeAt(nIndex);

			delete pTreeItemTmp;
			pTreeItemTmp = NULL;
			m_MapStringChildren.erase(iterMap);

		}
	}

	return true;
}

void CItemInstrumentInfo::setDataType( enDataTypeContract nDataTypeExchange )
{
	m_nDataTypeExchange = nDataTypeExchange;
}

CItemInstrumentInfo::enDataTypeContract CItemInstrumentInfo::getDataType()
{
	return m_nDataTypeExchange;
}

void CItemInstrumentInfo::setInstrumentID( unsigned int nInstrumentID )
{
	m_nInstrumentID = nInstrumentID;
}

unsigned int CItemInstrumentInfo::getInstrumentID()
{
	return m_nInstrumentID;
}

//QT_END_NAMESPACE


