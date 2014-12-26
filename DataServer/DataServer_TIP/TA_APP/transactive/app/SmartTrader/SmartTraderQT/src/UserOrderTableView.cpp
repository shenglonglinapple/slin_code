#include "UserOrderTableView.h"
#include "ProjectQTInclude.h"
#include "ItemModelUserOrder.h"
#include "DataUserOrder.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"

static const int DEFVALUE_INT_Window_Width = 600;
static const int DEFVALUE_INT_Window_Height = 300;




CUserOrderTableView::CUserOrderTableView( QWidget* parent)
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);

	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);

	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setAlternatingRowColors(true);
	this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	this->resizeColumnsToContents();

	m_pItemModel = NULL;
	m_pItemModel = new CItemModelUserOrder(this);
	m_pItemModel->setRootItem(CDataUserOrder::getInstance().getRootItem());
	this->setModel(m_pItemModel);
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserOrder(this);

}

CUserOrderTableView::~CUserOrderTableView()
{
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserOrder(NULL);

	if (NULL != m_pItemModel)
	{
		delete m_pItemModel;
		m_pItemModel = NULL;
	}


}

void CUserOrderTableView::slot_DataChange_UserOrder()
{
	MYLOG4CPP_DEBUG<<"CUserOrderTableView process slot_DataChange_UserOrder";
	m_pItemModel->setRootItem(CDataUserOrder::getInstance().getRootItem());
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	this->resizeColumnsToContents();
}
