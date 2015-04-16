#include "UserHoldAccountWidget.h"

#include <QtSql/QSqlTableModel>
#include "ProjectDBStruct.h"
#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"
#include "ClientDBManager.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 200;
static char* DEFVALUE_WINDOW_TITLE = "UserHoldAccount";
//this->setWindowTitle(QObject::tr(DEFVALUE_WINDOW_TITLE));


CUserHoldAccountWidget::CUserHoldAccountWidget( QWidget* parent)
{
	QModelIndex inValidIndex;
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);//mdi not work

	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);
	this->setWindowTitle(QObject::tr(DEFVALUE_WINDOW_TITLE));

	QGridLayout* pGridLayout = NULL;

	m_pUserHoldAccountTableView = NULL;
	m_pUserHoldAccountModel = NULL;

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
	pGridLayout->addWidget(m_pUserHoldAccountTableView, 0, 0, 1, 1);

	_CreateAction();
	_CreateConnect();

}

CUserHoldAccountWidget::~CUserHoldAccountWidget()
{
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserHoldAccount(NULL);
}
void CUserHoldAccountWidget::_CreateAction()
{
	//action
}
void CUserHoldAccountWidget::_CreateConnect()
{
}

void CUserHoldAccountWidget::slot_DataChange_UserHoldAccount()
{
	MYLOG4CPP_DEBUG<<"CUserHoldAccountWidget process slot_DataChange_UserHoldAccount";
	if (NULL != m_pUserHoldAccountModel)
	{
		m_pUserHoldAccountModel->select();
	}
	QModelIndex inValidIndex;
	m_pUserHoldAccountTableView->setCurrentIndex(inValidIndex);
	m_pUserHoldAccountTableView->resizeColumnsToContents();

}

