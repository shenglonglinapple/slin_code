#include "ClientManager.h"


#include <QtGui/QMenu> 
#include <QtGui/QCursor> 
#include <QtGui/QMessageBox>

#include "ClientLoginDialog.h"
#include "ClientMainWindow.h"
#include "ClientDataManagerWorker.h"
#include "SmartHotQuotesWindow.h"
#include "SignalSlotManager.h"
#include "ClientDataManagerWorker.h"

#include "Log4cppLogger.h"



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CClientManager::CClientManager()
{

	m_pClientLoginDialog = NULL;
	m_pClientMainWindow = NULL;


	m_pClientLoginDialog = new CClientLoginDialog();
	CSignalSlotManager::getInstance().setSignalSlot_ClientLoginParamChanged(m_pClientLoginDialog, &(CClientDataManagerWorker::getInstance()));

	m_pClientMainWindow = new CClientMainWindow();
	CClientDataManagerWorker::getInstance();

	_CreateConnect();

	m_pClientLoginDialog->show();

	//FOR Test, TODO.
	//CClientDataManagerWorker::getInstance()._Test();
}


CClientManager::~CClientManager()
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
	CClientDataManagerWorker::removeInstance();
}

void CClientManager::_CreateConnect()
{

	//
	QObject::connect(&(CClientDataManagerWorker::getInstance()), 
		SIGNAL(signalLoginToServerResult(int)),
		this,
		SLOT(slotLoginToServerResult(int)));


}



void CClientManager::slotLoginToServerResult( int nLoginResust )
{
	MYLOG4CPP_DEBUG<<"CClientManager process slotLoginToServerResult"
		<<" "<<"nLoginResust="<<nLoginResust;

	//logon ok
	if (nLoginResust >= 0)
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

