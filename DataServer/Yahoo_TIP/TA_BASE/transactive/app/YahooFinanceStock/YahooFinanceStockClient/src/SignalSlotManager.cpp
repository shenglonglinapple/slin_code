#include "SignalSlotManager.h"

#include "ClientDataManager.h"
#include "ClientMainWindow.h"

#include "Log4cppLogger.h"

CSignalSlotManager* CSignalSlotManager::m_pInstance = 0;
QMutex CSignalSlotManager::m_mutexInstance;

CSignalSlotManager& CSignalSlotManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CSignalSlotManager();
	}
	return (*m_pInstance);
}

void CSignalSlotManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CSignalSlotManager::CSignalSlotManager(void)
{	
	m_pRefSignal_ShownMessage = NULL;
	m_pRefSlot_ShownMessage = NULL;
}

CSignalSlotManager::~CSignalSlotManager(void)
{		

}

void CSignalSlotManager::set_Signal_ShownMessage( CClientDataManager* pRefSignal )
{
	m_pRefSignal_ShownMessage = pRefSignal;
}

void CSignalSlotManager::set_Slot_ShownMessage( CClientMainWindow* pRefSlot )
{
	m_pRefSlot_ShownMessage = pRefSlot;

	if (NULL != m_pRefSignal_ShownMessage && NULL != m_pRefSlot_ShownMessage)
	{
		QObject::connect(this, SIGNAL(signal_ShownMessage(QString)), this, SLOT(slot_ShownMessage(QString)));
	}
	else
	{
		QObject::disconnect(this, SIGNAL(signal_ShownMessage(QString)), this, SLOT(slot_ShownMessage(QString)));
	}
}

void CSignalSlotManager::slot_ShownMessage(QString strMessage)
{
	if (NULL != m_pRefSlot_ShownMessage)
	{
		m_pRefSlot_ShownMessage->slotShowMessage(strMessage);
	}
}

void CSignalSlotManager::emit_ShownMessage(QString strMessage)
{
	emit signal_ShownMessage(strMessage);
}
