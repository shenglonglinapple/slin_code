#include "ClientUIManager.h"


#include <QtGui/QMenu> 
#include <QtGui/QCursor> 
#include <QtGui/QMessageBox>

#include "ClientDataManager.h"

#include "ClientLoginWindow.h"
#include "ClientMainWindow.h"


#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CClientUIManager::CClientUIManager()
{
	m_pClientLoginDialog = NULL;
	m_pClientMainWindow = NULL;
	//data
	CClientDataManager::getInstance();

	m_pClientLoginDialog = new CClientLoginWindow();
	m_pClientMainWindow = new CClientMainWindow();

	_CreateConnect();

}


CClientUIManager::~CClientUIManager()
{
	if (NULL != m_pClientLoginDialog)
	{
		delete m_pClientLoginDialog;
		m_pClientLoginDialog = NULL;
	}

	if (NULL != m_pClientMainWindow)
	{
		delete m_pClientMainWindow;
		m_pClientMainWindow = NULL;
	}
	CClientDataManager::removeInstance();
}

void CClientUIManager::_CreateConnect()
{
	QObject::connect(m_pClientLoginDialog, 
		SIGNAL(signalLoginToServerRes(int)),
		this, 
		SLOT(slotLoginToServerRes(int)));
	
}
void CClientUIManager::showClientLoginWindow(bool bShow)
{
	if (bShow)
	{
		m_pClientLoginDialog->show();
	}
	else
	{
		m_pClientLoginDialog->setVisible(false);
	}
}
void CClientUIManager::slotLoginToServerRes( int nLoginToServerRes )
{
	MYLOG4CPP_DEBUG<<"CClientUIManager process slotLoginToServerRes"
		<<" "<<"nLoginToServerRes="<<nLoginToServerRes;

	//logon ok
	if (nLoginToServerRes >= 0)
	{
		m_pClientLoginDialog->setVisible(false);
		m_pClientLoginDialog->close();
		//login to server ok
		m_pClientMainWindow->show();
	}
	else
	{
		QMessageBox::about(NULL, "login to server Error!", "login to server Error!");
	}
}




//QT_END_NAMESPACE

