#include "UserInstrumentTableView.h"
#include "ProjectQTInclude.h"
#include "DataUserInstrument.h"
#include "ItemUserInstrument.h"
#include "ItemModelUserInstrument.h"
#include "SignalSlotManager.h"
#include "WaitingInstrumentTreeView.h"

#include "Log4cppLogger.h"

static const int DEFVALUE_INT_Window_Width = 300;
static const int DEFVALUE_INT_Window_Height = 500;

static const std::string DEFVALUE_String_ActionAddHotQuotes = "AddQuotes";//"添加合约报价";
static const std::string DEFVALUE_String_ActionRemoveHotQuotes = "RemoveQuotes";//"从列表中移除此合约报价";
static const std::string DEFVALUE_String_ActionCustomColumns = "CustomColumns";//"自定义列";



CUserInstrumentTableView::CUserInstrumentTableView( QWidget* parent)
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);

	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);

	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->setAlternatingRowColors(true);
	this->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	this->resizeColumnsToContents();

	m_pItemModelUserInstrument = NULL;
	m_pItemModelUserInstrument = new CItemModelUserInstrument(this);
	m_pItemModelUserInstrument->setRootItem(CDataUserInstrument::getInstance().getRootItem());
	this->setModel(m_pItemModelUserInstrument);
	CSignalSlotManager::getInstance().set_SignalSlot_DataChange_UserInstrument(NULL, this);

	//action
	m_pActionAddUserInstrument = NULL;
	m_pActionRemoveUserInstrument = NULL;
	m_pActionCustomColumns = NULL;
	//
	m_pWaitingInstrumentTreeView = NULL;
	m_pWaitingInstrumentTreeView = new CWaitingInstrumentTreeView(this);

	_CreateAction();
	_CreateConnect();
}

CUserInstrumentTableView::~CUserInstrumentTableView()
{
	if (NULL != m_pActionAddUserInstrument)
	{
		delete m_pActionAddUserInstrument;
		m_pActionAddUserInstrument = NULL;
	}

	if (NULL != m_pActionRemoveUserInstrument)
	{
		delete m_pActionRemoveUserInstrument;
		m_pActionRemoveUserInstrument = NULL;
	}

	if (NULL != m_pActionCustomColumns)
	{
		delete m_pActionCustomColumns;
		m_pActionCustomColumns = NULL;
	}

	if (NULL != m_pItemModelUserInstrument)
	{
		delete m_pItemModelUserInstrument;
		m_pItemModelUserInstrument = NULL;
	}
}
void CUserInstrumentTableView::_CreateAction()
{
	//action
	m_pActionAddUserInstrument = new QAction(QObject::tr(DEFVALUE_String_ActionAddHotQuotes.c_str()), this); 
	m_pActionRemoveUserInstrument = new QAction(QObject::tr(DEFVALUE_String_ActionRemoveHotQuotes.c_str()), this); 
	m_pActionCustomColumns = new QAction(QObject::tr(DEFVALUE_String_ActionCustomColumns.c_str()), this); 


}
void CUserInstrumentTableView::_CreateConnect()
{
	QObject::connect(m_pActionAddUserInstrument, SIGNAL(triggered()), 
		this, SLOT(slotActionAddUserInstrument())); 

	QObject::connect(m_pActionRemoveUserInstrument, SIGNAL(triggered()), 
		this, SLOT(slotActionRemoveUserInstrument())); 

	QObject::connect(m_pActionCustomColumns, SIGNAL(triggered()), 
		this, SLOT(slotActionCustomColumns())); 
}

void CUserInstrumentTableView::slot_DataChange_UserInstrument()
{
	MYLOG4CPP_DEBUG<<"CUserInstrumentTableView process slot_DataChange_UserInstrument";
	QModelIndex inValidIndex;
	m_pItemModelUserInstrument->setRootItem(CDataUserInstrument::getInstance().getRootItem());
	this->setCurrentIndex(inValidIndex);
	this->resizeColumnsToContents();

}

void CUserInstrumentTableView::slotActionAddUserInstrument()
{
	MYLOG4CPP_DEBUG<<"CUserInstrumentTableView process slotActionAddUserInstrument";
	m_pWaitingInstrumentTreeView->move(QCursor::pos());
	m_pWaitingInstrumentTreeView->show();

}


void CUserInstrumentTableView::slotActionCustomColumns()
{
	MYLOG4CPP_DEBUG<<"CUserInstrumentInfoView process slotActionCustomColumns";
}

void CUserInstrumentTableView::slotActionRemoveUserInstrument()
{
	MYLOG4CPP_DEBUG<<"CUserInstrumentTableView process slotActionRemoveUserInstrument";

}

void CUserInstrumentTableView::contextMenuEvent( QContextMenuEvent* pEvent )
{
	MYLOG4CPP_DEBUG<<"CUserInstrumentTableView contextMenuEvent";

	QModelIndex nCurrentIndex;
	CItemUserInstrument* pCurrentItem = NULL;
	m_pWaitingInstrumentTreeView->resetData();

	nCurrentIndex = this->currentIndex();	

	if (false == nCurrentIndex.isValid())
	{
		//treeview line no data
		//set menu pos
		QMenu menuRightClieck(this);
		menuRightClieck.addAction(m_pActionAddUserInstrument);	//first ContractInfoWindow reset data
		menuRightClieck.exec(QCursor::pos());
		return;
	}

	//treeview line have data
	pCurrentItem = (CItemUserInstrument*)nCurrentIndex.internalPointer();
	MYLOG4CPP_DEBUG<<"CUserInstrumentTableView::contextMenuEvent"
		<<" "<<"getInstrumentID="<<pCurrentItem->getNodeKey();

	//set menu pos
	QMenu menuRightClieck(this);
	menuRightClieck.addAction(m_pActionAddUserInstrument);	//first ContractInfoWindow reset data
	menuRightClieck.addAction(m_pActionRemoveUserInstrument);
	menuRightClieck.addAction(m_pActionCustomColumns);
	menuRightClieck.exec(QCursor::pos());
}

