#ifndef __CLASS_TREE_MODEL_ORDER_HH__
#define __CLASS_TREE_MODEL_ORDER_HH__




#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include "TreeItemOrder.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CTreeModelOrder : public QAbstractItemModel
{
    Q_OBJECT

public:
    CTreeModelOrder(QObject* parent = 0);
    ~CTreeModelOrder();
public:
    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

	Qt::ItemFlags flags(const QModelIndex &index) const;

public:
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

	bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole);

	bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex());

	bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex());

	bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());

	bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());;
public:
	void setRootItem(CTreeItemOrder* rootItem);
private:
	CTreeItemOrder* _GetItem( const QModelIndex& index ) const;
private:
    CTreeItemOrder* m_pRootItemCopy;
};


//QT_END_NAMESPACE

#endif//__CLASS_TREE_MODEL_ORDER_HH__
