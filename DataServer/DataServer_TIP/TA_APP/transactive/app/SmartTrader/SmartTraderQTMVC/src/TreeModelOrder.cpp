#include "TreeModelOrder.h"


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


#include "TreeItemOrder.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CTreeModelOrder::CTreeModelOrder(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemCopy = NULL;
}


CTreeModelOrder::~CTreeModelOrder()
{
	m_pRootItemCopy = NULL;
}



int CTreeModelOrder::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CTreeItemOrder*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemCopy->columnCount();
	}

	return nColumnCount;
}



QVariant CTreeModelOrder::data(const QModelIndex &index, int role) const
{
	CTreeItemOrder* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CTreeItemOrder*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CTreeModelOrder::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CTreeItemOrder* pTreeItem = NULL;
	CTreeItemOrder::enItemDataType nDataType = CTreeItemOrder::ItemDataType_ITEM;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CTreeItemOrder*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

	nDataType = pTreeItem->getDataType();
	if (CTreeItemOrder::ItemDataType_ITEM == nDataType)
	{
		//nFlagsTreeItem = Qt::ItemIsEditable;
		nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
		return nFlagsTreeItem;
	}

	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CTreeModelOrder::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        return m_pRootItemCopy->data(section);
		//return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CTreeModelOrder::index(int row, int column, const QModelIndex &parent) const
{
	CTreeItemOrder* parentItem = NULL;
	CTreeItemOrder* childItem = NULL;

    if (!hasIndex(row, column, parent))
	{
        return QModelIndex();
	}

    if (!parent.isValid())
	{
        parentItem = m_pRootItemCopy;
	}
    else
	{
        parentItem = static_cast<CTreeItemOrder*>(parent.internalPointer());
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



QModelIndex CTreeModelOrder::parent(const QModelIndex &index) const
{
	CTreeItemOrder* childItem = NULL;
	CTreeItemOrder* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CTreeItemOrder*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemCopy)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->childNumber(), 0, parentItem);
}



int CTreeModelOrder::rowCount(const QModelIndex &parent) const
{
    CTreeItemOrder* parentItem = NULL;
    if (parent.column() > 0)
	{
        return 0;
	}

    if (!parent.isValid())
	{
        parentItem = m_pRootItemCopy;
	}
    else
	{
        parentItem = static_cast<CTreeItemOrder*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CTreeModelOrder::setRootItem( CTreeItemOrder* rootItem )
{
	m_pRootItemCopy = rootItem;
	reset();
}


bool CTreeModelOrder::removeRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CTreeItemOrder* parentItem = _GetItem(parent);
	bool success = true;

	beginRemoveRows(parent, position, position + rows - 1);
	success = parentItem->removeChildren(position, rows);
	endRemoveRows();

	return success;
}


CTreeItemOrder* CTreeModelOrder::_GetItem( const QModelIndex& index ) const
{
	CTreeItemOrder *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CTreeItemOrder*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemCopy;
}

bool CTreeModelOrder::insertRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CTreeItemOrder *parentItem = _GetItem(parent);
	bool success;

	beginInsertRows(parent, position, position + rows - 1);
	success = parentItem->insertChildren(position, rows, m_pRootItemCopy->columnCount());
	endInsertRows();

	return success;
}

bool CTreeModelOrder::removeColumns( int position, int columns, const QModelIndex &parent /*= QModelIndex()*/ )
{
	bool success;

	beginRemoveColumns(parent, position, position + columns - 1);
	success = m_pRootItemCopy->removeColumns(position, columns);
	endRemoveColumns();

	if (m_pRootItemCopy->columnCount() == 0)
	{
		removeRows(0, rowCount());
	}

	return success;
}

bool CTreeModelOrder::insertColumns( int position, int columns, const QModelIndex &parent /*= QModelIndex()*/ )
{
	bool success;

	beginInsertColumns(parent, position, position + columns - 1);
	success = m_pRootItemCopy->insertColumns(position, columns);
	endInsertColumns();

	return success;
}

bool CTreeModelOrder::setHeaderData( int section, Qt::Orientation orientation, const QVariant &value, int role /*= Qt::EditRole*/ )
{
	if (role != Qt::EditRole || orientation != Qt::Horizontal)
		return false;

	bool result = m_pRootItemCopy->setData(section, value);

	if (result)
	{
		emit headerDataChanged(orientation, section, section);
	}

	return result;
}

bool CTreeModelOrder::setData( const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/ )
{
	if (role != Qt::EditRole)
		return false;

	CTreeItemOrder *item = _GetItem(index);
	bool result = item->setData(index.column(), value);

	if (result)
	{
		emit dataChanged(index, index);
	}

	return result;
}


//QT_END_NAMESPACE


















