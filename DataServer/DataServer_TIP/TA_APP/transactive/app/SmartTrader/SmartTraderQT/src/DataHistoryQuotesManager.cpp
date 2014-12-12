#include "DataHistoryQuotesManager.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "HistoryDataRequest.h"

CDataHistoryQuotesManager* CDataHistoryQuotesManager::m_pInstance = 0;
QMutex CDataHistoryQuotesManager::m_mutexInstance;

CDataHistoryQuotesManager& CDataHistoryQuotesManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataHistoryQuotesManager();
	}
	return (*m_pInstance);
}

void CDataHistoryQuotesManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataHistoryQuotesManager::CDataHistoryQuotesManager()
{


}

CDataHistoryQuotesManager::~CDataHistoryQuotesManager()
{

}

void CDataHistoryQuotesManager::addReqest( unsigned int nReqID, const CHistoryDataRequest* pReqest )
{
	QMutexLocker lock(&m_mutex_MapRequest);	

	CHistoryDataRequest* pNewReq = NULL;
	pNewReq = new CHistoryDataRequest();
	*pNewReq = *pReqest;
	pNewReq->m_nRequestID = nReqID;

	m_MapRequest.insert(nReqID, pNewReq);
	pNewReq = NULL;

}

void CDataHistoryQuotesManager::onHistoryDataDownloaded( unsigned int requestID, CMyBarsPtr bars )
{
	CHistoryDataRequest* pReq = NULL;
	pReq = _TryGetReq(requestID);
	if (NULL == pReq)
	{
		return;
	}

}

CHistoryDataRequest* CDataHistoryQuotesManager::_TryGetReq( unsigned int requestID )
{
	QMutexLocker lock(&m_mutex_MapRequest);	
	QMap<unsigned int, CHistoryDataRequest*>::iterator iterFind;
	CHistoryDataRequest* pReq = NULL;

	iterFind = m_MapRequest.find(requestID);
	if (iterFind != m_MapRequest.end())
	{
		pReq = iterFind.value();
	}

	return pReq;
}

void CDataHistoryQuotesManager::_RemoveReq( unsigned int requestID )
{
	QMutexLocker lock(&m_mutex_MapRequest);	
	QMap<unsigned int, CHistoryDataRequest*>::iterator iterFind;
	CHistoryDataRequest* pReq = NULL;

	iterFind = m_MapRequest.find(requestID);
	if (iterFind != m_MapRequest.end())
	{
		pReq = iterFind.value();
		delete pReq;
		pReq = NULL;
		iterFind.value() = NULL;
		m_MapRequest.erase(iterFind);
	}


	
}
