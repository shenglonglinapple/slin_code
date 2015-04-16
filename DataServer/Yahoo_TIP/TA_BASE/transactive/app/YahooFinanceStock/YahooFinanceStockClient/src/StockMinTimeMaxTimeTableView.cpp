#include "StockMinTimeMaxTimeTableView.h"

#include <QtSql/QSqlTableModel>

#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"
#include "ProjectDBStruct.h"
#include "SignalSlotManager.h"
#include "ClientDataManager.h"
#include "ClientDBManager.h"
#include "NewOrderWindow.h"
#include "HistoryData.h"
#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 500;

static const char* DEFVALUE_String_ActionReqHistoryData = "ReqHistoryData";
static const std::string DEFVALUE_String_ActionNewOrder = "NewOrder";//"下单";
static char* DEFVALUE_WINDOW_TITLE = "StockMinTimeMaxTime";
//this->setWindowTitle(QObject::tr(DEFVALUE_WINDOW_TITLE));



CStockMinTimeMaxTimeTableView::CStockMinTimeMaxTimeTableView( QWidget* parent)
{
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);//mdi not work

	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);
	this->setWindowTitle(QObject::tr(DEFVALUE_WINDOW_TITLE));

	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setAlternatingRowColors(true);
	this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	this->resizeColumnsToContents();

	m_pItemModel = NULL;
	m_pItemModel = new QSqlTableModel(this, *(CClientDBManager::getInstance().getDB()));
	m_pItemModel->setTable(str_TABLE_MINTIME_MAXTIME);
	m_pItemModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pItemModel->setSort(0, Qt::AscendingOrder);
	m_pItemModel->select();

	this->setModel((QAbstractItemModel *)m_pItemModel);
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	CSignalSlotManager::getInstance().set_Slot_DataChange_StockMinTimeMaxTime(this);
	CSignalSlotManager::getInstance().set_Slot_DataChange_NewOrderData(this);

	m_pActionReqHistoryData = NULL;
	m_pActionNewOrder = NULL;
	m_pNewOrderWindow = NULL;
	_SetupUI();
	_CreateAction();
	_CreateConnect();

}

CStockMinTimeMaxTimeTableView::~CStockMinTimeMaxTimeTableView()
{
	CSignalSlotManager::getInstance().set_Slot_DataChange_StockMinTimeMaxTime(NULL);
	CSignalSlotManager::getInstance().set_Slot_DataChange_NewOrderData(NULL);

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
	if (NULL != m_pActionNewOrder)
	{
		delete m_pActionNewOrder;
		m_pActionNewOrder = NULL;
	}
}

void CStockMinTimeMaxTimeTableView::_SetupUI()
{
	m_pNewOrderWindow = new CNewOrderWindow(this);
	m_pNewOrderWindow->hide();
}
void CStockMinTimeMaxTimeTableView::_CreateAction()
{
	//action
	m_pActionReqHistoryData = new QAction(QObject::tr(DEFVALUE_String_ActionReqHistoryData), this); 
	m_pActionNewOrder = new QAction(QObject::tr(DEFVALUE_String_ActionNewOrder.c_str()), this); 

}
void CStockMinTimeMaxTimeTableView::_CreateConnect()
{
	QObject::connect(m_pActionReqHistoryData, SIGNAL(triggered()), 
		this, SLOT(slotActionReqHistoryData())); 
	QObject::connect(m_pActionNewOrder, SIGNAL(triggered()), 
		this, SLOT(slotActionNewOrder())); 

}

void CStockMinTimeMaxTimeTableView::slot_DataChange_StockMinTimeMaxTime()
{

	MYLOG4CPP_DEBUG<<"CStockMinTimeMaxTimeTableView process slot_DataChange_StockMinTimeMaxTime";

	if (NULL != m_pItemModel)
	{
		m_pItemModel->setSort(0, Qt::AscendingOrder);
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
	menuRightClieck.addAction(m_pActionNewOrder);
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
		curRow = index.row(); //被选中的行  
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

void CStockMinTimeMaxTimeTableView::slotActionNewOrder()
{
	MYLOG4CPP_DEBUG<<"CStockMinTimeMaxTimeTableView process slotActionNewOrder";
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
		curRow = index.row(); //被选中的行  
		QSqlRecord record = m_pItemModel->record(curRow); 
		strSymbolUse = record.value(str_TABLE_MINTIME_MAXTIME_COLUMN_SYMBOLUSE).toString();
		strTimeFrom = record.value(str_TABLE_MINTIME_MAXTIME_COLUMN_MINTIME).toString();
		strTimeTo = record.value(str_TABLE_MINTIME_MAXTIME_COLUMN_MAXTIME).toString();
	}  
	MYLOG4CPP_DEBUG<<"CStockMinTimeMaxTimeTableView::slotActionNewOrder"<<" "<<"getNodeKey="<<strSymbolUse;

	if (!strSymbolUse.isEmpty())
	{
		//get history data from server
		//CClientDataManager::getInstance().send_req_ReqStockHistoryData(strSymbolUse, strTimeFrom, strTimeTo);

		m_pNewOrderWindow->resetData(strSymbolUse, strTimeFrom, strTimeTo);
		m_pNewOrderWindow->move(QCursor::pos());
		m_pNewOrderWindow->show();
	}
}

void CStockMinTimeMaxTimeTableView::slot_DataChange_NewOrderData( CHistoryData* pData )
{
	m_pNewOrderWindow->resetPrice(pData->m_strDate, pData->m_strSymbolUse, pData->m_strClose.toDouble());


	if (NULL != pData)
	{
		delete pData;
		pData = NULL;
	}
}
