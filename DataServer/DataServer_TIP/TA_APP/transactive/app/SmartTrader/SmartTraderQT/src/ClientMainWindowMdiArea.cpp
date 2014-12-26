#include "ClientMainWindowMdiArea.h"

#include "UserInstrumentTableView.h"
#include "UserTradeWindow.h"



CClientMainWindowMdiArea::CClientMainWindowMdiArea(QWidget *parent)
    : QMdiArea(parent)
{
    //this->resize(200, 300);

	m_pUserInstrumentTableView = NULL;
	m_pUserTradeWindow = NULL;

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
	m_pUserTradeWindow = new CUserTradeWindow(this);

	this->addSubWindow(m_pUserInstrumentTableView);
	this->addSubWindow(m_pUserTradeWindow);


	foreach (QMdiSubWindow *pSubWindow, this->subWindowList()) 
	{
		//TestChildWindow *mdiChild = qobject_cast<TestChildWindow *>(window->widget());
		this->setActiveSubWindow(pSubWindow);
	}
}

void CClientMainWindowMdiArea::_TranslateLanguage()
{

}


