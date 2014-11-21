#include "ItemModelUserInstrumentInfo.h"


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

#include "ItemUserInstrumentInfo.h"




//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CItemModelUserInstrumentInfo::CItemModelUserInstrumentInfo(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemRef = NULL;
}


CItemModelUserInstrumentInfo::~CItemModelUserInstrumentInfo()
{
	m_pRootItemRef = NULL;
}



int CItemModelUserInstrumentInfo::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CItemUserInstrumentInfo*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemRef->columnCount();
	}

	return nColumnCount;
}



QVariant CItemModelUserInstrumentInfo::data(const QModelIndex &index, int role) const
{
	CItemUserInstrumentInfo* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CItemUserInstrumentInfo*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CItemModelUserInstrumentInfo::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CItemUserInstrumentInfo* pTreeItem = NULL;
	CItemUserInstrumentInfo::enItemDataType nDataType = CItemUserInstrumentInfo::ItemDataType_ITEM;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CItemUserInstrumentInfo*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

	nDataType = pTreeItem->getDataType();
	if (CItemUserInstrumentInfo::ItemDataType_ITEM == nDataType)
	{
		//nFlagsTreeItem = Qt::ItemIsEditable;
		nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
		return nFlagsTreeItem;
	}

	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CItemModelUserInstrumentInfo::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        return m_pRootItemRef->data(section);
		//return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CItemModelUserInstrumentInfo::index(int row, int column, const QModelIndex &parent) const
{
	CItemUserInstrumentInfo* parentItem = NULL;
	CItemUserInstrumentInfo* childItem = NULL;

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
        parentItem = static_cast<CItemUserInstrumentInfo*>(parent.internalPointer());
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



QModelIndex CItemModelUserInstrumentInfo::parent(const QModelIndex &index) const
{
	CItemUserInstrumentInfo* childItem = NULL;
	CItemUserInstrumentInfo* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CItemUserInstrumentInfo*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemRef)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->childNumber(), 0, parentItem);
}



int CItemModelUserInstrumentInfo::rowCount(const QModelIndex &parent) const
{
    CItemUserInstrumentInfo* parentItem = NULL;
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
        parentItem = static_cast<CItemUserInstrumentInfo*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CItemModelUserInstrumentInfo::setRootItem( CItemUserInstrumentInfo* rootItem )
{
	m_pRootItemRef = rootItem;
	reset();
}


bool CItemModelUserInstrumentInfo::removeRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CItemUserInstrumentInfo* parentItem = _GetItem(parent);
	bool success = true;

	beginRemoveRows(parent, position, position + rows - 1);
	success = parentItem->removeChildren(position, rows);
	endRemoveRows();

	return success;
}


CItemUserInstrumentInfo* CItemModelUserInstrumentInfo::_GetItem( const QModelIndex& index ) const
{
	CItemUserInstrumentInfo *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CItemUserInstrumentInfo*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemRef;
}

bool CItemModelUserInstrumentInfo::insertRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CItemUserInstrumentInfo *parentItem = _GetItem(parent);
	bool success;

	beginInsertRows(parent, position, position + rows - 1);
	success = parentItem->insertChildren(position, rows, m_pRootItemRef->columnCount());
	endInsertRows();

	return success;
}

bool CItemModelUserInstrumentInfo::removeColumns( int position, int columns, const QModelIndex &parent /*= QModelIndex()*/ )
{
	bool success;

	beginRemoveColumns(parent, position, position + columns - 1);
	success = m_pRootItemRef->removeColumns(position, columns);
	endRemoveColumns();

	if (m_pRootItemRef->columnCount() == 0)
	{
		removeRows(0, rowCount());
	}

	return success;
}

bool CItemModelUserInstrumentInfo::insertColumns( int position, int columns, const QModelIndex &parent /*= QModelIndex()*/ )
{
	bool success;

	beginInsertColumns(parent, position, position + columns - 1);
	success = m_pRootItemRef->insertColumns(position, columns);
	endInsertColumns();

	return success;
}

bool CItemModelUserInstrumentInfo::setHeaderData( int section, Qt::Orientation orientation, const QVariant &value, int role /*= Qt::EditRole*/ )
{
	if (role != Qt::EditRole || orientation != Qt::Horizontal)
		return false;

	bool result = m_pRootItemRef->setData(section, value);

	if (result)
	{
		emit headerDataChanged(orientation, section, section);
	}

	return result;
}

bool CItemModelUserInstrumentInfo::setData( const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/ )
{
	if (role != Qt::EditRole)
		return false;

	CItemUserInstrumentInfo *item = _GetItem(index);
	bool result = item->setData(index.column(), value);

	if (result)
	{
		emit dataChanged(index, index);
	}

	return result;
}


//QT_END_NAMESPACE


















