#include "ProjectSQLManager.h"

#include "SQLData.h"
#include "SQLStringXmlParser.h"
#include "Log4cppLogger.h"


static const char*  DEF_VALUE_XML_FILE_SQL_STRING = "./xml/SQLString.xml";

CProjectSQLManager* CProjectSQLManager::m_pInstance = 0;
QMutex CProjectSQLManager::m_mutexInstance;

CProjectSQLManager& CProjectSQLManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CProjectSQLManager();
	}
	return (*m_pInstance);
}

void CProjectSQLManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CProjectSQLManager::CProjectSQLManager(void)
{
	m_strSQLStringXmlFile = DEF_VALUE_XML_FILE_SQL_STRING;
	m_pSQLStringXmlParser = NULL;
	m_pSQLStringXmlParser = new CSQLStringXmlParser();
	_ClearAllSQL();
	_BuildAllSQL();
}

CProjectSQLManager::~CProjectSQLManager( void )
{
	_ClearAllSQL();
	if (NULL != m_pSQLStringXmlParser)
	{
		delete m_pSQLStringXmlParser;
		m_pSQLStringXmlParser = NULL;
	}
}

void CProjectSQLManager::_ClearAllSQL()
{
	QMutexLocker lock(&m_mutex_MapSQLData);	
	QMap<QString, CSQLData*>::iterator iterMap;
	CSQLData* pData = NULL;

	iterMap = m_MapSQLData.begin();
	while (iterMap != m_MapSQLData.end())
	{
		pData = iterMap.value();
		delete pData;
		pData = NULL;

		iterMap++;
	}//while
	m_MapSQLData.clear();
}

void CProjectSQLManager::_BuildAllSQL()
{
	qint32 nFunRes = 0;

	_ClearAllSQL();

	if (NULL != m_pSQLStringXmlParser)
	{
		nFunRes = m_pSQLStringXmlParser->doParse(m_strSQLStringXmlFile, m_MapSQLData);
	}
}

qint32 CProjectSQLManager::_GetSQLData( CSQLData& objSQLData, const QString& sqlKey )
{
	qint32 nFunRes = 0;
	CSQLData* pFindData = NULL;

	if (!m_MapSQLData.contains(sqlKey))
	{
		MYLOG4CPP_ERROR<<"error! prepareSQLStatement not find sqlKey="<<sqlKey;
		nFunRes = -1;
		return nFunRes;
	}
	//get format string
	pFindData = m_MapSQLData[sqlKey];
	objSQLData = *pFindData;
	
	return nFunRes;
}
qint32 CProjectSQLManager::prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey )
{
	qint32 nFunRes = 0;
	CSQLData formatSQLData;
	QString strSQLKey = sqlKey.getParam();
	strSQLKey = strSQLKey.toUpper();

	nFunRes = _GetSQLData(formatSQLData, strSQLKey);

	objSQLData = formatSQLData;
	objSQLData.buildSQL();
	return nFunRes;
}

qint32 CProjectSQLManager::prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey,
	const CSQLParam& arg0 )
{
	qint32 nFunRes = 0;
	CSQLData formatSQLData;
	QString strSQLKey = sqlKey.getParam();
	strSQLKey = strSQLKey.toUpper();

	nFunRes = _GetSQLData(formatSQLData, strSQLKey);

	objSQLData = formatSQLData;
	nFunRes = objSQLData.buildSQL(arg0.getParam());
	return nFunRes;
}

qint32 CProjectSQLManager::prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
	const CSQLParam& arg0, const CSQLParam& arg1 )
{
	qint32 nFunRes = 0;
	CSQLData formatSQLData;
	QString strSQLKey = sqlKey.getParam();
	strSQLKey = strSQLKey.toUpper();

	nFunRes = _GetSQLData(formatSQLData, strSQLKey);

	objSQLData = formatSQLData;
	nFunRes = objSQLData.buildSQL(arg0.getParam(), arg1.getParam());
	return nFunRes;
}

qint32 CProjectSQLManager::prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
	const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2 )
{
	qint32 nFunRes = 0;
	CSQLData formatSQLData;
	QString strSQLKey = sqlKey.getParam();
	strSQLKey = strSQLKey.toUpper();

	nFunRes = _GetSQLData(formatSQLData, strSQLKey);

	objSQLData = formatSQLData;
	nFunRes = objSQLData.buildSQL(arg0.getParam(), arg1.getParam(), arg2.getParam());
	return nFunRes;
}

qint32 CProjectSQLManager::prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
	const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2, const CSQLParam& arg3)
{
	qint32 nFunRes = 0;
	CSQLData formatSQLData;
	QString strSQLKey = sqlKey.getParam();
	strSQLKey = strSQLKey.toUpper();

	nFunRes = _GetSQLData(formatSQLData, strSQLKey);

	objSQLData = formatSQLData;
	nFunRes = objSQLData.buildSQL(arg0.getParam(), arg1.getParam(), arg2.getParam(), arg3.getParam());
	return nFunRes;
}
qint32 CProjectSQLManager::prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
	const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2, const CSQLParam& arg3, const CSQLParam& arg4)
{
	qint32 nFunRes = 0;
	CSQLData formatSQLData;
	QString strSQLKey = sqlKey.getParam();
	strSQLKey = strSQLKey.toUpper();

	nFunRes = _GetSQLData(formatSQLData, strSQLKey);

	objSQLData = formatSQLData;
	nFunRes = objSQLData.buildSQL(arg0.getParam(), arg1.getParam(), 
		arg2.getParam(), arg3.getParam(), arg4.getParam());
	return nFunRes;
}
qint32 CProjectSQLManager::prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
	const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2, 
	const CSQLParam& arg3, const CSQLParam& arg4, const CSQLParam& arg5)
{
	qint32 nFunRes = 0;
	CSQLData formatSQLData;
	QString strSQLKey = sqlKey.getParam();
	strSQLKey = strSQLKey.toUpper();

	nFunRes = _GetSQLData(formatSQLData, strSQLKey);

	objSQLData = formatSQLData;
	nFunRes = objSQLData.buildSQL(arg0.getParam(), arg1.getParam(), 
		arg2.getParam(), arg3.getParam(), arg4.getParam(), arg5.getParam());
	return nFunRes;
}
qint32 CProjectSQLManager::prepareSQLData( CSQLData& objSQLData, const CSQLParam& sqlKey, 
	const CSQLParam& arg0, const CSQLParam& arg1, const CSQLParam& arg2, 
	const CSQLParam& arg3, const CSQLParam& arg4, const CSQLParam& arg5,
	const CSQLParam& arg6)
{
	qint32 nFunRes = 0;
	CSQLData formatSQLData;
	QString strSQLKey = sqlKey.getParam();
	strSQLKey = strSQLKey.toUpper();

	nFunRes = _GetSQLData(formatSQLData, strSQLKey);

	objSQLData = formatSQLData;
	nFunRes = objSQLData.buildSQL(arg0.getParam(), arg1.getParam(), 
		arg2.getParam(), arg3.getParam(), arg4.getParam(), 
		arg5.getParam(), arg6.getParam());
	return nFunRes;
}
