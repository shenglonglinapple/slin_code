#include "StockMinTimeMaxTimeTableView.h"

#include "DataStockMinTimeMaxTime.h"
#include "ItemModelStockMinTimeMaxTime.h"
#include "ItemStockMinTimeMaxTime.h"
#include "SignalSlotManager.h"
#include "ClientDataManager.h"
#include "DataStockMinTimeMaxTime.h"
#include "StockMinTimeMaxTime.h"

#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 500;

static const char* DEFVALUE_String_ActionReqHistoryData = "ReqHistoryData";


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
	m_pItemModel = new CItemModelStockMinTimeMaxTime(this);
	m_pItemModel->setRootItem(CDataStockMinTimeMaxTime::getInstance().getRootItem());
	this->setModel(m_pItemModel);
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

	MYLOG4CPP_DEBUG<<"CStockMinTimeMaxTimeTableView process slot_DataChange";
	m_pItemModel->setRootItem(CDataStockMinTimeMaxTime::getInstance().getRootItem());
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	this->resizeColumnsToContents();

}

void CStockMinTimeMaxTimeTableView::contextMenuEvent( QContextMenuEvent* pEvent )
{
	MYLOG4CPP_DEBUG<<"CStockMinTimeMaxTimeTableView contextMenuEvent";
	QModelIndex nCurrentIndex;
	if (false == nCurrentIndex.isValid())
	{
		//treeview line no data
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
	CItemStockMinTimeMaxTime* pCurrentItem = NULL;
	CStockMinTimeMaxTime* pDataRef = NULL;
	nCurrentIndex = this->currentIndex();
	if (false == nCurrentIndex.isValid())
	{
		return;
	}
	pCurrentItem = (CItemStockMinTimeMaxTime*)nCurrentIndex.internalPointer();
	MYLOG4CPP_DEBUG<<"CStockMinTimeMaxTimeTableView::slotActionReqHistoryData"
		<<" "<<"getNodeKey="<<pCurrentItem->getNodeKey();

	pDataRef = CDataStockMinTimeMaxTime::getInstance().findNode(pCurrentItem->getNodeKey());
	if (NULL != pDataRef)
	{
		CClientDataManager::getInstance().send_req_ReqStockHistoryData(
			pDataRef->m_strSymbolUse, pDataRef->m_strMinTime, pDataRef->m_strMaxTime);
	}
}
