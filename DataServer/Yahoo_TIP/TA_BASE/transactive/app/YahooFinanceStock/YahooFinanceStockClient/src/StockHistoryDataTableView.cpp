#include "StockHistoryDataTableView.h"

#include "DataStockHistoryData.h"
#include "ItemModelStockHistoryData.h"
#include "ItemStockHistoryData.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 500;


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
	m_pItemModel = new CItemModelStockHistoryData(this);
	m_pItemModel->setRootItem(CDataStockHistoryData::getInstance().getRootItem());
	this->setModel(m_pItemModel);
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
	m_pItemModel->setRootItem(CDataStockHistoryData::getInstance().getRootItem());
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	this->resizeColumnsToContents();

}
