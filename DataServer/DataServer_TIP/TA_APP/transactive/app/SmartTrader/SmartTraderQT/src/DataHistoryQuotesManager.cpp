#include "DataHistoryQuotesManager.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "HistoryDataRequest.h"
#include "DataHistoryQuotes.h"

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
	_FreeData_MapRequest();
	_FreeData_MapHistoryQuotes();
}

CDataHistoryQuotesManager::~CDataHistoryQuotesManager()
{
	_FreeData_MapRequest();
	_FreeData_MapHistoryQuotes();
}


void CDataHistoryQuotesManager::_FreeData_MapRequest()
{
	QMutexLocker lock(&m_mutex_MapRequest);	
	QMap<QString, CHistoryDataRequest*>::iterator iterMap;
	CHistoryDataRequest* pData = NULL;

	iterMap = m_MapRequest.begin();
	while (iterMap != m_MapRequest.end())
	{
		pData = iterMap.value();
		delete pData;
		pData = NULL;
		iterMap.value() = NULL;

		iterMap++;
	}
	m_MapRequest.clear();

}


void CDataHistoryQuotesManager::_FreeData_MapHistoryQuotes()
{	
	QMutexLocker lock(&m_mutex_MapHistoryQuotes);	
	QMap<unsigned int, CDataHistoryQuotes*>::iterator iterMap;
	CDataHistoryQuotes* pData = NULL;

	iterMap = m_MapHistoryQuotes.begin();
	while (iterMap != m_MapHistoryQuotes.end())
	{
		pData = iterMap.value();
		delete pData;
		pData = NULL;
		iterMap.value() = NULL;

		iterMap++;
	}
	m_MapHistoryQuotes.clear();

}

void CDataHistoryQuotesManager::addReqest( QString strReqID, const CHistoryDataRequest* pReqest )
{
	QMutexLocker lock(&m_mutex_MapRequest);	

	CHistoryDataRequest* pNewReq = NULL;
	pNewReq = new CHistoryDataRequest();
	*pNewReq = *pReqest;
	pNewReq->m_strRequestID = strReqID;

	m_MapRequest.insert(strReqID, pNewReq);
	pNewReq = NULL;

}

void CDataHistoryQuotesManager::onHistoryDataDownloaded( QString requestID, pSetMyBarsPtr bars )
{
	enum EMyBarType nBarType;
	unsigned int nTimeFrom;
	unsigned int nTimeTo;	
	std::string strInstrumentCode;
	int nInstruemntID;
	CDataHistoryQuotes* pDataHistoryQuotes = NULL;


	{
		QMutexLocker lock(&m_mutex_MapRequest);	
		QMap<QString, CHistoryDataRequest*>::iterator iterFind;
		CHistoryDataRequest* pReq = NULL;

		iterFind = m_MapRequest.find(requestID);
		if (iterFind == m_MapRequest.end())
		{
			return;
		}
		pReq = iterFind.value();
		nInstruemntID = pReq->m_nInstruemntID;
		strInstrumentCode = pReq->m_strInstrumentCode;
		nBarType = pReq->m_nBarType;
		nTimeFrom = pReq->m_nTimeFrom;
		nTimeTo = pReq->m_nTimeTo;
	}

	{
		QMutexLocker lock(&m_mutex_MapHistoryQuotes);	
		QMap<unsigned int, CDataHistoryQuotes*>::iterator iterMap;
		iterMap = m_MapHistoryQuotes.find(nInstruemntID);
		if (iterMap == m_MapHistoryQuotes.end())
		{
			//not find create new one
			pDataHistoryQuotes = NULL;
			pDataHistoryQuotes = new CDataHistoryQuotes();
			pDataHistoryQuotes->m_nInstrumentID = nInstruemntID;
			pDataHistoryQuotes->m_strInstrumentCode = strInstrumentCode;
			pDataHistoryQuotes->setBarType(nBarType);
			m_MapHistoryQuotes.insert(nInstruemntID, pDataHistoryQuotes);
		}
		else
		{
			pDataHistoryQuotes = iterMap.value();
			pDataHistoryQuotes->m_nInstrumentID = nInstruemntID;
			pDataHistoryQuotes->m_strInstrumentCode = strInstrumentCode;
			pDataHistoryQuotes->setBarType(nBarType);
		}

		pDataHistoryQuotes->onHistoryDataDownloaded(bars);
	}


}

void CDataHistoryQuotesManager::onBarDataUpdate(const CMyBarSummary &barData)
{
	int nInstruemntID;
	CDataHistoryQuotes* pDataHistoryQuotes = NULL;

	nInstruemntID = barData.instrumentID;


	{
		QMutexLocker lock(&m_mutex_MapHistoryQuotes);	
		QMap<unsigned int, CDataHistoryQuotes*>::iterator iterMap;
		iterMap = m_MapHistoryQuotes.find(nInstruemntID);
		if (iterMap == m_MapHistoryQuotes.end())
		{
			//not find 
			return;
		}
		else
		{
			pDataHistoryQuotes = iterMap.value();
			pDataHistoryQuotes->m_nInstrumentID = nInstruemntID;
			//pDataHistoryQuotes->setBarType(nBarType);
		}
		
		pDataHistoryQuotes->onBarDataUpdate(barData);
	}
}

void CDataHistoryQuotesManager::_RemoveReq(QString strReqID)
{
	QMutexLocker lock(&m_mutex_MapRequest);	
	QMap<QString, CHistoryDataRequest*>::iterator iterFind;
	CHistoryDataRequest* pReq = NULL;

	iterFind = m_MapRequest.find(strReqID);
	if (iterFind != m_MapRequest.end())
	{
		pReq = iterFind.value();
		delete pReq;
		pReq = NULL;
		iterFind.value() = NULL;
		m_MapRequest.erase(iterFind);
	}
}
