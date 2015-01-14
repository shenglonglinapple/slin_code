#include "ClientMainWindowMdiArea.h"

#include "StockMinTimeMaxTimeTableView.h"
#include "StockHistoryDataTableView.h"

#include "Log4cppLogger.h"

static const int DEFVALUE_INT_Window_Width_StockMinTimeMaxTimeTableView = 400;
static const int DEFVALUE_INT_Window_Height_StockMinTimeMaxTimeTableView = 300;

static const int DEFVALUE_INT_Window_Width_StockHistoryDataTableView = 400;
static const int DEFVALUE_INT_Window_Height_StockHistoryDataTableView = 300;


CClientMainWindowMdiArea::CClientMainWindowMdiArea(QWidget *parent)
    : QMdiArea(parent)
{
    //this->resize(200, 300);
	m_pStockMinTimeMaxTimeTableView = NULL;
	m_pStockHistoryDataTableView = NULL;

	_SetupUi();
	_TranslateLanguage();
}

CClientMainWindowMdiArea::~CClientMainWindowMdiArea()
{
	
}



void CClientMainWindowMdiArea::_SetupUi()
{
	int nIndex = 0;
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_pStockMinTimeMaxTimeTableView = new CStockMinTimeMaxTimeTableView(this);
	m_pStockHistoryDataTableView = new CStockHistoryDataTableView(this);

	this->addSubWindow(m_pStockMinTimeMaxTimeTableView);
	this->addSubWindow(m_pStockHistoryDataTableView);

	nIndex = 0;
	foreach (QMdiSubWindow *pSubWindow, this->subWindowList()) 
	{
		if (0 == nIndex)
		{
			//TestChildWindow *mdiChild = qobject_cast<TestChildWindow *>(window->widget());
			this->setActiveSubWindow(pSubWindow);
			this->activeSubWindow()->move(0, 0);
			this->activeSubWindow()->resize(DEFVALUE_INT_Window_Width_StockMinTimeMaxTimeTableView, 
				DEFVALUE_INT_Window_Height_StockMinTimeMaxTimeTableView);
		}
		else if (1 == nIndex)
		{
			this->setActiveSubWindow(pSubWindow);
			this->activeSubWindow()->move(DEFVALUE_INT_Window_Width_StockMinTimeMaxTimeTableView, 0);
			this->activeSubWindow()->resize(DEFVALUE_INT_Window_Width_StockHistoryDataTableView, 
				DEFVALUE_INT_Window_Height_StockHistoryDataTableView);
		}
		nIndex++;
	}//foreach
}

void CClientMainWindowMdiArea::_TranslateLanguage()
{

}


