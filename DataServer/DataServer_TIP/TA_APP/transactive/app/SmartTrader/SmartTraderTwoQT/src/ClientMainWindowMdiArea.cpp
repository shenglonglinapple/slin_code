#include "ClientMainWindowMdiArea.h"



#include "UserInstrumentTableView.h"


CClientMainWindowMdiArea::CClientMainWindowMdiArea(QWidget *parent)
    : QMdiArea(parent)
{
    //this->resize(200, 300);

	m_pUserInstrumentTableView = NULL;

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

	m_pUserInstrumentTableView = new CUserInstrumentTableView(this);
	this->addSubWindow(m_pUserInstrumentTableView);


	foreach (QMdiSubWindow *pSubWindow, this->subWindowList()) 
	{
		//TestChildWindow *mdiChild = qobject_cast<TestChildWindow *>(window->widget());
		this->setActiveSubWindow(pSubWindow);
	}
}

void CClientMainWindowMdiArea::_TranslateLanguage()
{

}


