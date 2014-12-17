#include "ItemModelWaitingInstrument.h"


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

#include "ItemWaitingInstrument.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CItemModelWaitingInstrument::CItemModelWaitingInstrument(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemRef = NULL;
}


CItemModelWaitingInstrument::~CItemModelWaitingInstrument()
{
	m_pRootItemRef = NULL;
}



int CItemModelWaitingInstrument::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CItemWaitingInstrument*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemRef->columnCount();
	}

	return nColumnCount;
}



QVariant CItemModelWaitingInstrument::data(const QModelIndex &index, int role) const
{
	CItemWaitingInstrument* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CItemWaitingInstrument*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CItemModelWaitingInstrument::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CItemWaitingInstrument* pTreeItem = NULL;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CItemWaitingInstrument*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}


	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CItemModelWaitingInstrument::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        return m_pRootItemRef->data(section);
		//return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CItemModelWaitingInstrument::index(int row, int column, const QModelIndex &parent) const
{
	CItemWaitingInstrument* parentItem = NULL;
	CItemWaitingInstrument* childItem = NULL;

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
        parentItem = static_cast<CItemWaitingInstrument*>(parent.internalPointer());
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



QModelIndex CItemModelWaitingInstrument::parent(const QModelIndex &index) const
{
	CItemWaitingInstrument* childItem = NULL;
	CItemWaitingInstrument* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CItemWaitingInstrument*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemRef)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->childNumber(), 0, parentItem);
}



int CItemModelWaitingInstrument::rowCount(const QModelIndex &parent) const
{
    CItemWaitingInstrument* parentItem = NULL;
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
        parentItem = static_cast<CItemWaitingInstrument*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CItemModelWaitingInstrument::setRootItem( CItemWaitingInstrument* rootItem )
{
	m_pRootItemRef = rootItem;
	reset();
}


bool CItemModelWaitingInstrument::removeRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CItemWaitingInstrument* parentItem = _GetItem(parent);
	bool success = true;

	beginRemoveRows(parent, position, position + rows - 1);
	success = parentItem->removeChildren(position, rows);
	endRemoveRows();

	return success;
}


CItemWaitingInstrument* CItemModelWaitingInstrument::_GetItem( const QModelIndex& index ) const
{
	CItemWaitingInstrument *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CItemWaitingInstrument*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemRef;
}

bool CItemModelWaitingInstrument::insertRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CItemWaitingInstrument *parentItem = _GetItem(parent);
	bool success;

	beginInsertRows(parent, position, position + rows - 1);
	success = parentItem->insertChildren(position, rows, m_pRootItemRef->columnCount());
	endInsertRows();

	return success;
}

bool CItemModelWaitingInstrument::removeColumns( int position, int columns, const QModelIndex &parent /*= QModelIndex()*/ )
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

bool CItemModelWaitingInstrument::insertColumns( int position, int columns, const QModelIndex &parent /*= QModelIndex()*/ )
{
	bool success;

	beginInsertColumns(parent, position, position + columns - 1);
	success = m_pRootItemRef->insertColumns(position, columns);
	endInsertColumns();

	return success;
}

bool CItemModelWaitingInstrument::setHeaderData( int section, Qt::Orientation orientation, const QVariant &value, int role /*= Qt::EditRole*/ )
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

bool CItemModelWaitingInstrument::setData( const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/ )
{
	if (role != Qt::EditRole)
		return false;

	CItemWaitingInstrument *item = _GetItem(index);
	bool result = item->setData(index.column(), value);

	if (result)
	{
		emit dataChanged(index, index);
	}

	return result;
}


//QT_END_NAMESPACE


















