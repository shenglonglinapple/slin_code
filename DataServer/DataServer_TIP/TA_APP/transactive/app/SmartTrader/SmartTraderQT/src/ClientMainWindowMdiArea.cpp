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
	m_pUserInstrumentTableView = new CUserInstrumentTableView(this);
	//m_pUserInstrumentTableView->move(10, 10);
	//m_pUserInstrumentTableView->resize(200, 200);

	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->addSubWindow(m_pUserInstrumentTableView);


	foreach (QMdiSubWindow *pSubWindow, this->subWindowList()) 
	{
		//TestChildWindow *mdiChild = qobject_cast<TestChildWindow *>(window->widget());
		//pSubWindow->move(10, 10);
		//pSubWindow->resize(200, 300);
		this->setActiveSubWindow(pSubWindow);
	}
}

void CClientMainWindowMdiArea::_TranslateLanguage()
{

}


