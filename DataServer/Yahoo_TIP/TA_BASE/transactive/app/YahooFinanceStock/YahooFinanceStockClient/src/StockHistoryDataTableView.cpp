#include "StockHistoryDataTableView.h"

#include <QtSql/QSqlTableModel>

#include "DataStockHistoryData.h"
#include "SignalSlotManager.h"
#include "ClientDBManager.h"
#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 500;

static const char*  str_TABLE_BAR_DATA_1DAY = "TABLE_BAR_DATA_1DAY";


CStockHistoryDataTableView::CStockHistoryDataTableView( QWidget* parent)
{
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);//mdi not work

	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);

	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setAlternatingRowColors(true);
	this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	this->resizeColumnsToContents();

	m_pItemModel = NULL;
	m_pItemModel = new QSqlTableModel(this, *(CClientDBManager::getInstance().getDB()));
	m_pItemModel->setTable(str_TABLE_BAR_DATA_1DAY);
	m_pItemModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pItemModel->select();
	
	this->setModel((QAbstractItemModel *)m_pItemModel);
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	CSignalSlotManager::getInstance().set_Slot_DataChange_StockHistoryData(this);


}

CStockHistoryDataTableView::~CStockHistoryDataTableView()
{
	CSignalSlotManager::getInstance().set_Slot_DataChange_StockHistoryData(NULL);

	if (NULL != m_pItemModel)
	{
		delete m_pItemModel;
		m_pItemModel = NULL;
	}


}

void CStockHistoryDataTableView::slot_DataChange_StockHistoryData()
{

	MYLOG4CPP_DEBUG<<"CStockHistoryDataTableView process slot_DataChange_StockHistoryData";

	if (NULL != m_pItemModel)
	{
		m_pItemModel->select();
	}

	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	this->resizeColumnsToContents();
}
