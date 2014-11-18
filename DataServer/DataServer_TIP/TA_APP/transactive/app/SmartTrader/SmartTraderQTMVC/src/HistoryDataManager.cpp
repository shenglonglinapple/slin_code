#include "HistoryDataManager.h"


#include "Log4cppLogger.h"



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

int CHistoryDataManager::getBarType()
{
	int nBarType;//FIVE_SECOND
	nBarType = m_pHistoryRequest->getBarType();
	return nBarType;
}

unsigned int CHistoryDataManager::getTimeFrom()
{
	unsigned int nTimeFrom;

	nTimeFrom = m_pHistoryACK->getTimeFrom();
	return nTimeFrom;
}

unsigned int CHistoryDataManager::getTimeTo()
{
	unsigned int nTimeTo;
	nTimeTo = m_pHistoryACK->getTimeTo();
	return nTimeTo;
}
