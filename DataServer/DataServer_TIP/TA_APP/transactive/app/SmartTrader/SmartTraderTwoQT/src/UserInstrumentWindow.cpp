#include "UserInstrumentWindow.h"

#include "ProjectQTInclude.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 400;
static int DEFVALUE_INT_Window_Height = 300;



CUserInstrumentWindow::CUserInstrumentWindow(QWidget* parent)
    : QMdiSubWindow(parent)
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);


	
}


CUserInstrumentWindow::~CUserInstrumentWindow()
{

}


QSize CUserInstrumentWindow::sizeHint() const
{
	//for QDockWidget
	return QSize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height); /* 在这里定义dock的初始大小 */
}

