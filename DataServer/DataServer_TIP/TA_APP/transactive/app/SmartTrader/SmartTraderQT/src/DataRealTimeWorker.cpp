#include "DataRealTimeWorker.h"


#include "RealTimeStockManager.h"
#include "ServerComManager.h"

//////////////////////////////////////////////////////////////////////////
CDataRealTimeWorker::CDataRealTimeWorker(void)
{	
	m_toTerminate = false;
	m_WorkerState = WORK_STATE_BEGIN;
	m_nDataWorkerState = DataWorkerState_Begin;

}

CDataRealTimeWorker::~CDataRealTimeWorker(void)
{
}


void CDataRealTimeWorker::run()
{
	m_WorkerState = WORK_STATE_BEGIN;
	m_nDataWorkerState = DataWorkerState_Begin;
	
	m_WorkerState = WORK_STATE_WORKING;
	while (false == m_toTerminate)
	{
		_ThreadJob();
		this->my_msleep(5000);

	}

	_ProcessUserTerminate();
	m_WorkerState = WORK_STATE_END;

}

void CDataRealTimeWorker::terminate()
{
	m_toTerminate = true;

	while (WORK_STATE_END != m_WorkerState)
	{
		this->msleep(10);
	}
}


int CDataRealTimeWorker::_ProcessUserTerminate()
{
	int nFunRes = 0;
	m_toTerminate = true;
	m_nDataWorkerState = DataWorkerState_End;
	return nFunRes;
}

bool CDataRealTimeWorker::isFinishWork()
{
	bool bFinishWork = false;
	if (DataWorkerState_End == m_nDataWorkerState)
	{
		bFinishWork = true;
	}
	return bFinishWork;

}

void CDataRealTimeWorker::_ThreadJob()
{
	switch (m_nDataWorkerState)
	{
	case DataWorkerState_Begin:
		m_nDataWorkerState = DataWorkerState_UpdateStockRealTimeInfo;
		break;
	case DataWorkerState_UpdateStockRealTimeInfo:
		//_DoJob_UpdateStockRealTimeInfo();
		_DoJob_UpdateStockRealTimeInfo_UseHistoryData();
		break;
	case DataWorkerState_End:
		this->my_msleep(100);
		break;
	default:
		this->my_msleep(100);
		break;
	}//switch (m_nDataWorkerState)
	CRealTimeStockManager::getInstance().historyAddOneDay();

}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void CDataRealTimeWorker::_DoJob_UpdateStockRealTimeInfo()
{
	std::list<CMyMarketData*> lstMyMarketData;
	std::list<CMyMarketData*>::iterator iterLst;
	CMyMarketData* pMyMarketData = NULL;

	CRealTimeStockManager::getInstance().getRealTime_MarketDataList(lstMyMarketData);

	iterLst = lstMyMarketData.begin();
	while (iterLst != lstMyMarketData.end())
	{
		pMyMarketData = (*iterLst);

		CServerComManager::getInstance().onMarketDataUpdate(*pMyMarketData);

		delete pMyMarketData;
		pMyMarketData = NULL;
		(*iterLst) = NULL;
		iterLst++;
	}//while
	lstMyMarketData.clear();

	m_nDataWorkerState = DataWorkerState_UpdateStockRealTimeInfo;
}



void CDataRealTimeWorker::_DoJob_UpdateStockRealTimeInfo_UseHistoryData()
{
	std::list<CMyMarketData*> lstMyMarketData;
	std::list<CMyMarketData*>::iterator iterLst;
	CMyMarketData* pMyMarketData = NULL;

	CRealTimeStockManager::getInstance().getHistory_MarketDataList(lstMyMarketData);

	iterLst = lstMyMarketData.begin();
	while (iterLst != lstMyMarketData.end())
	{
		pMyMarketData = (*iterLst);

		CServerComManager::getInstance().onMarketDataUpdate(*pMyMarketData);

		delete pMyMarketData;
		pMyMarketData = NULL;
		(*iterLst) = NULL;
		iterLst++;
	}//while
	lstMyMarketData.clear();


	m_nDataWorkerState = DataWorkerState_UpdateStockRealTimeInfo;
}
