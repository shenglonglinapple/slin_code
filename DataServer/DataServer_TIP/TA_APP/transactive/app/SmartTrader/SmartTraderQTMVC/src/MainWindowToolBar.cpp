#include "MainWindowToolBar.h"



static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Text = "BarInfo";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M1_Text = "M1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M5_Text = "M5";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M15_Text = "M15";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_M30_Text = "M30";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_H1_Text = "H1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_D1_Text = "D1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_W1_Text = "W1";
static const std::string DEFVALUE_String_Window_ToolBar_BarInfo_Action_MN_Text = "WN";


CMainWindowToolBar::CMainWindowToolBar( const QString &title, QWidget *parent /*= 0*/ )
:QToolBar(title, parent)
{
	_CreateActions();
	translateLanguage();
	_AddAction();
}

CMainWindowToolBar::CMainWindowToolBar( QWidget *parent /*= 0*/ )
:QToolBar(parent)
{
	_CreateActions();
	_AddAction();
}
void CMainWindowToolBar::_CreateActions()
{
	m_pAction_BarInfo_M1 = new QAction(this); 
	m_pAction_BarInfo_M5 = new QAction(this); 
	m_pAction_BarInfo_M15 = new QAction(this); 
	m_pAction_BarInfo_M30 = new QAction(this); 

	m_pAction_BarInfo_H1 = new QAction(this); 
	m_pAction_BarInfo_D1 = new QAction(this);
	m_pAction_BarInfo_W1 = new QAction(this);
	m_pAction_BarInfo_MN = new QAction(this);



}
void CMainWindowToolBar::_AddAction()
{	
	//m_ToolBar_BarInfo = addToolBar(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Text.c_str()));
	this->addAction(m_pAction_BarInfo_M1);
	this->addAction(m_pAction_BarInfo_M5);
	this->addAction(m_pAction_BarInfo_M15);
	this->addAction(m_pAction_BarInfo_M30);
	this->addAction(m_pAction_BarInfo_H1);
	this->addAction(m_pAction_BarInfo_D1);
	this->addAction(m_pAction_BarInfo_W1);
	this->addAction(m_pAction_BarInfo_MN);
}


void CMainWindowToolBar::translateLanguage()
{
	//
	m_pAction_BarInfo_M1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M1_Text.c_str()));
	m_pAction_BarInfo_M5->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M5_Text.c_str()));
	m_pAction_BarInfo_M15->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M15_Text.c_str()));
	m_pAction_BarInfo_M30->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_M30_Text.c_str()));
	m_pAction_BarInfo_H1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_H1_Text.c_str()));
	m_pAction_BarInfo_D1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_D1_Text.c_str()));
	m_pAction_BarInfo_W1->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_W1_Text.c_str()));
	m_pAction_BarInfo_MN->setText(QObject::tr(DEFVALUE_String_Window_ToolBar_BarInfo_Action_MN_Text.c_str()));


}
