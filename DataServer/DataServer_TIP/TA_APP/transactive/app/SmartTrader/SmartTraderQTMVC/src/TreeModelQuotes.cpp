#include "TreeModelQuotes.h"


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


#include "TreeItemContract.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CTreeModelQuotes::CTreeModelQuotes(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemCopy = NULL;
}


CTreeModelQuotes::~CTreeModelQuotes()
{
	m_pRootItemCopy = NULL;
}



int CTreeModelQuotes::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CTreeItemQuotes*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemCopy->columnCount();
	}

	return nColumnCount;
}



QVariant CTreeModelQuotes::data(const QModelIndex &index, int role) const
{
	CTreeItemQuotes* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CTreeItemQuotes*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CTreeModelQuotes::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CTreeItemQuotes* pTreeItem = NULL;
	CTreeItemQuotes::enDataTypeSmartQuotes nDataType = CTreeItemQuotes::DataTypeSmartQuotes_Instrument;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CTreeItemQuotes*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

	nDataType = pTreeItem->getDataType();
	if (CTreeItemQuotes::DataTypeSmartQuotes_Instrument == nDataType)
	{
		//nFlagsTreeItem = Qt::ItemIsEditable;
		nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
		return nFlagsTreeItem;
	}

	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CTreeModelQuotes::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        return m_pRootItemCopy->data(section);
		//return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CTreeModelQuotes::index(int row, int column, const QModelIndex &parent) const
{
	CTreeItemQuotes* parentItem = NULL;
	CTreeItemQuotes* childItem = NULL;

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
        parentItem = static_cast<CTreeItemQuotes*>(parent.internalPointer());
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



QModelIndex CTreeModelQuotes::parent(const QModelIndex &index) const
{
	CTreeItemQuotes* childItem = NULL;
	CTreeItemQuotes* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CTreeItemQuotes*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemCopy)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->childNumber(), 0, parentItem);
}



int CTreeModelQuotes::rowCount(const QModelIndex &parent) const
{
    CTreeItemQuotes* parentItem = NULL;
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
        parentItem = static_cast<CTreeItemQuotes*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CTreeModelQuotes::setRootItem( CTreeItemQuotes* rootItem )
{
	m_pRootItemCopy = rootItem;
	reset();
}


bool CTreeModelQuotes::removeRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CTreeItemQuotes* parentItem = _GetItem(parent);
	bool success = true;

	beginRemoveRows(parent, position, position + rows - 1);
	success = parentItem->removeChildren(position, rows);
	endRemoveRows();

	return success;
}


CTreeItemQuotes* CTreeModelQuotes::_GetItem( const QModelIndex& index ) const
{
	CTreeItemQuotes *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CTreeItemQuotes*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemCopy;
}

bool CTreeModelQuotes::insertRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CTreeItemQuotes *parentItem = _GetItem(parent);
	bool success;

	beginInsertRows(parent, position, position + rows - 1);
	success = parentItem->insertChildren(position, rows, m_pRootItemCopy->columnCount());
	endInsertRows();

	return success;
}

bool CTreeModelQuotes::removeColumns( int position, int columns, const QModelIndex &parent /*= QModelIndex()*/ )
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

bool CTreeModelQuotes::insertColumns( int position, int columns, const QModelIndex &parent /*= QModelIndex()*/ )
{
	bool success;

	beginInsertColumns(parent, position, position + columns - 1);
	success = m_pRootItemCopy->insertColumns(position, columns);
	endInsertColumns();

	return success;
}

bool CTreeModelQuotes::setHeaderData( int section, Qt::Orientation orientation, const QVariant &value, int role /*= Qt::EditRole*/ )
{
	if (role != Qt::EditRole || orientation != Qt::Horizontal)
		return false;

	bool result = m_pRootItemCopy->setData(section, value);

	if (result)
		emit headerDataChanged(orientation, section, section);

	return result;
}

bool CTreeModelQuotes::setData( const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/ )
{
	if (role != Qt::EditRole)
		return false;

	CTreeItemQuotes *item = _GetItem(index);
	bool result = item->setData(index.column(), value);

	if (result)
		emit dataChanged(index, index);

	return result;
}


//QT_END_NAMESPACE


















