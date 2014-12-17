#ifndef __CLASS_ITEM_MODEL_WAITING_INSTRUMENT_HH__
#define __CLASS_ITEM_MODEL_WAITING_INSTRUMENT_HH__




#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>

class CItemWaitingInstrument;


class CItemModelWaitingInstrument : public QAbstractItemModel
{
    Q_OBJECT

public:
    CItemModelWaitingInstrument(QObject* parent = 0);
    ~CItemModelWaitingInstrument();
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
	void setRootItem(CItemWaitingInstrument* rootItem);
private:
	CItemWaitingInstrument* _GetItem( const QModelIndex& index ) const;
private:
    CItemWaitingInstrument* m_pRootItemRef;
};


//QT_END_NAMESPACE

#endif//__CLASS_ITEM_MODEL_WAITING_INSTRUMENT_HH__
