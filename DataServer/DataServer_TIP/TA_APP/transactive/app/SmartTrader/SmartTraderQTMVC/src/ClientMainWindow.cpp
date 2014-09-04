#include "ClientMainWindow.h"

#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "SmartHotQuotesWindow.h"
#include "ClientDataManagerWorker.h"
#include "TreeItemContract.h"
#include "QuotesTableView.h"
#include "ContractInfoWindow.h"

#include "BoostLogger.h"
USING_BOOST_LOG;


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


static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Text = "BarInfo";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M1_Text = "M1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M5_Text = "M5";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M15_Text = "M15";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M30_Text = "M30";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_H1_Text = "H1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_D1_Text = "D1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_W1_Text = "W1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_MN_Text = "WN";




static const  std::string DEF_VALUE_MainWidgetWindowIcon = ":/images/MainWidgetWindowIcon";//任务栏中的图标


CClientMainWindow::CClientMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
	m_pClientDataManagerWorker = NULL;
	m_pSmartHotQuotesWindow = NULL;
	m_pMdiArea = NULL;
	m_pClientDataManagerWorker = new CClientDataManagerWorker();

 	_CreateActions();
 	_CreateMenus();
 	_CreateToolBars();
    setupUi();
	translateLanguage();

	_CreateConnect();
}


CClientMainWindow::~CClientMainWindow()
{
	if (NULL != m_pClientDataManagerWorker)
	{
		m_pClientDataManagerWorker->terminateAndWait();
		delete m_pClientDataManagerWorker;
		m_pClientDataManagerWorker = NULL;
	}

}

void CClientMainWindow::_CreateActions()
{
	//Menu Files
	m_pAction_ReConnect = new QAction(this); 
	m_pAction_ChangePassword = new QAction(this); 
	m_pAction_Exit = new QAction(this); 

	m_pAction_BarInfo_M1 = new QAction(this); 
	m_pAction_BarInfo_M5 = new QAction(this); 
	m_pAction_BarInfo_M15 = new QAction(this); 
	m_pAction_BarInfo_M30 = new QAction(this); 

	m_pAction_BarInfo_H1 = new QAction(this); 
	m_pAction_BarInfo_D1 = new QAction(this);
	m_pAction_BarInfo_W1 = new QAction(this);
	m_pAction_BarInfo_MN = new QAction(this);



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
	m_ToolBar_BarInfo = addToolBar(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Text.c_str()));
	m_ToolBar_BarInfo->addAction(m_pAction_BarInfo_M1);
	m_ToolBar_BarInfo->addAction(m_pAction_BarInfo_M5);
	m_ToolBar_BarInfo->addAction(m_pAction_BarInfo_M15);
	m_ToolBar_BarInfo->addAction(m_pAction_BarInfo_M30);
	m_ToolBar_BarInfo->addAction(m_pAction_BarInfo_H1);
	m_ToolBar_BarInfo->addAction(m_pAction_BarInfo_D1);
	m_ToolBar_BarInfo->addAction(m_pAction_BarInfo_W1);
	m_ToolBar_BarInfo->addAction(m_pAction_BarInfo_MN);

}


void CClientMainWindow::_CreateConnect()
{
	//
	QObject::connect(m_pClientDataManagerWorker, 
		SIGNAL(signalContractInfoChanged (CTreeItemContract*)),
		m_pSmartHotQuotesWindow->m_pTreeView_Quotes->m_pContractInfoWindow,
		SLOT(slotContractInfoChanged(CTreeItemContract*)));


	//
	QObject::connect(m_pSmartHotQuotesWindow->m_pTreeView_Quotes->m_pContractInfoWindow, 
		SIGNAL(signalAddContractToSmartQuotes (unsigned int)),
		m_pClientDataManagerWorker,
		SLOT(slotAddContractToSmartQuotes(unsigned int)));


	//
	QObject::connect(m_pSmartHotQuotesWindow->m_pTreeView_Quotes, 
		SIGNAL(signalRemoveContractFromSmartQuotes (unsigned int)),
		m_pClientDataManagerWorker,
		SLOT(slotRemoveContractFromSmartQuotes(unsigned int)));

	QObject::connect(m_pSmartHotQuotesWindow->m_pTreeView_Quotes, 
		SIGNAL(signalQuotesTableViewColumnsChanged ()),
		m_pClientDataManagerWorker,
		SLOT(slotQuotesTableViewColumnsChanged()));


	QObject::connect(m_pClientDataManagerWorker, 
		SIGNAL(signalQuotesInfoChanged(CTreeItemQuotes*)), 
		m_pSmartHotQuotesWindow, 
		SLOT(slotQuotesInfoChanged(CTreeItemQuotes*))); 

}
void CClientMainWindow::setupUi()
{
	//left
	QDockWidget* m_DockWidgetFirst = NULL;
	Qt::DockWidgetArea nDockWidgetFirstArea;
	QWidget* pWindowOne = NULL;
	
	//add Samrt hot Quotes window
	m_pSmartHotQuotesWindow = new CSmartHotQuotesWindow(this);

	m_DockWidgetFirst = new QDockWidget(this);
	m_DockWidgetFirst->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_DockWidgetFirst->setWidget(m_pSmartHotQuotesWindow);

	//right
	pWindowOne = new QWidget(this);

	m_pMdiArea = new QMdiArea(this);
	m_pMdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_pMdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	m_pMdiArea->addSubWindow(pWindowOne);

	foreach (QMdiSubWindow *window, m_pMdiArea->subWindowList()) 
	{
		//TestChildWindow *mdiChild = qobject_cast<TestChildWindow *>(window->widget());
		window->resize(300, 300);
		m_pMdiArea->setActiveSubWindow(window);
	}


	nDockWidgetFirstArea = Qt::LeftDockWidgetArea;
	this->addDockWidget(nDockWidgetFirstArea, m_DockWidgetFirst);
	this->setCentralWidget(m_pMdiArea);

	this->setWindowIcon(QIcon(QObject::tr(DEF_VALUE_MainWidgetWindowIcon.c_str())));//任务栏中的图标
	//this->setWindowTitle(QObject::tr(DEFVALUE_String_CSmartTraderClientMainWindow_Title.c_str()));
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);


	m_DockWidgetFirst->setWindowTitle(QObject::tr("Market Watch:"));


	QMetaObject::connectSlotsByName(this);
} 


void CClientMainWindow::translateLanguage()
{
	//
	m_pAction_ReConnect->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_ReConnect_Text.c_str()));
	m_pAction_ChangePassword->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_ChangePassword_Text.c_str()));
	m_pAction_Exit->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_Exit_Text.c_str()));
	m_pAction_BarInfo_M1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M1_Text.c_str()));
	m_pAction_BarInfo_M5->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M5_Text.c_str()));
	m_pAction_BarInfo_M15->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M15_Text.c_str()));
	m_pAction_BarInfo_M30->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M30_Text.c_str()));
	m_pAction_BarInfo_H1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_H1_Text.c_str()));
	m_pAction_BarInfo_D1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_D1_Text.c_str()));
	m_pAction_BarInfo_W1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_W1_Text.c_str()));
	m_pAction_BarInfo_MN->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_MN_Text.c_str()));


	//
	this->setWindowTitle(QObject::tr(DEFVALUE_String_CSmartTraderClientMainWindow_Title.c_str()));
}


//QT_END_NAMESPACE

