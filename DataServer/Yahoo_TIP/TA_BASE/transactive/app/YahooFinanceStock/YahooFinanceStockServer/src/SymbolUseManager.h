#ifndef __CLASS_SYMBOLUSE_MANAGER_H__
#define __CLASS_SYMBOLUSE_MANAGER_H__

#include <QtCore/QString>


class CSymbolUseManager
{
public:
    CSymbolUseManager(void);
	~CSymbolUseManager(void);

public:
	CSymbolUseManager& operator=(const CSymbolUseManager& objectCopy);
public:
	void logInfo(const QString& fileName, qint32 lineNumber);
public:
	static int getMaxUpdateFailedCount();
private:
	void _Clear();
public:
	QString m_strSymbolUse;
	QString m_strMaxTime;
	qint32 m_nUpdateFailed;
};

#endif//__CLASS_SYMBOLUSE_MANAGER_H__
