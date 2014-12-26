#include "ClientMainWindow.h"

#include "ClientMainWindowMenuBar.h"
#include "ClientMainWindowToolBar.h"
#include "ClientMainWindowMdiArea.h"


static int DEFVALUE_INT_Window_Width = 800;
static int DEFVALUE_INT_Window_Height = 600;

static const std::string DEFVALUE_String_CSmartTraderClientMainWindow_Title = "SmartTrader";
static const  std::string DEF_VALUE_MainWidgetWindowIcon = ":/images/MainWidgetWindowIcon.ico";//任务栏中的图标


CClientMainWindow::CClientMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);

	m_pClientMainWindowMenuBar = NULL;
	m_pClientMainWindowToolBar = NULL;
	m_pClientMainWindowMdiArea = NULL;
	_SetupUi();
}

CClientMainWindow::~CClientMainWindow()
{

}


void CClientMainWindow::closeEvent( QCloseEvent* pEvent )
{
	pEvent->accept();
	emit signal_Exit_ClientMainWindow();
}


void CClientMainWindow::_CreateMenuBar()
{
	m_pClientMainWindowMenuBar = new CClientMainWindowMenuBar(this);
	this->setMenuBar(m_pClientMainWindowMenuBar);
}

void CClientMainWindow::_CreateToolBars()
{
	m_pClientMainWindowToolBar = new CClientMainWindowToolBar(this);
	this->addToolBar(Qt::TopToolBarArea, m_pClientMainWindowToolBar);
}
void CClientMainWindow::_CreateMdiArea()
{
	m_pClientMainWindowMdiArea = new CClientMainWindowMdiArea(this);
	this->setCentralWidget(m_pClientMainWindowMdiArea);

}

void CClientMainWindow::_SetupUi()
{
	this->setWindowIcon(QIcon(QObject::tr(DEF_VALUE_MainWidgetWindowIcon.c_str())));//任务栏中的图标

	_CreateMenuBar();
	_CreateToolBars();
	_CreateMdiArea();

}
void CClientMainWindow::_TranslateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_CSmartTraderClientMainWindow_Title.c_str()));

}

