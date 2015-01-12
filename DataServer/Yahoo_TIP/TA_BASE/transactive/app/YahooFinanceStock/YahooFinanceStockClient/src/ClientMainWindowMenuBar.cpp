#include "ClientMainWindowMenuBar.h"

#include "ClientLoginWindow.h"

#include "Log4cppLogger.h"

static const char* DEFVALUE_String_Window_Menu_Files_Text = "File";
static const char* DEFVALUE_String_Window_Menu_Files_Action_ConnectToServer_Text = "ConnectToServer";


CClientMainWindowMenuBar::CClientMainWindowMenuBar(QWidget *parent)
    : QMenuBar(parent)
{
    //this->resize(200, 300);
	m_pClientLoginWindow = NULL;

	m_Menu_Files = NULL;

	m_pAction_ConnectToServer = NULL;

	m_pClientLoginWindow = new CClientLoginWindow(this);

	_CreateActions();
	_CreateMenus();
	_TranslateLanguage();
	_CreateConnect();
}

CClientMainWindowMenuBar::~CClientMainWindowMenuBar()
{
	if (NULL != m_pClientLoginWindow)
	{
		delete m_pClientLoginWindow;
		m_pClientLoginWindow = NULL;
	}
}
void CClientMainWindowMenuBar::_CreateActions()
{
	//Menu Files
	m_pAction_ConnectToServer = new QAction(this); 
	m_pAction_ConnectToServer->setCheckable(true);
	m_pAction_ConnectToServer->setChecked(false);//default D1

}
void CClientMainWindowMenuBar::_CreateConnect()
{
	QObject::connect(m_pAction_ConnectToServer, SIGNAL(triggered()), 
		this, SLOT(slotActionConnectToServerTriggered()));

}
void CClientMainWindowMenuBar::_CreateMenus()
{
	m_Menu_Files = this->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Files_Text));


	m_Menu_Files->addAction(m_pAction_ConnectToServer);
}

void CClientMainWindowMenuBar::_TranslateLanguage()
{
	m_pAction_ConnectToServer->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_ConnectToServer_Text));
}

void CClientMainWindowMenuBar::slotActionConnectToServerTriggered()
{	
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<"CClientMainWindowMenuBar"
		<<" "<<"slot:"<<"slotActionConnectToServerTriggered()";

	m_pAction_ConnectToServer->setChecked(true);//default 
	//m_pAction_ConnectToServer->setCheckable(false);
	//m_pAction_ConnectToServer->trigger();//default 
	m_pClientLoginWindow->setVisible(true);

}
