#include "ClientMainWindow.h"

#include <QtGui/QTabWidget>
#include "ProjectQTInclude.h"
#include "Order.h"

#include "ClientDataManagerWorker.h"

#include "BottomDockWidget.h"
#include "MidSubWidget.h"
#include "SmartHotQuotesWindow.h"
#include "QuotesTableView.h"

#include "ContractInfoWindow.h"
#include "CreateNewOrderDialog.h"
#include "TreeItemOrder.h"
#include "TreeItemContract.h"
#include "HistoryDataManager.h"

#include "MainWindowToolBar.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 900;
static int DEFVALUE_INT_Window_Height = 700;



static const std::string DEFVALUE_String_CSmartTraderClientMainWindow_Title = "SmartTrader";

static const std::string DEFVALUE_String_Window_Menu_Files_Text = "File";
static const std::string DEFVALUE_String_Window_Menu_Files_Action_ReConnect_Text = "ReConnect";
static const std::string DEFVALUE_String_Window_Menu_Files_Action_ChangePassword_Text = "Change Password";
static const std::string DEFVALUE_String_Window_Menu_Files_Action_Exit_Text = "Exit";

static const std::string DEFVALUE_String_Window_Menu_View_Text = "View";
static const std::string DEFVALUE_String_Window_Menu_Charts_Text = "Charts";
static const std::string DEFVALUE_String_Window_Menu_Tools_Text = "Tools";
static const std::string DEFVALUE_String_Window_Menu_Window_Text = "Window";
static const std::string DEFVALUE_String_Window_Menu_Help_Text = "Help";






static const  std::string DEF_VALUE_MainWidgetWindowIcon = ":/images/MainWidgetWindowIcon";//任务栏中的图标


CClientMainWindow::CClientMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
	m_pLeftDockWidget = NULL;
	m_pBottomDockWidget = NULL;
	m_pMdiArea = NULL;
	m_pEastMidSubWidget = NULL;
	m_pMainWindowToolBar = NULL;

 	_CreateActions();
 	_CreateMenus();
 	_CreateToolBars();
    setupUi();
	translateLanguage();


	//m_pClientDataManagerWorker = NULL:
	//m_pClientDataManagerWorker = new CClientDataManagerWorker();
	_CreateConnect();
}


CClientMainWindow::~CClientMainWindow()
{
// 	if (NULL != m_pClientDataManagerWorker)
// 	{
// 		delete m_pClientDataManagerWorker;
// 		m_pClientDataManagerWorker = NULL;
// 	}

}

void CClientMainWindow::_CreateActions()
{
	//Menu Files
	m_pAction_ReConnect = new QAction(this); 
	m_pAction_ChangePassword = new QAction(this); 
	m_pAction_Exit = new QAction(this); 
}

void CClientMainWindow::_CreateMenus()
{
	m_Menu_Files = menuBar()->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Files_Text.c_str()));
	m_Menu_Files->addAction(m_pAction_ReConnect);
	m_Menu_Files->addAction(m_pAction_ChangePassword);
	m_Menu_Files->addAction(m_pAction_Exit);
	m_Menu_View = menuBar()->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_View_Text.c_str()));
	m_Menu_Insert = menuBar()->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Charts_Text.c_str()));
	m_Menu_Tools = menuBar()->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Tools_Text.c_str()));
	m_Menu_Window = menuBar()->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Window_Text.c_str()));
	m_Menu_Help = menuBar()->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Help_Text.c_str()));

}

void CClientMainWindow::_CreateToolBars()
{
	m_pMainWindowToolBar = new CMainWindowToolBar(this);
	this->addToolBar(m_pMainWindowToolBar);
	m_pMainWindowToolBar->show();
}


void CClientMainWindow::_CreateConnect()
{

}
void CClientMainWindow::setupUi()
{
	//left
	QDockWidget* m_DockWidget_Left = NULL;
	QDockWidget* m_DockWidget_Bottom = NULL;
	Qt::DockWidgetArea nDockWidgetFirstArea;
	m_pEastMidSubWidget = NULL;
	
	//add Samrt hot Quotes window
	m_pLeftDockWidget = new CLeftDockWidget(this);
	CSignalSlotManager::getInstance().setSignalSlot_QuotesInfoChanged(&(CClientDataManagerWorker::getInstance()), m_pLeftDockWidget);

	m_pBottomDockWidget = new CBottomDockWidget(this);
	CSignalSlotManager::getInstance().setSignalSlot_OrderInfoChanged(&(CClientDataManagerWorker::getInstance()), m_pBottomDockWidget);

	m_DockWidget_Left = new QDockWidget(this);
	m_DockWidget_Left->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_DockWidget_Left->setWidget(m_pLeftDockWidget);

	m_DockWidget_Bottom = new QDockWidget(this);
	m_DockWidget_Bottom->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
	m_DockWidget_Bottom->setWidget(m_pBottomDockWidget);

	
	//right
	m_pEastMidSubWidget = new CMidSubWidget(this);
	CSignalSlotManager::getInstance().setSignalSlot_HistoryDataChanged(&(CClientDataManagerWorker::getInstance()), m_pEastMidSubWidget);

	//East West South North

	m_pMdiArea = new QMdiArea(this);
	m_pMdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_pMdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_pMdiArea->addSubWindow(m_pEastMidSubWidget);

	foreach (QMdiSubWindow *window, m_pMdiArea->subWindowList()) 
	{
		//TestChildWindow *mdiChild = qobject_cast<TestChildWindow *>(window->widget());
		window->resize(300, 300);
		m_pMdiArea->setActiveSubWindow(window);
	}


	nDockWidgetFirstArea = Qt::LeftDockWidgetArea;
	this->addDockWidget(nDockWidgetFirstArea, m_DockWidget_Left);
	nDockWidgetFirstArea = Qt::BottomDockWidgetArea;
	this->addDockWidget(nDockWidgetFirstArea, m_DockWidget_Bottom);	
	this->setCentralWidget(m_pMdiArea);

	this->setWindowIcon(QIcon(QObject::tr(DEF_VALUE_MainWidgetWindowIcon.c_str())));//任务栏中的图标
	//this->setWindowTitle(QObject::tr(DEFVALUE_String_CSmartTraderClientMainWindow_Title.c_str()));
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);


	m_DockWidget_Left->setWindowTitle(QObject::tr("Market Watch:"));
	m_DockWidget_Bottom->setWindowTitle(QObject::tr("Order Info:"));
	//m_DockWidget_Bottom->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);


	QMetaObject::connectSlotsByName(this);
} 


void CClientMainWindow::translateLanguage()
{
	//
	m_pAction_ReConnect->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_ReConnect_Text.c_str()));
	m_pAction_ChangePassword->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_ChangePassword_Text.c_str()));
	m_pAction_Exit->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_Exit_Text.c_str()));
	//
	this->setWindowTitle(QObject::tr(DEFVALUE_String_CSmartTraderClientMainWindow_Title.c_str()));
}

