#include "ServerComManager.h"

#include "BaseException.h"
#include "MyTradeClient.h"
#include "Log4cppLogger.h"


CServerComManager* CServerComManager::m_pInstance = 0;
QMutex CServerComManager::m_mutexInstance;

CServerComManager& CServerComManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CServerComManager();
	}
	return (*m_pInstance);
}

void CServerComManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;
}

CServerComManager::CServerComManager()
{
	m_pMyTradeClientRef = NULL;
}

CServerComManager::~CServerComManager()
{	
	m_pMyTradeClientRef = NULL;
}

void CServerComManager::setDataProcessHandle( const CMyTradeClient* pHandle )
{
	m_pMyTradeClientRef = (CMyTradeClient*)pHandle;
}

void CServerComManager::onInstrumentDownloaded( const CMyInstrument& instrument )
{
	if (NULL != m_pMyTradeClientRef)
	{
		m_pMyTradeClientRef->onInstrumentDownloaded(instrument);
	}
}

void CServerComManager::onMarketDataUpdate( const CMyMarketData &marketData )
{
	if (NULL != m_pMyTradeClientRef)
	{
		m_pMyTradeClientRef->onMarketDataUpdate(marketData);
	}
}

void CServerComManager::onHistoryDataDownloaded( QString requestID, pSetMyBarsPtr bars )
{
	if (NULL != m_pMyTradeClientRef)
	{
		m_pMyTradeClientRef->onHistoryDataDownloaded(requestID, bars);
	}
}

void CServerComManager::onBarDataUpdate( const CMyBarSummary &barData )
{
	if (NULL != m_pMyTradeClientRef)
	{
		m_pMyTradeClientRef->onBarDataUpdate(barData);
	}
}




