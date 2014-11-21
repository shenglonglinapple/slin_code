#ifndef __CLASS_ITEM_MODEL_INSTRUMENT_INFO_HH__
#define __CLASS_ITEM_MODEL_INSTRUMENT_INFO_HH__




#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CItemInstrumentInfo;


class CItemModelInstrumentInfo : public QAbstractItemModel
{
    Q_OBJECT

public:
    CItemModelInstrumentInfo(QObject* parent = 0);
    ~CItemModelInstrumentInfo();
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
	void setRootItem(CItemInstrumentInfo* rootItem);
private:
	CItemInstrumentInfo* _GetItem( const QModelIndex& index ) const;
private:
    CItemInstrumentInfo* m_pRootItemRef;
};


#endif//__CLASS_ITEM_MODEL_INSTRUMENT_INFO_HH__
