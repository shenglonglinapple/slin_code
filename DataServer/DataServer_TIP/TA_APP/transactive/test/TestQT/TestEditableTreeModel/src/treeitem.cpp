/*
    treeitem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include <QStringList>

#include "treeitem.h"




static const std::string DEFVALUE_String_ColumnName_StrategyOrders_CumQty = "CumQty";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_LastQty = "LastQty";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_OrderQty = "OrderQty";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_LeavesQty = "LeavesQty";

static const std::string DEFVALUE_String_ColumnName_StrategyOrders_Price = "Price";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_Price2 = "Price2";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_LastPx = "LastPx";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_AvgPrice = "AvgPrice";


static const std::string DEFVALUE_String_ColumnName_StrategyOrders_Side = "Side";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_OrderType = "OrderType";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_OrderStatus = "OrderStatus";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_RejectReason = "RejectReason";

static const std::string DEFVALUE_String_ColumnName_StrategyOrders_Text = "Text";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_UserID = "UserID";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_ClOrdID = "ClOrdID";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_OrderID = "OrderID";


static const std::string DEFVALUE_String_ColumnName_StrategyOrders_AccountID = "AccountID";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_StrategyID = "StrategyID";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_InstrumentID = "InstrumentID";
static const std::string DEFVALUE_String_ColumnName_StrategyOrders_TransactTime = "TransactTime";




//! [0]
TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}
//! [0]

//! [1]
TreeItem::~TreeItem()
{
	parentItem = NULL;
	itemData.clear();

	TreeItem* pItemTmp = NULL;
	QList<TreeItem*>::iterator iterList;
	iterList = childItems.begin();
	while (iterList != childItems.end())
	{
		pItemTmp = *iterList;

		delete pItemTmp;
		pItemTmp = NULL;

		iterList++;
	}//while

    //qDeleteAll(childItems);
}
//! [1]

//! [2]
TreeItem *TreeItem::child(int number)
{
    return childItems.value(number);
}
//! [2]

//! [3]
int TreeItem::childCount() const
{
    return childItems.count();
}
//! [3]

//! [4]
int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
//! [4]

//! [5]
int TreeItem::columnCount() const
{
    return itemData.count();
}
//! [5]

//! [6]
QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}
//! [6]

//! [7]
bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > childItems.size())
        return false;

    for (int row = 0; row < count; ++row) 
	{
        QList<QVariant> data;
		data.reserve(columns);
		TreeItem *item = NULL;
        item = new TreeItem(data, this);
        childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
bool TreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        itemData.insert(position, QVariant());

    foreach (TreeItem *child, childItems)
        child->insertColumns(position, columns);

    return true;
}
//! [8]

//! [9]
TreeItem *TreeItem::parent()
{
    return parentItem;
}
//! [9]

//! [10]
bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}
//! [10]

bool TreeItem::removeColumns(int position, int columns)
{
	QList<QVariant>::Iterator iterList;

    if (position < 0 || position + columns > itemData.size())
	{
        return false;
	}

    for (int column = 0; column < columns; ++column)
	{
		//itemData.remove(position);

		iterList = itemData.begin();
		iterList += position;
		itemData.erase(iterList);
	}

    foreach (TreeItem *child, childItems)
        child->removeColumns(position, columns);

    return true;
}

//! [11]
bool TreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}

void TreeItem::getLstClumnName( QStringList& lstClumnName )
{
	QString strColumnName;
	lstClumnName.clear();

	strColumnName = QObject::tr("Column_1");
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr("Column_2");
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr("Column_3");
	lstClumnName.append(strColumnName);

/*
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_CumQty.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_LastQty.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_OrderQty.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_LeavesQty.c_str());
	dataTreeItem.append(strColumnName);



	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_Price.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_Price2.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_LastPx.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_AvgPrice.c_str());
	dataTreeItem.append(strColumnName);


	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_Side.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_OrderType.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_OrderStatus.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_RejectReason.c_str());
	dataTreeItem.append(strColumnName);


	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_Text.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_UserID.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_ClOrdID.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_OrderID.c_str());
	dataTreeItem.append(strColumnName);


	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_AccountID.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_StrategyID.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_InstrumentID.c_str());
	dataTreeItem.append(strColumnName);
	strColumnName = QString(DEFVALUE_String_ColumnName_StrategyOrders_TransactTime.c_str());
	dataTreeItem.append(strColumnName);
*/

}

void TreeItem::getLstClumnName( QList<QVariant>& lstClumnName )
{
	QStringList strlstClumnName;
	QVariant varColumnName;

	lstClumnName.clear();

	TreeItem::getLstClumnName(strlstClumnName);

	foreach (const QString& strColumnName, strlstClumnName)
	{
		varColumnName = QVariant(strColumnName);
		lstClumnName.append(varColumnName);
	}
}

void TreeItem::appendChild( TreeItem** ppItem )
{
	TreeItem* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;
	childItems.push_back(pItem);
}


//! [11]
