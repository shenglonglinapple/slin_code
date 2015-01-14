#include "ItemModelStockMinTimeMaxTime.h"


//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QObject>
//
#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>

#include "ItemStockMinTimeMaxTime.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CItemModelStockMinTimeMaxTime::CItemModelStockMinTimeMaxTime(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemRef = NULL;
}


CItemModelStockMinTimeMaxTime::~CItemModelStockMinTimeMaxTime()
{
	m_pRootItemRef = NULL;
}



int CItemModelStockMinTimeMaxTime::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CItemStockMinTimeMaxTime*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemRef->columnCount();
	}

	return nColumnCount;
}



QVariant CItemModelStockMinTimeMaxTime::data(const QModelIndex &index, int role) const
{
	CItemStockMinTimeMaxTime* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CItemStockMinTimeMaxTime*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CItemModelStockMinTimeMaxTime::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CItemStockMinTimeMaxTime* pTreeItem = NULL;
	CItemStockMinTimeMaxTime::EItemType nDataType = CItemStockMinTimeMaxTime::ItemType_ITEM;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CItemStockMinTimeMaxTime*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

	nDataType = pTreeItem->getItemType();
	if (CItemStockMinTimeMaxTime::ItemType_ITEM == nDataType)
	{
		//nFlagsTreeItem = Qt::ItemIsEditable;
		//nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
		nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
		return nFlagsTreeItem;
	}

	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CItemModelStockMinTimeMaxTime::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        return m_pRootItemRef->data(section);
		//return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CItemModelStockMinTimeMaxTime::index(int row, int column, const QModelIndex &parent) const
{
	CItemStockMinTimeMaxTime* parentItem = NULL;
	CItemStockMinTimeMaxTime* childItem = NULL;

    if (!hasIndex(row, column, parent))
	{
        return QModelIndex();
	}

    if (!parent.isValid())
	{
        parentItem = m_pRootItemRef;
	}
    else
	{
        parentItem = static_cast<CItemStockMinTimeMaxTime*>(parent.internalPointer());
	}

    childItem = parentItem->child(row);
    if (childItem)
	{
        return createIndex(row, column, childItem);
	}
    else
	{
        return QModelIndex();
	}

	return QModelIndex();
}



QModelIndex CItemModelStockMinTimeMaxTime::parent(const QModelIndex &index) const
{
	CItemStockMinTimeMaxTime* childItem = NULL;
	CItemStockMinTimeMaxTime* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CItemStockMinTimeMaxTime*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemRef)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->childNumber(), 0, parentItem);
}



int CItemModelStockMinTimeMaxTime::rowCount(const QModelIndex &parent) const
{
    CItemStockMinTimeMaxTime* parentItem = NULL;
    if (parent.column() > 0)
	{
        return 0;
	}

    if (!parent.isValid())
	{
        parentItem = m_pRootItemRef;
	}
    else
	{
        parentItem = static_cast<CItemStockMinTimeMaxTime*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CItemModelStockMinTimeMaxTime::setRootItem( CItemStockMinTimeMaxTime* rootItem )
{
	m_pRootItemRef = rootItem;
	reset();
}


CItemStockMinTimeMaxTime* CItemModelStockMinTimeMaxTime::_GetItem( const QModelIndex& index ) const
{
	CItemStockMinTimeMaxTime *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CItemStockMinTimeMaxTime*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemRef;
}
















