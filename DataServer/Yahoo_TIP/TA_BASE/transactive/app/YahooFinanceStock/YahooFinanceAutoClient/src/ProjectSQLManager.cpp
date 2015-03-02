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


