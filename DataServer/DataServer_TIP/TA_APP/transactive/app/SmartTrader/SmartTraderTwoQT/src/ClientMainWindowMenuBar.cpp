#include "ClientMainWindowMenuBar.h"

static const std::string DEFVALUE_String_Window_Menu_Files_Text = "File";
static const std::string DEFVALUE_String_Window_Menu_Files_Action_ReConnect_Text = "ReConnect";
static const std::string DEFVALUE_String_Window_Menu_Files_Action_ChangePassword_Text = "Change Password";
static const std::string DEFVALUE_String_Window_Menu_Files_Action_Exit_Text = "Exit";

static const std::string DEFVALUE_String_Window_Menu_View_Text = "View";
static const std::string DEFVALUE_String_Window_Menu_Charts_Text = "Charts";
static const std::string DEFVALUE_String_Window_Menu_Tools_Text = "Tools";
static const std::string DEFVALUE_String_Window_Menu_Window_Text = "Window";
static const std::string DEFVALUE_String_Window_Menu_Help_Text = "Help";



CClientMainWindowMenuBar::CClientMainWindowMenuBar(QWidget *parent)
    : QMenuBar(parent)
{
    //this->resize(200, 300);

	m_pAction_ReConnect = NULL;
	m_pAction_ChangePassword = NULL;
	m_pAction_Exit = NULL;

	m_Menu_Files = NULL;
	m_Menu_View = NULL;
	m_Menu_Insert = NULL;
	m_Menu_Tools = NULL;
	m_Menu_Window = NULL;
	m_Menu_Help = NULL;


	_CreateActions();
	_CreateMenus();
	_TranslateLanguage();
}

CClientMainWindowMenuBar::~CClientMainWindowMenuBar()
{

}
void CClientMainWindowMenuBar::_CreateActions()
{
	//Menu Files
	m_pAction_ReConnect = new QAction(this); 
	m_pAction_ChangePassword = new QAction(this); 
	m_pAction_Exit = new QAction(this); 
}
void CClientMainWindowMenuBar::_CreateMenus()
{
	m_Menu_Files = this->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Files_Text.c_str()));
	m_Menu_View = this->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_View_Text.c_str()));
	m_Menu_Insert = this->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Charts_Text.c_str()));
	m_Menu_Tools = this->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Tools_Text.c_str()));
	m_Menu_Window = this->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Window_Text.c_str()));
	m_Menu_Help = this->addMenu(QObject::tr(DEFVALUE_String_Window_Menu_Help_Text.c_str()));


	m_Menu_Files->addAction(m_pAction_ReConnect);
	m_Menu_Files->addAction(m_pAction_ChangePassword);
	m_Menu_Files->addAction(m_pAction_Exit);
}

void CClientMainWindowMenuBar::_TranslateLanguage()
{
	m_pAction_ReConnect->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_ReConnect_Text.c_str()));
	m_pAction_ChangePassword->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_ChangePassword_Text.c_str()));
	m_pAction_Exit->setText(QObject::tr(DEFVALUE_String_Window_Menu_Files_Action_Exit_Text.c_str()));

}
