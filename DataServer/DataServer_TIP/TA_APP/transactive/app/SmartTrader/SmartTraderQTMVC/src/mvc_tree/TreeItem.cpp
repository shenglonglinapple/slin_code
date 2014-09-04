#include "TreeItem.h"


//QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE


static const std::string DEFVALUE_String_ColumnName_Column1 = "Column1";
static const std::string DEFVALUE_String_ColumnName_Column2 = "Column2";
static const std::string DEFVALUE_String_ColumnName_Column3 = "Column3";




TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
    parentItem = parent;
    itemData = data;
}



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



TreeItem *TreeItem::child(int number)
{
    return childItems.value(number);
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

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

TreeItem *TreeItem::parent()
{
    return parentItem;
}

bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}


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

	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Column1.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Column2.c_str());
	lstClumnName.append(strColumnName);
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_Column3.c_str());
	lstClumnName.append(strColumnName);



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



