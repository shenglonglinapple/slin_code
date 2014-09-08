#include "ClientManager.h"


#include <QtGui/QMenu> 
#include <QtGui/QCursor> 
#include <QtGui/QMessageBox>

#include "ClientLoginDialog.h"
#include "ClientMainWindow.h"
#include "ClientDataManagerWorker.h"
#include "SmartHotQuotesWindow.h"


#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CClientManager::CClientManager()
{

	m_pClientLoginDialog = NULL;
	m_pClientMainWindow = NULL;


	m_pClientLoginDialog = new CClientLoginDialog();
	m_pClientMainWindow = new CClientMainWindow();

	_CreateConnect();

	m_pClientLoginDialog->show();

	//FOR Test, TODO.
	//m_pClientMainWindow->m_pClientDataManagerWorker->_Test();
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
}

void CClientManager::_CreateConnect()
{
	QObject::connect(m_pClientLoginDialog, 
		SIGNAL(signalClientLoginParamChanged(CClientLoginParam*)),
		m_pClientMainWindow->m_pClientDataManagerWorker,
		SLOT(slotClientLoginParamChanged(CClientLoginParam*)));

	//
	QObject::connect(m_pClientMainWindow->m_pClientDataManagerWorker, 
		SIGNAL(signalLoginToServerResult(int)),
		m_pClientLoginDialog,
		SLOT(slotLoginToServerResult(int)));

	//
	QObject::connect(m_pClientMainWindow->m_pClientDataManagerWorker, 
		SIGNAL(signalLoginToServerResult(int)),
		this,
		SLOT(slotLoginToServerResult(int)));

}



void CClientManager::slotLoginToServerResult( int nLoginResust )
{
	LOG_DEBUG<<"CClientWindow process slotLoginToServerResult"
		<<" "<<"nLoginResust="<<nLoginResust;

	if (nLoginResust >= 0)
	{
		m_pClientMainWindow->show();
	}
}


//QT_END_NAMESPACE

