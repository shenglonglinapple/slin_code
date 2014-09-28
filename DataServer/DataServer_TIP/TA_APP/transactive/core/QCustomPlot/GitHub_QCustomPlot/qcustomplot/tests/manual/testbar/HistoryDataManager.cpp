#include "HistoryDataManager.h"



CHistoryDataManager::CHistoryDataManager()
{
	m_pHistoryACK = NULL;

	m_pHistoryACK = new CHistoryDataACK();
	m_pHistoryACK->initTestData();
	
}

CHistoryDataManager::~CHistoryDataManager()
{


	if (NULL != m_pHistoryACK)
	{
		delete m_pHistoryACK;
		m_pHistoryACK = NULL;
	}
}

int CHistoryDataManager::getBarType()
{
	int nBarType = FIVE_SECOND;//
	nBarType = m_pHistoryACK->getBarType();
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
