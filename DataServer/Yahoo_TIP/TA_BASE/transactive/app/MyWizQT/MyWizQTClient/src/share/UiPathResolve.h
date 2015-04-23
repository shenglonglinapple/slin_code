#ifndef __CLASS_UI_PATH_RESOLVE_H__
#define __CLASS_UI_PATH_RESOLVE_H__

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QString>


class CUiPathResolve 
{
public:
	static CUiPathResolve& getInstance();
	static void removeInstance();

private:
	static CUiPathResolve* m_pInstance;
	static QMutex m_mutexInstance;

private:
    CUiPathResolve(void);
	~CUiPathResolve(void);
private:
	void _LogAllPath();
public:
	void addBackslash(QString& strPath);
	void ensurePathExists(const QString& path);
	bool checkFileExists(const QString& path);

public:
	QString getResourcesPath();
	QString getResourcesSkinsPath();
	QString getResourcesSkinsThemePath(const QString& strThemeName);
	QString getResourcesSkinsThemePngPath(const QString& strThemeName, const QString& strPngName);
private:
	QString m_strApplicationDirPath;
	QString m_strHomePath;
	QString m_strCurrentPath;
	QString m_strRootPath;
	QString m_strTempPath;

};

#endif//__CLASS_UI_PATH_RESOLVE_H__
