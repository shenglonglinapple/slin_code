#include "ConfigInfo.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "CfgFileUtil.h"

#include "Log4cppLogger.h"

static const char* DEFAULT_STRING_VALUE_STRING_SPLIT = ",";


static const char*  DEF_VALUE_CONFIG_FILE = "./config.ini";
static const char*  DEF_VALUE_CONFIG_GROUP_config = "config";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath = "filedbpath";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath_defValue = "C:/LSL/LSL_DATA/SaveDataFile/";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath = "sqlitedbpath";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath_defValue = "C:/LSL/LSL_DATA/SaveDataSqliteDB/";

//static const char* DEF_VALUE_STRING_UTC_START_DATE_TIME = "1970-01-01 08:00:00";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument = "userinstrument";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue = "";//5614,5378

static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_username = "username";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_username_defValue = "username";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_password = "password";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_password_defValue = "password";

static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_serverip = "serverip";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_serverip_defValue = "127.0.0.1";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_serverport = "serverport";
static const quint16  DEF_VALUE_CONFIG_GROUP_config_KEY_serverport_defValue = 5000;



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
	m_strConfigFileName.clear();
	m_strFileDBPath.clear();
	m_strSQLiteDBPath.clear();
	m_LstUserInstrument.clear();
	m_strServerIP.clear();
	m_nServerPort = 0;
	m_strUserName.clear();
	m_strPassWord.clear();


	CCfgFileUtil::getInstance();

	m_strConfigFileName = DEF_VALUE_CONFIG_FILE;
	_LoadDataFromCfgFile();
}

CConfigInfo::~CConfigInfo()
{
	_WriteDataToCfgFile();
	CCfgFileUtil::removeInstance();
}

QString CConfigInfo::getFileDBPath()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_strFileDBPath.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath;
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath_defValue;
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath_defValue;
		}
		m_strFileDBPath = strValue;
	}

	return m_strFileDBPath;
}
void CConfigInfo::setFileDBPath(const QString& strFileDBPath)
{
	QMutexLocker lock(&m_mutexConfigFileHandle);
	QString strGroup;
	QString strKey;

	//if (strFileDBPath != m_strFileDBPath)
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath;
		CCfgFileUtil::getInstance().write(m_strConfigFileName, strGroup, strKey, strFileDBPath);
	}

	m_strFileDBPath = strFileDBPath;

}
QString CConfigInfo::getSQLiteDBPath()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_strSQLiteDBPath.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath;
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath_defValue;
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath_defValue;
		}
		m_strSQLiteDBPath = strValue;
	}

	return m_strSQLiteDBPath;
}
void CConfigInfo::setSQLiteDBPath(const QString& strSQLiteDBPath)
{
	QMutexLocker lock(&m_mutexConfigFileHandle);
	QString strGroup;
	QString strKey;

	//if (strSQLiteDBPath != m_strSQLiteDBPath)
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath;
		CCfgFileUtil::getInstance().write(m_strConfigFileName, strGroup, strKey, strSQLiteDBPath);
	}

	m_strSQLiteDBPath = strSQLiteDBPath;
}


void CConfigInfo::_LoadDataFromCfgFile()
{
	getFileDBPath();
	getSQLiteDBPath();
	getLstUserInstrument();
	getUserName();
	getPassWord();
	getServerIP();
	getServerPort();
}

void CConfigInfo::_WriteDataToCfgFile()
{
	QString strValue;
	QStringList strLstValue;
	strValue = m_strFileDBPath;
	setFileDBPath(strValue);
	strValue = m_strSQLiteDBPath;
	setSQLiteDBPath(strValue);
	strLstValue = m_LstUserInstrument;
	setLstUserInstrument(strLstValue);

}


QStringList CConfigInfo::getLstUserInstrument()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_LstUserInstrument.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument;
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue;
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue;
		}
		m_LstUserInstrument = strValue.split(DEFAULT_STRING_VALUE_STRING_SPLIT);
	}

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

void CConfigInfo::removeInstrument( unsigned int nInstrumentID )
{
	QString strUserInstruemt;
	strUserInstruemt = QString("%1").arg(nInstrumentID);

	removeInstrument(strUserInstruemt);

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

void CConfigInfo::setLstUserInstrument(const QStringList& lstStringValue )
{
	QMutexLocker lock(&m_mutexConfigFileHandle);
	QString strGroup;
	QString strKey;
	QString strValue;

	m_LstUserInstrument.clear();
	m_LstUserInstrument = lstStringValue;

	strValue = m_LstUserInstrument.join(DEFAULT_STRING_VALUE_STRING_SPLIT);//","

	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument;
		CCfgFileUtil::getInstance().write(m_strConfigFileName, strGroup, strKey, strValue);
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

QString CConfigInfo::getUserName()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_strUserName.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_username;
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_username_defValue;
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_username_defValue;
		}
		m_strUserName = strValue;
	}

	return m_strUserName;
}

QString CConfigInfo::getPassWord()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_strPassWord.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_password;
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_password_defValue;
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_password_defValue;
		}
		m_strPassWord = strValue;
	}

	return m_strPassWord;
}

QString CConfigInfo::getServerIP()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_strServerIP.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_serverip;
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_serverip_defValue;
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_serverip_defValue;
		}
		m_strServerIP = strValue;
	}

	return m_strServerIP;
}

qint16 CConfigInfo::getServerPort()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (0 == m_nServerPort)
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_serverport;
		strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_serverport_defValue);
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_serverport_defValue);
		}
		m_nServerPort = strValue.toUShort();
	}

	return m_nServerPort;
}


