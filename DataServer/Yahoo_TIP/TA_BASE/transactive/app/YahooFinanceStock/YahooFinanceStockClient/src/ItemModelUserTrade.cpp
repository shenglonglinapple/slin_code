#include "ItemModelUserTrade.h"


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

#include "ItemUserTrade.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CItemModelUserTrade::CItemModelUserTrade(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemRef = NULL;
}


CItemModelUserTrade::~CItemModelUserTrade()
{
	m_pRootItemRef = NULL;
}



int CItemModelUserTrade::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CItemUserTrade*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemRef->columnCount();
	}

	return nColumnCount;
}



QVariant CItemModelUserTrade::data(const QModelIndex &index, int role) const
{
	CItemUserTrade* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CItemUserTrade*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CItemModelUserTrade::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CItemUserTrade* pTreeItem = NULL;
	CItemUserTrade::EItemType nDataType = CItemUserTrade::ItemType_ITEM;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CItemUserTrade*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

	nDataType = pTreeItem->getItemType();
	if (CItemUserTrade::ItemType_ITEM == nDataType)
	{
		//nFlagsTreeItem = Qt::ItemIsEditable;
		//nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
		nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
		return nFlagsTreeItem;
	}

	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CItemModelUserTrade::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        return m_pRootItemRef->data(section);
		//return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CItemModelUserTrade::index(int row, int column, const QModelIndex &parent) const
{
	CItemUserTrade* parentItem = NULL;
	CItemUserTrade* childItem = NULL;

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
        parentItem = static_cast<CItemUserTrade*>(parent.internalPointer());
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



QModelIndex CItemModelUserTrade::parent(const QModelIndex &index) const
{
	CItemUserTrade* childItem = NULL;
	CItemUserTrade* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CItemUserTrade*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemRef)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->childNumber(), 0, parentItem);
}



int CItemModelUserTrade::rowCount(const QModelIndex &parent) const
{
    CItemUserTrade* parentItem = NULL;
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
        parentItem = static_cast<CItemUserTrade*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CItemModelUserTrade::setRootItem( CItemUserTrade* rootItem )
{
	m_pRootItemRef = rootItem;
	reset();
}


CItemUserTrade* CItemModelUserTrade::_GetItem( const QModelIndex& index ) const
{
	CItemUserTrade *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CItemUserTrade*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemRef;
}
















