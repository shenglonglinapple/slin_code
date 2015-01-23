#include "CfgFileUtil.h"

#include <QtCore/QSettings>
#include <QtCore/QString>
#include <QtCore/QStringList>
//#include <QtGui/QFontMetrics>
#include <QtCore/QFile>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Log4cppLogger.h"

CCfgFileUtil* CCfgFileUtil::m_pInstance = 0;
QMutex CCfgFileUtil::m_mutexInstance;

CCfgFileUtil& CCfgFileUtil::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CCfgFileUtil();
	}
	return (*m_pInstance);
}

void CCfgFileUtil::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CCfgFileUtil::CCfgFileUtil()
{
}

CCfgFileUtil::~CCfgFileUtil()
{

}

/*
		[config]
		skin=XXX.file
*/
void CCfgFileUtil::write(const QString& strConfigFileName,
	const QString& strGroup, const QString& strKey, const QString& strValue)
{
	if(strConfigFileName.isEmpty() || strKey.isEmpty())
	{
		MYLOG4CPP_ERROR<<"writeToConfig"
			<<" "<<"strConfigFileName="<<"NULL";
		return;
	}

	//创建配置文件操作对象
	QSettings settings(strConfigFileName, QSettings::IniFormat);

	//将信息写入配置文件
	settings.beginGroup(strGroup);
	settings.setValue(strKey, strValue);
	settings.endGroup();

	MYLOG4CPP_INFO<<"write"
		<<" "<<"strConfigFileName="<<strConfigFileName.toStdString()
		<<" "<<"strGroup="<<strGroup.toStdString()
		<<" "<<"strKey="<<strKey.toStdString()
		<<" "<<"strValue="<<strValue.toStdString();

}

/*
		[config]
		skin=XXX.file
*/
int CCfgFileUtil::read(const QString& strConfigFileName, const QString& strGroup, const QString& strKey, QString& strValue)
{
	int nRunRes = 0;
	QString strKeyTemp;
	QStringList allKeys;
	int nKeyIndex = 0;

	if(strConfigFileName.isEmpty() || strKey.isEmpty())
	{
		MYLOG4CPP_ERROR<<"read"
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
		MYLOG4CPP_WARNING<<"read"
			<<" "<<"strConfigFileName="<<strConfigFileName.toStdString()
			<<" "<<"not have key="<<strKeyTemp.toStdString();
		nRunRes = -1;
		return nRunRes;
	}

	//读取用户配置信息
	strValue = settings.value(strKeyTemp).toString();

	MYLOG4CPP_INFO<<"read"
		<<" "<<"strConfigFileName="<<strConfigFileName.toStdString()
		<<" "<<"strKeyTemp="<<strKeyTemp.toStdString()
		<<" "<<"strValue="<<strValue.toStdString();

	nRunRes = 0;
	return nRunRes;
}
