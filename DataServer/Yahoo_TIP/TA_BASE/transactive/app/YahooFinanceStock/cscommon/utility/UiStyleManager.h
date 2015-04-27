#ifndef __CLASS_UI_STYLE_MANAGER_H__
#define __CLASS_UI_STYLE_MANAGER_H__

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CUiStyleManager 
{
public:
	static CUiStyleManager& getInstance();
	static void removeInstance();

private:
	static CUiStyleManager* m_pInstance;
	static QMutex m_mutexInstance;

private:
    CUiStyleManager(void);
	~CUiStyleManager(void);
public:
	QString getThemeName();
};

#endif//__CLASS_UI_STYLE_MANAGER_H__
