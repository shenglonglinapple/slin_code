#ifndef __CLASS_PROJECT_SQL_MANAGER_H__
#define __CLASS_PROJECT_SQL_MANAGER_H__

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include <QtCore/QList>


class CSQLData;
class CSQLStringXmlParser;

class CProjectSQLManager 
{
public:
	static CProjectSQLManager& getInstance();
	static void removeInstance();
private:
	static CProjectSQLManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
    CProjectSQLManager(void);
	~CProjectSQLManager(void);
private:
	void _ClearAllSQL();
	void _BuildAllSQL();
private:
	QMutex m_mutex_MapSQLData;
	QMap<QString, CSQLData*> m_MapSQLData;
private:
	QString m_strSQLStringXmlFile;
	CSQLStringXmlParser* m_pSQLStringXmlParser;
};

#endif//__CLASS_PROJECT_SQL_MANAGER_H__
