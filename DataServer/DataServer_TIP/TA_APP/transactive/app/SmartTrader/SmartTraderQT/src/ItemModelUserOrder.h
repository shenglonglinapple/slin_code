#ifndef __CLASS_ITEM_MODEL_USER_INSTRUMENT_HH__
#define __CLASS_ITEM_MODEL_USER_INSTRUMENT_HH__




#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>

class CItemUserOrder;


class CItemModelUserOrder : public QAbstractItemModel
{
    Q_OBJECT

public:
    CItemModelUserOrder(QObject* parent = 0);
    ~CItemModelUserOrder();
public:
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;

public:
	void setRootItem(CItemUserOrder* rootItem);
private:
	CItemUserOrder* _GetItem( const QModelIndex& index ) const;
private:
    CItemUserOrder* m_pRootItemRef;
};


//QT_END_NAMESPACE

#endif//__CLASS_ITEM_MODEL_USER_INSTRUMENT_HH__
