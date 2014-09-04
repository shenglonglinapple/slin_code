#include "TreeItem.h"
#include "TreeModel.h"


TreeModel::TreeModel(QObject *parent)
: QAbstractItemModel(parent)
{
	rootItemCopy = NULL;
}

TreeModel::~TreeModel()
{
	rootItemCopy = NULL;

}

void TreeModel::setRootItem(TreeItem *rootItem)
{
	rootItemCopy = rootItem;
	reset();
}


int TreeModel::columnCount(const QModelIndex & /* parent */) const
{
	return rootItemCopy->columnCount();
}


QVariant TreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return QVariant();

	TreeItem *item = getItem(index);

	return item->data(index.column());
}


Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
	if (index.isValid()) {
		TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
		if (item) return item;
	}
	return rootItemCopy;
}


QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
							   int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootItemCopy->data(section);

	return QVariant();
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	TreeItem *parentItem = getItem(parent);

	TreeItem *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}


bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
	bool success;

	beginInsertColumns(parent, position, position + columns - 1);
	success = rootItemCopy->insertColumns(position, columns);
	endInsertColumns();

	return success;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	TreeItem *parentItem = getItem(parent);
	bool success;

	beginInsertRows(parent, position, position + rows - 1);
	success = parentItem->insertChildren(position, rows, rootItemCopy->columnCount());
	endInsertRows();

	return success;
}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	TreeItem *childItem = getItem(index);
	TreeItem *parentItem = childItem->parent();

	if (parentItem == rootItemCopy)
		return QModelIndex();

	return createIndex(parentItem->childNumber(), 0, parentItem);
}


bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
	bool success;

	beginRemoveColumns(parent, position, position + columns - 1);
	success = rootItemCopy->removeColumns(position, columns);
	endRemoveColumns();

	if (rootItemCopy->columnCount() == 0)
		removeRows(0, rowCount());

	return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	TreeItem *parentItem = getItem(parent);
	bool success = true;

	beginRemoveRows(parent, position, position + rows - 1);
	success = parentItem->removeChildren(position, rows);
	endRemoveRows();

	return success;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
	TreeItem *parentItem = getItem(parent);

	return parentItem->childCount();
}


bool TreeModel::setData(const QModelIndex &index, const QVariant &value,
						int role)
{
	if (role != Qt::EditRole)
		return false;

	TreeItem *item = getItem(index);
	bool result = item->setData(index.column(), value);

	if (result)
		emit dataChanged(index, index);

	return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
							  const QVariant &value, int role)
{
	if (role != Qt::EditRole || orientation != Qt::Horizontal)
		return false;

	bool result = rootItemCopy->setData(section, value);

	if (result)
		emit headerDataChanged(orientation, section, section);

	return result;
}

