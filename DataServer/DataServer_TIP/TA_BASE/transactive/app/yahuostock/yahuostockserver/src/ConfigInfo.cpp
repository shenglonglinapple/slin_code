#include "ConfigInfo.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "ConfigFileHelper.h"

#include "Log4cppLogger.h"



CConfigInfo* CConfigInfo::m_pInstance = 0;
QMutex CConfigInfo::m_mutexInstance;

CConfigInfo& CConfigInfo::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CConfigInfo();
	}
	return (*m_pInstance);
}

void CConfigInfo::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


CConfigInfo::CConfigInfo()
{
	m_strFileDBPath.clear();
	m_strSQLiteDBPath.clear();
	m_pConfigFileHelper = NULL;
	m_pConfigFileHelper = new CConfigFileHelper();
	_LoadDataFromCfgFile();
}

CConfigInfo::~CConfigInfo()
{
	_WriteDataToCfgFile();
	if (NULL != m_pConfigFileHelper)
	{
		delete m_pConfigFileHelper;
		m_pConfigFileHelper = NULL;
	}
	
}

QString CConfigInfo::getFileDBPath()
{
	return m_strFileDBPath;
}
void CConfigInfo::setFileDBPath(const QString& strFileDBPath)
{
	m_strFileDBPath = strFileDBPath;
	m_pConfigFileHelper->setFileDBPathToConfig(m_strFileDBPath);
	
}
QString CConfigInfo::getSQLiteDBPath()
{
	return m_strSQLiteDBPath;
}
void CConfigInfo::setSQLiteDBPath(const QString& strSQLiteDBPath)
{
	m_strSQLiteDBPath = strSQLiteDBPath;
	m_pConfigFileHelper->setSQLiteDBPathToConfig(m_strSQLiteDBPath);

}


void CConfigInfo::setLastUpdateTime( const QString& strLastUpdateTime )
{
	m_strLastUpdateTime = strLastUpdateTime;
	m_pConfigFileHelper->setLastUpdateTimeToConfig(m_strLastUpdateTime);

}

QString CConfigInfo::getLastUpdateTime()
{
	return m_strLastUpdateTime;
}

void CConfigInfo::_LoadDataFromCfgFile()
{
	m_strFileDBPath = m_pConfigFileHelper->getFileDBPathFormConfig();
	m_strSQLiteDBPath = m_pConfigFileHelper->getSQLiteDBPathFormConfig();
}

void CConfigInfo::_WriteDataToCfgFile()
{
	m_pConfigFileHelper->setFileDBPathToConfig(m_strFileDBPath);
	m_pConfigFileHelper->setSQLiteDBPathToConfig(m_strSQLiteDBPath);
	m_pConfigFileHelper->setLastUpdateTimeToConfig(m_strLastUpdateTime);

}



//QT_END_NAMESPACE

