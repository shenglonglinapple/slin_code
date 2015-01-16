#ifndef __CLASS_ITEM_MODEL_USER_TRADE_HH__
#define __CLASS_ITEM_MODEL_USER_TRADE_HH__

#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>

class CItemUserTrade;


class CItemModelUserTrade : public QAbstractItemModel
{
    Q_OBJECT

public:
    CItemModelUserTrade(QObject* parent = 0);
    ~CItemModelUserTrade();
public:
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;

public:
	void setRootItem(CItemUserTrade* rootItem);
private:
	CItemUserTrade* _GetItem( const QModelIndex& index ) const;
private:
    CItemUserTrade* m_pRootItemRef;
};



#endif//__CLASS_ITEM_MODEL_USER_TRADE_HH__
