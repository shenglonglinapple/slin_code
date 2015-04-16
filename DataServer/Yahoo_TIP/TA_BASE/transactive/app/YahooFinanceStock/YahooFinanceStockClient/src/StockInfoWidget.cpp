#include "StockInfoWidget.h"

#include <QtSql/QSqlTableModel>
#include "ProjectDBStruct.h"
#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"
#include "ClientDBManager.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 200;
static char* DEFVALUE_WINDOW_TITLE = "StockInfo";
//this->setWindowTitle(QObject::tr(DEFVALUE_WINDOW_TITLE));



CStockInfoWidget::CStockInfoWidget( QWidget* parent)
{
	QModelIndex inValidIndex;
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);//mdi not work

	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);
	this->setWindowTitle(QObject::tr(DEFVALUE_WINDOW_TITLE));

	QGridLayout* pGridLayout = NULL;

	m_pStockInfoTableView = NULL;
	m_pStockInfoModel = NULL;

	m_pStockInfoTableView = new QTableView(this);
	m_pStockInfoTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pStockInfoTableView->setAlternatingRowColors(true);
	m_pStockInfoTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_pStockInfoTableView->resizeColumnsToContents();

	m_pStockInfoModel = new QSqlTableModel(this, *(CClientDBManager::getInstance().getDB()));
	m_pStockInfoModel->setTable(str_TABLE_STOCKSSQLITE);
	m_pStockInfoModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pStockInfoModel->select();

	m_pStockInfoTableView->setModel(m_pStockInfoModel);
	m_pStockInfoTableView->setCurrentIndex(inValidIndex);
	CSignalSlotManager::getInstance().set_Slot_DataChange_StockInfo(this);


	pGridLayout = new QGridLayout(this);
	pGridLayout->addWidget(m_pStockInfoTableView, 0, 0, 1, 1);

	_CreateAction();
	_CreateConnect();

}

CStockInfoWidget::~CStockInfoWidget()
{
	CSignalSlotManager::getInstance().set_Slot_DataChange_StockInfo(NULL);
}
void CStockInfoWidget::_CreateAction()
{
	//action
}
void CStockInfoWidget::_CreateConnect()
{
}

void CStockInfoWidget::slot_DataChange_StockInfo()
{
	MYLOG4CPP_DEBUG<<"CStockInfoWidget process slot_DataChange_StockInfo";
	if (NULL != m_pStockInfoModel)
	{
		m_pStockInfoModel->select();
	}
	QModelIndex inValidIndex;
	m_pStockInfoTableView->setCurrentIndex(inValidIndex);
	m_pStockInfoTableView->resizeColumnsToContents();
}


