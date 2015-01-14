#include "ItemModelStockHistoryData.h"

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

#include "ItemStockHistoryData.h"


CItemModelStockHistoryData::CItemModelStockHistoryData(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemRef = NULL;
}


CItemModelStockHistoryData::~CItemModelStockHistoryData()
{
	m_pRootItemRef = NULL;
}



int CItemModelStockHistoryData::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CItemStockHistoryData*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemRef->columnCount();
	}

	return nColumnCount;
}



QVariant CItemModelStockHistoryData::data(const QModelIndex &index, int role) const
{
	CItemStockHistoryData* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CItemStockHistoryData*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CItemModelStockHistoryData::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CItemStockHistoryData* pTreeItem = NULL;
	CItemStockHistoryData::EItemType nDataType = CItemStockHistoryData::ItemType_ITEM;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CItemStockHistoryData*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

	nDataType = pTreeItem->getItemType();
	if (CItemStockHistoryData::ItemType_ITEM == nDataType)
	{
		//nFlagsTreeItem = Qt::ItemIsEditable;
		//nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
		nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
		return nFlagsTreeItem;
	}

	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CItemModelStockHistoryData::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        return m_pRootItemRef->data(section);
		//return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CItemModelStockHistoryData::index(int row, int column, const QModelIndex &parent) const
{
	CItemStockHistoryData* parentItem = NULL;
	CItemStockHistoryData* childItem = NULL;

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
        parentItem = static_cast<CItemStockHistoryData*>(parent.internalPointer());
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



QModelIndex CItemModelStockHistoryData::parent(const QModelIndex &index) const
{
	CItemStockHistoryData* childItem = NULL;
	CItemStockHistoryData* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CItemStockHistoryData*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemRef)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->childNumber(), 0, parentItem);
}



int CItemModelStockHistoryData::rowCount(const QModelIndex &parent) const
{
    CItemStockHistoryData* parentItem = NULL;
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
        parentItem = static_cast<CItemStockHistoryData*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CItemModelStockHistoryData::setRootItem( CItemStockHistoryData* rootItem )
{
	m_pRootItemRef = rootItem;
	reset();
}


CItemStockHistoryData* CItemModelStockHistoryData::_GetItem( const QModelIndex& index ) const
{
	CItemStockHistoryData *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CItemStockHistoryData*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemRef;
}
















