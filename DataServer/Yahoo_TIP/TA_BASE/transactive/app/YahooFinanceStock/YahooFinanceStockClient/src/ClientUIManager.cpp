#include "ClientUIManager.h"

#include "ClientMainWindow.h"
#include "ClientDataManager.h"
#include "SignalSlotManager.h"
#include "Log4cppLogger.h"

CClientUIManager::CClientUIManager()
{
	m_pClientMainWindow = NULL;
	m_pClientMainWindow = new CClientMainWindow();

	CClientDataManager::getInstance();
	CSignalSlotManager::getInstance();
}


CClientUIManager::~CClientUIManager()
{
	CSignalSlotManager::removeInstance();
	CClientDataManager::removeInstance();

	if (NULL != m_pClientMainWindow)
	{
		MYLOG4CPP_DEBUG<<"close CClientMainWindow";
		delete m_pClientMainWindow;
		m_pClientMainWindow = NULL;
	}
}
void CClientUIManager::showCClientMainWindow( bool bShow )
{
	MYLOG4CPP_DEBUG<<"open CClientMainWindow bShow="<<bShow;
	if (NULL != m_pClientMainWindow)
	{
		m_pClientMainWindow->setVisible(true);
	}

}




//QT_END_NAMESPACE

