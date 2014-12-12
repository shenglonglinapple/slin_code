#include "ClientMainWindow.h"
#include "ClientDataManager.h"
#include "ClientLoginParam.h"

CClientMainWindow::CClientMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(200, 300);

	CClientDataManager::getInstance();
	CClientLoginParam objclientLoginParam;
	CClientDataManager::getInstance().slotClientLoginParamChanged(&objclientLoginParam);

}

CClientMainWindow::~CClientMainWindow()
{

	CClientDataManager::removeInstance();
}
