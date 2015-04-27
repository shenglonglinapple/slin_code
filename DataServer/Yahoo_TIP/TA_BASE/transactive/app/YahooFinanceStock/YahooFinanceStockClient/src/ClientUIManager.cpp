#include "ClientUIManager.h"

#include "ConfigInfo.h"
#include "ClientDataManager.h"
#include "SignalSlotManager.h"

#include "ClientMainWindow.h"

#include "Log4cppLogger.h"

CClientUIManager::CClientUIManager()
{
	CConfigInfo::getInstance();
	CSignalSlotManager::getInstance();
	CClientDataManager::getInstance();
	//CSignalSlotManager::set_Signal_ShownMessage(CClientDataManager*);

	m_pClientMainWindow = NULL;
	m_pClientMainWindow = new CClientMainWindow();
	CSignalSlotManager::getInstance().set_Slot_ShownMessage(m_pClientMainWindow);

}


CClientUIManager::~CClientUIManager()
{

	if (NULL != m_pClientMainWindow)
	{
		//CSignalSlotManager::getInstance().set_Slot_ShownMessage(NULL);

		MYLOG4CPP_DEBUG<<"close CClientMainWindow";
		delete m_pClientMainWindow;
		m_pClientMainWindow = NULL;
	}

	CClientDataManager::removeInstance();
	CSignalSlotManager::removeInstance();
	CConfigInfo::removeInstance();

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

