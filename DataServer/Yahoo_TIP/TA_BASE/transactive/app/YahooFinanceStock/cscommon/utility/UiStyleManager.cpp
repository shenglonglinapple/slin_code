#include "UiStyleManager.h"
#include "UiPathResolve.h"


static const char*  DEF_VALUE_ThemeName_Default = "default";


CUiStyleManager* CUiStyleManager::m_pInstance = 0;
QMutex CUiStyleManager::m_mutexInstance;

CUiStyleManager& CUiStyleManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CUiStyleManager();
	}
	return (*m_pInstance);
}

void CUiStyleManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CUiStyleManager::CUiStyleManager(void)
{

}

CUiStyleManager::~CUiStyleManager( void )
{

}
QString CUiStyleManager::getThemeName()
{
	QString strTheme = DEF_VALUE_ThemeName_Default;
	return strTheme;
}


