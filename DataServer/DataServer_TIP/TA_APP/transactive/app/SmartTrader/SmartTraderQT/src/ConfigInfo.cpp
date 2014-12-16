#include "ConfigInfo.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "ConfigFileHelper.h"

#include "Log4cppLogger.h"

static const std::string DEFAULT_STRING_VALUE_STRING_SPLIT = ",";


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
	m_strLastUpdateTime = m_pConfigFileHelper->getLastUpdateTimeFormConfig();
	m_LstUserInstrument = m_pConfigFileHelper->getUserInstrumentFormConfig().split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());
}

void CConfigInfo::_WriteDataToCfgFile()
{
	m_pConfigFileHelper->setFileDBPathToConfig(m_strFileDBPath);
	m_pConfigFileHelper->setSQLiteDBPathToConfig(m_strSQLiteDBPath);
	m_pConfigFileHelper->setLastUpdateTimeToConfig(m_strLastUpdateTime);
	m_pConfigFileHelper->setUserInstrumentToConfig(m_LstUserInstrument.join(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str()));
}


QStringList CConfigInfo::getLstUserInstrument()
{
	return m_LstUserInstrument;
}

void CConfigInfo::removeInstrument(const QString& strInstrumentID)
{
	QStringList lstStringValue;
	QStringList lstStringValueNew;
	QString  strValue;

	lstStringValue = getLstUserInstrument();

	foreach (const QString& strValue, lstStringValue)
	{
		if (strInstrumentID != strValue)
		{
			lstStringValueNew.push_back(strValue);
		}
	}

	setLstUserInstrument(lstStringValueNew);


}

void CConfigInfo::addInstrument(const QString& strInstrumentID)
{
	QStringList lstStringValue;
	lstStringValue = getLstUserInstrument();

	if (!lstStringValue.contains(strInstrumentID))
	{
		lstStringValue.push_back(strInstrumentID);
		setLstUserInstrument(lstStringValue);
	}
}

void CConfigInfo::addInstrument( unsigned int nInstrumentID )
{
	QString strUserInstruemt;
	strUserInstruemt = QString("%1").arg(nInstrumentID);

	addInstrument(strUserInstruemt);
}

void CConfigInfo::setLstUserInstrument( QStringList& lstStringValue )
{
	QString strValue;
	QString strValueGet;

	strValue = lstStringValue.join(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	m_pConfigFileHelper->setUserInstrumentToConfig(strValue);

	//refush memory data
	strValueGet = m_pConfigFileHelper->getUserInstrumentFormConfig();
	m_LstUserInstrument.clear();
	if (!strValueGet.isEmpty())
	{
		m_LstUserInstrument = strValueGet.split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	}


}
bool CConfigInfo::checkUserInstrument( const QString& strInstrumentID )
{
	bool bFunRes = false;
	//subscribeMarketData user hot Instrument
	QStringList LstUserInstrument;
	LstUserInstrument = CConfigInfo::getInstance().getLstUserInstrument();
	if (LstUserInstrument.contains(strInstrumentID))
	{
		bFunRes = true;
	}

	return bFunRes;
}

bool CConfigInfo::checkUserInstrument( unsigned int nInstrumentID )
{
	QString strUserInstruemt;
	strUserInstruemt = QString("%1").arg(nInstrumentID);
	return checkUserInstrument(strUserInstruemt);
}
