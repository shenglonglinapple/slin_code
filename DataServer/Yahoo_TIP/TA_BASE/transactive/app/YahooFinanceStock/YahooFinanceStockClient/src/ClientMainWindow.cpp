#include "ClientMainWindow.h"

#include "ClientMainWindowMenuBar.h"
#include "ClientMainWindowToolBar.h"
#include "ClientMainWindowMdiArea.h"
#include "ClientMainWindowStatusBar.h"

#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 1000;
static int DEFVALUE_INT_Window_Height = 700;

static const char* DEFVALUE_String_CSmartTraderClientMainWindow_Title = "SmartTrader";
static const char* DEF_VALUE_MainWidgetWindowIcon = ":/images/MainWidgetWindowIcon.ico";//任务栏中的图标


CClientMainWindow::CClientMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);

	m_pClientMainWindowMenuBar = NULL;
	m_pClientMainWindowToolBar = NULL;
	m_pClientMainWindowStatusBar = NULL;
	m_pClientMainWindowMdiArea = NULL;
	_SetupUi();

}

CClientMainWindow::~CClientMainWindow()
{

}


void CClientMainWindow::closeEvent( QCloseEvent* pEvent )
{
	MYLOG4CPP_DEBUG<<"CClientMainWindow closeEvent pEvent=0x"<<pEvent;
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

void CClientMainWindow::_CreateStatusBars()
{
	m_pClientMainWindowStatusBar = new CClientMainWindowStatusBar(this);
	this->setStatusBar(m_pClientMainWindowStatusBar);

}

void CClientMainWindow::_CreateMdiArea()
{
	m_pClientMainWindowMdiArea = new CClientMainWindowMdiArea(this);
	this->setCentralWidget(m_pClientMainWindowMdiArea);

}

void CClientMainWindow::_SetupUi()
{
	//this->setWindowIcon(QIcon(QObject::tr(DEF_VALUE_MainWidgetWindowIcon.c_str())));//任务栏中的图标

	_CreateMenuBar();
	_CreateToolBars();
	_CreateMdiArea();
	_CreateStatusBars();

}
void CClientMainWindow::_TranslateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_CSmartTraderClientMainWindow_Title));

}

void CClientMainWindow::slotShowMessage( QString strMessage )
{
	MYLOG4CPP_DEBUG<<"class:"<<"CClientMainWindow"
		<<" "<<"slot:"<<"slotShowMessage"
		<<" "<<"param:"<<"strMessage="<<strMessage;

	if (NULL != m_pClientMainWindowStatusBar)
	{
		m_pClientMainWindowStatusBar->clearMessage();
		m_pClientMainWindowStatusBar->showMessage(strMessage);
	}

}

