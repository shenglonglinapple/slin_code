#include "StockMinTimeMaxTimeTableView.h"

#include <QtSql/QSqlTableModel>

#include "ProjectQTInclude.h"

#include "SignalSlotManager.h"
#include "ClientDataManager.h"
#include "ClientDBManager.h"


#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 500;

static const char* DEFVALUE_String_ActionReqHistoryData = "ReqHistoryData";


static const char*  str_TABLE_MINTIME_MAXTIME = "TABLE_MINTIME_MAXTIME";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE = "SymbolUse";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME = "MinTime";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME = "MaxTime";
static const char*  str_TABLE_MINTIME_MAXTIME_COLUMN_COUNT = "Count";


CStockMinTimeMaxTimeTableView::CStockMinTimeMaxTimeTableView( QWidget* parent)
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
	m_pItemModel->setTable(str_TABLE_MINTIME_MAXTIME);
	m_pItemModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pItemModel->select();

	this->setModel((QAbstractItemModel *)m_pItemModel);
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	CSignalSlotManager::getInstance().set_Slot_DataChange_StockMinTimeMaxTime(this);


	m_pActionReqHistoryData = NULL;
	_CreateAction();
	_CreateConnect();

}

CStockMinTimeMaxTimeTableView::~CStockMinTimeMaxTimeTableView()
{
	CSignalSlotManager::getInstance().set_Slot_DataChange_StockMinTimeMaxTime(NULL);

	if (NULL != m_pItemModel)
	{
		delete m_pItemModel;
		m_pItemModel = NULL;
	}

	if (NULL != m_pActionReqHistoryData)
	{
		delete m_pActionReqHistoryData;
		m_pActionReqHistoryData = NULL;
	}
}
void CStockMinTimeMaxTimeTableView::_CreateAction()
{
	//action
	m_pActionReqHistoryData = new QAction(QObject::tr(DEFVALUE_String_ActionReqHistoryData), this); 

}
void CStockMinTimeMaxTimeTableView::_CreateConnect()
{
	QObject::connect(m_pActionReqHistoryData, SIGNAL(triggered()), 
		this, SLOT(slotActionReqHistoryData())); 
}

void CStockMinTimeMaxTimeTableView::slot_DataChange_StockMinTimeMaxTime()
{

	MYLOG4CPP_DEBUG<<"CStockMinTimeMaxTimeTableView process slot_DataChange_StockMinTimeMaxTime";

	if (NULL != m_pItemModel)
	{
		m_pItemModel->select();
	}
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	this->resizeColumnsToContents();

}

void CStockMinTimeMaxTimeTableView::contextMenuEvent( QContextMenuEvent* pEvent )
{
	MYLOG4CPP_DEBUG<<"CStockMinTimeMaxTimeTableView contextMenuEvent";
	QModelIndex nCurrentIndex;
	nCurrentIndex = this->currentIndex();
	if (false == nCurrentIndex.isValid())
	{
		return;
	}
	//set menu pos
	QMenu menuRightClieck(this);
	menuRightClieck.addAction(m_pActionReqHistoryData);
	menuRightClieck.exec(QCursor::pos());
}

void CStockMinTimeMaxTimeTableView::slotActionReqHistoryData()
{
	QModelIndex nCurrentIndex;
	QString strSymbolUse;
	QString strTimeFrom;
	QString strTimeTo;
	int curRow = 0;
	int nColumnIndex = 0;

	nCurrentIndex = this->currentIndex();
	if (false == nCurrentIndex.isValid())
	{
		return;
	}
	QItemSelectionModel *selections = this->selectionModel(); //返回当前的选择模式  
	QModelIndexList selecteds = selections->selectedIndexes(); //返回所有选定的模型项目索引列表  
	foreach (QModelIndex index, selecteds)  
	{  
		curRow = index.row(); //删除所有被选中的行  
		QSqlRecord record = m_pItemModel->record(curRow); 
		strSymbolUse = record.value(str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE).toString();
		strTimeFrom = record.value(str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME).toString();
		strTimeTo = record.value(str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME).toString();
	}  
	MYLOG4CPP_DEBUG<<"CStockMinTimeMaxTimeTableView::slotActionReqHistoryData"<<" "<<"getNodeKey="<<strSymbolUse;

	if (!strSymbolUse.isEmpty())
	{
		CClientDataManager::getInstance().send_req_ReqStockHistoryData(strSymbolUse, strTimeFrom, strTimeTo);
	}
}
