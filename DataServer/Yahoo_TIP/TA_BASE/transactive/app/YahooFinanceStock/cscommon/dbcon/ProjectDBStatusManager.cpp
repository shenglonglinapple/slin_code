#include "ProjectDBStatusManager.h"


#include "Log4cppLogger.h"


static const char*  DEF_VALUE_XML_FILE_SQL_STRING = "../cscommon/Xml/DBCfg.xml";

CProjectDBStatusManager* CProjectDBStatusManager::m_pInstance = 0;
QMutex CProjectDBStatusManager::m_mutexInstance;

CProjectDBStatusManager& CProjectDBStatusManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CProjectDBStatusManager();
	}
	return (*m_pInstance);
}

void CProjectDBStatusManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CProjectDBStatusManager::CProjectDBStatusManager(void)
{


}

CProjectDBStatusManager::~CProjectDBStatusManager( void )
{

}

