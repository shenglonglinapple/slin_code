#include "TreeItemOrder.h"


//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QStringList>

#include "OrderInfo.h"
#include "ConfigInfo.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


static const std::string DEFVALUE_String_ColumnName_Data_Key = "Key";//


static const std::string DEFVALUE_String_ColumnName_OrderInfo_CumQty = "CumQty";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_LastQty = "LastQty";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderQty = "OrderQty";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_LeavesQty = "LeavesQty";//

static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price = "Price";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price2 = "Price2";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_LastPx = "LastPx";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_AvgPrice = "AvgPrice";//

static const std::string DEFVALUE_String_ColumnName_OrderInfo_Side = "Side";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderType = "OrderType";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderStatus = "OrderStatus";//


static const std::string DEFVALUE_String_ColumnName_OrderInfo_RejectReason = "RejectReason";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Text = "Text";//

static const std::string DEFVALUE_String_ColumnName_OrderInfo_UserID = "UserID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_ClOrdID = "ClOrdID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderID = "OrderID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_AccountID = "AccountID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_StrategyID = "StrategyID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_InstrumentID = "InstrumentID";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_TransactTime = "TransactTime";//


static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderInfoMasks = "OrderInfoMasks";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Fees = "Fees";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_Margin = "Margin";//


//NS_BEGIN(TA_App_App)

CTreeItemOrder::CTreeItemOrder(const QList<QVariant> &data, CTreeItemOrder *parent /*= 0*/ )
{
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_ItemDataNum = 0;
	m_LstChildItems.clear();

	m_pParentItem = parent;
	m_ItemData = data;
	m_ItemDataNum = m_ItemData.count();
	m_nDataType = ItemDataType_NULL;
;
}

CTreeItemOrder::CTreeItemOrder()
{
	QList<QVariant> dataTreeItem;
	getLstClumnName(dataTreeItem);
	
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();

	m_pParentItem = NULL;
	m_ItemData = dataTreeItem;
	m_ItemDataNum = m_ItemData.count();
	m_nDataType = ItemDataType_NULL;

}


CTreeItemOrder::~CTreeItemOrder()
{
	CTreeItemOrder* pTreeItem = NULL;
	QList<CTreeItemOrder*>::iterator iterLst;

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pTreeItem = (*iterLst);

		if (NULL != pTreeItem)
		{
			delete pTreeItem;
			pTreeItem = NULL;
		}

		iterLst++;
	}
	m_LstChildItems.clear();


	m_pParentItem = NULL;
	m_ItemData.clear();


}

void CTreeItemOrder::appendChild(CTreeItemOrder** ppItem)
{
	CTreeItemOrder* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;

	m_LstChildItems.push_back(pItem);


}

CTreeItemOrder* CTreeItemOrder::child(int row)
{
	return m_LstChildItems.value(row);
}

int CTreeItemOrder::childCount() const
{
    return m_LstChildItems.count();
}

int CTreeItemOrder::columnCount() const
{
    return m_ItemData.count();
}

QVariant CTreeItemOrder::data(int column) const
{
    return m_ItemData.value(column);
}

CTreeItemOrder* CTreeItemOrder::parent()
{
    return m_pParentItem;
}

int CTreeItemOrder::childNumber() const
{
	int nIndex = 0;

    if (NULL != m_pParentItem)
	{
		//nIndex = m_pParentItem->m_LstChildItems.indexOf(const_cast<TreeItem*>(this));
		nIndex = m_pParentItem->indexOfChildren(const_cast<CTreeItemOrder*>(this));
        return nIndex;
	}

    return nIndex;
}

int CTreeItemOrder::indexOfChildren(CTreeItemOrder* pChildrenItem) const
{
	int nIndex = 0;
	nIndex = m_LstChildItems.indexOf(pChildrenItem);
	return nIndex;
}

void CTreeItemOrder::appendChildByData(COrderInfo* pData)
{
	QList<QVariant> dataTreeItem;
	CTreeItemOrder* pTreeItemInstrumentCode = NULL;

	pTreeItemInstrumentCode = new CTreeItemOrder(dataTreeItem, this);
	pTreeItemInstrumentCode->resetCurrentNodeData(pData);
	pTreeItemInstrumentCode->setDataType(ItemDataType_ITEM);

	this->appendChild(&pTreeItemInstrumentCode);
	pTreeItemInstrumentCode = NULL;
}



void CTreeItemOrder::_GetItemDataFromClass(COrderInfo* pData, QList<QVariant>& itemDataTmp)
{

	QVariant varValueGet;
	QStringList strlstClumnNameShow;
	CTreeItemOrder::getLstClumnName(strlstClumnNameShow);

	itemDataTmp.clear();
	m_nKey = pData->getValueByName(DEFVALUE_String_ColumnName_Data_Key.c_str()).toUInt();

	foreach (const QString& strColumnName, strlstClumnNameShow)
	{
		varValueGet = pData->getValueByName(strColumnName);
		itemDataTmp.push_back(varValueGet);
	}

	return;
}



void CTreeItemOrder::resetCurrentNodeData(COrderInfo* pData )
{
	m_ItemData.clear();
	m_ItemDataNum = 0;

	_GetItemDataFromClass(pData, m_ItemData);
	m_ItemDataNum = m_ItemData.count();
}

void CTreeItemOrder::resetCurrentNodeDataDefultValue()
{
	QList<QVariant> dataTreeItem;

	for (int nIndex = 0; nIndex < m_ItemDataNum; nIndex++)
	{
		dataTreeItem.push_back("");
	}
	m_ItemData.clear();
	m_ItemData = dataTreeItem;
	m_ItemDataNum = m_ItemData.count();
}


void CTreeItemOrder::resetChildrenData(COrderInfo* pData )
{
	CTreeItemOrder* pTreeItemFind = NULL;
	QList<CTreeItemOrder*>::iterator iterLst;
	unsigned int nKeyValue = 0;
	nKeyValue = pData->getKey();

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pTreeItemFind = (*iterLst);

		if (pTreeItemFind->getKey() == nKeyValue)
		{
			pTreeItemFind->resetCurrentNodeData(pData);
			break;
		}

		iterLst++;
	}
	
}


bool CTreeItemOrder::removeChildren( int position, int count )
{
	CTreeItemOrder* pTreeItem = NULL;

	if (position < 0 || position + count > m_LstChildItems.size())
	{
		LOG_ERROR<<"removeChildren() error!"
			<<" "<<"position="<<position
			<<" "<<"count="<<count
			<<" "<<"m_LstChildItems.count()="<<m_LstChildItems.count();

		return false;
	}

	for (int row = 0; row < count; ++row)
	{
		//get and remove 
		pTreeItem = m_LstChildItems.takeAt(position);

		if (NULL != pTreeItem)
		{
			delete pTreeItem;
			pTreeItem = NULL;
		}
	}

	return true;
}

void CTreeItemOrder::setDataType( enItemDataType nDataTypeExchange )
{
	m_nDataType = nDataTypeExchange;
}

CTreeItemOrder::enItemDataType CTreeItemOrder::getDataType()
{
	return m_nDataType;
}


void CTreeItemOrder::getLstClumnName(QStringList& strlstClumnName )
{
	QString strColumnName;
	strlstClumnName.clear();
	
	//	static const std::string DEFVALUE_String_ColumnName_OrderInfo_CumQty = "CumQty";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_CumQty.c_str();
	strlstClumnName.push_back(strColumnName);

	//	static const std::string DEFVALUE_String_ColumnName_OrderInfo_LastQty = "LastQty";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_LastQty.c_str();
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderQty = "OrderQty";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_OrderQty.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_LeavesQty = "LeavesQty";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_LeavesQty.c_str();
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price = "Price";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_Price.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Price2 = "Price2";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_Price2.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_LastPx = "LastPx";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_LastPx.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_AvgPrice = "AvgPrice";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_AvgPrice.c_str();
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Side = "Side";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_Side.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderType = "OrderType";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_OrderType.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderStatus = "OrderStatus";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_OrderStatus.c_str();
	strlstClumnName.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_RejectReason = "RejectReason";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_RejectReason.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Text = "Text";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_Text.c_str();
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_UserID = "UserID";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_UserID.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_ClOrdID = "ClOrdID";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_ClOrdID.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderID = "OrderID";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_OrderID.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_AccountID = "AccountID";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_AccountID.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_StrategyID = "StrategyID";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_StrategyID.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_InstrumentID = "InstrumentID";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_InstrumentID.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_TransactTime = "TransactTime";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_TransactTime.c_str();
	strlstClumnName.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderInfoMasks = "OrderInfoMasks";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_OrderInfoMasks.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Fees = "Fees";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_Fees.c_str();
	strlstClumnName.push_back(strColumnName);
	//static const std::string DEFVALUE_String_ColumnName_OrderInfo_Margin = "Margin";//
	strColumnName = DEFVALUE_String_ColumnName_OrderInfo_Margin.c_str();
	strlstClumnName.push_back(strColumnName);

	return;
}

void CTreeItemOrder::getLstClumnName(QList<QVariant>& lstClumnName )
{
	QStringList strlstClumnName;
	QVariant varColumnName;

	lstClumnName.clear();

	CTreeItemOrder::getLstClumnName(strlstClumnName);

	foreach (const QString& strColumnName, strlstClumnName)
	{
		varColumnName = QVariant(strColumnName);
		lstClumnName.push_back(varColumnName);
	}

	return;
}




bool CTreeItemOrder::insertChildren( int position, int count, int columns )
{
	if (position < 0 || position > m_LstChildItems.size())
	{
		return false;
	}

	for (int row = 0; row < count; ++row) 
	{
		QList<QVariant> dataTreeItem;
// 		for (int nColumn = 0; nColumn < columns; nColumn++)
// 		{
// 			dataTreeItem.push_back("");
// 		}
		CTreeItemOrder* pTreeItemInstrumentCode = NULL;
		pTreeItemInstrumentCode = new CTreeItemOrder(dataTreeItem, this);
		pTreeItemInstrumentCode->resetCurrentNodeDataDefultValue();
		pTreeItemInstrumentCode->setDataType(ItemDataType_ITEM);
		m_LstChildItems.insert(position, pTreeItemInstrumentCode);
		pTreeItemInstrumentCode = NULL;

	}

	return true;
}

bool CTreeItemOrder::insertColumns( int position, int columns )
{
	if (position < 0 || position > m_ItemData.size())
	{
		return false;
	}

	for (int column = 0; column < columns; ++column)
	{
		m_ItemData.insert(position, QVariant());
	}

	foreach (CTreeItemOrder *children, m_LstChildItems)
	{
		children->insertColumns(position, columns);
	}

	return true;
}

bool CTreeItemOrder::removeColumns( int position, int columns )
{
	QList<QVariant>::Iterator iterList;

	if (position < 0 || position + columns > m_ItemData.size())
	{
		return false;
	}

	for (int column = 0; column < columns; ++column)
	{
		//m_ItemData.remove(position);

		iterList = m_ItemData.begin();
		iterList += position;
		m_ItemData.erase(iterList);
	}

	foreach (CTreeItemOrder *child, m_LstChildItems)
	{
		child->removeColumns(position, columns);
	}

	return true;
}

bool CTreeItemOrder::setData( int column, const QVariant &dataValue )
{
	if (column < 0 || column >= m_ItemData.size())
	{
		return false;
	}

	m_ItemData[column] = dataValue;

	return true;
}


void CTreeItemOrder::rootNodeSetColumnsName()
{
	if (CTreeItemOrder::ItemDataType_ROOT != m_nDataType)
	{
		return;
	}
	m_ItemData.clear();
	m_ItemDataNum = 0;

	CTreeItemOrder::getLstClumnName(m_ItemData);

	m_ItemDataNum = m_ItemData.count();
	this->setDataType(CTreeItemOrder::ItemDataType_ROOT);
}

unsigned int CTreeItemOrder::getKey()
{
	return m_nKey;
}


//QT_END_NAMESPACE

