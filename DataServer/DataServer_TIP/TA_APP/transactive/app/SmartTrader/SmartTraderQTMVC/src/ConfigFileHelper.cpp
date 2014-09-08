#include "ConfigFileHelper.h"

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QtGui/QFontMetrics>


#include "BoostLogger.h"
USING_BOOST_LOG;





//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

static const std::string  DEF_VALUE_CONFIG_FILE = "./config.ini";
static const std::string  DEF_VALUE_CONFIG_GROUP_config = "config";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_skin = "skin";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_skin_defValue = ":/skin/skin_green_big";

static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument = "userinstrument";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue = "";//5614,5378

//CTreeItemQuotes::getLstClumnName(strlstClumnName);
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_AllAvailableColumns = "allavailableColumns";
//static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_AllAvailableColumns_defValue = "Change,Exchange Name,Contract Name,Bid Volume,Bid,Offer Volume,Offer,Last Volume,Last,YDSP,Status,Opening,Bid Total,Offer Total,Low,High,Closeing,Ref Price,UpdateTime";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_AllAvailableColumns_defValue = "";
//CTreeItemQuotes::getLstClumnName(strlstClumnName); = DEF_VALUE_CONFIG_GROUP_config_KEY_SelectedColumns_defValue
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_SelectedColumns = "selectedcolumns";
static const std::string  DEF_VALUE_CONFIG_GROUP_config_KEY_SelectedColumns_defValue = "Change,Exchange Name,Contract Name,Bid Volume,Bid,Offer Volume,Offer,Last Volume,Last,YDSP,Status,Opening,Bid Total,Offer Total,Low,High,Closeing,Ref Price,UpdateTime";


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
		LOG_ERROR<<"setConfigFile"
			<<" "<<"strConfigFileName="<<"NULL";
	}
	else
	{
		LOG_INFO<<"setConfigFile"
			<<" "<<"strConfigFileName="<<strConfigFileName.toStdString();
	}
}


/*
		[config]
		skin=XXX.file
*/
int CConfigFileHelper::_WriteToConfig(const QString& strConfigFileName, const QString& strGroup, const QString& strKey, const QString& strValue)
{
	boost::mutex::scoped_lock lock(m_mutexConfigFileName);	

	int nRunRes = 0;
	QSettings *configFileHandle = NULL;

	if(strConfigFileName.isEmpty() || strKey.isEmpty())
	{
		LOG_ERROR<<"writeToConfig"
			<<" "<<"strConfigFileName="<<"NULL";

		nRunRes = -1;
		return nRunRes;
	}

	//创建配置文件操作对象
	configFileHandle = new QSettings(strConfigFileName, QSettings::IniFormat);

	//将信息写入配置文件
	configFileHandle->beginGroup(strGroup);
	configFileHandle->setValue(strKey, strValue);
	configFileHandle->endGroup();

	LOG_INFO<<"writeToConfig"
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
	boost::mutex::scoped_lock lock(m_mutexConfigFileName);	

	int nRunRes = 0;
	QSettings *configFileHandle = NULL;
	QString strKeyTemp;
	QStringList allKeys;
	int nKeyIndex = 0;

	if(strConfigFileName.isEmpty() || strKey.isEmpty())
	{
		LOG_ERROR<<"readFormConfig"
			<<" "<<"strConfigFileName="<<"NULL";

		nRunRes = -1;
		return nRunRes;
	}


	//创建配置文件操作对象
	configFileHandle = new QSettings(strConfigFileName, QSettings::IniFormat);
	strKeyTemp = strGroup + "/" + strKey;

	//check
	nKeyIndex = -1;
	allKeys = configFileHandle->allKeys();//"config/skin"
	nKeyIndex = allKeys.indexOf(strKeyTemp);//allKeys.indexOf();
	if (-1 == nKeyIndex)
	{
		LOG_WARNING<<"readFormConfig"
			<<" "<<"strConfigFileName="<<strConfigFileName.toStdString()
			<<" "<<"not have key="<<strKeyTemp.toStdString();
		nRunRes = -1;
		return nRunRes;
	}

	//读取用户配置信息
	strValue = configFileHandle->value(strKeyTemp).toString();

	LOG_INFO<<"readFormConfig"
		<<" "<<"strConfigFileName="<<strConfigFileName.toStdString()
		<<" "<<"strKeyTemp="<<strKeyTemp.toStdString()
		<<" "<<"strValue="<<strValue.toStdString();

	nRunRes = 0;
	return nRunRes;
}


QString CConfigFileHelper::getSkinNameFormConfig()
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;
	QString strValue;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_skin.c_str();
	strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_skin_defValue.c_str();

	nFunRes = _ReadFormConfig(strConfigFileName, strGroup, strKey, strValue);

	if (0 != nFunRes)
	{
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_skin_defValue.c_str();
	}

	return strValue;
}

void CConfigFileHelper::setSkinNameToConfig(const QString& strValue)
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_skin.c_str();

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

QString CConfigFileHelper::getUserAllAvailableColumns()
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;
	QString strValue;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_AllAvailableColumns.c_str();
	strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_AllAvailableColumns_defValue.c_str();

	nFunRes = _ReadFormConfig(strConfigFileName, strGroup, strKey, strValue);

	if (0 != nFunRes)
	{
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_AllAvailableColumns_defValue.c_str();
	}


	return strValue;

}
QString CConfigFileHelper::getUserAllAvailableColumnsDefault()
{
	QString strValue;
	strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_AllAvailableColumns_defValue.c_str();
	return strValue;
}

void CConfigFileHelper::setUserAllAvailableColumns(const QString& strValue)
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_AllAvailableColumns.c_str();

	nFunRes = _WriteToConfig(strConfigFileName, strGroup, strKey, strValue);

	return;

}


QString CConfigFileHelper::getUserSelectedColumnnsDefault()
{
	QString strValue;
	strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_SelectedColumns_defValue.c_str();
	return strValue;
}

QString CConfigFileHelper::getUserSelectedColumnns()
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;
	QString strValue;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_SelectedColumns.c_str();
	strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_SelectedColumns_defValue.c_str();

	nFunRes = _ReadFormConfig(strConfigFileName, strGroup, strKey, strValue);

	if (0 != nFunRes)
	{
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_SelectedColumns_defValue.c_str();
	}


	return strValue;
}
void CConfigFileHelper::setUserSelectedColumns(const QString& strValue)
{
	int nFunRes = 0;
	QString strConfigFileName;
	QString strGroup;
	QString strKey;

	strConfigFileName = m_strConfigFileName;
	strGroup = DEF_VALUE_CONFIG_GROUP_config.c_str();
	strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_SelectedColumns.c_str();

	nFunRes = _WriteToConfig(strConfigFileName, strGroup, strKey, strValue);

	return;

}




//QT_END_NAMESPACE

