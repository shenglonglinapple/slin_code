#ifndef __CLASS_PROJECT_SQL_MANAGER_H__
#define __CLASS_PROJECT_SQL_MANAGER_H__

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>
#include <QtCore/QList>

#include "SQLData.h"
#include "SQLParam.h"

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
public:
	qint32 prepareSQLData(CSQLData& objSQLData, const CSQLParam& sqlKey);
	qint32 prepareSQLData(CSQLData& objSQLData, const CSQLParam& sqlKey,
		const CSQLParam& arg0);
	qint32 prepareSQLData(CSQLData& objSQLData, const CSQLParam& sqlKey,
		const CSQLParam& arg0, const CSQLParam& arg1);
	qint32 prepareSQLData(CSQLData& objSQLData, const CSQLParam& sqlKey,
		const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2);
	qint32 prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
		const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2, 
		const CSQLParam& arg3);
	qint32 prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
		const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2, 
		const CSQLParam& arg3, const CSQLParam& arg4);
	qint32 prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
		const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2, 
		const CSQLParam& arg3, const CSQLParam& arg4, const CSQLParam& arg5);
	qint32 prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
		const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2, 
		const CSQLParam& arg3, const CSQLParam& arg4, const CSQLParam& arg5,
		const CSQLParam& arg6);
	qint32 prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
		const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2,
		const CSQLParam& arg3, const CSQLParam& arg4, const CSQLParam& arg5, 
		const CSQLParam& arg6, const CSQLParam& arg7);
	qint32 prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey,
		const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2,
		const CSQLParam& arg3, const CSQLParam& arg4, const CSQLParam& arg5, 
		const CSQLParam& arg6, const CSQLParam& arg7, const CSQLParam& arg8);
private:
	void _ClearAllSQL();
	void _BuildAllSQL();
	qint32 _GetSQLData( CSQLData& objSQLData, const QString& sqlKey );
private:
	QMutex m_mutex_MapSQLData;
	QMap<QString, CSQLData*> m_MapSQLData;//SQLKey, ALLSQL
private:
	QString m_strSQLStringXmlFile;
	CSQLStringXmlParser* m_pSQLStringXmlParser;
};

#endif//__CLASS_PROJECT_SQL_MANAGER_H__
