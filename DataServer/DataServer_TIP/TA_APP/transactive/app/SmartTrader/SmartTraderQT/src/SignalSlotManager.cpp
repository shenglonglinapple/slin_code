#include "SignalSlotManager.h"

#include "UserInstrumentTableView.h"

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
	m_pRefSignal_DataChange_UserInstrument = NULL;
	m_pRefSlot_DataChange_UserInstrument = NULL;
}

CSignalSlotManager::~CSignalSlotManager(void)
{		

}

void CSignalSlotManager::set_Signal_DataChange_UserInstrument( CClientDataManager* pRefSignal)
{
	m_pRefSignal_DataChange_UserInstrument = pRefSignal;
}
void CSignalSlotManager::set_Slot_DataChange_UserInstrument(CUserInstrumentTableView* pRefSlot )
{
	m_pRefSlot_DataChange_UserInstrument = pRefSlot;

	if (NULL != m_pRefSignal_DataChange_UserInstrument && NULL != m_pRefSlot_DataChange_UserInstrument)
	{
		QObject::connect(this, SIGNAL(signal_DataChange_UserInstrument()), this, SLOT(slot_DataChange_UserInstrument()));
	}
	else
	{
		QObject::disconnect(this, SIGNAL(signal_DataChange_UserInstrument()), this, SLOT(slot_DataChange_UserInstrument()));
	}
}

void CSignalSlotManager::slot_DataChange_UserInstrument()
{
	if (NULL != m_pRefSlot_DataChange_UserInstrument)
	{
		m_pRefSlot_DataChange_UserInstrument->slot_DataChange_UserInstrument();
	}
}

void CSignalSlotManager::emit_DataChange_UserInstrument()
{
	emit signal_DataChange_UserInstrument();
}

