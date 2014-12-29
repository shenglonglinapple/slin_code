#include "ClientMainWindowMdiArea.h"

#include "UserInstrumentTableView.h"
#include "UserTradeWindow.h"

static const int DEFVALUE_INT_Window_Width_CUserInstrumentTableView = 500;
static const int DEFVALUE_INT_Window_Height_CUserInstrumentTableView = 300;

static const int DEFVALUE_INT_Window_Width_CUserTradeWindow = 1100;
static const int DEFVALUE_INT_Window_Height_CUserTradeWindow = 300;


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
	int nIndex = 0;
	int heightValue = 0;
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_pUserInstrumentTableView = new CUserInstrumentTableView(this);
	m_pUserTradeWindow = new CUserTradeWindow(this);

	this->addSubWindow(m_pUserInstrumentTableView);
	this->addSubWindow(m_pUserTradeWindow);

	nIndex = 0;
	foreach (QMdiSubWindow *pSubWindow, this->subWindowList()) 
	{
		if (0 == nIndex)
		{
			//TestChildWindow *mdiChild = qobject_cast<TestChildWindow *>(window->widget());
			this->setActiveSubWindow(pSubWindow);
			heightValue = 0;
			this->activeSubWindow()->move(0, heightValue);
			this->activeSubWindow()->resize(DEFVALUE_INT_Window_Width_CUserInstrumentTableView, 
				DEFVALUE_INT_Window_Height_CUserInstrumentTableView);
		}
		else if (1 == nIndex)
		{
			this->setActiveSubWindow(pSubWindow);
			heightValue = DEFVALUE_INT_Window_Height_CUserInstrumentTableView + 10;
			this->activeSubWindow()->move(0, heightValue);
			this->activeSubWindow()->resize(DEFVALUE_INT_Window_Width_CUserTradeWindow, 
				DEFVALUE_INT_Window_Height_CUserTradeWindow);
		}
		nIndex++;
	}//foreach
}

void CClientMainWindowMdiArea::_TranslateLanguage()
{

}


