#include <QTableView>
#include <QAbstractTableModel>
#include <QItemDelegate>
#include <QStringList>
#include <QPainter>
#include <QHeaderView>

/********************ProgressBarDelegate********************/
class ProgressBarDelegate : public QItemDelegate
{
    Q_OBJECT

public:

    ProgressBarDelegate(QObject* parent = 0);
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

};

/********************TableModel********************/
class TableModel : public QAbstractTableModel 
{
    Q_OBJECT

public:

    TableModel(QObject *parent = 0);
    ~TableModel(void);
    void setHorizontalHeaderList(QStringList horizontalHeaderList);
    void setVerticalHeaderList(QStringList verticalHeaderList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;  
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void setModalDatas(QList< QStringList > *rowlist);
    void refrushModel();

signals:

	void updateCount(int count);

private:

    QStringList horizontal_header_list;
    QStringList vertical_header_list;
    QList< QStringList > *arr_row_list;

};

/********************ReadOnlyTableView********************/
class TableView : public QTableView
{
    Q_OBJECT

public:

    TableView(QWidget *parent=0);
    ~TableView(void);
    void addRow(QStringList rowList);
	int rowCount();

signals:

	void updateCount(int count);

public slots:

	void remove();
	void clear();
	void changeValue();

private:

    void initHeader();

private:

    TableModel *model;
    QList< QStringList > grid_data_list;
    ProgressBarDelegate *progressbar_delegate;

};
