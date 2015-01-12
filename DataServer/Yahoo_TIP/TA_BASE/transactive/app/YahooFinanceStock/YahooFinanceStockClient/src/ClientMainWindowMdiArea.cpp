#include "ClientMainWindowMdiArea.h"


static const int DEFVALUE_INT_Window_Width_CUserInstrumentTableView = 500;
static const int DEFVALUE_INT_Window_Height_CUserInstrumentTableView = 300;

static const int DEFVALUE_INT_Window_Width_CUserTradeWindow = 1100;
static const int DEFVALUE_INT_Window_Height_CUserTradeWindow = 300;


CClientMainWindowMdiArea::CClientMainWindowMdiArea(QWidget *parent)
    : QMdiArea(parent)
{
    //this->resize(200, 300);
	_SetupUi();
	_TranslateLanguage();
}

CClientMainWindowMdiArea::~CClientMainWindowMdiArea()
{

}



void CClientMainWindowMdiArea::_SetupUi()
{
	
}

void CClientMainWindowMdiArea::_TranslateLanguage()
{

}


