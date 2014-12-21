#include "ItemModelUserInstrument.h"


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

#include "ItemUserInstrument.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CItemModelUserInstrument::CItemModelUserInstrument(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemRef = NULL;
}


CItemModelUserInstrument::~CItemModelUserInstrument()
{
	m_pRootItemRef = NULL;
}



int CItemModelUserInstrument::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CItemUserInstrument*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemRef->columnCount();
	}

	return nColumnCount;
}



QVariant CItemModelUserInstrument::data(const QModelIndex &index, int role) const
{
	CItemUserInstrument* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CItemUserInstrument*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CItemModelUserInstrument::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CItemUserInstrument* pTreeItem = NULL;
	CItemUserInstrument::EItemType nDataType = CItemUserInstrument::ItemType_ITEM;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CItemUserInstrument*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

	nDataType = pTreeItem->getItemType();
	if (CItemUserInstrument::ItemType_ITEM == nDataType)
	{
		//nFlagsTreeItem = Qt::ItemIsEditable;
		//nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
		nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
		return nFlagsTreeItem;
	}

	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CItemModelUserInstrument::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        return m_pRootItemRef->data(section);
		//return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CItemModelUserInstrument::index(int row, int column, const QModelIndex &parent) const
{
	CItemUserInstrument* parentItem = NULL;
	CItemUserInstrument* childItem = NULL;

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
        parentItem = static_cast<CItemUserInstrument*>(parent.internalPointer());
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



QModelIndex CItemModelUserInstrument::parent(const QModelIndex &index) const
{
	CItemUserInstrument* childItem = NULL;
	CItemUserInstrument* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CItemUserInstrument*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemRef)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->childNumber(), 0, parentItem);
}



int CItemModelUserInstrument::rowCount(const QModelIndex &parent) const
{
    CItemUserInstrument* parentItem = NULL;
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
        parentItem = static_cast<CItemUserInstrument*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CItemModelUserInstrument::setRootItem( CItemUserInstrument* rootItem )
{
	m_pRootItemRef = rootItem;
	reset();
}


CItemUserInstrument* CItemModelUserInstrument::_GetItem( const QModelIndex& index ) const
{
	CItemUserInstrument *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CItemUserInstrument*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemRef;
}
















