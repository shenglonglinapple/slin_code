#include "table_view.h"
#include <QApplication>

/********************ProgressBarDelegate********************/
ProgressBarDelegate::ProgressBarDelegate(QObject *parent)
	: QItemDelegate(parent)
{

}

void ProgressBarDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(index.column() == 2)
    {
		int progress = index.model ()->data(index, Qt::DisplayRole).toInt ();
        QStyleOptionProgressBarV2 progressBarOption;
        progressBarOption.state = QStyle:: State_Enabled;
        progressBarOption.direction = QApplication:: layoutDirection ();
        progressBarOption.rect = option.rect;
        progressBarOption.fontMetrics = QApplication:: fontMetrics ();
        progressBarOption.minimum = 0;
        progressBarOption.maximum = 100;
        progressBarOption.textAlignment = Qt:: AlignCenter;
        progressBarOption.textVisible = true;
        progressBarOption.progress = progress;
        progressBarOption.text = QString("%1%").arg(progressBarOption.progress);
        QApplication:: style ()->drawControl(QStyle::CE_ProgressBar, &progressBarOption, painter);
    } else {
		return QItemDelegate::paint (painter, option, index);
	}
}

/********************TableModel********************/
TableModel::TableModel(QObject *parent)
	: QAbstractTableModel(parent), arr_row_list(NULL)
{

}

TableModel::~TableModel(void)
{
    arr_row_list = NULL;
}

void TableModel::setHorizontalHeaderList(QStringList horizontalHeaderList)
{
    horizontal_header_list = horizontalHeaderList;
}

void TableModel::setVerticalHeaderList(QStringList verticalHeaderList)
{
    vertical_header_list = verticalHeaderList;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    if(vertical_header_list.size() > 0)
        return vertical_header_list.size();

	if(NULL == arr_row_list)
		return 0;
	else
		return arr_row_list->size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    if(horizontal_header_list.size() > 0)
        return horizontal_header_list.size();

	if(NULL == arr_row_list)
		return 0;
	else if(arr_row_list->size() < 1)
		return 0;
	else
		return arr_row_list->at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(NULL == arr_row_list)
        return QVariant();

    if(arr_row_list->size() < 1)
        return QVariant();

    if (role == Qt::TextAlignmentRole) 
    {
        return int(Qt::AlignLeft | Qt::AlignVCenter);
    } 
    else if (role == Qt::DisplayRole) 
    {
        if(index.row() >= arr_row_list->size())
            return QVariant();
        if(index.column() >= arr_row_list->at(0).size())
            return QVariant();
        return arr_row_list->at(index.row()).at(index.column());
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role==Qt::DisplayRole)  
    {  
        if(orientation==Qt::Horizontal) // 水平表头  
        {  
            if(horizontal_header_list.size() > section)
                return horizontal_header_list[section];
            else
                return QVariant(); 
        }  
        else
        {
            if(vertical_header_list.size() > section)
                return vertical_header_list[section]; // 垂直表头  
            else
                return QVariant();
        }
    }  

    return QVariant(); 
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    Qt::ItemFlags flag = QAbstractItemModel::flags(index);  

    // flag|=Qt::ItemIsEditable // 设置单元格可编辑,此处注释,单元格无法被编辑  
    return flag;  
}

void TableModel::setModalDatas(QList< QStringList > *rowlist)
{
    arr_row_list = rowlist;
}

void TableModel::refrushModel()
{
    beginResetModel();
    endResetModel();

	emit updateCount(this->rowCount(QModelIndex()));
}

/********************TableView********************/
TableView::TableView(QWidget *parent)
	: QTableView(parent)
{
	this->setAlternatingRowColors(true);
	this->setStyleSheet( "QTableView{background-color: rgb(250, 250, 115);"   
		"alternate-background-color: rgb(141, 163, 215);}" ); 
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->horizontalHeader()->setStretchLastSection(true);
	this->horizontalHeader()->setHighlightSections(false); 
	this->verticalHeader()->setVisible(false);
	this->setShowGrid(false);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);

    model = new TableModel();
    this->setModel(model);
    this->initHeader();
    model->setModalDatas(&grid_data_list);
    progressbar_delegate = new ProgressBarDelegate();
    this->setItemDelegate(progressbar_delegate);

	connect(model, SIGNAL(updateCount(int)), this, SLOT(updateCount(int)));

    this->initHeader();
}

TableView::~TableView(void)
{
    if(progressbar_delegate) {
        delete progressbar_delegate;
        progressbar_delegate = NULL;
    }

    if(model) {
        delete model;
        model = NULL;
    }
    grid_data_list.clear();
}

void TableView::addRow(QStringList rowList)
{
    grid_data_list.append(rowList);
    model->refrushModel();
}

void TableView::remove()
{
	QModelIndexList model_index_list = this->selectedIndexes();
	int model_count = model_index_list.count();
	if(model_count <= 0)
		return;

	QList<int> list_row;
	for(int i=model_count-1; i>=0; i--)
	{
		QModelIndex model_index = model_index_list.at(i);
		int row = model_index.row();
		if(!list_row.contains(row))
			list_row.append(row);
	}

	if(list_row.isEmpty())
		return;

	qSort(list_row);

	for(int i=list_row.count()-1; i>=0; i--)
	{
		grid_data_list.removeAt(list_row.at(i));
	}

	model->refrushModel();
}

void TableView::clear()
{
	grid_data_list.clear();
	model->refrushModel();
}

int TableView::rowCount()
{
	return model->rowCount(QModelIndex());
}

void TableView::initHeader()
{
    QStringList header;
    header << tr("name") << tr("size") << tr("progress") << tr("speed") << tr("left time") << tr("state");
    model->setHorizontalHeaderList(header);
}

void TableView::changeValue()
{
	//这里以10行尾列进行更新
	int row_count = this->rowCount();
	if(row_count < 10)
		return;

	for(int i=0; i<10; i++)
	{
		QStringList file_list = grid_data_list.at(i);
		int progress = rand()%100;
		QStringList row_list;
		row_list <<  file_list.at(0) << file_list.at(1) << QString::number(progress) << file_list.at(3) << file_list.at(4) << file_list.at(5);
		grid_data_list.replace(i, row_list);
	}

	model->refrushModel();
}