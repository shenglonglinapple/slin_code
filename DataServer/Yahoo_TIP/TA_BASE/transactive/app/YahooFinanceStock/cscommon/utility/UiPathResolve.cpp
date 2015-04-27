#include "UiPathResolve.h"

#include <QtCore/QtGlobal>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtGui/QApplication>
#include <QtCore/QDebug>

#include "QtCppLogger.h"



static const char*  DEF_VALUE_Resources = "Resources";
static const char*  DEF_VALUE_Resources_images= "Resources/images";
static const char*  DEF_VALUE_Resources_skins = "Resources/skins";
static const char*  DEF_VALUE_Resources_skins_default = "Resources/skins/default";


CUiPathResolve* CUiPathResolve::m_pInstance = 0;
QMutex CUiPathResolve::m_mutexInstance;

CUiPathResolve& CUiPathResolve::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CUiPathResolve();
	}
	return (*m_pInstance);
}

void CUiPathResolve::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CUiPathResolve::CUiPathResolve(void)
{
	_LogAllPath();
}

CUiPathResolve::~CUiPathResolve( void )
{

}

////API begin
void CUiPathResolve::addBackslash(QString& strPath)
{
	strPath.replace('\\', '/');

	if (strPath.endsWith('/'))
	{
		return;
	}

	strPath += '/';
}

void CUiPathResolve::ensurePathExists(const QString& path)
{
	QDir dir;
	dir.mkpath(path);
}

bool CUiPathResolve::checkFileExists(const QString& path)
{
	bool bFileExists = false;
	QFile fileTmp(path);
	bFileExists = fileTmp.exists();
	return bFileExists;
}


////API end

void CUiPathResolve::_LogAllPath()
{
	m_strApplicationDirPath.clear();
	m_strHomePath.clear();
	m_strCurrentPath.clear();
	m_strTempPath.clear();

	//m_strApplicationDirPath=c:/LSL/SVNWork/slin_code/DataServer/Yahoo_TIP/bin/win32_nd/
	m_strApplicationDirPath = QApplication::applicationDirPath();
	addBackslash(m_strApplicationDirPath);
	qDebug()<<"m_strApplicationDirPath="<<m_strApplicationDirPath;

	//m_strHomePath=C:/Users/lin.shenglong
	m_strHomePath = QDir::homePath();
	addBackslash(m_strHomePath);
	qDebug()<<"m_strHomePath="<<m_strHomePath;

	//m_strCurrentPath=C:\LSL\SVNWork\slin_code\DataServer\Yahoo_TIP\TA_BASE\transactive\app\YahooFinanceStock\YahooFinanceStockClient
	m_strCurrentPath = QDir::currentPath();
	addBackslash(m_strCurrentPath);
	qDebug()<<"m_strCurrentPath="<<m_strCurrentPath;

	//m_strRootPath=C:/
	m_strRootPath = QDir::rootPath();
	addBackslash(m_strRootPath);
	qDebug()<<"m_strRootPath="<<m_strRootPath;


	//m_strTempPath=C:/Users/LIN~1.SHE/AppData/Local/Temp
	m_strTempPath = QDir::tempPath();
	addBackslash(m_strTempPath);
	qDebug()<<"m_strTempPath="<<m_strTempPath;

}

QString CUiPathResolve::getResourcesPath()
{
	QString strPath;

	strPath = m_strCurrentPath;
	strPath += DEF_VALUE_Resources;
	addBackslash(strPath);

	return strPath;
}
QString CUiPathResolve::getResourcesSkinsPath()
{
	QString strPath;

	strPath = m_strCurrentPath;
	strPath += DEF_VALUE_Resources_skins;
	addBackslash(strPath);

	return strPath;
}
QString CUiPathResolve::getResourcesSkinsThemePath(const QString& strThemeName)
{
	QString strPath;

	strPath = getResourcesSkinsPath();
	strPath += strThemeName; //"default"
	addBackslash(strPath);

	return strPath;
}

QString CUiPathResolve::getResourcesSkinsThemePngPath(const QString& strThemeName, const QString& strPngName)
{
	QString strPath;

	strPath = getResourcesSkinsThemePath(strThemeName);
	strPath += strPngName;

	if (false == checkFileExists(strPath))
	{
		qWarning()<<"m_strHomePath="<<m_strHomePath;
	}
	return strPath;
}