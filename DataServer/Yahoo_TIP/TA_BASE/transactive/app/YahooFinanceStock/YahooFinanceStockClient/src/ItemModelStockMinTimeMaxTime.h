#ifndef __CLASS_ITEM_MODEL_STOCK_MIN_TIME_MAX_TIME_HH__
#define __CLASS_ITEM_MODEL_STOCK_MIN_TIME_MAX_TIME_HH__




#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>

class CItemStockMinTimeMaxTime;


class CItemModelStockMinTimeMaxTime : public QAbstractItemModel
{
    Q_OBJECT

public:
    CItemModelStockMinTimeMaxTime(QObject* parent = 0);
    ~CItemModelStockMinTimeMaxTime();
public:
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;

public:
	void setRootItem(CItemStockMinTimeMaxTime* rootItem);
private:
	CItemStockMinTimeMaxTime* _GetItem( const QModelIndex& index ) const;
private:
    CItemStockMinTimeMaxTime* m_pRootItemRef;
};



#endif//__CLASS_ITEM_MODEL_STOCK_MIN_TIME_MAX_TIME_HH__
