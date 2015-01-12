#include "SignalSlotManager.h"


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
}

CSignalSlotManager::~CSignalSlotManager(void)
{		

}
