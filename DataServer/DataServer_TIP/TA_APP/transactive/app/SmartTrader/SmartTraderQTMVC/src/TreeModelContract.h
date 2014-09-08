#ifndef __CLASS_TREE_MODEL_CONTRACT_HH__
#define __CLASS_TREE_MODEL_CONTRACT_HH__




#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CTreeItemContract;


class CTreeModelContract : public QAbstractItemModel
{
    Q_OBJECT

public:
    CTreeModelContract(QObject* parent = 0);
    ~CTreeModelContract();
public:
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
public:
	bool removeRows( int position, int rows, const QModelIndex &parent /*= QModelIndex()*/ );

public:
	void setRootItem(CTreeItemContract* rootItem);
private:
	CTreeItemContract* _GetItem( const QModelIndex& index ) const;
private:
    CTreeItemContract* m_pRootItemCopy;
};
//QT_END_NAMESPACE


#endif//__CLASS_TREE_MODEL_CONTRACT_HH__
