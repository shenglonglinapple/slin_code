#include "DbDataOperImp.h"

#include "core/DataAccess/src/IQueryAdapter.h"
#include "core/DataAccess/src/ConnectionPoolManager.h"


#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)





CDbDataOperImp::CDbDataOperImp(CDbStatusItem* pDbStatusItem, IQueryAdapter* pQueryAdapter )
{
	m_pDbStatusItem = pDbStatusItem;
	m_pQueryAdapter = pQueryAdapter;
	m_MapColumnName.clear();
	m_nColumnNameCount = 0;
	m_lstDbDataRowBuffers.clear();

	if (NULL != m_pQueryAdapter)
	{
		LOG_INFO<<"TODO. check getLstColumnName can work ok!";
		m_nColumnNameCount = m_pQueryAdapter->getLstColumnName(m_MapColumnName);
	}
}

CDbDataOperImp::~CDbDataOperImp()
{
	if (NULL != m_pDbStatusItem && NULL != m_pQueryAdapter)
	{
		TA_Base_Core::CConnectionPoolManager::getInstance().cleanQuery(m_pDbStatusItem, m_pQueryAdapter);
	}
}


void CDbDataOperImp::fetchData( int nFetchNum /*= FETCH_MAX_ROWS*/ )
{

	try
	{
		m_lstDbDataRowBuffers.clear();

		if ( NULL == m_pQueryAdapter )
		{
			LOG_ERROR<<"Query is not got";
		}
		else
		{
			m_pQueryAdapter->fetchData( m_nColumnNameCount, m_lstDbDataRowBuffers, nFetchNum );
		}
	}
	catch(DataAccessException& db)
	{
		db.logInfo(LogFLInfo);
		throw db;
	}

}

std::string CDbDataOperImp::getStringData( const int rowIndex, const std::string& fieldName, const std::string defaultValue /*= ""*/ )
{
	std::string target = _GetStringData(rowIndex, fieldName);

	if ( target.empty() )
	{
		return defaultValue;
	}

	return target;
}

std::string CDbDataOperImp::_GetStringData( const int rowIndex, const std::string& fieldName)
{
	std::string strRetrunValue;
	MapColumNameIndexIterT iterMapFind;
	int nFieldNameIndex = -1;

	if (rowIndex > m_lstDbDataRowBuffers.size())
	{
		LOG_ERROR<<"rowIndex is greater than the number of rows";
		return strRetrunValue;
	}
	// Find the field name in the map
	iterMapFind = m_MapColumnName.find(fieldName);
	if (iterMapFind == m_MapColumnName.end())
	{
		//not find
		LOG_ERROR<<"The fieldName specified was not found"
			<<" "<<"fieldName="<<fieldName;
		nFieldNameIndex = -1;
		return strRetrunValue;
	}
	else
	{
		nFieldNameIndex = iterMapFind->second;
		LOG_DEBUG<<"The fieldName specified was found"
			<<" "<<"fieldName="<<fieldName
			<<" "<<"nFieldNameIndex="<<nFieldNameIndex;
	}
	
	
	strRetrunValue = m_lstDbDataRowBuffers[rowIndex][nFieldNameIndex];
	LOG_DEBUG<<"The fieldName specified was found"
		<<" "<<"fieldName="<<fieldName
		<<" "<<"nFieldNameIndex="<<nFieldNameIndex
		<<" "<<"strRetrunValue(excluding quotes)="<<strRetrunValue;

	return strRetrunValue;

}






NS_END(TA_Base_Core)



