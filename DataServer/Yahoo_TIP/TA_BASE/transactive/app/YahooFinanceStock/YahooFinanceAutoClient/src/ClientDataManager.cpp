#include "ClientDataManager.h"

#include <QtCore/QStringList>
#include <QtCore/QByteArray>

#include "ClientActorManager.h"
#include "ConfigInfo.h"
#include "Log4cppLogger.h"
#include "ProjectSQLManager.h"

CClientDataManager* CClientDataManager::m_pInstance = 0;
QMutex CClientDataManager::m_mutexInstance;

CClientDataManager& CClientDataManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CClientDataManager();
	}
	return (*m_pInstance);
}

void CClientDataManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CClientDataManager::CClientDataManager(void)
{
	CConfigInfo::getInstance();
	CProjectSQLManager::getInstance();
	CClientActorManager::getInstance();
}

CClientDataManager::~CClientDataManager(void)
{
	CClientActorManager::removeInstance();
	CProjectSQLManager::removeInstance();
	CConfigInfo::removeInstance();
}

void CClientDataManager::startAllClient()
{
	QString strServerIP = "127.0.0.1";
	quint16 nServerPort = 5000;
	QString strUserName = "usernamelsl";
	QString strPassWord = "passwordlsl";

	strUserName = CConfigInfo::getInstance().getUserName();
	strPassWord = CConfigInfo::getInstance().getPassWord();
	strServerIP = CConfigInfo::getInstance().getServerIP();
	nServerPort = CConfigInfo::getInstance().getServerPort();

	CClientActorManager::getInstance().createClient(
		strServerIP, nServerPort, strUserName, strPassWord);
}

