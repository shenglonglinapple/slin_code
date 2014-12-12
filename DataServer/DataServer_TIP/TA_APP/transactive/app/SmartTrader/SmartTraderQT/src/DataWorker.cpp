#include "DataWorker.h"
#include "ReqData.h"
#include "MyInstrument.h"
#include "StockData.h"
#include "MyTradeClient.h"
#include "HistoryData.h"

#include "StaticStockManager.h"
#include "RealTimeStockManager.h"
#include "HistoryStockManager.h"


//////////////////////////////////////////////////////////////////////////
CDataWorker::CDataWorker(void)
{	
	m_toTerminate = false;
	m_nReqWorkerState = ReqWokerState_Begin;
	m_nDataWorkerState = DataWorkerState_Begin;

	m_pMyTradeClientRef = NULL;

	{
		QMutexLocker lock(&m_mutex_LstReqData);
		m_LstReqData.clear();
	}
	{
		QMutexLocker lock(&m_mutex_CurrentReqData);
		m_pCurrentReqData = NULL;
	}
}

CDataWorker::~CDataWorker(void)
{
	m_pMyTradeClientRef = NULL;
	_Free_LstReqData();
}


void CDataWorker::run()
{
	m_nReqWorkerState = ReqWokerState_Begin;
	m_nDataWorkerState = DataWorkerState_Begin;

	while (false == m_toTerminate)
	{
		_ThreadJob();
		this->my_msleep(100);
	}

	_ProcessUserTerminate();
}

void CDataWorker::terminate()
{
	m_toTerminate = true;
}


int CDataWorker::_ProcessUserTerminate()
{
	int nFunRes = 0;
	m_toTerminate = true;
	m_nReqWorkerState = ReqWokerState_End;
	m_nDataWorkerState = DataWorkerState_End;
	return nFunRes;
}

bool CDataWorker::isFinishWork()
{
	bool bFinishWork = false;
	if (ReqWokerState_End == m_nReqWorkerState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CDataWorker::_ThreadJob()
{
	switch (m_nReqWorkerState)
	{
	case ReqWokerState_Begin:
		m_nReqWorkerState = ReqWokerState_CheckProcessReq;
		break;
	case ReqWokerState_CheckProcessReq:
		_DoJob_CheckProcessReq();
		break;
	case ReqWokerState_End:
		this->my_msleep(100);
		break;
	default:
		this->my_msleep(100);
		break;
	}//switch (m_nReqWorkerState)


	switch (m_nDataWorkerState)
	{
	case DataWorkerState_Begin:
		m_nDataWorkerState = DataWorkerState_UpdateStockRealTimeInfo;
		break;
	case DataWorkerState_UpdateStockRealTimeInfo:
		_DoJob_UpdateStockRealTimeInfo();
		break;
	case DataWorkerState_End:
		this->my_msleep(100);
		break;
	default:
		this->my_msleep(100);
		break;
	}//switch (m_nDataWorkerState)

}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CDataWorker::setDataProcessHandle( CMyTradeClient* pHandle )
{
	m_pMyTradeClientRef = pHandle;
}

void CDataWorker::append_req( CReqData* pReqData )
{
	QMutexLocker lock(&m_mutex_LstReqData);	
	m_LstReqData.append(pReqData);
}

void CDataWorker::_Free_LstReqData()
{
	{
		QMutexLocker lock(&m_mutex_CurrentReqData);
		if (NULL != m_pCurrentReqData)
		{
			delete m_pCurrentReqData;
			m_pCurrentReqData = NULL;
		}
	}


	{
		QMutexLocker lock(&m_mutex_LstReqData);
		QList<CReqData*>::iterator  iterLst;
		iterLst = m_LstReqData.begin();
		while (iterLst != m_LstReqData.end())
		{
			delete (*iterLst);
			*iterLst = NULL;

			iterLst++;
		}//while
	}

}
CReqData* CDataWorker::_TryGet_ReqData()
{
	CReqData* pReqDataTmp = NULL;
	QMutexLocker lock(&m_mutex_LstReqData);
	QList<CReqData*>::iterator  iterLst;

	pReqDataTmp = NULL;
	iterLst = m_LstReqData.begin();
	if (iterLst != m_LstReqData.end())
	{
		pReqDataTmp = *iterLst;
		m_LstReqData.erase(iterLst);
	}//while

	return pReqDataTmp;
}




void CDataWorker::_DoJob_CheckProcessReq()
{
	EReqType nReqType = EReqType_Begin;

	{
		QMutexLocker lock(&m_mutex_CurrentReqData);
		if (NULL != m_pCurrentReqData)
		{
			delete m_pCurrentReqData;
			m_pCurrentReqData = NULL;
		}

		m_pCurrentReqData = NULL;
		m_pCurrentReqData = _TryGet_ReqData();
	}

	if (NULL == m_pCurrentReqData)
	{
		return;
	}

	nReqType = m_pCurrentReqData->getReqType();

	switch (nReqType)
	{
	case EReqType_DownLoadStockID:
		_ProcessReq_DownLoadStockID();
		break;
	case EReqType_SubscribeMarketData:
		_ProcessReq_SubscribeMarketData();
		break;
	case EReqType_UnSubscribeMarketData:
		_ProcessReq_UnSubscribeMarketData();
		break;
	case EReqType_DownloadHistoryData:
		_ProcessReq_DownloadHistoryData();
		break;		
	default:
		break;
	}

	m_nReqWorkerState = ReqWokerState_CheckProcessReq;
	return;
}

void CDataWorker::_DoJob_UpdateStockRealTimeInfo()
{
	std::list<CMyMarketData*> lstMyMarketData;
	std::list<CMyMarketData*>::iterator iterLst;
	CMyMarketData* pMyMarketData = NULL;

	CRealTimeStockManager::getInstance().getRealTimeMarketData(lstMyMarketData);

	iterLst = lstMyMarketData.begin();
	while (iterLst != lstMyMarketData.end())
	{
		pMyMarketData = (*iterLst);

		if (NULL != m_pMyTradeClientRef)
		{
			m_pMyTradeClientRef->onMarketDataUpdate(*pMyMarketData);
		}
		delete pMyMarketData;
		pMyMarketData = NULL;
		(*iterLst) = NULL;
		iterLst++;
	}//while
	lstMyMarketData.clear();

	m_nDataWorkerState = DataWorkerState_UpdateStockRealTimeInfo;
}

void CDataWorker::_ProcessReq_DownLoadStockID()
{
	QMutexLocker lock(&m_mutex_CurrentReqData);

	std::list<CStockData*>::iterator iterLst;
	CStockData* pStockData = NULL;
	CMyInstrument myInstrument;

	std::list<CStockData*> LstStockData;
	CStaticStockManager::getInstance().doWork_getStockData(LstStockData);
	if (LstStockData.size() > 0)
	{
		iterLst = LstStockData.begin();
		while (iterLst != LstStockData.end())
		{				
			pStockData = (*iterLst);
			if (NULL != pStockData)
			{
				myInstrument.setValue(pStockData);
				if (NULL != m_pMyTradeClientRef)
				{
					m_pMyTradeClientRef->onInstrumentDownloaded(myInstrument);
				}
				delete pStockData;
				pStockData = NULL;
			}

			pStockData = NULL;

			*iterLst = NULL;

			iterLst++;
		}//iterLst

	}
	LstStockData.clear();

	//who do job who delete
	if (NULL != m_pCurrentReqData)
	{
		delete m_pCurrentReqData;
		m_pCurrentReqData = NULL;
	}

}

void CDataWorker::_ProcessReq_SubscribeMarketData()
{
	QMutexLocker lock(&m_mutex_CurrentReqData);

	CRealTimeStockManager::getInstance().addRealTimeReq(m_pCurrentReqData->getInstrumentCode());

	//who do job who delete
	if (NULL != m_pCurrentReqData)
	{
		delete m_pCurrentReqData;
		m_pCurrentReqData = NULL;
	}
}

void CDataWorker::_ProcessReq_UnSubscribeMarketData()
{
	QMutexLocker lock(&m_mutex_CurrentReqData);

	CRealTimeStockManager::getInstance().removeRealTimeReq(m_pCurrentReqData->getInstrumentCode());

	//who do job who delete
	if (NULL != m_pCurrentReqData)
	{
		delete m_pCurrentReqData;
		m_pCurrentReqData = NULL;
	}
}

void CDataWorker::_ProcessReq_DownloadHistoryData()
{
	QMutexLocker lock(&m_mutex_CurrentReqData);
	CHistoryStockManager::LstHistoryDataT lstHistoryData;
	CHistoryStockManager::LstHistoryDataIterT iterLst;
	CHistoryData* pHistoryData = NULL;

	CHistoryStockManager::getInstance().downloadHistoryData(
		m_pCurrentReqData->getInstrumentCode(),
		m_pCurrentReqData->getTimeFrom(),
		m_pCurrentReqData->getTimeTo(),
		lstHistoryData);

	CMyBarsPtrHelper myBarsPtrhelper;
	CMyBarsPtr pMyBars = myBarsPtrhelper.convertValue(lstHistoryData);


	if (NULL != m_pMyTradeClientRef)
	{
		m_pMyTradeClientRef->onHistoryDataDownloaded(m_pCurrentReqData->getRequestID(), pMyBars);
	}

	iterLst = lstHistoryData.begin();
	while (iterLst != lstHistoryData.end())
	{
		pHistoryData = (*iterLst);

		delete pHistoryData;
		pHistoryData = NULL;

		iterLst++;
	}//while

	lstHistoryData.clear();



	//who do job who delete
	if (NULL != m_pCurrentReqData)
	{
		delete m_pCurrentReqData;
		m_pCurrentReqData = NULL;
	}
}

