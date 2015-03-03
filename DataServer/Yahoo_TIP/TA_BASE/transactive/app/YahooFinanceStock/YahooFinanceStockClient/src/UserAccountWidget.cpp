#include "UserAccountWidget.h"

#include <QtSql/QSqlTableModel>
#include "ProjectDBStruct.h"
#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"
#include "ClientDBManager.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 200;



CUserAccountWidget::CUserAccountWidget( QWidget* parent)
{
	QModelIndex inValidIndex;
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);//mdi not work

	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);

	QGridLayout* pGridLayout = NULL;

	m_pUserAccountTableView = NULL;
	m_pUserAccountModel = NULL;
	m_pUserHoldAccountTableView = NULL;
	m_pUserHoldAccountModel = NULL;

	m_pUserAccountTableView = new QTableView(this);
	m_pUserAccountTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pUserAccountTableView->setAlternatingRowColors(true);
	m_pUserAccountTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_pUserAccountTableView->resizeColumnsToContents();

	m_pUserAccountModel = new QSqlTableModel(this, *(CClientDBManager::getInstance().getDB()));
	m_pUserAccountModel->setTable(str_TABLE_USER_ACCOUNT);
	m_pUserAccountModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pUserAccountModel->select();

	m_pUserAccountTableView->setModel(m_pUserAccountModel);
	m_pUserAccountTableView->setCurrentIndex(inValidIndex);
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserAccount(this);


	m_pUserHoldAccountTableView = new QTableView(this);
	m_pUserHoldAccountTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pUserHoldAccountTableView->setAlternatingRowColors(true);
	m_pUserHoldAccountTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_pUserHoldAccountTableView->resizeColumnsToContents();

	m_pUserHoldAccountModel = new QSqlTableModel(this, *(CClientDBManager::getInstance().getDB()));
	m_pUserHoldAccountModel->setTable(str_TABLE_USER_HOLD_ACCOUNT);
	m_pUserHoldAccountModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pUserHoldAccountModel->select();

	m_pUserHoldAccountTableView->setModel(m_pUserHoldAccountModel);
	m_pUserHoldAccountTableView->setCurrentIndex(inValidIndex);
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserHoldAccount(this);

	pGridLayout = new QGridLayout(this);
	pGridLayout->addWidget(m_pUserAccountTableView, 0, 0, 1, 1);
	pGridLayout->addWidget(m_pUserHoldAccountTableView, 2, 0, 1, 1);

	_CreateAction();
	_CreateConnect();

}

CUserAccountWidget::~CUserAccountWidget()
{
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserAccount(NULL);
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserHoldAccount(NULL);
}
void CUserAccountWidget::_CreateAction()
{
	//action
}
void CUserAccountWidget::_CreateConnect()
{
}

void CUserAccountWidget::slot_DataChange_UserAccount()
{
	MYLOG4CPP_DEBUG<<"CUserAccountWidget process slot_DataChange_UserAccount";
	if (NULL != m_pUserAccountModel)
	{
		m_pUserAccountModel->select();
	}
	QModelIndex inValidIndex;
	m_pUserAccountTableView->setCurrentIndex(inValidIndex);
	m_pUserAccountTableView->resizeColumnsToContents();
}

void CUserAccountWidget::slot_DataChange_UserHoldAccount()
{
	MYLOG4CPP_DEBUG<<"CUserAccountWidget process slot_DataChange_UserHoldAccount";
	if (NULL != m_pUserHoldAccountModel)
	{
		m_pUserHoldAccountModel->select();
	}
	QModelIndex inValidIndex;
	m_pUserHoldAccountTableView->setCurrentIndex(inValidIndex);
	m_pUserHoldAccountTableView->resizeColumnsToContents();

}

