#include "ItemModelInstrumentInfo.h"


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

#include "ItemInstrumentInfo.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


CItemModelInstrumentInfo::CItemModelInstrumentInfo(QObject *parent)
    : QAbstractItemModel(parent)
{
	m_pRootItemRef = NULL;
}


CItemModelInstrumentInfo::~CItemModelInstrumentInfo()
{
	m_pRootItemRef = NULL;
}



int CItemModelInstrumentInfo::columnCount(const QModelIndex &parent) const
{
	int nColumnCount = 0;

    if (parent.isValid())
	{
        nColumnCount = static_cast<CItemInstrumentInfo*>(parent.internalPointer())->columnCount();
	}
    else
	{
        nColumnCount = m_pRootItemRef->columnCount();
	}

	return nColumnCount;
}



QVariant CItemModelInstrumentInfo::data(const QModelIndex &index, int role) const
{
	CItemInstrumentInfo* item = NULL;

    if (!index.isValid())
	{
        return QVariant();
	}

    if (role != Qt::DisplayRole)
	{
        return QVariant();
	}

    item = static_cast<CItemInstrumentInfo*>(index.internalPointer());

    return item->data(index.column());
}



Qt::ItemFlags CItemModelInstrumentInfo::flags(const QModelIndex &index) const
{
	Qt::ItemFlags nFlagsTreeItem;
	CItemInstrumentInfo* pTreeItem = NULL;
	CItemInstrumentInfo::enDataTypeContract nDataTypeExchange = CItemInstrumentInfo::DataTypeContract_InstrumentCode;

    if (!index.isValid())
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

    //return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

	pTreeItem = static_cast<CItemInstrumentInfo*>(index.internalPointer());

	if (NULL == pTreeItem)
	{
		nFlagsTreeItem = Qt::NoItemFlags;
		return nFlagsTreeItem;
	}

	nDataTypeExchange = pTreeItem->getDataType();
	if (CItemInstrumentInfo::DataTypeContract_InstrumentCode == nDataTypeExchange)
	{
		//nFlagsTreeItem = Qt::ItemIsEditable;
		nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable |  Qt::ItemIsEditable;
		return nFlagsTreeItem;
	}

	nFlagsTreeItem = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	return nFlagsTreeItem;
}



QVariant CItemModelInstrumentInfo::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		//return QVariant();
        //return rootItemCopy->data(section);
		return QVariant("root_column");
	}

    return QVariant();
}



QModelIndex CItemModelInstrumentInfo::index(int row, int column, const QModelIndex &parent) const
{
	CItemInstrumentInfo* parentItem = NULL;
	CItemInstrumentInfo* childItem = NULL;

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
        parentItem = static_cast<CItemInstrumentInfo*>(parent.internalPointer());
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



QModelIndex CItemModelInstrumentInfo::parent(const QModelIndex &index) const
{
	CItemInstrumentInfo* childItem = NULL;
	CItemInstrumentInfo* parentItem = NULL;

    if (!index.isValid())
	{
        return QModelIndex();
	}

    childItem = static_cast<CItemInstrumentInfo*>(index.internalPointer());
    parentItem = childItem->parent();

    if (parentItem == m_pRootItemRef)
	{
        return QModelIndex();
	}

    return createIndex(parentItem->row(), 0, parentItem);
}



int CItemModelInstrumentInfo::rowCount(const QModelIndex &parent) const
{
    CItemInstrumentInfo* parentItem = NULL;
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
        parentItem = static_cast<CItemInstrumentInfo*>(parent.internalPointer());
	}

    return parentItem->childCount();
}

void CItemModelInstrumentInfo::setRootItem( CItemInstrumentInfo* rootItem )
{
	m_pRootItemRef = rootItem;
	reset();
}


bool CItemModelInstrumentInfo::removeRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ )
{
	CItemInstrumentInfo* parentItem = _GetItem(parent);
	bool success = true;
	int nRemoveRowNum = 1;

	beginRemoveRows(parent, position, position + nRemoveRowNum - 1);
	success = parentItem->removeChildren(position);
	endRemoveRows();

	return success;
}


CItemInstrumentInfo* CItemModelInstrumentInfo::_GetItem( const QModelIndex& index ) const
{
	CItemInstrumentInfo *item = NULL;

	if (index.isValid()) 
	{
		item = static_cast<CItemInstrumentInfo*>(index.internalPointer());
		if (NULL != item) 
		{
			return item;
		}
	}

	return m_pRootItemRef;
}


//QT_END_NAMESPACE



















