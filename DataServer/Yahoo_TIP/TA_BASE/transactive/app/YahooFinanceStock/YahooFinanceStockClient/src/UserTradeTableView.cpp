#include "UserTradeTableView.h"

#include <QtSql/QSqlTableModel>
#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"
#include "ClientDBManager.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 200;



CUserTradeTableView::CUserTradeTableView( QWidget* parent)
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
	m_pItemModel->setTable(str_TABLE_USER_TRADE_INFO);
	m_pItemModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pItemModel->select();

	this->setModel(m_pItemModel);
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserTrade(this);


	_CreateAction();
	_CreateConnect();

}

CUserTradeTableView::~CUserTradeTableView()
{
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserTrade(NULL);

	if (NULL != m_pItemModel)
	{
		delete m_pItemModel;
		m_pItemModel = NULL;
	}


}
void CUserTradeTableView::_CreateAction()
{
	//action
}
void CUserTradeTableView::_CreateConnect()
{
}

void CUserTradeTableView::slot_DataChange_UserTrade()
{
	MYLOG4CPP_DEBUG<<"CUserTradeTableView process slot_DataChange_UserTrade";
	if (NULL != m_pItemModel)
	{
		m_pItemModel->select();
	}
	QModelIndex inValidIndex;
	this->setCurrentIndex(inValidIndex);
	this->resizeColumnsToContents();
}

