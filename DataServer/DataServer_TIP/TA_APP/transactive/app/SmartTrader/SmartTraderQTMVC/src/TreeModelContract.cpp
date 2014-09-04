#include "TreeModelContract.h"


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


CTreeModelContract::CTreeModelContract(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemCopy = NULL;
}


CTreeModelContract::~CTreeModelContract()
{
	m_pRootItemCopy = NULL;
}



int CTreeModelContract::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CTreeItemContract*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemCopy->columnCount();
	}

	return nColumnCount;
}



QVariant CTreeModelContract::data(const QModelIndex &index, int role) const
{
	CTreeItemContract* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CTreeItemContract*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CTreeModelContract::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CTreeItemContract* pTreeItem = NULL;
	CTreeItemContract::enDataTypeContract nDataTypeExchange = CTreeItemContract::DataTypeContract_InstrumentCode;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CTreeItemContract*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

	nDataTypeExchange = pTreeItem->getDataType();
	if (CTreeItemContract::DataTypeContract_InstrumentCode == nDataTypeExchange)
	{
		//nFlagsTreeItem = Qt::ItemIsEditable;
		nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
		return nFlagsTreeItem;
	}

	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CTreeModelContract::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        //return rootItemCopy->data(section);
		return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CTreeModelContract::index(int row, int column, const QModelIndex &parent) const
{
	CTreeItemContract* parentItem = NULL;
	CTreeItemContract* childItem = NULL;

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
        parentItem = static_cast<CTreeItemContract*>(parent.internalPointer());
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



QModelIndex CTreeModelContract::parent(const QModelIndex &index) const
{
	CTreeItemContract* childItem = NULL;
	CTreeItemContract* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CTreeItemContract*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemCopy)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->row(), 0, parentItem);
}



int CTreeModelContract::rowCount(const QModelIndex &parent) const
{
    CTreeItemContract* parentItem = NULL;
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
        parentItem = static_cast<CTreeItemContract*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CTreeModelContract::setRootItem( CTreeItemContract* rootItem )
{
	m_pRootItemCopy = rootItem;
	reset();
}


bool CTreeModelContract::removeRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CTreeItemContract* parentItem = _GetItem(parent);
	bool success = true;
	int nRemoveRowNum = 1;

	beginRemoveRows(parent, position, position + nRemoveRowNum - 1);
	success = parentItem->removeChildren(position);
	endRemoveRows();

	return success;
}


CTreeItemContract* CTreeModelContract::_GetItem( const QModelIndex& index ) const
{
	CTreeItemContract *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CTreeItemContract*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemCopy;
}


//QT_END_NAMESPACE



















