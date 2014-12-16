#include "ConfigFileHelper.h"

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QFontMetrics>

#include <QtCore/QFile>

#include "Log4cppLogger.h"


static const std::string  DEF_VALUE_CONFIG_FILE = "./config.ini";
static const std::string  DEF_VALUE_CONFIG_GROUP_config = "config";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath = "filedbpath";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath_defValue = "C:/LSL/LSL_DATA/SaveDataFile/";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath = "sqlitedbpath";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath_defValue = "C:/LSL/LSL_DATA/SaveDataSqliteDB/";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_lastupdatetime = "lastupdatetime";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_lastupdatetime_defValue = "1970-01-01 08:00:00";
//static const std::string DEF_VALUE_STRING_UTC_START_DATE_TIME = "1970-01-01 08:00:00";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument = "userinstrument";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue = "";//5614,5378


CConfigFileHelper::CConfigFileHelper()
{
	m_strConfigFileName = DEF_VALUE_CONFIG_FILE.c_str();
}

CConfigFileHelper::~CConfigFileHelper()
{

}

void CConfigFileHelper::setConfigFile( const QString& strConfigFileName )
{
	m_strConfigFileName = strConfigFileName;

	if (m_strConfigFileName.isEmpty())
	{
		m_strConfigFileName = DEF_VALUE_CONFIG_FILE.c_str();
		MYLOG4CPP_ERROR<<"setConfigFile"
			<<" "<<"strConfigFileName="<<"NULL";
	}
	else
	{
		MYLOG4CPP_INFO<<"setConfigFile"
			<<" "<<"strConfigFileName="<<strConfigFileName.toStdString();
	}
}


/*
		[config]
		skin=XXX.file
*/
int CConfigFileHelper::_WriteToConfig(const QString& strConfigFileName,
	const QString& strGroup, const QString& strKey, const QString& strValue)
{
	QMutexLocker lock(&m_mutexConfigFileName);	

	int nRunRes = 0;

	if(strConfigFileName.isEmpty() || strKey.isEmpty())
	{
		MYLOG4CPP_ERROR<<"writeToConfig"
			<<" "<<"strConfigFileName="<<"NULL";

		nRunRes = -1;
		return nRunRes;
	}

	//创建配置文件操作对象
	QSettings settings(strConfigFileName, QSettings::IniFormat);

	//将信息写入配置文件
	settings.beginGroup(strGroup);
	settings.setValue(strKey, strValue);
	settings.endGroup();

	MYLOG4CPP_INFO<<"writeToConfig"
		<<" "<<"strConfigFileName="<<strConfigFileName.toStdString()
		<<" "<<"strGroup="<<strGroup.toStdString()
		<<" "<<"strKey="<<strKey.toStdString()
		<<" "<<"strValue="<<strValue.toStdString();

	return nRunRes;
}

/*
		[config]
		skin=XXX.file
*/
int CConfigFileHelper::_ReadFormConfig(const QString& strConfigFileName, const QString& strGroup, const QString& strKey, QString& strValue)
{
	QMutexLocker lock(&m_mutexConfigFileName);	

	int nRunRes = 0;
	QString strKeyTemp;
	QStringList allKeys;
	int nKeyIndex = 0;

	if(strConfigFileName.isEmpty() || strKey.isEmpty())
	{
		MYLOG4CPP_ERROR<<"readFormConfig"
			<<" "<<"strConfigFileName="<<"NULL";

		nRunRes = -1;
		return nRunRes;
	}


	//创建配置文件操作对象
	QSettings settings(strConfigFileName, QSettings::IniFormat);
	strKeyTemp = strGroup + "/" + strKey;

	//check
	nKeyIndex = -1;
	allKeys = settings.allKeys();//"config/skin"
	nKeyIndex = allKeys.indexOf(strKeyTemp);//allKeys.indexOf();
	if (-1 == nKeyIndex)
	{
		MYLOG4CPP_WARNING<<"readFormConfig"
			<<" "<<"strConfigFileName="<<strConfigFileName.toStdString()
			<<" "<<"not have key="<<strKeyTemp.toStdString();
		nRunRes = -1;
		return nRunRes;
	}

	//读取用户配置信息
	strValue = settings.value(strKeyTemp).toString();

	MYLOG4CPP_INFO<<"readFormConfig"
		<<" "<<"strConfigFileName="<<strConfigFileName.toStdString()
		<<" "<<"strKeyTemp="<<strKeyTemp.toStdString()
		<<" "<<"strValue="<<strValue.toStdString();

	nRunRes = 0;
	return nRunRes;
}


QString CConfigFileHelper::getFileDBPathFormConfig()
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;
	QString strValue;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath.c_str();
	strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath_defValue.c_str();

	nFunRes = _ReadFormConfig(strConfigFileName, strGroup, strKey, strValue);

	if (0 != nFunRes)
	{
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath_defValue.c_str();
	}

	return strValue;
}

void CConfigFileHelper::setFileDBPathToConfig(const QString& strValue)
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath.c_str();

	nFunRes = _WriteToConfig(strConfigFileName, strGroup, strKey, strValue);

	return;
}


QString CConfigFileHelper::getSQLiteDBPathFormConfig()
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;
	QString strValue;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath.c_str();
	strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath_defValue.c_str();

	nFunRes = _ReadFormConfig(strConfigFileName, strGroup, strKey, strValue);

	if (0 != nFunRes)
	{
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath_defValue.c_str();
	}

	return strValue;
}

void CConfigFileHelper::setSQLiteDBPathToConfig(const QString& strValue)
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath.c_str();

	nFunRes = _WriteToConfig(strConfigFileName, strGroup, strKey, strValue);

	return;
}



QString CConfigFileHelper::getLastUpdateTimeFormConfig()
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;
	QString strValue;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_lastupdatetime.c_str();
	strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_lastupdatetime_defValue.c_str();

	nFunRes = _ReadFormConfig(strConfigFileName, strGroup, strKey, strValue);

	if (0 != nFunRes)
	{
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_lastupdatetime_defValue.c_str();
	}

	return strValue;
}


void CConfigFileHelper::setLastUpdateTimeToConfig(const QString& strValue)
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_lastupdatetime.c_str();

	nFunRes = _WriteToConfig(strConfigFileName, strGroup, strKey, strValue);

	return;
}


QString CConfigFileHelper::getUserInstrumentFormConfig()
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;
	QString strValue;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument.c_str();
	strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue.c_str();

	nFunRes = _ReadFormConfig(strConfigFileName, strGroup, strKey, strValue);
	if (0 != nFunRes)
	{
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue.c_str();
	}
	return strValue;
}

void CConfigFileHelper::setUserInstrumentToConfig(const QString& strValue)
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument.c_str();

	nFunRes = _WriteToConfig(strConfigFileName, strGroup, strKey, strValue);

	return;
}
