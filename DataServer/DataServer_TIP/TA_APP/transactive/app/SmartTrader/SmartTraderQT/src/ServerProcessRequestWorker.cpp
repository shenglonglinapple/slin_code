#include "ServerProcessRequestWorker.h"
#include "ReqData.h"
#include "MyInstrument.h"
#include "StockData.h"
#include "MyTradeClient.h"
#include "HistoryData.h"

#include "StaticStockManager.h"
#include "RealTimeStockManager.h"
#include "HistoryStockManager.h"
#include "DataRealTimeWorker.h"
#include "DataOrderManager.h"
#include "ServerComManager.h"

#include "OrderData.h"

//////////////////////////////////////////////////////////////////////////
CServerProcessRequestWorker::CServerProcessRequestWorker(void)
{	
	m_toTerminate = false;
	m_WorkerState = WORK_STATE_BEGIN;
	m_nReqWorkerState = ReqWokerState_Begin;


	{
		QMutexLocker lock(&m_mutex_LstReqData);
		m_LstReqData.clear();
	}
	{
		QMutexLocker lock(&m_mutex_CurrentReqData);
		m_pCurrentReqData = NULL;
	}
	CRealTimeStockManager::getInstance();
	CHistoryStockManager::getInstance();
	CDataOrderManager::getInstance();
}

CServerProcessRequestWorker::~CServerProcessRequestWorker(void)
{
	_Free_LstReqData();
	CRealTimeStockManager::removeInstance();
	CDataOrderManager::removeInstance();
	CHistoryStockManager::removeInstance();
}


void CServerProcessRequestWorker::run()
{
	m_WorkerState = WORK_STATE_BEGIN;
	m_nReqWorkerState = ReqWokerState_Begin;

	m_WorkerState = WORK_STATE_WORKING;
	while (false == m_toTerminate)
	{
		_ThreadJob();
		this->my_msleep(100);
	}

	_ProcessUserTerminate();
	m_WorkerState = WORK_STATE_END;
}

void CServerProcessRequestWorker::terminate()
{
	m_toTerminate = true;
	while (WORK_STATE_END != m_WorkerState)
	{
		this->msleep(10);
	}
}


int CServerProcessRequestWorker::_ProcessUserTerminate()
{
	int nFunRes = 0;
	m_nReqWorkerState = ReqWokerState_End;
	return nFunRes;
}

bool CServerProcessRequestWorker::isFinishWork()
{
	bool bFinishWork = false;
	if (ReqWokerState_End == m_nReqWorkerState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CServerProcessRequestWorker::_ThreadJob()
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


}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void CServerProcessRequestWorker::append_req( CReqData* pReqData )
{
	QMutexLocker lock(&m_mutex_LstReqData);	
	m_LstReqData.append(pReqData);
}

void CServerProcessRequestWorker::_Free_LstReqData()
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
CReqData* CServerProcessRequestWorker::_TryGet_ReqData()
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




void CServerProcessRequestWorker::_DoJob_CheckProcessReq()
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
	case EReqType_BUYMARKET:
		_ProcessReq_BuyMarket();
		break;
	case EReqType_SELLMARKET:
		_ProcessReq_SellMarket();
		break;
	default:
		break;
	}

	m_nReqWorkerState = ReqWokerState_CheckProcessReq;
	return;
}

void CServerProcessRequestWorker::_ProcessReq_DownLoadStockID()
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
				CServerComManager::getInstance().onInstrumentDownloaded(myInstrument);

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

void CServerProcessRequestWorker::_ProcessReq_SubscribeMarketData()
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

void CServerProcessRequestWorker::_ProcessReq_UnSubscribeMarketData()
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

void CServerProcessRequestWorker::_ProcessReq_DownloadHistoryData()
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
	pSetMyBarsPtr pMyBars = myBarsPtrhelper.convertValue(lstHistoryData);

	CServerComManager::getInstance().onHistoryDataDownloaded(m_pCurrentReqData->getRequestUUID(), pMyBars);

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

void CServerProcessRequestWorker::_ProcessReq_BuyMarket()
{
	QMutexLocker lock(&m_mutex_CurrentReqData);
	COrderData* pOrderData = NULL;

	pOrderData = new COrderData();

	pOrderData->m_strUUID = m_pCurrentReqData->getRequestUUID();
	pOrderData->m_strInstrumentCode = m_pCurrentReqData->getInstrumentCode().c_str();
	pOrderData->m_nInstrumentID = pOrderData->m_strInstrumentCode.mid(0, pOrderData->m_strInstrumentCode.indexOf(".")).toUInt();
	pOrderData->m_nSide = COrderData::BUY;
	pOrderData->m_nOrderType = COrderData::MARKET;
	pOrderData->m_nVolume = m_pCurrentReqData->getVolume();

	CDataOrderManager::getInstance().addOrder(pOrderData);
	
	//who do job who delete
	if (NULL != m_pCurrentReqData)
	{
		delete m_pCurrentReqData;
		m_pCurrentReqData = NULL;
	}
	if (NULL != pOrderData)
	{
		delete pOrderData;
		pOrderData = NULL;
	}
}

void CServerProcessRequestWorker::_ProcessReq_SellMarket()
{
	QMutexLocker lock(&m_mutex_CurrentReqData);
	COrderData* pOrderData = NULL;

	pOrderData = new COrderData();

	pOrderData->m_strUUID = m_pCurrentReqData->getRequestUUID();
	pOrderData->m_strInstrumentCode = m_pCurrentReqData->getInstrumentCode().c_str();
	pOrderData->m_nInstrumentID = pOrderData->m_strInstrumentCode.mid(0, pOrderData->m_strInstrumentCode.indexOf(".")).toUInt();
	pOrderData->m_nSide = COrderData::SELL;
	pOrderData->m_nOrderType = COrderData::MARKET;
	pOrderData->m_nVolume = m_pCurrentReqData->getVolume();

	CDataOrderManager::getInstance().addOrder(pOrderData);

	//who do job who delete
	if (NULL != m_pCurrentReqData)
	{
		delete m_pCurrentReqData;
		m_pCurrentReqData = NULL;
	}
	if (NULL != pOrderData)
	{
		delete pOrderData;
		pOrderData = NULL;
	}
}

