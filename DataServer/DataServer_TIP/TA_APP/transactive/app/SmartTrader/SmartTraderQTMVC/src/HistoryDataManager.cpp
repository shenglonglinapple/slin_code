#include "HistoryDataManager.h"


#include "BoostLogger.h"
USING_BOOST_LOG;


CHistoryDataManager::CHistoryDataManager()
{
	m_pHistoryRequest = NULL;
	m_pHistoryACK = NULL;

	m_pHistoryRequest = new CHistoryDataRequest();
	m_pHistoryACK = new CHistoryDataACK();
	
}

CHistoryDataManager::~CHistoryDataManager()
{

	if (NULL != m_pHistoryRequest)
	{
		delete m_pHistoryRequest;
		m_pHistoryRequest = NULL;
	}

	if (NULL != m_pHistoryACK)
	{
		delete m_pHistoryACK;
		m_pHistoryACK = NULL;
	}
}
