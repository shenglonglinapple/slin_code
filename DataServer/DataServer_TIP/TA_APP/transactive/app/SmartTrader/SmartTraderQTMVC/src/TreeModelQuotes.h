#ifndef __CLASS_TREE_MODEL_QUOTES_HH__
#define __CLASS_TREE_MODEL_QUOTES_HH__




#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include "TreeItemQuotes.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CTreeModelQuotes : public QAbstractItemModel
{
    Q_OBJECT

public:
    CTreeModelQuotes(QObject* parent = 0);
    ~CTreeModelQuotes();
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
	void setRootItem(CTreeItemQuotes* rootItem);
private:
	CTreeItemQuotes* _GetItem( const QModelIndex& index ) const;
private:
    CTreeItemQuotes* m_pRootItemCopy;
};


//QT_END_NAMESPACE

#endif//__CLASS_TREE_MODEL_CONTRACT_HH__
