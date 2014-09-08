#include "TreeItemContract.h"


//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QObject>


#include "ContractInfo.h"

//#include "BoostLogger.h"
//USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


CTreeItemContract::CTreeItemContract(const QList<QVariant> &data, CTreeItemContract *parent /*= 0*/ )
{
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_MapStringChildren.clear();

	m_pParentItem = parent;
	m_ItemData = data;
	m_nDataTypeExchange = CTreeItemContract::DataTypeContract_InstrumentCode;
	m_nInstrumentID = 0;
}

CTreeItemContract::CTreeItemContract()
{
	QList<QVariant> dataTmp;
	CTreeItemContract* parent = NULL;
	QString strTmp = "NULL";
	dataTmp.push_back(strTmp);
	parent = NULL;

	m_pParentItem = NULL;
	m_ItemData.clear();
	m_MapStringChildren.clear();

	m_pParentItem = parent;
	m_ItemData = dataTmp;
	m_nDataTypeExchange = CTreeItemContract::DataTypeContract_InstrumentCode;

}


CTreeItemContract::~CTreeItemContract()
{
	CTreeItemContract* pTreeItem = NULL;
	QMap<QString, CTreeItemContract*>::iterator iterMap;

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

void CTreeItemContract::appendChild(const QString& strMapKey, CTreeItemContract** ppItem)
{
	CTreeItemContract* pItem = NULL;
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

CTreeItemContract* CTreeItemContract::child(int row)
{
  //  return m_LstChildItems.value(row);

	int nIndex = 0;
	CTreeItemContract* pTreeItem = NULL;
	QMap<QString, CTreeItemContract*>::iterator iterMap;

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

int CTreeItemContract::childCount() const
{
    //return m_LstChildItems.count();
	return m_MapStringChildren.size();
}

int CTreeItemContract::columnCount() const
{
    return m_ItemData.count();
}

QVariant CTreeItemContract::data(int column) const
{
    return m_ItemData.value(column);
}

CTreeItemContract* CTreeItemContract::parent()
{
    return m_pParentItem;
}

int CTreeItemContract::row() const
{
	int nIndex = 0;

    if (NULL != m_pParentItem)
	{
		//nIndex = m_pParentItem->m_LstChildItems.indexOf(const_cast<TreeItem*>(this));
		nIndex = m_pParentItem->indexOfChildren(const_cast<CTreeItemContract*>(this));
        return nIndex;
	}

    return nIndex;
}

int CTreeItemContract::indexOfChildren(CTreeItemContract* pChildrenItem) const
{
	int nIndex = 0;
	CTreeItemContract* pTreeItemTmp = NULL;
	QMap<QString,CTreeItemContract*>::const_iterator iterMap;
	
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

void CTreeItemContract::appendThreeChild(const CContractInfo* pExchangeInfo)
{
	_AppendChildExchangeName(pExchangeInfo);
}

void CTreeItemContract::_AppendChildExchangeName( const CContractInfo* pExchangeInfo )
{
	QString strItemValue;
	QList<QVariant> dataTreeItem;
	CTreeItemContract* pTreeItemExchangeName = NULL;
	QMap<QString, CTreeItemContract*>::iterator iterFind;
	strItemValue = pExchangeInfo->getExchangeName();

	dataTreeItem.clear();
	dataTreeItem.push_back(strItemValue);
	pTreeItemExchangeName = new CTreeItemContract(dataTreeItem, this);
	pTreeItemExchangeName->setDataType(CTreeItemContract::DataTypeContract_ExchangeName);
	pTreeItemExchangeName->setInstrumentID(pExchangeInfo->getInstrumentID());

	this->setDataType(CTreeItemContract::DataTypeContract_Root);
	this->appendChild(strItemValue, &pTreeItemExchangeName);
	pTreeItemExchangeName = NULL;


	iterFind = m_MapStringChildren.find(strItemValue);
	if (iterFind != m_MapStringChildren.end())
	{
		pTreeItemExchangeName = iterFind.value();
		pTreeItemExchangeName->appendChildUnderlyingCode(pExchangeInfo);
	}


}
void CTreeItemContract::appendChildUnderlyingCode( const CContractInfo* pExchangeInfo )
{
	QString strItemValue;
	QList<QVariant> dataTreeItem;
	CTreeItemContract* pTreeItemUnderlyingCode = NULL;
	QMap<QString, CTreeItemContract*>::iterator iterFind;

	strItemValue = pExchangeInfo->getUnderlyingCode();

	dataTreeItem.clear();
	dataTreeItem.push_back(strItemValue);
	pTreeItemUnderlyingCode = new CTreeItemContract(dataTreeItem, this);
	pTreeItemUnderlyingCode->setDataType(CTreeItemContract::DataTypeContract_UnderlyingCode);
	pTreeItemUnderlyingCode->setInstrumentID(pExchangeInfo->getInstrumentID());

	this->setDataType(CTreeItemContract::DataTypeContract_ExchangeName);
	this->appendChild(strItemValue, &pTreeItemUnderlyingCode);
	pTreeItemUnderlyingCode = NULL;


	iterFind = m_MapStringChildren.find(strItemValue);
	if (iterFind != m_MapStringChildren.end())
	{
		pTreeItemUnderlyingCode = iterFind.value();
		pTreeItemUnderlyingCode->appendChildInstrumentCode(pExchangeInfo);
	}



}

void CTreeItemContract::appendChildInstrumentCode( const CContractInfo* pExchangeInfo )
{	

	QString strItemValue;
	QList<QVariant> dataTreeItem;
	CTreeItemContract* pTreeItemInstrumentCode = NULL;
	QMap<QString, CTreeItemContract*>::iterator iterFind;

	strItemValue = pExchangeInfo->getInstrumentCode();

	dataTreeItem.clear();
	dataTreeItem.push_back(strItemValue);
	pTreeItemInstrumentCode = new CTreeItemContract(dataTreeItem, this);
	pTreeItemInstrumentCode->setDataType(CTreeItemContract::DataTypeContract_InstrumentCode);
	pTreeItemInstrumentCode->setInstrumentID(pExchangeInfo->getInstrumentID());

	this->setDataType(CTreeItemContract::DataTypeContract_UnderlyingCode);
	this->appendChild(strItemValue, &pTreeItemInstrumentCode);
	pTreeItemInstrumentCode = NULL;

}

bool CTreeItemContract::removeChildren(int position)
{
	int nIndex = 0;
	CTreeItemContract* pTreeItemTmp = NULL;
	QMap<QString,CTreeItemContract*>::iterator iterMap;

	if (position < 0 || position > m_MapStringChildren.size())
	{
// 		LOG_ERROR<<"removeChildren() error!"
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

void CTreeItemContract::setDataType( enDataTypeContract nDataTypeExchange )
{
	m_nDataTypeExchange = nDataTypeExchange;
}

CTreeItemContract::enDataTypeContract CTreeItemContract::getDataType()
{
	return m_nDataTypeExchange;
}

void CTreeItemContract::setInstrumentID( unsigned int nInstrumentID )
{
	m_nInstrumentID = nInstrumentID;
}

unsigned int CTreeItemContract::getInstrumentID()
{
	return m_nInstrumentID;
}

//QT_END_NAMESPACE


