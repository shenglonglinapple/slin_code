#include "DataUserInstrument.h"

#include "ItemUserInstrument.h"
//
#include "Log4cppLogger.h"

CDataUserInstrument* CDataUserInstrument::m_pInstance = 0;
QMutex CDataUserInstrument::m_mutexInstance;

CDataUserInstrument& CDataUserInstrument::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataUserInstrument();
	}
	return (*m_pInstance);
}

void CDataUserInstrument::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataUserInstrument::CDataUserInstrument(void)
{	
	m_pItemUserInstrument = NULL;
	m_pItemUserInstrument = new CItemUserInstrument();
}

CDataUserInstrument::~CDataUserInstrument(void)
{		
	if (NULL != m_pItemUserInstrument)
	{
		delete m_pItemUserInstrument;
		m_pItemUserInstrument = NULL;
	}
}

CItemUserInstrument* CDataUserInstrument::getRootItem()
{
	return m_pItemUserInstrument;
}

