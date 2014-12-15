#include "ClientMainWindowMdiArea.h"
#include "UserInstrumentWindow.h"


CClientMainWindowMdiArea::CClientMainWindowMdiArea(QWidget *parent)
    : QMdiArea(parent)
{
    //this->resize(200, 300);
	m_pUserInstrumentWindow = NULL;

	_SetupUi();
	_TranslateLanguage();
}

CClientMainWindowMdiArea::~CClientMainWindowMdiArea()
{

}



void CClientMainWindowMdiArea::_SetupUi()
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_pUserInstrumentWindow = new CUserInstrumentWindow(this);
	this->addSubWindow(m_pUserInstrumentWindow);

	foreach (QMdiSubWindow *pSubWindow, this->subWindowList()) 
	{
		//TestChildWindow *mdiChild = qobject_cast<TestChildWindow *>(window->widget());
		//pSubWindow->move(10, 10);
		pSubWindow->resize(200, 300);
		this->setActiveSubWindow(pSubWindow);
	}
}

void CClientMainWindowMdiArea::_TranslateLanguage()
{

}


