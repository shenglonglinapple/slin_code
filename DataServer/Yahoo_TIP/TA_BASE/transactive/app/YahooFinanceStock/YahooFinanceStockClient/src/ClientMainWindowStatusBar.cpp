#include "ClientMainWindowStatusBar.h"

#include <QtGui/QAction>
#include "ProjectCommonData.h"
#include "Log4cppLogger.h"


static const char* DEFVALUE_String_Window_ToolBar_BarInfo_Text = "BarInfo";

static const char* DEFVALUE_String_Window_ToolBar_BarInfo_Action_D1_Text = "D1";



CClientMainWindowStatusBar::CClientMainWindowStatusBar( QWidget *parent /*= 0*/ )
:QStatusBar(parent)
{

}

CClientMainWindowStatusBar::~CClientMainWindowStatusBar()
{

}

