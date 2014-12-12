#include "HistoryDataManager.h"


#include "Log4cppLogger.h"



CHistoryQutoes::CHistoryQutoes()
{
	m_pHistoryRequest = NULL;
	m_pHistoryACK = NULL;

	m_pHistoryRequest = new CHistoryDataRequest();
	m_pHistoryACK = new CHistoryDataACK();
	
}

CHistoryQutoes::~CHistoryQutoes()
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

int CHistoryQutoes::getBarType()
{
	int nBarType;//FIVE_SECOND
	nBarType = m_pHistoryRequest->getBarType();
	return nBarType;
}

unsigned int CHistoryQutoes::getTimeFrom()
{
	unsigned int nTimeFrom;

	nTimeFrom = m_pHistoryACK->getTimeFrom();
	return nTimeFrom;
}

unsigned int CHistoryQutoes::getTimeTo()
{
	unsigned int nTimeTo;
	nTimeTo = m_pHistoryACK->getTimeTo();
	return nTimeTo;
}

void CHistoryQutoes::setInstrumentID( unsigned int nInstrumentID )
{
	if (NULL != m_pHistoryACK)
	{
		m_pHistoryACK->setInstrumentID(nInstrumentID);
	}
	m_nInstrumentID = nInstrumentID;
}

unsigned int CHistoryQutoes::getInstrumentID()
{
	return m_nInstrumentID;
}

void CHistoryQutoes::setHistoryDataRequest( const CHistoryDataRequest* pReq )
{
	*m_pHistoryRequest = *pReq;

	m_nRequestID = m_pHistoryRequest->m_nRequestID;
}
